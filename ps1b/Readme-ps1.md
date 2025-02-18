### Contact
Name: Sameera Sakinala
Section: 202
Time to Complete: 7hours

### Description
This project implements a Fibonacci LFSR for the transformation of an image by performing bitwise XOR operations. In this approach, the input image's pixel values are jumbled up using the given seed by this LFSR algorithm. This program will load up an image and then transform it and then displays the original and the transformed images using the SFML graphics library.

### Features
LFSR Implementation:

The LFSR is seeded and run to produce bits used in the color value transformation of each pixel. The bits are XOR'd with each pixel's red, green, and blue channels.
Image Transformation:

The PhotoMagic::transform function utilizes the values returned from the LFSR to each pixel within an image, scrambling its colors. The now-transformed image is saved to a new file.
SFML Windows for Visualization:

### Issues :
The 4 test cases are running perfectly and the encryption and decryption are undergoing properly .


### Acknowledgements
SFML documentation: https://www.sfml-dev.org/documentation/
C++ reference for bitwise operations.

### Credits :
No external images were used.