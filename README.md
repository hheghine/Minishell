# Minishell
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

## What Is Bash and How Does It Work?

The shell is a program that the user can use to interact with an operating system's services. [Bash](https://www.gnu.org/software/bash/manual/bash.html) is the GNU shell, and is currently the most common shell program. We took the challenge of recreating bash very literally, so the first thing we did was learn [how bash actually works](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf). Essentially it breaks down the process into 4 steps: `lexer` → `parser` → `expander` → `executor`.
