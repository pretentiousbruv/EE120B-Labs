# Test file for "Lab2_introToAVR"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "weight > 140 and A - C > 80"
# Set inputs
setPINA 0x55
setPINB 0x46
setPINC 0x02
# Continue for several ticks
continue 2
# Set expect values
expectPORTD 0x9F 
# Check pass/fail
checkResult

# Add tests below
test "weight > 140 and A - C < 80"
setPINA 0x4A
setPINB	0x46
setPINC 0x02
continue 2
expectPORTD 0x91
checkResult

test "weight < 140 and A - C > 80"
setPINA 0x55
setPINB 0x04
setPINC 0x02
continue 2
expectPORTD 0x5A
checkResult

test "weight < 140 and A - C < 80"
setPINA 0x4A
setPINB 0x04
setPINC 0x02
continue 2
expectPORTD 0x50
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
