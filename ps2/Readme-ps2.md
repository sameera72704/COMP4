# PS2: Pentaflake

## Contact
Name: Sameera Sakinala 
ID : 02149444
Section: 202 


Time to Complete: 9hours 


## Description
This project implements a Pentaflake fractal generator using the SFML graphics library. A Pentaflake is a recursive geometric pattern created by repeatedly arranging pentagons. The program takes command-line arguments for side length, recursion depth, and an optional rotation angle, then generates and displays the Pentaflake pattern in a window.

### Features
Adjustable side length and recursion depth, controlled by command-line inputs
Optional rotation parameter to tilt the entire structure
A simple animation that gradually rotates the Pentaflake
Two-color scheme to make each level of recursion visually distinct
Efficient memory management using std::vector to handle pentagon shapes

### Issues
1. Initially struggled with the mathematical calculations for correct pentagon placement
2. Faced challenges in implementing the recursive algorithm efficiently
3. Had to carefully manage memory usage for deep recursion levels
4. Encountered some difficulties in setting up the SFML library correctly

### Extra Credit
1. I added a basic animation that rotates the entire fractal.
2. The command-line now includes an optional rotation parameter.
3. The two-color scheme helps to visually differentiate between recursion levels, making the fractal easier to interpret.


## Acknowledgements
1. SFML documentation was a helpful reference throughout (https://www.sfml-dev.org/documentation/)
2. guidance on pdf ( https://uml.umassonline.net/bbcswebdav/pid-2992604-dt-content-rid-33085295_1/xid-33085295_1 )
3. Online resources for mathematical formulas related to pentagon geometry 