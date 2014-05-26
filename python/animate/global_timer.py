import time

class GlobalTimer(object):
    def __init__(self, sleep_second):
        self.register_list = []
        self.current_frame_id = 0
        self.sleep_time = sleep_second

    def run(self):
        while True:
            print('year: {0}'.format(2000 + self.current_frame_id))

            for o in self.register_list:
                o.on_timer(self)
            time.sleep(self.sleep_time)
            self.current_frame_id += 1

            if len(self.register_list) == 0:
                break
