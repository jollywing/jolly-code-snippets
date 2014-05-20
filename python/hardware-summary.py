
import os
from os import terminal_size

os_info = os.uname()
print('OS:', os_info.sysname)
print('Kernel Release:', os_info.release)
print('Machine:', os_info.machine)
print('HostName:', os_info.nodename)

f = open('/proc/cpuinfo')

cores = 0
thread_count = 0
model_name = 'unknown'

while True:
    line = f.readline()
    if len(line) == 0:
        break
    if line.startswith('processor'):
        thread_count += 1
    elif line.startswith('model name'):
        temp = line.partition(':')
        model_name = temp[2].strip()
    elif line.startswith('cpu cores'):
        temp = line.partition(':')
        cores = int(temp[2].strip())
        
f.close()

print('CPU INFO:')
print('  MODEL NAME:', model_name)
print('  {0} cores'.format(cores))
print('  {0} threads'.format(thread_count))

f = open('/proc/meminfo')
mem_total = 0
mem_used = 0
while True:
    if mem_total > 0 and mem_used > 0:
        break
    line = f.readline()
    if len(line) == 0:
        break

    if line.startswith('MemTotal'):
        temp = line.partition(':')
        temp = temp[2].strip().partition(' ')
        mem_total = int(temp[0]) / 1024
    elif line.startswith('MemFree'):
        temp = line.partition(':')
        temp = temp[2].strip().partition(' ')
        mem_used = int(temp[0]) / 1024

print('MEMORY INFO:')
print('  TOTAL: {0:.2}G'.format(mem_total))
print('  USED: {0:.2}G'.format(mem_used))
