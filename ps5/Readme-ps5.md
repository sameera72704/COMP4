# PS5: DNA Alignment

## Contact
Name    : Sameera Sakinala 
uml id  : 02149444
Section : 202 
Time to Complete: 8hours 

#### Description

### Features
This project implements the Edit Distance (Levenshtein distance) algorithm for DNA sequence alignment. The primary goal is to compute the minimum number of operations (insertions, deletions, or substitutions) needed to convert one DNA string into another. I employed dynamic programming to achieve this, following these key steps:


### Algorithm Description 
I implemented  the Edit Distance (Levenshtein distance) algorithm using dynamic programming, which is a fancy way of saying I break down the problem into smaller, manageable pieces. Here’s how it works:
Initialization:and start by creating our opt matrix, which is sized (m+1) x (n+1).
The first row and column are initialized to represent the cost of converting strings to an empty string: opt[i] = i and opt[j] = j.
Filling the Matrix:
Next, i  filled in each cell of the matrix by comparing characters from both sequences.
For each cell opt[i][j], calculate:
Substitution: If the characters differ, I took the value from opt[i-1][j-1] and add a penalty.
Deletion: i looked at opt[i-1][j] and add 1 for deleting a character.
Insertion: i  checked opt[i][j-1] and add 1 for inserting a character.
I choose the minimum of these options to fill in opt[i][j].
Backtracking for Alignment:
Once the matrix is filled, I start from the bottom-right corner (opt[m][n]) and trace back to construct our alignment.
This step involves choosing paths based on how i arrived at each cell, allowing us to visualize how one sequence can be transformed into another.
Time Complexity: O(mn)
Space Complexity: O(mn)
This algorithm ensures I find an optimal solution by considering all possible edit operations at every step.


1. Data Structure:
I used a 2D matrix (opt) to store the minimum edit distance at each position. Here, opt[i][j] represents the edit distance between the first i characters of string x and the first j characters of string y. This choice allows for efficient memoization of subproblems, reducing redundant calculations and improving overall performance.
2. 
1. Base Case: The edit distance is initialized for scenarios where one string is empty. Converting one string to an empty string involves only insertions or deletions.
2. Recursion: For each pair of characters, I computed the minimum edit distance by considering three possible operations:
 1. Substitution (if characters differ) 
 2.   Insertion
 3.  Deletion
3. Functions:
 1.  penalty(char a, char b): Returns 0 if characters match, else returns 1 (penalty for substitution).
 2.  min3(int a, int b, int c): Computes the minimum of three values (used for dynamic programming).
 3.  optDistance(): Computes the minimum edit distance.
 4.  alignment(): Constructs the optimal alignment of the two DNA sequences.
 5. minComparisonAnalysis(): Compares the efficiency of min3 function with direct comparison.
 6. optimizationComparisonAnalysis(): Measures the execution time of current and future optimized versions of optDistance.

### Testing
The program has been tested using unit tests to ensure the core logic works as expected:

1. Penalty Test:        Ensures the penalty function correctly assigns 0 for matches and 1 for mismatches.
2. Min3 Test:           Verifies that the minimum of three values is correctly computed.
3. Edit Distance Test:  Validates the edit distance computation between two DNA strings.
4. Alignment Test:      Ensures that the alignment function generates an alignment string.
5. Swapped Strings Test: Confirms that swapping input strings produces different alignments but the same edit distance.
6. Direction Test: Checks that the alignment is generated in the correct order.
7. Alignment Completeness Test: Verifies that all characters from both input sequences are present in the final alignment and checks for cut ends.

### Issues

1. Memory: The program consumes significant memory with larger inputs; it may crash or be killed when input size exceeds approximately 50,000 characters.

2. Performance: The program's performance decreases with larger sequences; both computation time and memory requirements increase significantly.

## Analysis

### Example

Test Input : 

AACAGTTACC
TAAGGTCA

Excepted Output : 

Edit distance = 7
A T 1
A A 0
C - 2
A A 0
G G 0
T G 1
T T 0
A - 2
C C 0
C A 1
Execution time is 8.9197e-05 seconds
Memory used: 0 MB

## Did the Program Work?
Yes, it correctly calculated the distance as 7 and gave the expected alignment.

### Specs
Your Computer
Memory: 16.0GB
Processors: Intel(R) Core(TM) i5-1235U @ 1.30 GHz

### Runs

| data file     | distance | memory (mb) | time (seconds) | partner time |
|---------------|----------|-------------|----------------|--------------|
|ecoli2500.txt  |   118    | 24.2422 MB  |   0.171339     |     ----     |
|ecoli5000.txt  |   160    | 95.8203 MB  |   0.686965     |     -----    |
|ecoli10000.txt |   223    | 382.191 MB  |   2.91143      |     ------   |
|ecoli20000.txt |   3135   | 1527.34 MB  |   11.5976      |      ------  |
|ecoli50000.txt |   killed |      --     |     --         |        ---   |
|ecoli100000.txt|   killed |      --     |     --         |       ------ |



### Valgrind
-----------------------------------------
|  data file         |   Memory Usage   |
-----------------------------------------
| ecoli2500.txt      |   24.08 MB       |
|ecoli5000.txt       |  95.77 MB        |
|ecoli10000.txt      |  382.2 MB        |
|ecoli20000.txt      |  1.491 GB        |
|ecoli50000.txt      |  KILLED          |
|ecoli100000.txt     |  KILLED          |
-----------------------------------------



## Extra Credit
Implementation of minComparisonAnalysis and optimizationComparisonAnalysis functions for performance analysis.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

for assistance with C++ dynamic arrays : https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new .
 to view the logs / for visualizing memory usage : https://milianw.de/tag/massif-visualizer .  
More documentation on valgrind and massif  :  http://valgrind.org/docs/manual/ms-manual.html.