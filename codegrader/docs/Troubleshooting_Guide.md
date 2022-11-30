# Troubleshooting and Known Issues

## Very long compilation time for first run
### Issue
When running Educheck for the first time, it takes a long time to compile the code.
### Solution
This is a known issue as Educheck compiles the whole Mbed OS for the first time. However, the processing time for the next student should be much shorter as it will only compile the student and relevant Greentea test files.

## Error: Timemout
### Issue
Test build passes but the Greentea test fails with timeout error.
### Solution
- If you are getting: "could not open port 'COM11': Permission error", then make sure you close Mbed Studio - make sure it's not opened at all. Mbed Studio was may have been using the port/did not close port when done thus you weren't able to run the test.

## Compilation error: Multiple redefinitions of functions and variables
### Issue
During compilation, you get an error reporting that there are multiple redefinitions of functions and variables.
### Solution
Check that Educheck `labcheck` Python scripts are including the correct C++ files. Also, ensure that the `labcheck` scripts clean up any build files of that particular student before moving on to the next student


