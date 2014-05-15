
# semicolon is not needed, but add it in the end of a statement won't harm.
i = 5;
print(i);

# However, If you put several statements in a single line,
# you need seperate the statements with semicolon!
i = i + 1; print(i)

# you also can write a statement in multiple lines by add backslash
# For example:

i = \
    i * i
print(i)

# However, if you break the line between ([{ and }]), 
# backslash is not needed.
print(i,
      i/2)
