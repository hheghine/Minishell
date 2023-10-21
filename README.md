# Minishell

![Starry](https://github.com/hheghine/Minishell/assets/119530584/cc74c604-ed69-4a13-816b-2308c44e2da0)

---
## What Is Bash and How Does It Work?

The shell is a program that the user can use to interact with an operating system's services. [Bash](https://www.gnu.org/software/bash/manual/bash.html) is the GNU shell, and is currently the most common shell program. We took the challenge of recreating bash very literally, so the first thing we did was learn [how bash actually works](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf). Essentially it breaks down the process into 4 steps: `lexer` → `parser` → `expander` → `executor`.

The general idea for this shell is reading a string of commands in a prompt using [readline](https://www.man7.org/linux/man-pages/man3/readline.3.html).

## The Challenge

- Display a promt while waiting for a new commmand.
- Have a working history.
- Find and launch executables (using the PATH variable or an absolute path).
- Handle `'` (single) and `"` (double) quotes like in bash.
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
