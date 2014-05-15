#!/usr/bin/python

""" 
PPSS (Python based P2P Streaming Simulator)
my first python problem: a event-driven p2p streaming simulator
author: jiqing
update: 2010-8-27
version: 0.9.2 [not only streaming but also file sharing]

===============================================================
 Copyright (C) 2009  jiqing (jiqingwu@gmail.com)
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 
===============================================================
""" 
"""
TODO:
    Why does the performance decrease as time passes?
"""

import random
import time

""" There are some constants below,
you can change it to setup your simulation."""

""" You can set which kind of application
you are simulating here """
FILE_SHARING = 1
STREAMING = 2
APP = 1

""" You can set SAMPLE_ID to -1,
to forbid the output of debug information.
If you set DETAIL to 1, the information of packet level will output"""
SAMPLE_ID = -1
DETAIL = 0

""" All available scheduling algorithms. """
RANDOM_PULL = 1
RF_PULL = 2

""" special for the experiments of F2F algorithm. """
F2F_OPTIMAL = 4
F2F_PULL = 5

""" scheduling alg for our internet model """
ENDURE_PULL = 6

""" Specify your scheduling algorithm here,
now only RANDOM_PULL, F2F_PULL, PUSH_PULL are available.  """
SCHEDULE = 4

""" set SRV_SIDE_SCHEDULE to 1 enable serving peer side schedule """
SRV_SIDE_SCHEDULE = 1

""" For push-pull scheduling, set the count of substreams here. """
SUBSTREAM = 4

""" All available overlay construction algorithms """
RANDOM_OVERLAY = 1
DELAY_OVERLAY = 2
""" add your own overlay construction algorithm here. """

""" Specify your overlay construction algorithm here """
OVERLAY = RANDOM_OVERLAY

""" Set the duration (mseconds) of your simulation here. """
SIM_DURATION = 600000
""" For file sharing application, set the number of chunks."""
SIM_CHUNKS = 500

""" Set the number of peers in your simulation,
the source peer is not included. """
NODE_CNT = 200

""" Set the duration (mseconds) that all new peers join the system. """
JOIN_DURATION = 10000

""" To simulate flash crowds, set FLASH to 1. """
FLASH = 0

""" Set the scale of flash crowd here. """
FLASH_CNT = 50

""" Set when the flash crowd happends. """
FLASH_TIME = SIM_DURATION/2

""" Set the duration (mseconds) of your flash crowd. """
FLASH_DURATION = 5000

""" How long a chunk plays back? """
FORWARD_INTERVAL = 500
""" How long between two Adding neighbors """
FIND_NBR_INTERVAL = 200
""" How many neighbors a peer has """
NBR_CNT = 8
""" The cycle of exchanging buffermaps """
NOTIFY_INTERVAL = 2000
""" The cycle of requesting chunks """
REQ_INTERVAL = 1000
""" The cycle of statistics """
STAT_INTERVAL = 5000
# """ The cycle of evaluating QoS of serving peers """
# EVAL_INTERVAL = 3000

""" How many packets the buffer can hold. """
BUF_CAP = 30
""" When a peer reaches the BUF_RATIO, it can start playback. """
BUF_RATIO = 0.4

""" In average, How long to send a data chunk """
SEND_INTERVAL = 100
SEND_QUEUE_LEN = 15
""" Set the max delay of sending a packet,
When you use delay matrix, this may be useless. """
MAX_DELAY = 300

""" !!! YOU NEED NOT MODIFY THE FOLLOWING CONSTANTS !!! """

""" THERE are some events in your simulation,
such as joining and leaving of a peer,
receiving some packet of a peer."""
EVENT_PEER_JOIN = 0
EVENT_PEER_LEAVE = 1
EVENT_RECEIVE = 2
EVENT_FORWARD = 3
EVENT_SEND = 5
""" For my F2F algorithm """
EVENT_UPLOAD = 6
""" The event that a peer look for its neighbors."""
EVENT_FIND_NBR = 7
""" The event that a peer broadcast its data avalability to
its neighbors. """
EVENT_NOTIFY = 8
""" The event that a peer request data from its neighbors """
EVENT_SCHEDULE = 9
""" The event that you gather statistics. """
EVENT_STAT = 10
""" The event that a peer evaluate the qos of its neighbors. """
EVENT_EVAL = 11

""" All packet types are list here. """
PACKET_LEAVE = 100
PACKET_ADD_NBR = 101
""" When its request for adding neighbor is accepted,
it will receive a PACKET_ACK. """
PACKET_ACK = 102
PACKET_DATA = 103
PACKET_REQ = 104
""" A peer inform its neighbors which packets it holds
by sending PACKET_NOTIFY. """
PACKET_NOTIFY = 105
""" packet for subscribing substream and unscribing """
PACKET_SUB = 106
PACKET_UNSUB = 107

#LOW_RATE_LIMIT = 1000 / FORWARD_INTERVAL
#MATRIX_FILE = 'data/MeridianMatrix-UT'
#PACKET_SIZE = 1250  #byte

############################################################

class FileChunk(object):
    """ structure of file chunk in cache """
    def __init__(self, state, rareness):
        self.m_state = state    # 0: miss; 1: downloading; 2: have
        self.m_rareness = rareness

class BufferElement(object):
    """ structure of packet in buffer """
    def __init__(self, state, seq, rareness):
        self.m_state = state
        self.m_seq = seq
        self.m_rareness = rareness

# class SendQueueItem(object):
#     """ structure of item in send queue """
#     def __init__(self, peer, seq):
#         self.m_dest_peer = peer
#         self.m_seq = seq

class Peer(object):
    """ peer in overlay: include server and normal peer """
    new_seq = 0

