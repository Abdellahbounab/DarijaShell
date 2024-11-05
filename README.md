# DarijaShell: A Darija-Friendly Shell

DarijaShell is a compact shell implemented in C from scratch, designed to mimic the functionality of Bash while incorporating a unique twist: the addition of Darija slang terms to simplify command usage. This project aims to provide a more intuitive and user-friendly shell experience for those familiar with the Moroccan Darija dialect.

## Features

Core Shell Functionality:
Execute system commands
Handle input/output redirection
Support background processes
Implement job control
Provide command history and editing
Darija Slang Integration:
Recognize and interpret Darija-based commands
Map slang terms to equivalent Bash commands
Provide a more natural and accessible user interface
In-Depth Exploration:
Dive into system calls for process management and file I/O
Analyze the tokenizer for parsing user input
Examine the execution of built-in commands
Explore advanced shell features and customization options

Standard Commands & Darija slang commands:

* ```chkonana``` = ```whoami```
* ```sir``` = ```cd```
* ```fin``` = ```pwd```
* ```ktb``` = ```echo```
* ```khrj``` = ```exit```
* ```hsb``` = ```wc```
* ```byn``` = ```cat```
* ```lhaj``` = ```sudo```
* ```9yd``` = ```export```
* ```jib```  = ```grep```
* and all other Standard commands...

## Technical Details

### System Calls:
fork, exec, wait, pipe, signal, etc.
### Tokenizer:
Lexical analysis to break input into tokens
Parsing tokens to understand command structure
### Built-in Commands:
Implementation of common shell commands like cd, pwd, exit, etc.
Customization and extension of built-in commands
Contributing

We welcome contributions to DarijaShell! If you're interested in improving the shell, feel free to fork the repository and submit pull requests.
