# OSSimulation
Project done for CSCI340 Operating Systems. Simulates the movement of processes  done by an OS

Commands"
Initialize OS Simulation by entering RAM between 1 and 4,000,000,000, number of Hard Disks and Printers available
Number of HDD and Printers is between 0 and 10

A p m -to create a new process where p is priority 0-4, m is the amount of memory the process takes
example: A 4 10000

t -terminates process in CPU, next process with highest priority uses the CPU

d h -current process in CPU enters the HDD Queue number h
example: d 9

p p -current process in CPU enters the Printer Queue number p
example: p 9

D h -current process in HDD h finishes the current process which re-enteres CPU
example: D 8

P p -current process in Printer p finishes the current process which re-enters CPU
example: P 8

S r -Shows the process in the CPU queues and the order in which they will enter the CPU
S i -Shows the process in the HDD and Printers queues
S m -Shows which processes are using which block of memory