# INITIALIZE PEER

    def __init__ (self, peer_id,topology, event_engine):
        """ peer class constructor """
        self.m_topology = topology	# for accessing other peers
        self.m_engine = event_engine	# for scheduling event
        self.m_peer_id = peer_id	# for peer ID

        self.m_start_seq = 0	# for stating load, initial pointer
        self.m_seq_num = 0		# for play pointer
        self.m_played = 0		# for stating quality
        self.m_should_played = 0	# for stating quality
        self.m_sent = 0			# for bandwidth utility
        self.m_rejected = 0		# for rejected ratio
        self.m_total_reqs = 0		# for rejected ratio
        self.m_avail_bw = 0		# for bw aware schedule


        self.m_buffer = []		# for streaming buffer
        for i in range(BUF_CAP):
            e = BufferElement(0, -1, 0)
            self.m_buffer.append(e)
        self.m_buffering = True		# for buffering state
        self.m_buffer_time = 0		# for time of buffering
        self.m_recved = 0		# for buffering finish
        self.m_good_rate_cycles = 0	# for buffering finish?

        self.m_file_cache = []		# for file cache
        for i in range(SIM_CHUNKS):
            c = FileChunk(0, 0)
            self.m_file_cache.append(c)

        self.m_nbrs = []		# for neighbors
        self.m_finding_nbrs = False	# for finding nbr state
        self.m_cycle_recved = 0		# for switching nbr?
        self.m_low_qos_cycles = 0	# for switching nbr?

        self.last_nbr_send = 0		# for cycle sending

        self.m_join_time = 0		# for online duration
        self.m_leave_time = 0		# for online duration
        self.m_online = False		# for online state, neccessary?

    def set_life_time(self, join_time, leave_time):
        """ for peer churn """
        self.m_join_time = join_time
        self.m_leave_time = leave_time

    def set_bandwidth(self, out_bw, in_bw):
        """ To set according to the real model,
        the outbound bandwidth decides the sending interval. """
        self.m_outbound_bw = out_bw
        self.m_inbound_bw = in_bw

    def bw_utility(self):
        should_sent = float(self.m_engine.m_current_time -\
                                self.m_join_time) / SEND_INTERVAL
        return self.m_sent / should_sent

    def find_nbrs(self):
        """ normal peers find their neighbours,
        you can describe your algorithm of overlay
        construction here."""

        """ if all other online peers are all nbrs of this peer,
        return """
        if len(self.m_nbrs) >= NBR_CNT:
            self.m_finding_nbrs = False
            return

        if self.m_finding_nbrs == True:
            self.m_engine.schedule_event(FIND_NBR_INTERVAL,\
                    EVENT_FIND_NBR, self)

        if len(self.m_nbrs) == len(self.m_topology.online_peers) - 1:
            return

        """ find a object peer """
        if OVERLAY == RANDOM_OVERLAY:
            object_index = self.find_nbr_random()
        elif OVERLAY == DELAY_OVERLAY:
            object_index = self.find_nbr_delay()

        """ send a packet of adding neighbor to the peer """
        if object_index >= 0:
            p = self.m_topology.online_peers[object_index]
            packet = Packet(self,p,PACKET_ADD_NBR)
            self.send_pkt(packet)

    def find_nbr_random(self):
        """find a neighbor candidate randomly"""
        while True:
            index = random.randrange( \
                    len(self.m_topology.online_peers) )
            p = self.m_topology.online_peers[index]
            if self != p and self.nbr_index(p) == -1:
                return index

    def find_nbr_delay(self):
        """ find a neighbor candidate with a little RTT """
        return -1

    def add_nbr(self, p):
        """ when receive an ACK or a ADD_NBR packet """
        nbr = Neighbour(p)
        self.m_nbrs.append(nbr)
        if len(self.m_nbrs) == NBR_CNT:
            self.m_finding_nbrs = False
        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            self.print_nbrs()

    def del_nbr(self, n):
        """ when receive a LEAVE packet """
        self.m_nbrs.remove(n)
        self.m_finding_nbrs = True
        self.find_nbrs()
        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            print "%d: %d remove neighbor %d."%\
                    (self.m_engine.m_current_time,\
                    SAMPLE_ID, packet.m_src_peer.m_peer_id)
            self.print_nbrs()

    def print_nbrs(self):
        print "nbr list: ",
        nbrs = []
        for n in self.m_nbrs:
            nbrs.append(n.m_peer.m_peer_id)
        print nbrs

    def maintain_nbrs(self):
        if self.m_finding_nbrs == True or \
                self.m_peer_id == 0: return
        # if aggregate rate is less than the playback rate
        if self.m_cycle_recved < REQ_INTERVAL / FORWARD_INTERVAL/2:
            self.m_low_qos_cycles += 1
        else:
            self.m_low_qos_cycles = 0
        self.m_cycle_recved = 0
        if self.m_low_qos_cycles >= 3:
            bad_nbr = self.m_nbrs[0]
            recv_cnt = self.m_nbrs[0].cycle_recved
            for n in self.m_nbrs:
                if n.cycle_recved < recv_cnt:
                    recv_cnt = n.cycle_recved
                    bad_nbr = n
            self.del_nbr(bad_nbr)

    def schedule(self):
        """ scheduling periodically, decide requesting which
        packets from which nbrs, or pushing wich packets to
        which nbrs. """
        self.m_engine.schedule_event(REQ_INTERVAL,\
                EVENT_SCHEDULE, self)

        if len(self.m_nbrs) == 0: return
        # self.m_avail_bw = REQ_INTERVAL / SEND_INTERVAL
        self.maintain_nbrs()

        if APP == STREAMING and self.m_buffering == True:
            chunk_num = 0
            obj_nbr = None
            for nbr in self.m_nbrs:
                if nbr.m_peer.avail_items_absolute() > chunk_num:
                    chunk_num = nbr.m_peer.avail_items_absolute()
                    obj_nbr = nbr
            if obj_nbr:
                self.m_seq_num = obj_nbr.m_peer.min_seq()

        if SCHEDULE == RANDOM_PULL:
            self.random_pull()
        elif SCHEDULE == RF_PULL:
            self.rf_pull()
        elif SCHEDULE == F2F_OPTIMAL: 
            if APP == FILE_SHARING:
                self.f2f_fs_optimal()
            else: self.f2f_stream_optimal()
        elif SCHEDULE == F2F_PULL:
            if APP == FILE_SHARING:
                self.f2f_fs_pull()
            else: self.f2f_stream_pull()
        elif SCHEDULE == ENDURE_PULL:
            if APP == STREAMING:
                self.endurable_pull()

    def random_pull(self):
        """ select packet in order, select peer randomly """
        if self.m_peer_id == 0: return

        cycle_reqed = 0
        if APP == FILE_SHARING:
            for seq in range(SIM_CHUNKS):
                if self.want(seq):
                    self.m_total_reqs += 1
                    holders = []
                    for nbr in self.m_nbrs:
                        if nbr.m_peer.have(seq):
                            holders.append(nbr)
                    if len(holders) > 0:
                        i = random.randrange(len(holders))
                        holders[i].req_queue.append(seq)
                        self.m_file_cache[seq].m_state = 1
                        cycle_reqed += 1
                        if cycle_reqed > REQ_INTERVAL / FORWARD_INTERVAL:
                            break
                    else:
                        self.m_rejected += 1
        else:
            seqs_reqed = []
            for seq in range(self.m_seq_num + 1,\
                                 self.m_seq_num + BUF_CAP):
                if self.have(seq): continue
                self.m_total_reqs += 1
                holders = []
                for nbr in self.m_nbrs:
                    if nbr.m_peer.have(seq):
                        holders.append(nbr)
                if len(holders) > 0:
                    seqs_reqed.append(seq)
                    i = random.randrange(len(holders))
                    holders[i].req_queue.append(seq)
                    # cycle_reqed += 1
                    # if cycle_reqed > REQ_INTERVAL / FORWARD_INTERVAL:
                    #     break
                else:
                    self.m_rejected += 1
            if self.m_peer_id == SAMPLE_ID:
                print "Scheduled: ",
                print seqs_reqed
        self.send_req_pkts()

    def rf_pull(self):
        """ select packet in order of rareness,
        select peer randomly. """
        if self.m_peer_id == 0: return

        for nbr in self.m_nbrs:
            nbr.req_queue = []
        seqs_vs_holdernum = [None,]*NBR_CNT
        for i in range(len(seqs_vs_holdernum)):
            seqs_vs_holdernum[i] = []
        seqs_to_req = {}
        
        if APP == FILE_SHARING:
            for seq in range(SIM_CHUNKS):
                if self.want(seq):
                    holders = []
                    for nbr in self.m_nbrs:
                        if nbr.m_peer.have(seq):
                            holders.append(nbr)
                    if len(holders) > 0:
                        seqs_vs_holdernum[len(holders)-1].append(seq)
                        seqs_to_req[seq] = holders
        else:
            cycle_reqed = 0
            for seq in range(self.m_seq_num,\
                                 self.m_seq_num + int(3 * BUF_CAP/4)):
                if self.have(seq): continue
                self.m_total_reqs += 1
                holders = []
                for nbr in self.m_nbrs:
                    if nbr.m_peer.have(seq):
                        holders.append(nbr)
                if len(holders) > 0:
                    seqs_vs_holdernum[len(holders)-1].append(seq)
                    seqs_to_req[seq] = holders
                    cycle_reqed += 1
                    if cycle_reqed > REQ_INTERVAL / FORWARD_INTERVAL:
                        break
                else:
                    self.m_rejected += 1

        for seqs in seqs_vs_holdernum:
            for seq in seqs:
                i = random.randrange(len(seqs_to_req[seq]))
                seqs_to_req[seq][i].req_queue.append(seq)
                # if APP == STREAMING:
                #     self.m_buffer[seq %BUF_CAP].m_seq = seq
                #     self.m_buffer[seq %BUF_CAP].m_state = 1
                # else:
                if APP == FILE_SHARING:
                    self.m_file_cache[seq].m_state = 1
        self.send_req_pkts()

    def endurable_peer(self, seq):
        chunk_num = 0
        obj_peer = None
        for p in self.m_topology.online_peers:
            if p.have(seq) and p.m_avail_bw > 0:
                if p.avail_items_absolute() > chunk_num:
                    chunk_num = p.avail_items_absolute()
                    obj_peer = p

        return obj_peer

    def endurable_pull(self):
        """ select serving peer in order of endurability """
        if self.m_peer_id == 0: return
        for p in self.m_topology.online_peers:
            if p != self:
                p.m_avail_bw = REQ_INTERVAL / SEND_INTERVAL

        cycle_reqed = 0
        for seq in range(self.m_seq_num + 1,\
                             self.m_seq_num + int(BUF_CAP*3/4) ):
            if not self.have(seq):
                self.m_total_reqs += 1
                obj_peer = self.endurable_peer(seq)
                if obj_peer:
                    obj_peer.m_avail_bw -= 1
                    packet = PacketRequest(self, obj_peer, PACKET_REQ)
                    packet.append_seq(seq)
                    self.send_pkt(packet)
                    # self.m_buffer[seq %BUF_CAP].m_seq = seq
                    # self.m_buffer[seq %BUF_CAP].m_state = 1
                    cycle_reqed += 1
                    if cycle_reqed > REQ_INTERVAL / FORWARD_INTERVAL:
                        break
                else:
                    self.m_rejected += 1
        # if self.m_buffering == False:
        #     self.m_req_start += REQ_INTERVAL / FORWARD_INTERVAL

    def send_req_pkts(self):
        for nbr in self.m_nbrs:
            if len(nbr.req_queue) > 0:
                packet = PacketRequest(self, nbr.m_peer, PACKET_REQ)
                packet.set_pkts_list(nbr.req_queue)
                self.send_pkt(packet)
                if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                    print "%d: %d request data pkts from %d" %\
                        (self.m_engine.m_current_time, SAMPLE_ID,
                         nbr.m_peer.m_peer_id)
            nbr.req_queue =[]

    def buffer_finish(self):
        """ judge whether the buffering does finish."""
        if self.m_buffering == True and \
                self.m_recved / float(BUF_CAP) >= BUF_RATIO:
            self.m_buffering = False
            self.m_buffer_time = self.m_engine.m_current_time\
                - self.m_join_time
            self.m_start_seq = self.m_seq_num
            if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                print "%d: %d finishes buffering, buffer time: %d"\
                    %(self.m_engine.m_current_time, SAMPLE_ID,\
                          self.m_buffer_time)

    # def buffer_level(self, sstream_index):
    #     if sstream_index >= SUBSTREAM or sstream_index < 0:
    #         print "wrong substream index !"
    #         return

    #     buffered = 0
    #     location = 0
    #     i = sstream_index
    #     while i < BUF_CAP:
    #         seq = self.m_buffer[i].m_seq
    #         if seq > self.m_seq_num:
    #             buffered +=1
    #         location += 1
    #         i += SUBSTREAM

    #     return float(buffered) / location
            
    def want(self, seq):
        """ whether this peer is interested in segment with given seq
        @param: int seq
        @return: True or False """
        if APP == FILE_SHARING:
            if self.m_file_cache[seq].m_state == 0:
                return True
        else:
            if seq > self.m_seq_num and\
                    seq < self.m_seq_num + BUF_CAP and \
                    (not self.have(seq)):
                return True
            
        return False

    def have(self, seq):
        """ whether segment with given seq is in this peer's buffer"""
        if APP == STREAMING:
            if self.m_buffer[seq % BUF_CAP].m_seq == seq and\
                    self.m_buffer[seq %BUF_CAP].m_state == 2:
                return True
        else:
            if self.m_file_cache[seq].m_state == 2:
                return True

        return False

    def print_buffer(self):
        print "Seq num: %d" %(self.m_seq_num)
        print "[",
        for i in range(BUF_CAP):
            print "%d:%d "%(self.m_buffer[i].m_seq, self.m_buffer[i].m_state),
        print "]"
    
    def print_info(self):
        print "ID: %d" %(self.m_peer_id)
        print "join time: %d" %(self.m_join_time)
        self.print_nbrs()
        print "Buffering: ",
        print self.m_buffering
        print "Recved: %d" % (self.m_recved)
        print "Buffer ratio: %.3f" % (float(self.m_recved) / BUF_CAP)
        self.print_buffer()
        print "want to req: %d" %(self.m_total_reqs)
        print "rejected: %d" % (self.m_rejected)
        print "avg send queue length: %d" %( self.avg_send_queue_len() )

    def nbr_index(self, peer):
        """ Judge whether a given peer is a neighbor,
        if it is, renturn its index, else return -1. """
        for i in range(len(self.m_nbrs)):
            if self.m_nbrs[i].m_peer.m_peer_id == peer.m_peer_id:
                return i
        return -1
 
    def join(self):
        """ new peer join the system """
        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            print "%d: %d joined" % (self.m_engine.m_current_time,\
                                         self.m_peer_id)
            self.m_topology.print_online_peers(self.m_engine)

        self.m_online = True
        if APP == STREAMING:
            self.forward()
        else:
            if self.m_peer_id == 0:
                for i in range(SIM_CHUNKS):
                    self.m_file_cache[i].m_state = 2

        if APP == STREAMING:
            if self.m_peer_id == 0:
                self.m_buffering = False
            else:
                self.m_buffering = True

        if self.m_peer_id != 0:
            self.m_finding_nbrs = True
            self.find_nbrs()

        self.m_engine.schedule_event(REQ_INTERVAL,\
                EVENT_SCHEDULE, self)
        self.m_engine.schedule_event(SEND_INTERVAL,\
                EVENT_SEND, self)

    def leave(self):
        """ if a peer leave the system elegantly,
        it send packets to inform its neighors."""
        for n in self.m_nbrs:
            pkt = Packet(self, n.m_peer, PACKET_LEAVE)
            self.send_pkt(pkt)
        self.m_online = False

    def forward(self):
        """ for source peer, create new packets peoridically;
        for normal peer, update playback process."""
        self.m_engine.schedule_event(FORWARD_INTERVAL,\
                EVENT_FORWARD, self)

        if self.m_peer_id == 0:
            self.m_buffer[Peer.new_seq % BUF_CAP].m_seq =\
                Peer.new_seq
            self.m_buffer[Peer.new_seq % BUF_CAP].m_state = 2
            self.m_buffer[Peer.new_seq % BUF_CAP].m_rareness = 1
            Peer.new_seq += 1
            """ In fact, the m_seq_num of source is nonsense. """
            if Peer.new_seq >= BUF_CAP:
                self.m_seq_num += 1
        else:
            if self.m_buffering == False:
                if self.have(self.m_seq_num):	# state quality
                    self.m_played += 1
                self.m_should_played +=1
                self.m_seq_num += 1		# playback

                if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                    print "%d: %d forward, seq num: %d. played: %d"\
                        % (self.m_engine.m_current_time, SAMPLE_ID,\
                           self.m_seq_num, self.m_played)

    def quality(self):
        if self.m_peer_id == 0: return 1
        else:
            if self.m_buffering == True or self.m_should_played == 0:
                return 0
            else:
                return float(self.m_played)/( self.m_should_played)

    def broadcast(self):
        """ peer broadcast its buffermap to its neighbours """
        self.m_engine.schedule_event(NOTIFY_INTERVAL,\
                EVENT_NOTIFY, self)

        if SCHEDULE == PUSH_PULL or SCHEDULE == HAPP:
            return

        for nbr in self.m_nbrs:
            packet = PacketNotify(self, nbr.m_peer, PACKET_NOTIFY)
            self.send_pkt(packet)

    def fair_serv(self):
        """ send packets to each neighbor fairly.
        @input: send_queue of each neighbor """
        #find a nbr in turn
        nbr_idx = -1
        for i in range( len(self.m_nbrs) ):
            self.last_nbr_send %= len(self.m_nbrs)
            if len(self.m_nbrs[ self.last_nbr_send ].send_queue)\
                    > 0:
                nbr_idx = self.last_nbr_send
                break
            self.last_nbr_send += 1

        if nbr_idx < 0: return
        sended = False
        for seq in self.m_nbrs[nbr_idx].send_queue:
            if self.have(seq):
                packet = PacketData(self, self.m_nbrs[nbr_idx].\
                        m_peer,\
                        PACKET_DATA, seq)
                self.send_pkt(packet)
                self.m_nbrs[nbr_idx].send_queue.remove(seq)
                sended = True
            if sended == True:
                break
        self.last_nbr_send += 1

    def fast_serv(self):
        # find the rarest chunk
        nbr_list = []
        rarest_seq = -1
        min_copy_num = NODE_CNT
        for n in self.m_nbrs:
            for seq in n.send_queue:
                if seq == rarest_seq:
                    nbr_list.append(n)
                elif self.have(seq):
                    copy_num = 0
                    for p in self.m_topology.online_peers:
                        if p.have(seq):
                            copy_num += 1
                    if copy_num <= min_copy_num:
                        nbr_list = []
                        min_copy_num = copy_num
                        rarest_seq = seq
                        nbr_list.append(n)

        if rarest_seq == -1: return
        #find the requestor with largest rbw
        idlest_nbr = None
        avail_chunks = SIM_CHUNKS
        for n in nbr_list:
            chunk_num = n.m_peer.avail_items_relative()
            if chunk_num <= avail_chunks:
                avail_chunks = chunk_num
                idlest_nbr = n
        if idlest_nbr == None: return
        #send chunk to the requestor
        packet = PacketData(self, idlest_nbr.m_peer,\
                PACKET_DATA, rarest_seq)
        self.send_pkt(packet)
        idlest_nbr.send_queue.remove(rarest_seq)

    def send(self):
        """ pick a packet to send, and send it"""

        """ TODO: adaptive SEND_INTERVAL for different bandwidth"""
        self.m_engine.schedule_event(SEND_INTERVAL,\
                EVENT_SEND, self)

        if len(self.m_nbrs) == 0: return
        
        if SRV_SIDE_SCHEDULE == 1:
            self.fast_serv()   
        else:
            self.fair_serv()

    def avg_send_queue_len(self):
        if len(self.m_nbrs) == 0:
            return 0
        total_len = 0
        for n in self.m_nbrs:
            total_len += len(n.send_queue)
        return float(total_len) / len(self.m_nbrs)

    def pushing_which(self, nbr):
        """ maybe to delete """
        li = []
        for i in range(SUBSTREAM):
            if self == nbr.m_pushing_nbrs[i].m_peer:
                li.append(i)
        return li

    def min_seq(self):
        min_seq = -1
        for i in range(BUF_CAP):
            if self.m_buffer[i].m_state == 2:
                if min_seq < 0 or self.m_buffer[i].m_seq < min_seq:
                    min_seq = self.m_buffer[i].m_seq
        return min_seq

    def avail_items_absolute(self):
        avail_items = 0
        if APP == STREAMING:
            for i in range(BUF_CAP):
                if self.m_buffer[i].m_state == 2:
                    avail_items += 1
        else:
            for i in range(SIM_CHUNKS):
                if self.have(i):
                    avail_items += 1
        return avail_items

    def avail_items_relative(self):
        avail_items = 0
        if APP == STREAMING:
            for i in range(BUF_CAP):
                for nbr in self.m_nbrs:
                    if nbr.m_peer.want(self.m_buffer[i].m_seq):
                        avail_items +=1
                        break
        else:
            for i in range(SIM_CHUNKS):
                if self.have(i):
                    avail_items +=1
        return avail_items

    def f2f_fs_optimal(self):
        """ optimal distribution for file sharing """
        rare_dict = {}
        for chunk in range(SIM_CHUNKS):
            copy_num = 0
            for p in self.m_topology.online_peers:
                if p.have(chunk):
                    copy_num += 1
            if self.have(chunk)\
                    and copy_num < NODE_CNT + 1:
                rare_dict[chunk] = copy_num
        chunk_none_want = []
        want_dict = {}
        for chunk in rare_dict:
            want_nbrs = []
            for nbr in self.m_nbrs:
                if nbr.m_peer.want(chunk):
                    want_nbrs.append(nbr)
            if len(want_nbrs) == 0:
                chunk_none_want.append(chunk)
            else:
                want_dict[chunk] = want_nbrs
        for chunk in chunk_none_want:
            del rare_dict[chunk]

        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            print "rare_dict: %d" % (len(rare_dict))
