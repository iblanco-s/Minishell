
# Minishell

42 project, creating our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

![Logo](https://github.com/iblanco-s/Minishell/blob/master/inc/minishell.gif)

## Content
### Built-ins

- echo with the -n option
- cd with relative or absolute paths  
- pwd without options
- export without options
- unset without options
- env without options or arguments
- exit without options

### Parsing

The parser in my Minishell project can handle:

- Single quotes (')
- Double quotes (")
- Expansion of environment variables ($) followed by characters.
- $? that expands to the exit status of the most recently executed foreground pipeline.

### Pipes and Redirection

- Implemented pipes (|) .
- Implemented redirection:
  - < redirects input.
  - > redirects output.
  - "<<" receives a delimiter.
  - ">>" redirects output in append mode.

### Signals

- Managed ctrl-C, ctrl-D, and ctrl-\ to function as in bash.
  - In interactive mode:
    - ctrl-C prints a new prompt on a new line.
    - ctrl-D terminates the shell.
    - ctrl-\ does nothing.

## Installation

To install and run the Minishell project:

```bash
  make
  ./minishell
```
