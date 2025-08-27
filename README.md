# Shell-Project
This repostiory contains a custom build Shell, written in C. It was made for the Alpine Linux Distribution. It was designed for easier manipulation of the file system 
including moving, copying, renaming and deleting of files. Functionalities that are not implemented can be accessed by entering the run-command together with the system call.

## Compilation of the Shell
The shell can be compiled with the makefile. By typing the command "make", the shell gets compiled if it is not already up to date.
An executable file named "shell.out" is created. The shell can be executed with the command "./shell.out".
## List of Commands
- show
- showdir
- showfiles
- rename <old_name> <new_name>
- delete
- delete <file_name>
- move
- move <old_path> <new_path>
- copy
- copy <old_path> <new_path>
- go
- run <system_call>
- help
- log
- exit