#        times = 0
        while len(rare_dict) > 0:
            valid_chunk = -1
            copy_num = NODE_CNT + 1
            for chunk in rare_dict:
                if rare_dict[chunk] < copy_num:
                    valid_chunk = chunk
                    copy_num = rare_dict[chunk]
            if valid_chunk == -1: break
            obj_nbr = None
            avail_chunks = SIM_CHUNKS
            for n in want_dict[valid_chunk]:
                if n.m_peer.avail_items_relative() < avail_chunks:
                    obj_nbr = n
                    avail_chunks = n.m_peer.avail_items_relative()
            if obj_nbr != None:
                obj_nbr.send_queue.append(valid_chunk)
#                    times += 1
                obj_nbr.m_peer.m_file_cache[valid_chunk].\
                    m_state = 1 #downloading
                if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                    print "%d will upload %d to %d." %\
                        (SAMPLE_ID, valid_chunk, \
                             obj_nbr.m_peer.m_peer_id)
            del rare_dict[valid_chunk]

    def f2f_fs_pull(self):

        rare_dict = {}
        for i in range(SIM_CHUNKS):
            if self.m_file_cache[i].m_state == 2:
                self.m_file_cache[i].m_rareness = 1
            else:
                self.m_file_cache[i].m_rareness = 0
            for nbr in self.m_nbrs:
                if nbr.m_peer.m_file_cache[i].m_state == 2:
                    self.m_file_cache[i].m_rareness += 1
            if self.m_file_cache[i].m_state == 0:
                rare_dict[i] = self.m_file_cache[i].m_rareness
                #if self.m_peer_id == SAMPLE_ID:
                    #print rare_dict[i],

        if self.m_peer_id == 0: return

        chunk_no_owner = []
        owner_dict = {}
        for chunk in rare_dict:
            have_nbrs = []
            for nbr in self.m_nbrs:
                if nbr.m_peer.have(chunk):
                    have_nbrs.append(nbr)
            if len(have_nbrs) == 0:
                chunk_no_owner.append(chunk)
            else:
                owner_dict[chunk] = have_nbrs

        for chunk in chunk_no_owner:
            del rare_dict[chunk]
        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            print "rare_dict: %d"%(len(rare_dict))

        while len(rare_dict) > 0:
            chunk_to_req = -1
            min_rareness = SIM_CHUNKS
            for chunk in rare_dict:
                if rare_dict[chunk] <= min_rareness:
                    chunk_to_req = chunk
                    min_rareness = rare_dict[chunk]
            if chunk_to_req < 0: break
            obj_nbr = None
            avail_chunks = SIM_CHUNKS
            for n in owner_dict[chunk_to_req]:
                if n.m_peer.avail_items_relative()\
                        <= avail_chunks:
                    obj_nbr = n
                    avail_chunks = n.m_peer.avail_items_relative()
            if obj_nbr != None:
                obj_nbr.req_queue.append(chunk_to_req)
                self.m_file_cache[chunk_to_req].m_state = 1
                if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                    print "%d request %d from %d." %\
                        (SAMPLE_ID, chunk_to_req, \
                             obj_nbr.m_peer.m_peer_id)
            
            del rare_dict[chunk_to_req]

        self.send_req_pkts()

    def f2f_stream_optimal(self):
        want_dict = {}
        for i in range(BUF_CAP):
            self.m_buffer[i].m_rareness = 0
            for p in self.m_topology.online_peers:
                if p.have(self.m_buffer[i].m_seq):
                    self.m_buffer[i].m_rareness += 1
            want_dict[i] = []
            for nbr in self.m_nbrs:
                if nbr.m_peer.want(self.m_buffer[i].m_seq):
                    want_dict[i].append(nbr)

        pkts_no_wanter = []
        for idx in want_dict:
            if want_dict[idx] == []:
                pkts_no_wanter.append(idx)
        for idx in pkts_no_wanter:
            del want_dict[idx]

        for n in self.m_nbrs:
            n.send_queue = []
        
        sended = 0
        while len(want_dict) > 0:
            obj_idx = -1
            obj_rareness = NODE_CNT + 1
            for idx in want_dict:
                if self.m_buffer[idx].m_rareness < obj_rareness:
                    obj_rareness = self.m_buffer[idx].m_rareness
                    obj_idx = idx
            if obj_idx == -1: break
            obj_nbr = None
            avail_items = BUF_CAP
            for nbr in want_dict[obj_idx]:
                if nbr.m_peer.avail_items_relative() <= avail_items:
                    obj_nbr = nbr
                    avail_items = nbr.m_peer.avail_items_relative()
            if obj_nbr != None:
                sended += 1
                obj_nbr.send_queue.append(\
                    self.m_buffer[obj_idx].m_seq)
                obj_nbr.m_peer.m_buffer[obj_idx].m_seq = \
                    self.m_buffer[obj_idx].m_seq
                obj_nbr.m_peer.m_buffer[obj_idx].m_state = 1
                self.m_buffer[obj_idx].m_rareness += 1
                want_dict[obj_idx].remove(obj_nbr)
                if want_dict[obj_idx] == []:
                    del want_dict[obj_idx]
                if sended > REQ_INTERVAL / SEND_INTERVAL:
                    break
                
    def f2f_stream_pull(self):
        if self.m_peer_id == 0: return

        for i in range(BUF_CAP):
            self.m_buffer[i].m_rareness = 0
            if self.m_buffer[i].m_seq >= 0:
                if self.m_buffer[i].m_state == 2:
                    self.m_buffer[i].m_rareness += 1
                for n in self.m_nbrs:
                    if n.m_peer.have(self.m_buffer[i].m_seq):
                        self.m_buffer[i].m_rareness += 1

        have_dict = {}
        for seq in range(self.m_seq_num + 1, \
                             self.m_seq_num + BUF_CAP):
            if not self.have(seq):
                have_dict[seq] = []
                for n in self.m_nbrs:
                    if n.m_peer.have(seq):
                        have_dict[seq].append(n)
        seq_no_owner = []
        for seq in have_dict:
            if have_dict[seq] == []:
                seq_no_owner.append(seq)
        for seq in seq_no_owner:
            del have_dict[seq]

        while len(have_dict) > 0:
            obj_seq = -1
            owner_num = NBR_CNT
            for seq in have_dict:
                if len(have_dict[seq]) <= owner_num:
                    obj_seq = seq
                    owner_num = len(have_dict[seq])
            obj_nbr = None
            avail_item = BUF_CAP
            for n in have_dict[obj_seq]:
                if n.m_peer.avail_items_relative() < avail_item:
                    avail_item = n.m_peer.avail_items_relative()
                    obj_nbr = n
            if obj_nbr != None:
                obj_nbr.req_queue.append(obj_seq)
            del have_dict[obj_seq]

        self.send_req_pkts()

    def send_pkt(self, packet):
        #TODO: delay Matrix
        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            print "%d send packet to %d, type: %d. "%\
                (SAMPLE_ID, packet.m_dest_peer.m_peer_id, packet.m_type)
        time = self.m_engine.m_current_time + \
            random.randrange(MAX_DELAY)
        e = Event(time, EVENT_RECEIVE, packet.m_dest_peer)
        e.packet(packet)
        self.m_engine.add_event(e)

    def receive_pkt(self,packet):
        """ handle all kinds of packets received """ 
        if packet == None:
            return

        if packet.m_type == PACKET_LEAVE:
            for n in self.m_nbrs:
                if n.m_peer== packet.m_src_peer:
                    self.del_nbr(n)
                    break
            return

        elif packet.m_type == PACKET_ADD_NBR:
            if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                print "%d: %d receive packet of adding nbr from %d."%\
                    (self.m_engine.m_current_time, SAMPLE_ID,\
                         packet.m_src_peer.m_peer_id)
            if len(self.m_nbrs) < NBR_CNT and \
                    self.nbr_index(packet.m_src_peer) == -1:
                self.add_nbr(packet.m_src_peer)
                p = Packet(self, packet.m_src_peer, PACKET_ACK)
                self.send_pkt(p)
            del packet

        elif packet.m_type == PACKET_ACK: 
            if len(self.m_nbrs) < NBR_CNT and \
                    self.nbr_index(packet.m_src_peer) == -1:
                self.add_nbr(packet.m_src_peer)

        elif packet.m_type == PACKET_DATA:
            if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                print "%d: %d receive data pkt from %d, seq num: %d"%\
                    (self.m_engine.m_current_time, self.m_peer_id,\
                     packet.m_src_peer.m_peer_id, packet.m_seq)
            if APP == FILE_SHARING:
                self.m_file_cache[packet.m_seq].m_state = 2
                self.m_recved += 1
            else:
                self.m_recved += 1
                # print "Recive: %d, %d" % (self.m_peer_id, self.m_recved)
                self.buffer_finish()
                self.m_buffer[packet.m_seq %BUF_CAP].m_seq =\
                    packet.m_seq
                self.m_buffer[packet.m_seq %BUF_CAP].m_state=2

            self.m_cycle_recved += 1
            for n in self.m_nbrs:
                if n.m_peer == packet.m_src_peer:
                    n.cycle_recved += 1
            del packet

        elif packet.m_type == PACKET_SUB:
            """ PUSH_PULL: subscribe a substream """
            idx = self.nbr_index(packet.m_src_peer)
            if idx != -1:
                self.m_pushed_nbrs.append(idx)
                seq = packet.m_seq
                ss_idx = packet.m_idx
                self.m_nbrs[idx].push_to_it[ss_idx] = seq

                if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                    print "%d: %d receive subscribe pkt from %d,\
                            ss_idx: %d, seq: %d" %(\
                            self.m_engine.m_current_time,\
                            self.m_peer_id,\
                            packet.m_src_peer.m_peer_id,\
                            ss_idx, seq)

        elif packet.m_type == PACKET_UNSUB:
            idx = self.nbr_index(packet.m_src_peer)
            if in_list(idx, self.m_pushed_nbrs) != -1:
                self.m_pushed_nbrs.remove(idx)
            ss_idx = packet.m_idx
            self.m_nbrs[idx].push_to_it[ss_idx] = -1

            if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                print "%d: %d receive unsubscribe pkt from %d,\
                        ss_idx: %d" %(self.m_engine.m_current_time,\
                        self.m_peer_id, packet.m_src_peer.m_peer_id,\
                        ss_idx)

        elif packet.m_type == PACKET_REQ:
            idx = self.nbr_index(packet.m_src_peer)
            if idx >= 0:
                self.handle_request(idx, packet)

                if self.m_peer_id == SAMPLE_ID and DETAIL==1:
                    print "%d: %d requested by %d:" %\
                            (self.m_engine.m_current_time,\
                            SAMPLE_ID,\
                            self.m_nbrs[idx].m_peer.m_peer_id),
                    print self.m_nbrs[idx].send_queue
                    self.print_buffer()
            del packet

        elif packet.m_type == PACKET_NOTIFY:
            if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
                print "%d: %d received broadcast message from %d." %\
                    (self.m_engine.m_current_time, SAMPLE_ID,\
                         packet.m_src_peer.m_peer_id)
            del packet
        else:
            print " what is fucking this packet ???"
            del packet

    def handle_request(self, nbr_idx, pkt_req):
        """ according to the request packet, 
        rearrange the send queue """
        for seq_new in pkt_req.m_pkts_to_req:
            in_queue = False
            for seq_old in self.m_nbrs[nbr_idx].send_queue:
                if seq_new == seq_old:
                    in_queue = True
                    break
            if in_queue == False:
                self.m_nbrs[nbr_idx].send_queue.append(seq_new)
                # for file sharing, need not drop the head
                #if len(self.m_nbrs[nbr_idx].send_queue) > SEND_QUEUE_LEN:
                    #del self.m_nbrs[nbr_idx].send_queue[0]

