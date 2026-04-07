#!/bin/bash

# MINISHELL TESTING GUIDE

## PROGRAM BUILD & RUN

### 1. Clean Build
```bash
cd /Users/khairallahmawla/Desktop/kousa
make clean && make
```

### 2. Run Interactive Shell
```bash
./minishell
```

You should see the prompt:
```
minishell$
```

---

## COMPREHENSIVE TEST CASES

### CATEGORY 1: BASIC COMMANDS

```bash
minishell$ echo hello world
# Expected: prints "hello world"

minishell$ pwd
# Expected: prints current directory

minishell$ whoami
# Expected: prints current user (external command)
```

---

### CATEGORY 2: QUOTE HANDLING

```bash
# Single quotes - NO variable expansion
minishell$ echo 'hello $USER'
# Expected: hello $USER (literal dollar sign)

# Double quotes - WITH variable expansion
minishell$ echo "hello $USER"
# Expected: hello [your_username]

# Mixed quotes
minishell$ echo 'single' "double" plain
# Expected: single double plain

# Empty strings
minishell$ echo ""
# Expected: newline only

minishell$ echo ''
# Expected: newline only
```

---

### CATEGORY 3: VARIABLE EXPANSION

```bash
# Existing variable
minishell$ echo $USER
# Expected: [your_username]

# Non-existent variable (should expand to empty)
minishell$ echo $NONEXISTENT
# Expected: (empty line)

# Exit status (should be 0 from echo)
minishell$ echo test && echo $?
# Expected: test
#           0

# Exit status from failed command
minishell$ nonexistent_cmd
# Expected: error message

minishell$ echo $?
# Expected: non-zero exit code (127 or similar)
```

---

### CATEGORY 4: OUTPUT REDIRECTION

```bash
# Redirect output to file
minishell$ echo "test content" > /tmp/testfile.txt
minishell$ cat /tmp/testfile.txt
# Expected: test content

# Append to file
minishell$ echo "more content" >> /tmp/testfile.txt
minishell$ cat /tmp/testfile.txt
# Expected: test content
#           more content

# Overwrite vs append
minishell$ echo "overwrite" > /tmp/testfile.txt
minishell$ cat /tmp/testfile.txt
# Expected: overwrite (no "more content")
```

---

### CATEGORY 5: INPUT REDIRECTION

```bash
# Create test file first
minishell$ echo "file contents" > /tmp/input.txt

# Read from file
minishell$ cat < /tmp/input.txt
# Expected: file contents

# With redirection in middle of command
minishell$ wc -l < /tmp/input.txt
# Expected: 1 (one line in file)
```

---

### CATEGORY 6: HEREDOC

```bash
# Heredoc syntax
minishell$ cat << EOF
> Hello from heredoc
> Line 2
> EOF
# Expected: Hello from heredoc
#           Line 2

# Heredoc with variable expansion
minishell$ cat << END
> User: $USER
> END
# Expected: User: [your_username]

# Note: Heredoc can span multiple lines
# Type: cat << DELIMITER
# Then type content line by line
# Then type DELIMITER on a line by itself
```

---

### CATEGORY 7: PIPES

```bash
# Simple pipe
minishell$ ls | wc -l
# Expected: number of files/folders in current directory

# Multiple pipes
minishell$ ls | grep test | wc -l
# Expected: count of items with "test" in name

# Pipe with builtin and external
minishell$ echo "hello" | cat
# Expected: hello

# Different pipe combinations
minishell$ echo -e "line1\nline2\nline3" | grep line2
# Expected: line2
```

---

### CATEGORY 8: BUILT-IN: echo

```bash
# Basic echo
minishell$ echo hello
# Expected: hello

# Echo with -n (no newline)
minishell$ echo -n hello
# Expected: hello (no newline, cursor stays on same line)

# Multiple arguments
minishell$ echo hello world test
# Expected: hello world test

# Echo with variables
minishell$ echo $USER is here
# Expected: [username] is here

# Echo with redirections
minishell$ echo "test" > /tmp/echo_test.txt
minishell$ cat /tmp/echo_test.txt
# Expected: test
```

---

### CATEGORY 9: BUILT-IN: cd

```bash
# Change to absolute path
minishell$ cd /tmp
minishell$ pwd
# Expected: /tmp

# Change to relative path
minishell$ cd ..
minishell$ pwd
# Expected: parent directory of /tmp

# Without arguments (goes to home, if implemented)
minishell$ cd
minishell$ pwd
# Expected: home directory (or error if not supported)

# Invalid path (should stay in current directory)
minishell$ cd /nonexistent
# Expected: error message
minishell$ pwd
# Expected: current directory unchanged
```

---

### CATEGORY 10: BUILT-IN: pwd

