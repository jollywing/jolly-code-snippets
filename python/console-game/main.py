
def test_print_hero(r):
    r.status_str()

from roles import *
from role import Role, print_roles_status


r = Role(rTianBoGuang)
r2 = Role(rTianBoGuang)

rList = [r , r2]

print_roles_status(rList)
