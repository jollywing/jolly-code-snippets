
class AnimateObject(object):
    ''' A instance who will act according to timer. '''

    def __init__(self):
        self.timer_on = False
        self.timer_func = None
        self.old_frame_id = 0
        self.expire_frame_id = 0
        self.update_frame_interval = 1

    def register(self, global_timer, duration, on_timer_func, update_interval = 1):
        self.old_frame_id = global_timer.current_frame_id
        self.expire_frame_id = self.old_frame_id + duration
        self.timer_func = on_timer_func
        self.update_frame_interval = update_interval

        if not self in global_timer.register_list:
            global_timer.register_list.append(self)

    def unregister(self, global_timer):
        if self in global_timer.register_list:
            i = global_timer.register_list.index(self)
            del global_timer.register_list[i]

    def on_timer(self, global_timer):
        if self.old_frame_id + self.update_frame_interval == \
           global_timer.current_frame_id:
            self.old_frame_id = global_timer.current_frame_id
            self.timer_func()

        if self.old_frame_id >= self.expire_frame_id:
            self.unregister(global_timer)
