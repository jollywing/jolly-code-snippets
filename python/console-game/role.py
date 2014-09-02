
class Role(object):
    def __init__(self, d):
        self.name = d['name']
        self.lvl = d['lvl']
        self.maxhp = d['maxhp']
        self.maxmp = d['maxmp']
        self.attack = d['attack']
        self.hp = self.maxhp
        self.mp = self.maxmp

    def status_str(self):
        max_len = 0
        name_str = u'{0}:({1})'.format(self.name, self.lvl)
        if len(name_str) > max_len:
            max_len = len(name_str)

        p = int(self.hp / self.maxhp * 10)
        hp_str = u'HP: {0}{1} ({2}/{3})'.format('+' * p, '-' * (10 - p), self.hp, self.maxhp)
        if len(hp_str) > max_len:
            max_len = len(hp_str)

        p = int(self.mp / self.maxmp * 10)
        mp_str = u'MP: {0}{1} ({2}/{3})'.format('+' * p, '-' * (10 - p), self.mp, self.maxmp)
        if len(mp_str) > max_len:
            max_len = len(mp_str)

        strs = []
        strs.append(u'.' * (max_len + 2))
        strs.append(u'|{0}{1}|'.format(name_str, ' ' * (max_len - len(name_str))))
        strs.append(u'|{0}{1}|'.format(hp_str, ' ' * (max_len - len(hp_str))))
        strs.append(u'|{0}{1}|'.format(mp_str, ' ' * (max_len - len(mp_str))))
        strs.append(u'.' * (max_len + 2))
        return strs

def print_roles_status(role_list):
    status = []
    for r in role_list:
        status.append(r.status_str())

    for i in range(0, 5):
        s = ''
        for strs in status:
            s += strs[i] + '\t'
        print(s)