```bash
# Print working directory
minishell$ pwd
# Expected: absolute path to current directory

# After changing directory
minishell$ cd /tmp
minishell$ pwd
# Expected: /tmp
```

---

### CATEGORY 11: BUILT-IN: export

```bash
# Set variable
minishell$ export MYVAR=myvalue
minishell$ echo $MYVAR
# Expected: myvalue

# Export multiple times
minishell$ export VAR1=value1
minishell$ export VAR2=value2
minishell$ echo $VAR1 $VAR2
# Expected: value1 value2

# Verify in subshell (pipe to external command)
minishell$ export TESTVAR=hello
minishell$ bash -c 'echo $TESTVAR'
# Expected: hello (if properly exported)
```

---

### CATEGORY 12: BUILT-IN: unset

```bash
# Unset a variable
minishell$ export TEMP=value
minishell$ echo $TEMP
# Expected: value

minishell$ unset TEMP
minishell$ echo $TEMP
# Expected: (empty)

# Unset non-existent variable (should not error)
minishell$ unset NONEXISTENT
# Expected: no error
```

---

### CATEGORY 13: BUILT-IN: env

```bash
# Print all environment variables
minishell$ env
# Expected: list of all environment variables (PATH, USER, HOME, etc.)

# Pipe to grep to verify
minishell$ env | grep USER
# Expected: USER=[your_username]

# Verify exported variables appear
minishell$ export CUSTOM=test
minishell$ env | grep CUSTOM
# Expected: CUSTOM=test
```

---

### CATEGORY 14: BUILT-IN: exit

```bash
# Exit with default status (0)
minishell$ exit
# Expected: shell exits, returns to regular shell prompt

# Exit with specific status
minishell$ exit 42
# Expected: shell exits with status 42
```

---

### CATEGORY 15: SIGNAL HANDLING

```bash
# Ctrl+C (SIGINT)
minishell$ 
# (Type something, then press Ctrl+C)
# Expected: ^C
#           minishell$ (new prompt on new line)

# Ctrl+D (EOF)
minishell$ 
# (Press Ctrl+D)
# Expected: shell exits gracefully

# Ctrl+\ (SIGQUIT)
minishell$
# (Press Ctrl+\ )
# Expected: nothing happens, shell continues
```

---

### CATEGORY 16: COMPLEX COMBINATIONS

```bash
# Variable + Redirection + Pipe
minishell$ export PREFIX="TEST"
minishell$ echo "$PREFIX: $(date)" | cat > /tmp/complex.txt
minishell$ cat /tmp/complex.txt
# Expected: TEST: [current date]

# Pipe + Redirection + Variable Expansion
minishell$ ls /tmp | grep test > /tmp/result.txt
minishell$ cat /tmp/result.txt
# Expected: matching files

# Heredoc + Variable + Pipe
minishell$ cat << EOF | grep USER
> USER=$USER
> HOME=$HOME
> EOF
# Expected: USER=[username]

# Multiple redirections (if supported)
minishell$ cat < /tmp/input.txt > /tmp/output.txt
minishell$ diff /tmp/input.txt /tmp/output.txt
# Expected: no difference (files are same)
```

---

### CATEGORY 17: ERROR HANDLING

```bash
# Unclosed quote (should reject)
minishell$ echo "hello
> 
# Expected: error about unclosed quote OR cursor waiting for close

# Invalid operator combination (if applicable)
minishell$ echo > > test
# Expected: error about invalid syntax

# Non-existent command
minishell$ nonexistent_command
# Expected: command not found error, exit status nonzero

# Check exit status after error
minishell$ nonexistent_command
minishell$ echo $?
# Expected: non-zero (127 or similar)
```

---

## QUICK VALIDATION CHECKLIST

Run these to quickly verify major features:

```bash
# 1. Quotes & Variables
echo 'no $expand' && echo "yes $expand" && echo $USER

# 2. Pipes
ls | grep minishell

# 3. Redirections
echo "test" > /tmp/test.txt && cat < /tmp/test.txt

# 4. Exit Status
ls /nonexistent; echo $?

# 5. All Builtins
cd /tmp && pwd && echo "test" >> /tmp/test.txt && env | head -3 && exit 0
```

---

## EXPECTED OUTPUT STRUCTURE

The program should show:
```
minishell$ [command]
[output]
minishell$ [next command]
```

---

## NOTES

- The readline library provides command history (up/down arrows)
- Ctrl+C behavior: Shows ^C, then new prompt
- Ctrl+D behavior: Cleanly exits the shell
- Variable expansion happens during parsing, before execution
- Single quotes prevent ALL interpretation
- Double quotes allow $ expansion only
- Heredoc doesn't update history (as per requirements)

