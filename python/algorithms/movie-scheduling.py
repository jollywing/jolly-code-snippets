
#  _________      _____    _______________
#    YeWen3       Dance     ColdMountain  
#        ______________        ___________________
#         MidnightTrain          KillHitele       
#            _________
#             OhShit  

# You are a popular actor, you have a set of films to take part in.
# but some of them are time-overlapped,
# you need select a subset, without overlapped time, and with max interval.

#. tuple, index from 0
#. list, copy through slicing list
#. bool, True or False
#. function, define:
#. for loop
#. if statement
#. print string
#. logic: and, or, not
#. list.reverse(), help(list)

# Input a films list, return a sorted list
def sort_by_start(films):
    films_to_sort = films[:]
    for i in range(1, len(films_to_sort)):
        for j in range(i, 0, -1):
            if films_to_sort[j][0] < films_to_sort[j-1][0]:
                t = films_to_sort[j]
                films_to_sort[j] = films_to_sort[j-1]
                films_to_sort[j-1] = t
            else:
                break
    return films_to_sort

def earliest_job(films):
    jobs = []
    job_due = -1
    films_sorted = sort_by_start(films)

    for duration in films_sorted:
        if duration[0] > job_due:
            jobs.append(duration)
            job_due = duration[1]

    return jobs

# from large interval to little interval
def sort_by_interval(films):
    films_to_sort = films[:]
    for i in range(1, len(films_to_sort)):
        for j in range(i, 0, -1):
            interval = films_to_sort[j][1] - films_to_sort[j][0]
            prev_interval = films_to_sort[j-1][1] - films_to_sort[j-1][0]
            if prev_interval < interval:
                t = films_to_sort[j]
                films_to_sort[j] = films_to_sort[j-1]
                films_to_sort[j-1] = t
            else:
                break
    return films_to_sort

def conflict(job, jobs):
    for j in jobs:
        if job_conflict(j, job):
            return True

    return False

def longest_job(films):
    jobs = []
    job_due = -1                # the end time of previous job
    films_sorted = sort_by_interval(films)
    for job in films_sorted:
        if not conflict(job, jobs):
            jobs.append(job)
    return jobs

def shortest_job(films):
    jobs = []
    job_due = -1                # the end time of previous job
    films_sorted = sort_by_interval(films)
    films_sorted.reverse()      # from short to long
    for job in films_sorted:
        if not conflict(job, jobs):
            jobs.append(job)
    return jobs

def job_conflict(job1, job2):
    if (job1[1] - job1[0]) < (job2[1] - job2[0]):
        short_job = job1
        long_job = job2
    else:
        short_job = job2
        long_job = job1

    if (long_job[0] <= short_job[0] and short_job[0] <= long_job[1]) or\
       (long_job[0] <= short_job[1] and short_job[1] <= long_job[1]):
        return True
    return False

def optimal_scheduling(films):
    jobs = []
    films_input = films[:]

    while len(films_input) > 0:
        # find out the job ended earliest
        job_due = -1
        quick_end_job = None
        for job in films_input:
            if job_due < 0 or job[1] < job_due:
                job_due = job[1]
                quick_end_job = job

        jobs.append(quick_end_job)
        films_input.remove(quick_end_job)

        conflict_jobs = []
        for job in films_input:
            if job_conflict(quick_end_job, job):
                conflict_jobs.append(job)

        for job in conflict_jobs:
            films_input.remove(job)

    return jobs

# films = [(1, 7), (5, 14), (7, 13), (10, 14), (17, 25), (20, 31)]
films = [(5, 14), (1, 7), (17, 25), (7, 13), (10, 14), (20, 31)]
jobs = earliest_job(films)
print('scheduling earliest jobs, the result is {}.'.format(jobs))

jobs = longest_job(films)
print('scheduling longest jobs, the result is {}.'.format(jobs))

jobs = shortest_job(films)
print('scheduling shortest jobs, the result is {}.'.format(jobs))

jobs = optimal_scheduling(films)
print('scheduling optimal jobs, the result is {}.'.format(jobs))
