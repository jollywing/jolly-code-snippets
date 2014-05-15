#!/usr/bin/python2

""" 
EPSS (Extensible P2P Streaming Simulator)
This is a event-driven p2p streaming simulator
for the research of scheduling algorithm, overlay construction,
and flash crowd.
author: WU Jiqing (jiqingwu@gmail.com)
update: 2012-07-28
version: 1.0.2

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

import random
import time

""" There are some constants below,
you can change it to setup your simulation."""

""" You can set SAMPLE_ID to -1,
to forbid the output of debug information.
If you set DETAIL to 1, the information of packet level will output """
SAMPLE_ID = -1
DETAIL = 0

""" You can set which kind of application
you are simulating here """
FILE_SHARING = 1
STREAMING = 2
APP = 1

""" Set the duration (mseconds) of your simulation here. """
SIM_DURATION = 600000
""" For file sharing application, set the number of chunks."""
SIM_CHUNKS = 500

""" For distribution delay of single chunk """
SAMPLE_SEQ_TIME = 0
SAMPLE_SEQ_PEERS = 0
SAMPLE_SEQ = 10
SAMPLE_SEQ_RATIO = 0.9

""" All available scheduling algorithms. """
RANDOM_PULL = 1
RF_PULL = 2
GREEDY_PULL = 3
# You can add your scheduling algorithm here.

""" Specify your scheduling algorithm here """
SCHEDULE = 1

""" Specify the on schedule algorithm on serving peer side here """
BEST_EFFORT_SERV = 0
FAIR_SERV = 1
FAST_SERV = 2
DEADLINE_SERV = 3
DEADLINE_FAST_SERV = 4
SRV_SIDE_SCHEDULE = 1

""" All available overlay construction algorithms,
add your own overlay construction algorithm here. """
RANDOM_OVERLAY = 1
DELAY_OVERLAY = 2

""" Specify your overlay construction algorithm here """
OVERLAY = RANDOM_OVERLAY

""" Set the number of peers in your simulation,
the source peer is not included. """
NODE_CNT = 100
""" Set the duration (mseconds) that all new peers join the system. """
JOIN_DURATION = 5000

""" To simulate flash crowds, set FLASH to True. """
FLASH_CROWD = False
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
NBR_CNT = 5
""" The cycle of exchanging buffermaps """
NOTIFY_INTERVAL = 2000
""" The cycle of requesting chunks """
REQ_INTERVAL = 1000
""" The cycle of statistics """
STAT_INTERVAL = 20000

""" How many packets the buffer can hold. """
BUF_CAP = 40
""" When a peer reaches the BUF_RATIO, it can start playback. """
BUF_RATIO = 0.4

""" In average, How long to send a data chunk """
SEND_INTERVAL = 100
SEND_QUEUE_LEN = 15
""" Set the max delay of sending a packet,
When you use delay matrix, this may be useless. """
MAX_DELAY = 150

USE_DELAY_MATRIX = False
MATRIX_FILE = 'simplified-matrix.dat'

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

############################################################

class FileChunk(object):
    """ structure of file chunk in cache """
    def __init__(self, state, rareness):
        self.m_state = state    # 0: miss; 1: downloading; 2: have

class BufferElement(object):
    """ structure of packet in buffer """
    def __init__(self, state, seq, rareness):
        self.m_state = state
        self.m_seq = seq
        self.m_req_time = -1
        self.m_response_time = -1

class Peer(object):
    """ peer in overlay: include server and normal peer """
    new_seq = 0

    def __init__ (self, peer_id,topology, event_engine):
        """ peer class constructor """
        self.m_topology = topology	# for accessing other peers
        self.m_engine = event_engine	# for scheduling event
        self.m_peer_id = peer_id	# for peer ID

        self.m_start_seq = 0	# for stating load, initial pointer
        self.m_seq_num = 0		# for play pointer
        self.m_played = 0		# for stating quality
        self.m_should_played = 0	# for stating quality
        self.m_late = 0         # for stating late packets
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
        """ return the bandwidth utility of this peer. """
        should_sent = float(self.m_engine.m_current_time -\
                                self.m_join_time) / SEND_INTERVAL
        return self.m_sent / should_sent

    def find_nbrs(self):
        """ normal peers find their neighbours,
        you can describe your algorithm of overlay
        construction here."""

        if len(self.m_nbrs) >= NBR_CNT:
            self.m_finding_nbrs = False
            return

        if self.m_finding_nbrs == True:
            self.m_engine.schedule_event(FIND_NBR_INTERVAL,\
                    EVENT_FIND_NBR, self)

        """ if all other online peers are all nbrs of this peer,
        return """
        if len(self.m_nbrs) == len(self.m_topology.online_peers) - 1:
            return

        """ find a object peer """
        candidate_peer = None
        if OVERLAY == RANDOM_OVERLAY:
            candidate_peer = self.find_nbr_random()
        elif OVERLAY == DELAY_OVERLAY:
            candidate_peer = self.find_nbr_delay()

        """ send a packet of adding neighbor to the peer """
        if not candidate_peer is None:
            packet = Packet(self, candidate_peer, PACKET_ADD_NBR)
            self.send_pkt(packet)

    def find_nbr_random(self):
        """find a neighbor candidate randomly"""
        while True:
            index = random.randrange( \
                    len(self.m_topology.online_peers) )
            p = self.m_topology.online_peers[index]
            if self != p and self.nbr_index(p) == -1:
                return p

    def find_nbr_delay(self):
        """ find a neighbor candidate with a little RTT """
        candidate_peer = None
        min_delay = 1000
        for p in self.m_topology.online_peers:
            if p.m_peer_id == self.m_peer_id:
                continue
            if self.nbr_index(p) != -1:
                continue
            if len(p.m_nbrs) >= NBR_CNT:
                continue
            latency = self.m_topology.latency_matrix[self.m_peer_id]\
                [p.m_peer_id]
            if latency < min_delay:
                min_delay = latency
                candidate_peer = p
        return candidate_peer

    def add_nbr(self, p):
        """ when receive an ACK or a ADD_NBR packet """
        nbr = Neighbour(p)
        self.m_nbrs.append(nbr)
        if len(self.m_nbrs) == NBR_CNT:
            self.m_finding_nbrs = False
        # print debug information
        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            self.print_nbrs()

    def del_nbr(self, n):
        """ when receive a LEAVE packet """
        self.m_nbrs.remove(n)
        self.m_finding_nbrs = True
        self.find_nbrs()
        # print debug information
        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            print "%d: %d remove neighbor %d." % \
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
        # If this peer is server or it has enough neighbors, return
        if self.m_finding_nbrs == True or \
                self.m_peer_id == 0: return
        # if aggregate rate is less than the playback rate
        # Q: why divided by 2?
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

        # if this peer has no neighbor, do nothing
        if len(self.m_nbrs) == 0: return
        
        if APP == STREAMING and self.m_buffering == True:
            # find the neighbor peer with the most available blocks
            chunk_num = 0
            obj_nbr = None
            for nbr in self.m_nbrs:
                if nbr.m_peer.avail_items_absolute() > chunk_num:
                    chunk_num = nbr.m_peer.avail_items_absolute()
                    obj_nbr = nbr
            # reset the requesting pointer
            if obj_nbr:
                self.m_seq_num = obj_nbr.m_peer.min_seq()

        if SCHEDULE == RANDOM_PULL:
            self.random_pull()
        elif SCHEDULE == RF_PULL:
            self.rf_pull()
        elif SCHEDULE == GREEDY_PULL:
            self.greedy_pull()

        self.maintain_nbrs()

    def random_pull(self):
        """ select packet in order, select peer randomly """
        # If this is a source peer, do nothing
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
                    # add the times that this peer is rejected
                    else:
                        self.m_rejected += 1
        else:
            seqs_reqed = []
            for seq in range(self.m_seq_num + 1,\
                                 self.m_seq_num + BUF_CAP):
                if self.have(seq): continue
                self.m_total_reqs += 1
                self.m_buffer[seq% BUF_CAP].m_req_time = \
                        self.m_engine.m_current_time
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

    def greedy_pull(self):
        if APP == FILE_SHARING:
            seq_begin = 0
            seq_end = SIM_CHUNKS
        else:
            seq_begin = self.m_seq_num + 1
            seq_end = self.m_seq_num + BUF_CAP

        reqed_this_cycle = 0
        for seq in range(seq_begin, seq_end):
            if not self.want(seq): continue
            self.m_total_reqs += 1
            
            holders = []
            for nbr in self.m_nbrs:
                if nbr.m_peer.have(seq):
                    holders.append(nbr)
                    
            if len(holders) > 0:
                short_queue_len = 10000
                fast_holder = None
                for holder in holders:
                    queue_len = holder.m_peer.total_send_queue_len()
                    if queue_len <= short_queue_len:
                        short_queue_len = queue_len
                        fast_holder = holder
                if fast_holder != None:
                    fast_holder.req_queue.append(seq)
                    reqed_this_cycle += 1;
                    if APP == FILE_SHARING:
                        self.m_file_cache[seq].m_state = 1
                        if reqed_this_cycle >\
                                (REQ_INTERVAL / SEND_INTERVAL) *\
                                len(self.m_nbrs):
                            break
                    else:
                        self.m_buffer[seq% BUF_CAP].m_req_time = \
                            self.m_engine.m_current_time
            else:
                self.m_rejected += 1
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
                if APP == FILE_SHARING:
                    self.m_file_cache[seq].m_state = 1
                else:
                    self.m_buffer[seq % BUF_CAP].m_req_time = \
                        self.m_engine.m_current_time

        self.send_req_pkts()

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
                else:
                    self.m_late +=1
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
                        m_peer, PACKET_DATA, seq)
                self.send_pkt(packet)
                self.m_nbrs[nbr_idx].send_queue.remove(seq)
                self.m_sent += 1
                sended = True
            if sended == True:
                break
        self.last_nbr_send += 1

    def best_effort_serv(self):
        """ serve neighbor peer one by one, serve next
        neighbor until serving of this neighbor is completed. """
        for n in self.m_nbrs:
            for seq in n.send_queue:
                if self.have(seq):
                    packet = PacketData(self, n.m_peer,\
                            PACKET_DATA, seq)
                    self.send_pkt(packet)
                    n.send_queue.remove(seq)
                    self.m_sent += 1
                    return

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
        self.m_sent += 1

    def deadline_pure_serv(self):
        # construct request queue
        req_queue = {}
        for n in self.m_nbrs:
            for seq in n.send_queue:
                if seq not in req_queue:
                    req_queue[seq] = []
                req_queue[seq].append(n)
        # find the least dealine
        snd_seq = -1
        Delta = float(SIM_DURATION) / FORWARD_INTERVAL
        for req_seq in req_queue.keys():
            total_delta = 0
            for n in req_queue[req_seq]:
                total_delta += req_seq - n.m_peer.m_seq_num
            delta = float(total_delta) / len(req_queue[req_seq])
            if delta <= Delta:
                Delta = delta
                snd_seq = req_seq
        if snd_seq == -1:
            return

        # find the nbr with fast process
        fast_nbr = None
        seq_num = 0
        for n in req_queue[snd_seq]:
            if n.m_peer.m_seq_num >= seq_num:
                seq_num = n.m_peer.m_seq_num
                fast_nbr = n
        if fast_nbr == None: return
        # send
        packet = PacketData(self, fast_nbr.m_peer,\
                PACKET_DATA, snd_seq)
        self.send_pkt(packet)
        fast_nbr.send_queue.remove(snd_seq)
        self.m_sent += 1

    def deadline_hybrid_serv(self):
        # construct request queue
        req_queue = {}
        for n in self.m_nbrs:
            for seq in n.send_queue:
                if seq not in req_queue:
                    req_queue[seq] = []
                req_queue[seq].append(n)
        # find the least dealine
        snd_seq = -1
        Delta = float(SIM_DURATION) / FORWARD_INTERVAL
        for req_seq in req_queue.keys():
            total_delta = 0
            for n in req_queue[req_seq]:
                total_delta += req_seq - n.m_peer.m_seq_num
            delta = float(total_delta) / len(req_queue[req_seq])
            if delta <= Delta:
                Delta = delta
                snd_seq = req_seq
        if snd_seq == -1:
            return
        # find the max relative bandwidth
        idlest_nbr = None
        avail_chunks = SIM_CHUNKS
        for n in req_queue[snd_seq]:
            chunk_num = n.m_peer.avail_items_relative()
            if chunk_num <= avail_chunks:
                avail_chunks = chunk_num
                idlest_nbr = n
        if idlest_nbr == None: return
        # send
        packet = PacketData(self, idlest_nbr.m_peer,\
                PACKET_DATA, snd_seq)
        self.send_pkt(packet)
        idlest_nbr.send_queue.remove(snd_seq)
        self.m_sent += 1

    def send(self):
        """ pick a packet to send, and send it"""

        """ TODO: adaptive SEND_INTERVAL for different bandwidth"""
        self.m_engine.schedule_event(SEND_INTERVAL,\
                EVENT_SEND, self)

        if len(self.m_nbrs) == 0: return

        if SRV_SIDE_SCHEDULE == FAIR_SERV:
            self.fair_serv()
        elif SRV_SIDE_SCHEDULE == FAST_SERV:
            self.fast_serv()   
        elif SRV_SIDE_SCHEDULE == DEADLINE_SERV:
            self.deadline_pure_serv()
        elif SRV_SIDE_SCHEDULE == DEADLINE_FAST_SERV:
            self.deadline_hybrid_serv()
        else:
            self.best_effort_serv()

    def avg_send_queue_len(self):
        if len(self.m_nbrs) == 0:
            return 0
        total_len = 0
        for n in self.m_nbrs:
            total_len += len(n.send_queue)
        return float(total_len) / len(self.m_nbrs)

    def total_send_queue_len(self):
        total_len = 0
        for n in self.m_nbrs:
            total_len += len(n.send_queue)
        return total_len

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

    def avg_response_time(self):
        resp_time_sum = 0
        resp_pkt_cnt = 0
        for i in range(BUF_CAP):
            if self.m_buffer[i].m_response_time > 0:
                resp_time_sum += self.m_buffer[i].m_response_time
                resp_pkt_cnt += 1
        if resp_pkt_cnt > 0:
            return float(resp_time_sum) / resp_pkt_cnt
        else:
            return  -1

    def send_pkt(self, packet):
        #TODO: delay Matrix
        if self.m_peer_id == SAMPLE_ID and DETAIL == 1:
            print "%d send packet to %d, type: %d. "%\
                (SAMPLE_ID, packet.m_dest_peer.m_peer_id, packet.m_type)

        matrix_delay = self.m_topology.latency_matrix[self.m_peer_id]\
            [packet.m_dest_peer.m_peer_id]
        time = self.m_engine.m_current_time + matrix_delay
                
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

            self.m_recved += 1
            self.m_cycle_recved += 1
            for n in self.m_nbrs:
                if n.m_peer == packet.m_src_peer:
                    n.cycle_recved += 1
                    break

            if APP == FILE_SHARING:
                self.m_file_cache[packet.m_seq].m_state = 2
            else:
                self.m_recved += 1
                self.buffer_finish()
                buf_idx = packet.m_seq % BUF_CAP
                self.m_buffer[buf_idx].m_seq = packet.m_seq
                self.m_buffer[buf_idx].m_state = 2
                self.m_buffer[buf_idx].m_response_time =\
                        self.m_engine.m_current_time - \
                        self.m_buffer[buf_idx].m_req_time

                global SAMPLE_SEQ_TIME, SAMPLE_SEQ_PEERS,\
                        SAMPLE_SEQ_RATIO 
                if SAMPLE_SEQ_TIME == 0:
                    if packet.m_seq == SAMPLE_SEQ:
                        SAMPLE_SEQ_PEERS += 1
                        if (float(SAMPLE_SEQ_PEERS) / \
                                len(self.m_topology.online_peers)) >= \
                                SAMPLE_SEQ_RATIO:
                            SAMPLE_SEQ_TIME = self.m_engine.m_current_time

            del packet

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
                self.m_nbrs[nbr_idx].send_queue = \
                        sorted(self.m_nbrs[nbr_idx].send_queue)
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

    def random_latency_matrix(self):
        if FLASH_CROWD:
            peer_count = NODE_CNT + FLASH_CNT + 1
        else:
            peer_count = NODE_CNT + 1

        for k in range(peer_count):
            self.latency_matrix.append([])
            for n in range(peer_count):
                if n == k:
                    self.latency_matrix[k].append(0)
                else:
                    self.latency_matrix[k].append(\
                        random.randrange(MAX_DELAY))

    def load_latency_matrix(self,filename):
        """ load latency matrix from filename into matrix """
        self.random_latency_matrix()

        if FLASH_CROWD:
            max_peer_id = NODE_CNT + FLASH_CNT
        else:
            max_peer_id = NODE_CNT

        f = open(filename,'r')
        while 1:
            s = f.readline()
            fields = s.split()
            peer1 = int(fields[0])
            peer2 = int(fields[1])
            latency = int(float(fields[2])/2000)
            
            if peer1 > max_peer_id:
                break
            if peer2 <= max_peer_id:
                self.latency_matrix[peer1][peer2] = latency
                self.latency_matrix[peer2][peer1] = latency

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
        if FLASH_CROWD:
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

    def avg_late(self):
        started = 0
        total_late = 0
        for p in self.m_topo.online_peers:
            if p.m_peer_id != 0 and p.m_buffering == False:
                started += 1
                total_late += p.m_late
        if started > 0:
            return int( float(total_late) / started )
        else:
            return 0

    def avg_resp_time(self):
        avg_resp_time_sum = 0
        valid_peer_cnt = 0
        for p in self.m_topo.online_peers:
            if p.avg_response_time() > 0:
                avg_resp_time_sum += p.avg_response_time()
                valid_peer_cnt += 1

        if valid_peer_cnt > 0:
            return avg_resp_time_sum / valid_peer_cnt
        else:
            return 0

    def avg_throughput(self):
        throughput = 0
        for p in self.m_topo.online_peers:
            throughput += p.m_recved
        return int( float(throughput) / \
                len(self.m_topo.online_peers))

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

    def load_balance(self):
        """ stat deviation of load """
        if len(self.m_topo.online_peers) < 2:
            return 0

        avg_sent = 0
        for p in self.m_topo.online_peers:
            avg_sent += p.m_sent
        avg_sent = float(avg_sent)/len(self.m_topo.online_peers)

        deviation = 0
        for p in self.m_topo.online_peers:
            deviation += (p.m_sent - avg_sent) ** 2
        deviation = float(deviation) /\
                (len(self.m_topo.online_peers) - 1)

        return deviation

    def runtime_print(self, engine):
        if APP == STREAMING:
            print "%d\t%.3f\t%.3f\t%d\t%d\t%.3f\t%.2f" %\
                (engine.m_current_time / 1000, \
                self.rejected_ratio(), self.avg_quality(),\
                self.avg_late(), self.avg_throughput(),\
                self.load_balance(), self.avg_resp_time())
            self.m_file.write(
                    "%d\t%.3f\t%.3f\t%d\t%d\t%.3f\t%.2f\n" %\
                (engine.m_current_time / 1000, \
                self.rejected_ratio(), self.avg_quality(),\
                self.avg_late(), self.avg_throughput(),\
                self.load_balance(), self.avg_resp_time() ) )

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
        fp.write('SAMPLE_SEQ:%d, SAMPLE_SEQ_TIME:%d\n\n' % \
                (SAMPLE_SEQ, SAMPLE_SEQ_TIME))

        fp.write('0\t0.00\n')
        for v in range(0, max_delay/1000 + 1):
            fp.write('%d\t%.2f\n' % (v+1, float(points[v])/\
                    len(self.m_topo.online_peers)) )
        fp.close()

#################################################################

topology = UnderTopo()
engine = EventEngine(topology)
print "wait please! loading data ..."
topology.schedule_all_peers(engine)
if USE_DELAY_MATRIX:
    topology.load_latency_matrix(MATRIX_FILE)
else:
    topology.random_latency_matrix()
print "simulation start ..."

engine.run(SIM_DURATION)
print "simulation finish at %d."%(engine.m_current_time)
# print "time cost: ", time.clock()

# vim: foldmethod=indent
