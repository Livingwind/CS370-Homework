HW3: Christopher William Westerman

Checks to see if numbers are divisible by another number by calling other processes.
	When calling other processes, uses a pipe to feed the location of a previously
	declared shared memory segment and uses the later to share data between the
	Checker and Coordinator.

Coordinator.c:	Source code of the coordinator
Checker.c:	Source code of the checker
makefile:	Makefile to compile the previous.  Contains make all and make clean.
README.txt:	This file.

To test call:
	./Coordinator X Y1 Y2 Y3 Y4
	X = (int) Divisor
	Y = (int) Dividend
