import pwd

print "All available users"
users = pwd.getpwall()

user_list = []

for u in users:
    user_list.append(u.pw_name)

print ", ".join(user_list)

u_name = raw_input("Input user name, check the details: ")

try:
    e = pwd.getpwnam(u_name)
    print "user name:", e.pw_name
    print "user id:", e.pw_uid
    print "group id:", e.pw_gid
    print "home dir:", e.pw_dir
    print "shell:", e.pw_shell
except KeyError:
    print u_name, "is not a valid user!!"