class Neighbour(object):
    """ neighbour information """
    def __init__(self, peer):
        self.m_peer = peer
        self.req_queue = []
        self.send_queue = []
        self.recv_cnt = 0   # receive from this neighbour
        self.req_cnt = 0    # request from this neighbour
        self.serv_time = -1
        self.cycle_recved = 0

        self.push_to_it=[-1,]*SUBSTREAM # substream seqs
        self.last_send_sidx = 0 # for fair bandwidth alloc
        self.pushed_by_it = [] # pushed streams from this nbr
 
class Packet(object):
    def __init__(self,src_peer,dest_peer,type):
        self.m_src_peer = src_peer
        self.m_dest_peer = dest_peer
        self.m_type = type

    def src_peer(self, src_peer):
        self.m_src_peer = src_peer

    def dest_peer(self, dest_peer):
        self.m_dest_peer = dest_peer

class PacketData(Packet):
    """ packet data for streaming and file sharing"""
    def __init__(self,src_peer, dest_peer, type,seq_num):
        super(PacketData,self).__init__(src_peer,dest_peer,type)
        self.m_seq = seq_num

class PacketRequest(Packet):
    def __init__(self,src_peer, dest_peer, type):
        super(PacketRequest,self).__init__(src_peer,dest_peer,type)
        self.m_pkts_to_req = []

    def set_pkts_list(self, list):
        self.m_pkts_to_req.extend(list)

    def append_seq(self, seq):
        self.m_pkts_to_req.append(seq)

