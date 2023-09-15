# CS4532 Concurrent Programming Lab_01 - 190310J, 190709P

## Description

The program has a linked list implemented with Member, Insert and Delete functions.
The program is made to run all 3 test cases using the pre-defined 
- n: Total number of elements in the linked list before the execution of the operations
- m: Total number of operations.
- m_member: Total number of Member operations in ratio. 
- m_insert: Total number of Insert operations in ratio. 
- m_delete: Total number of Delete operations in ratio. 
- total_cases: Number of test cases. (In this test, the value is 3)  

Those attributes are set as global variables in the program (main.c).
Linked list will be populated and the operation list will be shuffled in each execution.

The result will be generated as  results.csv file in ../test_results/ directory


## Instructions

The program was impl
To run the program the directory structure should be kept as it is.

### steps 
1. Open your terminal.
2. Navigate to the directory where your C file is located using the cd command. 
3. To change the number of tests, change the variable in **line 10** in `main.c`. 
The limit for `num_of_tests` is **1000** 
4. Once you’re in the correct directory, compile your C file using the gcc compiler.`gcc main.c common.c -o main -lm`
5. Run the compiled program.`./main`. 
Even if, num_of_tests is not given, program will be run using default value (100)

