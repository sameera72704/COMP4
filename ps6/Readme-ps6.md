# PS6: RandWriter

## Contact
Name:  SAMEERA SAKINALA
Section: 102
Time to Complete: 7 HOURS 


## Description

This project implements a Markov Chain text generator based on a given input string. 
It models transitions between k-grams (substrings of length k) and generates pseudo-random text based on the statistical properties of these transitions. 
It supports:
1. Building a frequency map from the input text.
2. Generating random text using k-grams.
3. Using lambdas to transform the alphabet.

### Features

1. Text Processing: The input string is processed to build a Markov model of order k. Each possible k-gram is mapped to the character(s) that follow it, and the frequency of transitions is recorded.
2. Random Text Generation: The generate() method generates text of length L based on the given initial k-gram, using the frequencies of transitions.
3. Alphabet Transformation: A function transformAlphabet() is provided, which allows applying a lambda to transform the alphabet, e.g., converting characters to uppercase.
4. Circular Text Handling: The input text is treated as circular to handle the edge cases where the end of the string connects to the beginning.


### Testing

The following tests were written to verify the correctness of the program:

1. Constructor: Ensures that the RandWriter constructor works for valid inputs and throws an exception when the text length is smaller than k.
2. Frequency Calculation: Validates that both the general frequency of k-grams and the frequency of a specific character following a k-gram are correct.
3. Random Character Generation (kRand): Verifies that the kRand() function generates characters with correct probabilities based on the frequencies.
4. Text Generation (generate): Tests that the generate() method produces text of the correct length and starts with the specified k-gram.
5. Alphabet Transformation: Uses a lambda function to convert the alphabet to uppercase and validates the transformation.
All tests pass successfully with the given implementation.

### Lambda

The lambda expression used in this project is designed to transform characters in the alphabet (e.g., converting all characters to uppercase). The lambda was passed to the transformAlphabet() method, which applies it to each character in the alphabet stored in the RandWriter object. 
Here's the lambda used:
 "" rw.transformAlphabet([](char c) { return std::toupper(c); }); ""
This converts each character in the alphabet string to uppercase.

### Issues

Generating Exactly Correct Length: Initially, there was a discrepancy in generating the required number of characters. This was fixed by refining the loop conditions in the generate() function to ensure the output length matches the expected value.

### Extra Credit

While no extra credit tasks were completed for this project, future work could involve creating a WordWriter that generates text based on words instead of characters, which would be a more advanced extension of the current approach.

## Acknowledgements
C++ map (http://www.cplusplus.com/reference/map/map/) 