class PacketSubscribe(Packet):
    def __init__(self, src_peer, dest_peer, type, seq):
        super(PacketSubscribe,self).__init__(src_peer,dest_peer,type)
        self.m_start_seq = seq

class PacketUnSub(Packet):
    def __init__(self, src_peer, dest_peer, type, ss_idx):
        super(PacketUnSub,self).__init__(src_peer,dest_peer,type)
        self.m_idx = ss_idx

class PacketNotify(Packet):
    """ buffer map nitification """
    def __init__(self, src_peer,dest_peer,type):
        super(PacketNotify,self).__init__(src_peer,dest_peer,type)

class Event(object):
    """ event class """
    def __init__(self, time, event_type, peer):
        self.m_time = time
        self.m_type = event_type
        self.m_peer = peer
        self.m_packet = None

    def packet(self,p):
        self.m_packet = p

class EventEngine(object):
    def __init__(self, topology):
        self.m_current_time = 0
        self.m_event_queue = []
        self.m_topology = topology
        self.m_monitor = None

    """ You can add new event and its handling here """
    def handle_event(self,e):
        self.m_current_time = e.m_time

        if e.m_type == EVENT_FORWARD:
            if e.m_peer.m_online:
                e.m_peer.forward()
        elif e.m_type == EVENT_SEND:
            if e.m_peer.m_online:
                e.m_peer.send()
        elif e.m_type == EVENT_RECEIVE:
            if e.m_peer.m_online:
                e.m_peer.receive_pkt(e.m_packet)
        elif e.m_type == EVENT_FIND_NBR:
            if e.m_peer.m_online:
                e.m_peer.find_nbrs()
        elif e.m_type == EVENT_NOTIFY:
            if e.m_peer.m_online:
                e.m_peer.broadcast()
        elif e.m_type == EVENT_STAT:
            self.m_monitor.runtime_print(self)
            self.schedule_event(STAT_INTERVAL, EVENT_STAT, None)
        elif e.m_type == EVENT_SCHEDULE:
            if e.m_peer.m_online:
                e.m_peer.schedule()
        elif e.m_type == EVENT_PEER_JOIN:
            self.m_topology.online_peers.append(e.m_peer)
            e.m_peer.join()
        elif e.m_type == EVENT_PEER_LEAVE:
            self.m_topology.online_peers.remove(e.m_peer)
            e.m_peer.leave()
        elif e.m_type == EVENT_EVAL:
            pass
