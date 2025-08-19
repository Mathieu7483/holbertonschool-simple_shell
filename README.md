# holbertonschool-simple_shell
create a simple shell
<img src= "https://github.com/Mathieu7483/holbertonschool-simple_shell/blob/Mathieu/img/image%20readme%20pour%20simple%20shell.png">

# 📚 holbertonschool-simple_shell
Welcome to my holbertonschool-simple_shell repository! This directory marks the beginning of my intensive journey into learning the C programming language, with a strong focus on low-level programming. It compiles the exercises completed as part of my training, centered around building a simple shell in collaboration with two fellow students: Mathis and Heytem.

Through these projects, my goal is to develop a deep understanding of how programs work "under the hood"—exploring memory management, compilation processes, and direct interactions with the operating system.

# 📚 Table of Contents

# 💡 Project Context
This project is part of the Holberton School programming curriculum. It focuses on creating a custom simple shell, how it works , and how to use it.

# 📖 Learned Resources
At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

General
Who designed and implemented the original Unix operating system
Who wrote the first version of the UNIX shell
Who invented the B programming language (the direct predecessor to the C programming language)
Who is Ken Thompson
How does a shell work
What is a pid and a ppid
How to manipulate the environment of the current process
What is the difference between a function and a system call
How to create processes
What are the three prototypes of main
How does the shell use the PATH to find the programs
How to execute another program with the execve system call
How to suspend the execution of a process until one of its children terminates
What is EOF / “end-of-file”?

# ✅ General Requirements
General
Allowed editors: vi, vim, emacs
All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All your files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Your shell should not have any memory leaks
No more than 5 functions per file
All your header files should be include guarded
Use system calls only when you need to (why?)
GitHub
There should be one project repository per group. If you clone/fork/whatever a project repository with the same name before the second deadline, you risk a 0% score.

More Info
Output
Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)
Example of error with sh:
```bash
julien@ubuntu:/# echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
julien@ubuntu:/# echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
Same error with your program hsh:
```
```bash
julien@ubuntu:/# echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
julien@ubuntu:/# echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
```

List of allowed functions and system calls+
all functions from string.h
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- printf (man 3 printf)
- fprintf (man 3 fprintf)
- vfprintf (man 3 vfprintf)
- sprintf (man 3 sprintf)
- putchar (man 3 putchar)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

Compilation
Your shell will be compiled this way:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
Testing
Your shell should work like this in interactive mode:
```bash
julien@ubuntu:/# ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
julien@ubuntu:/#
```
But also in non-interactive mode:
```bash
julien@ubuntu:/# echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
julien@ubuntu:/# cat test_ls_2
/bin/ls
/bin/ls
julien@ubuntu:/# cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
julien@ubuntu:/#
```

# 💻 Usage
## Installation :
```bash
git clone https://github.com/username/repositoryname.git
```
you can add it to your personnal repository and username.

To access the manpage:
```bash
~/Holberton/holbertonschool-simple_shell$man ./man_1_simple_shell
```
# ⚙️ Compilation
The files in this project are compiled using gcc with the following options:

```bash

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
To check for memory leaks, use:

```bash
valgrind --leak-check=full ./simple_shell
```

after compilation, you can directly use the simple shell
```bash
for example : 
hsh ls

output:
AUTHORS  README.md  functions.c  hsh  img  man_1_simple_shell  shell_v0.1.c  shell_v0.3.c  shell_v0.4.c  simple_shell.h
```

# 📊 Flowchart et Snippets
## Flowchart

## Snippets

# 📋 Project Structure and Tasks
## *The project is organized around the progressive implementation of the simple shell and its functionalities.*

### Tasks
This project was developed incrementally, with new features added at each stage:

0. Initialization
The README.md, man_1_simple_shell, and AUTHORS files were created to document the project and list all contributors.

1. Betty Would Be Proud
The entire source code adheres to the Betty coding style, ensuring clean and readable code.

2. Simple Shell 0.1
A basic UNIX command-line interpreter was implemented.

The shell displays a prompt and executes simple, single-word commands without arguments.

It handles the end-of-file condition (Ctrl+D) and execution errors.

3. Simple Shell 0.2
The shell was improved to handle command lines with arguments.

4. Simple Shell 0.3
The shell can now find executables located in the directories specified by the PATH environment variable.

It checks if a command exists before calling fork.

5. Simple Shell 0.4
The exit built-in was implemented, allowing for a clean exit from the shell.

6. Simple Shell 1.0
The env built-in was added, which prints the current environment.



# ✍️ [Authors](https://github.com/Mathieu7483/holbertonschool-simple_shell/blob/Mathieu/AUTHORS)
[Mathis ROY](https://github.com/rpokman), [Heytem KEDDOUS](https://github.com/h7k2), [Mathieu GODALIER](https://github.com/Mathieu7483) — Students in programming at Holberton School