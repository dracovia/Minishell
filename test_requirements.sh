#!/bin/bash

# Minishell Requirements Test Script
# Tests all required features against the specification

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

TESTS_PASSED=0
TESTS_FAILED=0
TESTS_UNKNOWN=0

test_feature() {
    local feature="$1"
    local status="$2"
    
    case "$status" in
        "PASS")
            echo -e "${GREEN}✓${NC} $feature"
            ((TESTS_PASSED++))
            ;;
        "FAIL")
            echo -e "${RED}✗${NC} $feature"
            ((TESTS_FAILED++))
            ;;
        "UNKNOWN")
            echo -e "${YELLOW}?${NC} $feature"
            ((TESTS_UNKNOWN++))
            ;;
    esac
}

echo "============================================"
echo "MINISHELL REQUIREMENTS CHECKLIST"
echo "============================================"

echo ""
echo "=== QUOTE HANDLING ==="
test_feature "Single quotes (prevent all interpretation)" "UNKNOWN"
test_feature "Double quotes (allow \$ expansion)" "UNKNOWN"
test_feature "Unclosed quotes error handling" "UNKNOWN"

echo ""
echo "=== REDIRECTIONS ==="
test_feature "< Input redirection" "UNKNOWN"
test_feature "> Output redirection" "UNKNOWN"
test_feature ">> Append mode redirection" "UNKNOWN"
test_feature "<< Heredoc with delimiter" "UNKNOWN"

echo ""
echo "=== PIPES ==="
test_feature "| Pipe operator (connect command output to input)" "UNKNOWN"
test_feature "Multiple pipes in sequence" "UNKNOWN"

echo ""
echo "=== EXPANSION ==="
test_feature "Environment variables (\$VAR)" "UNKNOWN"
test_feature "Exit status (\$?)" "UNKNOWN"
test_feature "Environment variable not found (empty)" "UNKNOWN"

echo ""
echo "=== SIGNAL HANDLING (Interactive Mode) ==="
test_feature "Ctrl+C displays new prompt on new line" "UNKNOWN"
test_feature "Ctrl+D exits the shell" "UNKNOWN"
test_feature "Ctrl+\\ does nothing" "UNKNOWN"

echo ""
echo "=== BUILT-IN COMMANDS ==="
test_feature "echo (with -n option)" "UNKNOWN"
test_feature "cd (relative or absolute path)" "UNKNOWN"
test_feature "pwd (no options)" "UNKNOWN"
test_feature "export (no options)" "UNKNOWN"
test_feature "unset (no options)" "UNKNOWN"
test_feature "env (no options or arguments)" "UNKNOWN"
test_feature "exit (no options)" "UNKNOWN"

echo ""
echo "============================================"
echo "MANUAL TESTING INSTRUCTIONS:"
echo "============================================"
echo ""
echo "To test manually, run: ./minishell"
echo ""
echo "Test Cases:"
echo "  1. echo hello                    # Basic echo"
echo "  2. echo -n test                  # Echo with -n flag"
echo "  3. echo 'hello\$USER'            # Single quotes (no expansion)"
echo "  4. echo \"hello \$USER\"           # Double quotes (with expansion)"
echo "  5. echo \$USER                     # Variable expansion"
echo "  6. echo \$?                        # Exit status"
echo "  7. pwd                            # Print working directory"
echo "  8. cd /tmp && pwd                # Change directory with pipe"
echo "  9. ls | grep test                # Pipe test"
echo " 10. echo test > file.txt          # Output redirection"
echo " 11. cat < file.txt                # Input redirection"
echo " 12. echo test >> file.txt         # Append redirection"
echo " 13. cat << EOF                    # Heredoc test"
echo " 14. export VAR=value && echo \$VAR # Export"
echo " 15. unset VAR && echo \$VAR        # Unset"
echo " 16. env | head                    # Env command"
echo " 17. exit                          # Exit command"
echo ""
echo "============================================"
echo "SUMMARY:"
echo "============================================"
echo -e "Passed:  ${GREEN}${TESTS_PASSED}${NC}"
echo -e "Failed:  ${RED}${TESTS_FAILED}${NC}"
echo -e "Unknown: ${YELLOW}${TESTS_UNKNOWN}${NC}"
echo -e "Total:   $((TESTS_PASSED + TESTS_FAILED + TESTS_UNKNOWN))"
echo ""