#            if e.m_peer.m_online:
#                e.m_peer.eval_nbrs()
        else:
            print "I don't know what happened ..."

    def run(self,duration):
        self.m_records = open('quality', 'w')
        self.m_monitor = GlobalMonitor(self.m_topology, \
                self.m_records)
        self.schedule_event(STAT_INTERVAL, EVENT_STAT, None)
        while self.m_event_queue != []:
            e = self.m_event_queue[0]
            del self.m_event_queue[0]
            self.handle_event(e)
            if self.m_current_time > duration:
                break

        self.m_records.close()
        self.m_monitor.delay_cdf()

    def add_event(self,e):
        index = 0
        for event in self.m_event_queue:
            if e.m_time < event.m_time:
                self.m_event_queue.insert(index,e)
                return
            index +=1
        self.m_event_queue.append(e)

    def schedule_event(self, interval, event_type, peer):
        time = self.m_current_time + interval
        e = Event(time, event_type, peer)
        self.add_event(e)

class UnderTopo(object):
    """underlying topology """
    def __init__(self):
        self.all_peers = []
        self.online_peers = []
        self.latency_matrix = []

    def load_latency_matrix(self,filename):
        """ load latency matrix from filename into matrix
        TO COMPLETED """
        for k in range(NODE_CNT):
            self.latency_matrix.append([])
            for n in range(NODE_CNT):
                self.latency_matrix[k].append(-1)
        f = open(filename,'r')
        while 1:
            s = f.readline()
            r = s.split()
            peer_id1 = int(r[0])
            if peer_id1 <= NODE_CNT:
                peer_id2 = int(r[1])
                if peer_id2 <= NODE_CNT:
                    latency = int(r[2])/2
                    self.latency_matrix[peer_id1-1][peer_id2-1]\
                        = latency
                    self.latency_matrix[peer_id2-1][peer_id1-1]\
                        = latency
            else:
                break
        f.close()

    def join_server(self, event_engine):
        peer = Peer(0, self, event_engine)
        self.all_peers.append(peer)
        e = Event(0, EVENT_PEER_JOIN,peer)
        event_engine.add_event(e)
        leave_time = SIM_DURATION + 1000
        e = Event(leave_time, EVENT_PEER_LEAVE,peer)
        event_engine.add_event(e)

    def join_peers(self,event_engine, begin_time, duration, peer_cnt):
        """schedule all peers join and leave """
        begin_id = len(self.all_peers)
        for i in range(peer_cnt):
            peer = Peer(begin_id + i,self,event_engine)
            self.all_peers.append(peer)
            """ random join model and there is no churn """
            peer.set_life_time(\
              begin_time + random.randrange(duration),\
              SIM_DURATION + 1000)
            e = Event(peer.m_join_time, EVENT_PEER_JOIN,peer)
            event_engine.add_event(e)
            e = Event(peer.m_leave_time, EVENT_PEER_LEAVE, peer)
            event_engine.add_event(e)

    def schedule_all_peers(self, engine):
        """ schedule join and leave of all peers 
        @param: EventEngine engine
        @return: None"""
        self.join_server(engine)
        self.join_peers(engine, 0, JOIN_DURATION, NODE_CNT)
        if FLASH == 1:
            self.join_peers(engine, FLASH_TIME, FLASH_DURATION,\
              FLASH_CNT)

    def print_online_peers(self, engine):
        print "%d: online peers: " % (engine.m_current_time),
        for p in self.online_peers:
            print "%d, " % (p.m_peer_id),
        print

