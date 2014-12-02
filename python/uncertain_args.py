# python 2
# multiple args
def get_avg(grade, *scores):
    sum_score = 0
    avg = 0
    for x in scores:
        sum_score += x

    if sum_score > 0:
        avg = float(sum_score) / len(scores)

    print 'Class %d: %f.' % (grade, avg)

get_avg(1, 100, 99, 98, 60, 44)

# multiple keywords args
def collect(**data):
    for x in data:
        print x, ':', data[x]

collect(dollar=8, name='Zhang', skill='shit')
