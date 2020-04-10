# Overview

Minishell is the first 42 shell project, we had to build the minimum viable version of a shell, including a prompt waiting for user input, signal handling, command execution from $PATH or from an absolute path.. (more details in [the subject](https://gitlab.com/Bccyv/minishell/-/blob/master/subject.pdf)).

As good students, we did a little bit more:
- Key shortcuts for command line editing
- Command history
- Autocompletion
- Wildcards
- Dynamic git prompt
- 'Assistant' builtin that brings you coffe (Ok, maybe not)

## Shortcuts

 - `ctrl-u` erase command
 - `ctrl-k` erase command after cursor
 - `ctrl-h` erase command before cursor
 - `ctrl-p` scroll up  history
 - `ctrl-n` scroll down history
 - `❮ / ❯` move cursor left / right
 - `optn + ❮ / ❯` move cursor left / right word by word
 - `fn +  ❮ / ❯` move cursor at the beginning / end of the line
 - 

# Installation & execution

    git clone https://gitlab.com/bccyv/minishell
    cd minishell
    make
    ./minishell

