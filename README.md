# Minishell — Parser Prototype

An early C prototype for the 42 Minishell project, focused on reading and analyzing command-line input.

## What's included

- A GNU Readline prompt (`$>`) and command history.
- A custom tokenizer with quote and operator handling.
- Tokens stored in a doubly linked list.
- Lexer analysis and experimental syntax-tree structures.
- Supporting string and list utilities in [utils](utils).

## Current scope

This snapshot is a parsing experiment. In [main.c](main.c), syntax-tree construction and command execution are commented out. Entering a command does not execute it as a shell command. Environment-handling code is also experimental and is not enabled by the main loop.

## Requirements and build

Requires GCC, Make, and the GNU Readline development headers and library (`readline/readline.h`, `readline/history.h`, and `-lreadline`). On Debian/Ubuntu, the development package is named `libreadline-dev`.

```sh
make
./minishell
```

The Makefile enables `-Wall -Wextra -Werror`; compiler diagnostics may block this unfinished snapshot even after Readline is installed. The available cleanup targets are `clean`, `fclean`, and `re`.

## Exploring the prototype

Enter a line such as `echo hello | cat` at the prompt to exercise tokenization and analysis. This is parser input, not an executable pipeline. End-of-input and empty/whitespace input take the current loop's exit/error path.

See [shell_header.h](shell_header.h) for token types and syntax-tree definitions, and [utils/lexer_analyzer.c](utils/lexer_analyzer.c) for analysis logic.

## Concepts practiced

Lexical analysis, token classification, quote states, linked lists, syntax-tree design, interactive input, and memory ownership.
