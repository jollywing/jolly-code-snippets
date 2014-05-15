
# customer is classfied into A group and B group
# B has priority to A
# If B group is not empty, invite a customer from B group
# customer for Personal business is queued into A group
# customer for Company business is queued into B group
# Open time: 9:00 - 17:00, 8 hours
# 9:00 - 11:30, 5 customers come per hour.
# 11:30 - 14:30, 2 customers come per hour.
# 14:30 - 17:00, 4 customers come per hour.
# service B ocuppies 15 - 30 minutes.
# service A ocuppies 5 - 15 minutes.
# A customers: B customers = 4: 1
# statics: 
# how many customers were served in a day?
# how many A customers and how many B customers.
# working time and idle time

import random

class CustomerType(object):
    def __init__(self, id, min_time, max_time):
        self.id = id
        self.min_time = min_time
        self.max_time = max_time

class Customer(object):
    def __init__(self, group, id, arrive_time):
        self.group = group
        self.id = id
        self.arrive_time = arrive_time
        self.wait_time = 0
        self.service_time = random.randint(self.group.min_time,
                                           self.group.max_time)

class Queue(object):
    def __init__(self):
        self.start_oclock = 9
        self.work_hours = 8
        self.group_type_a = CustomerType('A', 5, 15)
        self.group_type_b = CustomerType('B', 15, 30)
        self.group_a_counter = 0
        self.group_b_counter = 0
        self.come_per_hour = (5, # 9:00 - 10:00
                              5, # 10:00 - 11:00
                              3, # 11:00 - 12:00
                              2, # 12:00 - 13:00
                              2, # 13:00 - 14:00
                              3, # 14:00 - 15:00
                              4, # 15:00 - 16:00
                              4);# 16:00 - 17:00

        self.customers = []

    def create_customers(self):
        arrive_times = [];
        for i in range(self.work_hours):
            come_this_hour = random.randint(self.come_per_hour[i] - 1,
                                            self.come_per_hour[i] + 1);
            for j in range(come_this_hour):
                this_hour = self.start_oclock + i;
                time = random.randint(this_hour * 60, (this_hour + 1) * 60)
                arrive_times.append(time)

        arrive_times.sort();
        customer_count = len(arrive_times)
        for i in range(customer_count):
            self.new_customer(arrive_times[i])

    def new_customer(self, arrive_time):
        rand = random.randint(0, 100)
        customer = None
        if rand < 20:
            self.group_b_counter += 1
            customer = Customer(self.group_type_b,
                                self.group_b_counter, arrive_time)
        else:
            self.group_a_counter += 1
            customer = Customer(self.group_type_a,
                                self.group_a_counter, arrive_time)
        self.customers.append(customer)

class Agent(object):
    def __init__(self):
        self.time_clock = 540   # minutes from 00:00

        self.idle_time = 0
        self.busy_time = 0
        self.group_a_serv_time = 0
        self.group_b_serv_time = 0
        self.max_queue_length = 0
        self.served_count = 0
        self.group_a_counter = 0
        self.group_b_counter = 0

        self.global_queue = Queue()
        self.global_queue.create_customers()
        self.group_a = []
        self.group_b = []

    def fill_width_with_0(self, num, width):
        a = 10 ** (width - 1)
        fill_string = ""
        while a > 1:
            if num / a == 0:
                fill_string += "0"
                a /= 10
            else:
                break
        return "{}{}".format(fill_string, num)

    def time_string(self):
        # Python does not support such syntax!!
        # hour_string = current_hour < 10 ? "0" + current_hour: "" + current_hour

        hour_string = self.fill_width_with_0(self.time_clock / 60, 2)
        min_string = self.fill_width_with_0(self.time_clock % 60, 2)
        return "{}:{}".format(hour_string, min_string)

    def queue_customer(self, customer):
        if customer.group == self.global_queue.group_type_a:
            self.group_a.append(customer)
        else:
            self.group_b.append(customer)

    def serv_customer(self, customer):
        customer_id_string = self.fill_width_with_0(customer.id, 3)
        print("{}: {}{}, {} minutes".format(self.time_string(),
                                            customer.group.id,
                                            customer_id_string,
                                            customer.service_time))
        self.time_clock += customer.service_time
        self.busy_time += customer.service_time
        self.served_count += 1

    def next_customer(self):

        queue_length = len(self.group_a) + len(self.group_b)
        if self.max_queue_length < queue_length:
            self.max_queue_length = queue_length

        # if service queue is empty, advance the time clock
        if len(self.group_a) == 0 and len(self.group_b) == 0:
            if len(self.global_queue.customers) == 0:
                return
            else:
                customer = self.global_queue.customers[0]
                self.idle_time += customer.arrive_time - self.time_clock
                self.time_clock = customer.arrive_time
                self.queue_customer(customer)
                del self.global_queue.customers[0]

        if len(self.group_b) > 0:
            self.serv_customer(self.group_b[0])
            self.group_b_serv_time += self.group_b[0].service_time
            self.group_b_counter += 1
            del self.group_b[0]
        elif len(self.group_a) > 0:
            self.serv_customer(self.group_a[0])
            self.group_a_serv_time += self.group_a[0].service_time
            self.group_a_counter += 1
            del self.group_a[0]

        # queue the customers who arrived before current time
        while len(self.global_queue.customers) > 0:
            if self.global_queue.customers[0].arrive_time <= self.time_clock:
                self.queue_customer(self.global_queue.customers[0])
                del self.global_queue.customers[0]
            else:
                break
            

    def on_job(self):
        while len(self.group_a) > 0 or len(self.group_b) > 0 or \
              len(self.global_queue.customers) > 0:
            self.next_customer()

    def stat(self):
        print("\n------------------------------")
        print("Served Customers: {}".format(self.served_count))
        print("Type A Customers: {}".format(self.group_a_counter))
        print("Type B Customers: {}".format(self.group_b_counter))
        print("Type A Serve time: {} minutes, Average: {} minutes".format(
            self.group_a_serv_time, self.group_a_serv_time / self.group_a_counter))
        print("Type B Serve time: {} minutes, Average: {} minutes".format(
            self.group_b_serv_time, self.group_b_serv_time / self.group_b_counter))
        print("Max Queue Length: {}".format(self.max_queue_length))
        print("Busy time: {} minutes".format(self.busy_time))
        print("Idle time: {} minutes".format(self.idle_time))
        print("------------------------------\n")

a = Agent()
a.on_job()
a.stat()
