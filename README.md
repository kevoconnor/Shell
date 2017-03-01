# COS421 Shell Implementation
Operating Systems

Revised by Kevin O'Connor on February 28, 2017

Simple shell implementation written in C to understand processes; uses different system calls such as fork( ), execve( ), waitpid( ), chdir( ), getcwd( ), getenv( ), open( ), and sigaction( ).

Built-in commands:
--------------------------------
Support for simple commands like cd ( wrapper for chdir( ) ), pwd ( wrapper for getcwd( ) ), version, and exit.

Commands with relative paths:
--------------------------------
Attempts each possible command path using the PATH environment variable.
Example: 'ls' input will try /bin/ls, /usr/bin/ls, /usr/local/bin/ls, etc until it finds a valid path to execute.

Commands with arguments:
--------------------------------
Program will split input by spaces and create an array of pointers, 'argv[ ]', which is used to pass into execve( ).

Background commands:
--------------------------------
When a '&' is the last argument given, the shell looks for another command to process, while pushing the previous one into the background.
The sigaction( ) system call is used so that when the operating system sees that a child process has completed it sends the SIGCHLD signal alerting the program where the process is reaped properly.

Input/output redirection:
--------------------------------
The program recognizes a '<' or '>' character in the input to redirect the input/output. 
* Currently works when only one '<' or '>' is given; piping is not supported either.


A lot of the code can be refactored, currently everything is basically in one large function in a while loop and would become much easier to work with if it were more modular and separated into individual functions for larger portions of code such as parsing the input (and to help support file I/O and piping).