class GlobalMonitor(object):

    def __init__(self, topo, file):
        self.m_topo = topo
        self.m_file = file

    def avg_quality(self):
        started = 0
        avg_quality = 0
        for p in self.m_topo.online_peers:
            if p.m_peer_id != 0 and p.m_buffering == False:
                started += 1
                avg_quality += p.quality()

        if started > 0:
            return float(avg_quality) / started
        else:
            return 0

    def rejected_ratio(self):
        if len(self.m_topo.online_peers) == 0:
            return 0
        rejected = 0
        for p in self.m_topo.online_peers:
            if p.m_total_reqs > 0:
                rejected += float(p.m_rejected)/ \
                        p.m_total_reqs
        return float(rejected) / len(self.m_topo.online_peers)

    def complete_ratio(self):
        if len(self.m_topo.online_peers) == 0:
            return 0
        comp_ratio = 0
        for p in self.m_topo.online_peers:
            comp_ratio += float(p.avail_items_relative())/ \
                    SIM_CHUNKS
        return float(comp_ratio) / \
                len(self.m_topo.online_peers)

    def distrib_load(self):
        load = 0
        for p in self.m_topo.online_peers:
            if APP == FILE_SHARING:
                load += SIM_CHUNKS - p.avail_items_relative()
            else:
                load += (Peer.new_seq - p.m_start_seq + 1\
                        - p.m_recved)
        return load

    def runtime_print(self, engine):
        if APP == STREAMING:
            print "%d\t%.3f\t%.3f" %\
                (engine.m_current_time / 1000, \
                self.rejected_ratio(), self.avg_quality())
            self.m_file.write( "%d\t%.3f\t%.3f\n" %\
                (engine.m_current_time / 1000, \
                self.rejected_ratio(), self.avg_quality()) )

        else:
            print "%d\t%d\t%.3f" %\
                    (engine.m_current_time / 1000,\
                    self.distrib_load(),\
                    self.complete_ratio())
            self.m_file.write( "%d\t%d\t%.3f\n" %\
                    (engine.m_current_time / 1000,\
                    self.distrib_load(),\
                    self.complete_ratio()) )

    def delay_cdf(self):
        max_delay = 0
        for p in self.m_topo.all_peers:
            if p.m_buffering == False and \
                    p.m_buffer_time > max_delay:
                max_delay = p.m_buffer_time
        print "the max delay:", max_delay
        if max_delay == 0: return

        points = [0,]*(max_delay/1000 + 1)
        for p in self.m_topo.online_peers:
            delay = p.m_buffer_time
            for v in range(delay/1000 + 1, max_delay/1000 + 1):
                points[v] += 1

        print "writing delay cdf to file ... "
        fp = open('delay', 'w')
        fp.write('0\t0.00\n')
        for v in range(0, max_delay/1000 + 1):
            fp.write('%d\t%.2f\n' % (v+1, float(points[v])/\
                    len(self.m_topo.online_peers)) )
        fp.close()

def in_list(obj, li):
    """ where to use this """
    for i in range(len(li)):
        if obj == li[i]:
            return i
    return -1

#################################################################

topology = UnderTopo()
engine = EventEngine(topology)
print "wait please! loading data ..."
topology.schedule_all_peers(engine)
#topology.load_latency_matrix(MATRIX_FILE)
print "simulation start ..."
engine.run(SIM_DURATION)
print "simulation finish at %d."%(engine.m_current_time)
print "time cost: ", time.clock()

# vim: foldmethod=indent
