# Minishell

A Unix shell is a command-line interpreter or shell that provides a command line user interface for Unix-like operating systems. The shell is both an interactive command language and a scripting language, and is used by the operating system to control the execution of the system using shell scripts.<br><br>
This project is about creating a simple shell.

![Screenshot from 2023-11-07 23-34-49](https://github.com/hheghine/Minishell/assets/119530584/163fa9eb-86ad-4517-9e39-254745b2b970)

## What Is Bash and How Does It Work?

The shell is a program that that takes keyboard commands and passes them to the operating system to carry out. Almost all Linux distributions supply a shell program from the GNU Project called [Bash](https://www.gnu.org/software/bash/manual/bash.html). The name is an acronym for "Bourne-again shell," in reference to the fact that Bash is an enhanced replacement for "sh," the original Unix shell program written by Steve Bourne.

So [how bash actually works](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)? Essentially it breaks down the process into 4 steps: `lexer` → `parser` → `expander` → `executor`.

The general idea for this shell is reading a string of commands in a prompt using [readline](https://www.man7.org/linux/man-pages/man3/readline.3.html).

## The Challenge

- Follow the [shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html).
- Not use more than one global variable.
- Display a **promt** while waiting for a new commmand.
- Have a working **history**.
- Find and launch **executables** (using the PATH variable or an absolute path).
- Handle `'` (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle `"` (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
- Implement redirections such as:
  - `<` redirect input.
  - `>` redirect output.
  - `<<` heredoc (doesn't affect history).
  - `>>` redirect output in append mode.
- Implement `|` (pipes).
- Handle **environment variables**.
- Handle `$?`.
- `ctrl-C`, `ctrl-D`, and `ctrl-\` should behave like in bash.
- Recreate the following **builtins**:
  - `echo` with option `-n`.
  - `cd` with only a relative or absolute path.
  -  `pwd` (no flags).
  - `export` (no flags).
  - `unset` (no flags).
  - `env` (no flags or arguments).
  - `exit` (no flags).
---
## Visuals
### ANSI Escape Sequences: Colours
```
#!/bin/bash
#
#   This file echoes a bunch of color codes to the 
#   terminal to demonstrate what's available.  Each 
#   line is the color code of one forground color,
#   out of 17 (default + 16 escapes), followed by a 
#   test use of that color on all nine background 
#   colors (default + 8 escapes).
#

T='gYw'   # The test text

echo -e "\n                 40m     41m     42m     43m\
     44m     45m     46m     47m";

for FGs in '    m' '   1m' '  30m' '1;30m' '  31m' '1;31m' '  32m' \
           '1;32m' '  33m' '1;33m' '  34m' '1;34m' '  35m' '1;35m' \
           '  36m' '1;36m' '  37m' '1;37m';
  do FG=${FGs// /}
  echo -en " $FGs \033[$FG  $T  "
  for BG in 40m 41m 42m 43m 44m 45m 46m 47m;
    do echo -en "$EINS \033[$FG\033[$BG  $T  \033[0m";
  done
  echo;
done
echo
```
