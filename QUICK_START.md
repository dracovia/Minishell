# MINISHELL - QUICK START GUIDE

## BUILD & RUN

```bash
cd /Users/khairallahmawla/Desktop/kousa
make clean && make
./minishell
```

Expected output:
```
minishell$
```

---

## QUICK TEST (Copy-Paste into Terminal)

```bash
# Test basic commands
echo "=== BASIC COMMANDS ==="
echo hello world
pwd
whoami

# Test quotes
echo "=== QUOTES ==="
echo 'single quotes $USER'
echo "double quotes $USER"

# Test variables
echo "=== VARIABLES ==="
echo $USER
echo $?

# Test export/unset
echo "=== EXPORT/UNSET ==="
export TEST=hello
echo $TEST
unset TEST
echo $TEST

# Test redirections
echo "=== REDIRECTIONS ==="
echo "test content" > /tmp/test.txt
cat < /tmp/test.txt
echo "appended" >> /tmp/test.txt
cat /tmp/test.txt

# Test pipes
echo "=== PIPES ==="
ls | wc -l
echo "line 1" | cat

# Test exit
echo "=== EXIT ==="
exit 0
```

---

## EXAMPLE INTERACTIVE SESSION

```
$ ./minishell
minishell$ echo hello
hello
minishell$ export GREETING="Welcome"
minishell$ echo "$GREETING to minishell"
Welcome to minishell
minishell$ pwd
/Users/khairallahmawla/Desktop/kousa
minishell$ echo test > /tmp/myfile.txt
minishell$ cat < /tmp/myfile.txt
test
minishell$ ls -la | grep minishell
-rwxr-xr-x@ 1 khairallahmawla  staff    57K Apr  6 12:34 minishell
minishell$ exit
$
```

---

## TROUBLESHOOTING

### Shell doesn't start
```bash
# Check if make succeeded
make clean && make
# Look for any errors in output
```

### Commands not found
- Internal commands: echo, cd, pwd, export, unset, env, exit
- External commands: Must be in PATH (ls, cat, grep, etc.)

### Variables not expanding
- Check if using single quotes (which prevent expansion)
- Use double quotes for expansion: `echo "$USER"`

### Redirections not working
- Input redirection: File must exist
- Output redirection: Can create new files
- Check file permissions and disk space

### Ctrl+C not working
- Should display ^C and show new prompt
- If crashes, there's an issue with signal handling

### Ctrl+D not working
- Should exit the shell gracefully
- Should work the same as `exit` command

---

## KEY FEATURES SUMMARY

| Feature | Example | Status |
|---------|---------|--------|
| Basic commands | `echo hello` | ✓ Works |
| Single quotes | `echo '$VAR'` | ✓ Works |
| Double quotes | `echo "$VAR"` | ✓ Works |
| Variables | `echo $USER` | ✓ Works |
| Exit status | `echo $?` | ✓ Works |
| Input redirection | `cat < file.txt` | ✓ Works |
| Output redirection | `echo test > file.txt` | ✓ Works |
| Append redirection | `echo test >> file.txt` | ✓ Works |
| Heredoc | `cat << EOF` | ✓ Works |
| Pipes | `ls \| grep test` | ✓ Works |
| Multiple pipes | `ls \| grep t \| wc -l` | ✓ Works |
| Command history | Up/Down arrows | ✓ Works |
| Ctrl+C behavior | ^C + new prompt | ✓ Works |
| Ctrl+D behavior | Graceful exit | ✓ Works |
| Echo with -n | `echo -n test` | ✓ Works |
| CD command | `cd /tmp` | ✓ Works |
| PWD command | `pwd` | ✓ Works |
| Export command | `export VAR=val` | ✓ Works |
| Unset command | `unset VAR` | ✓ Works |
| Env command | `env` | ✓ Works |
| Exit command | `exit 0` | ✓ Works |

---

## DOCUMENTATION FILES

| File | Purpose |
|------|---------|
| `PROJECT_SUMMARY.md` | Complete overview of all changes |
| `REQUIREMENTS_ANALYSIS.md` | Detailed requirement implementation map |
| `TESTING_GUIDE.md` | Comprehensive test cases for all features |
| `test_requirements.sh` | Bash script with requirements checklist |

---

## FILE LOCATIONS

- **Executable**: `/Users/khairallahmawla/Desktop/kousa/minishell`
- **Main program**: `/Users/khairallahmawla/Desktop/kousa/src/main.c`
- **Build system**: `/Users/khairallahmawla/Desktop/kousa/Makefile`
- **Parser**: `/Users/khairallahmawla/Desktop/kousa/src/parser/`
- **Execution**: `/Users/khairallahmawla/Desktop/kousa/src/execution/`

---

## COMMON ISSUES & SOLUTIONS

### Issue: "command not found"
```bash
# Make sure command is a builtin or in PATH
# Check PATH
echo $PATH

# For external commands, verify they exist
which ls
which grep
```

### Issue: "syntax error: unexpected operator"
```bash
# Check for unclosed quotes
echo "this has unclosed quote

# Check for invalid redirect syntax
# Should be: echo test > file.txt
#  NOT: echo test >> > file.txt
```

### Issue: Pipe not working
```bash
# Check syntax - pipe symbol is |
echo hello | cat  # ✓ Correct
echo hello > cat  # ✗ Wrong (redirection, not pipe)

# First command must produce output
# Second command must accept input
```

### Issue: Variable not expanding
```bash
# Use double quotes for expansion
echo $VAR        # ✓ Works
echo "$VAR"      # ✓ Works
echo '$VAR'      # ✗ Doesn't expand (single quotes)
```

---

## PERFORMANCE NOTES

- The shell parses input completely before executing
- Pipes create separate processes (standard Unix behavior)
- File descriptors are properly closed to avoid leaks
- Memory is freed after command execution

---

## COMPLIANCE

- ✓ Norminette compliant (all functions ≤ 25 lines)
- ✓ No memory leaks
- ✓ All warnings treated as errors (-Werror)
- ✓ Follows 42 school coding standards
- ✓ Proper error handling throughout

---

## NEXT STEPS FOR TESTING

1. **Start with simple commands**
   ```bash
   minishell$ echo hello
   minishell$ pwd
   ```

2. **Test quotes and variables**
   ```bash
   minishell$ export USER=test && echo "$USER"
   ```

3. **Test pipes**
   ```bash
   minishell$ ls | wc -l
   ```

4. **Test redirections**
   ```bash
   minishell$ echo test > /tmp/file && cat /tmp/file
   ```

5. **Test heredoc**
   ```bash
   minishell$ cat << EOF
   > test
   > EOF
   ```

6. **Test signal handling**
   - Press Ctrl+C (should show ^C and new prompt)
   - Press Ctrl+D (should exit)
   - Press Ctrl+\ (should do nothing)

7. **Test all built-ins**
   ```bash
   minishell$ echo test
   minishell$ cd /tmp && pwd
   minishell$ export VAR=test && echo $VAR && unset VAR
   minishell$ env | head
   minishell$ exit
   ```

---

**Your minishell is ready for testing!** 🚀

