
#  *
# ***
#*****
#
def print_stars(line, max_stars):
    if line > max_stars:
        return 0,0
    max_line = max_stars
    middle_line = max_stars / 2
    space_num = abs((line - 1) - middle_line)
    star_num = (max_stars / 2 - space_num) *2 + 1
    print ' ' * space_num,
    print '*' * star_num
    return space_num, star_num


max_stars = 10
for i in range(0, 10):
    print_stars(i + 1, max_stars)
