
from animate_object import AnimateObject
from global_timer import GlobalTimer

class Role1(AnimateObject):
    def __init__(self, age):
        self.age = age
        AnimateObject.__init__(self)

    def update_age(self):
        self.age += 1
        print('Role1: Now, I\'m {0} years old.'.format(self.age))

class Role2(AnimateObject):
    def __init__(self, year):
        self.year = year
        AnimateObject.__init__(self)

    def say_something(self):
        self.year += 1
        print('Role2: I have practiced painting for {0} years.'.format(self.year))

gt = GlobalTimer(0.2)
r1 = Role1(15)
r1.register(gt, 30, r1.update_age, 3)

r2 = Role2(5)
r2.register(gt, 40, r2.say_something, 4)

gt.run()
