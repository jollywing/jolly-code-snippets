import commands

while True:
    print """Input shell command, and press enter.
    If you want to exit, input 'q' and press enter."""
    command = raw_input("$ ")
    if command == "q":
        break

    result = commands.getstatusoutput(command)
    print "OUTPUT: ", result[1]
    print "STATUS: ", result[0]
    print "========================="
