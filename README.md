**simple_shell**
_by Josh and Phemmy_

Emulate the functionality of the linux shell

hsh.c
  │
  ├───── input.c
  │
  ├───── parser.c
  │
  ├───── search.c
  │
  └───── execute.c

* input.c
Handle input either from user in interactive mode or from a file or piped input
in non-interactive mode.

* parser.c
Handle special characters such as '*' that should not be intepreted as is.

* search.c
find out whether the command (first element in the array of command tokens) is
an existingand executable file.

* execute.c
create new process with fork and execute commands using execve.
