
class Computer(object):
    class Monitor(object):
        def __init__(self, x, y, logo):
            self.scr_x = x
            self.scr_y = y
            self.logo = logo

    def __init__(self, x, y, logo):
        # although in the class, you need use 'Computer.Monitor' to access Monitor
        self.monitor = Computer.Monitor(x, y, logo)

c = Computer(1024, 768, 'lenovo')
print c.monitor.scr_x, c.monitor.scr_y

m = Computer.Monitor(640, 480, 'KOEI')
print m.scr_x, m.scr_y, m.logo
