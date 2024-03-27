# Huffman Encoding and Decoding

## Overview

This program implements Huffman encoding and decoding in C++. It constructs a Huffman tree based on the frequency of characters in a given input, assigns binary codes to each character, and then uses these codes to encode a text. Additionally, it can decode a Huffman encoded string back to its original form. The program reads character frequencies and the text to encode from separate files, performs Huffman encoding, decodes the encoded text, and outputs the results.

## Features

- Builds a Huffman tree to determine the most efficient binary codes for characters based on their frequencies.
- Encodes text using the generated Huffman codes.
- Decodes Huffman encoded text back to its original form.
- Reads character frequencies and text to encode from files.

## File Formats

### Input Files

1. **Character Frequency File (`test1.txt`)**: This file contains characters and their frequencies. Each line should have a character followed by its frequency, separated by a space.

   Example:

- a 5
- b 9
- c 12


2. **Text to Encode File (`test2.txt`)**: This file contains the text that will be encoded using the Huffman codes generated from the frequencies provided in `test1.txt`.

Example:

- abbcccdddd


### Output

The program will output:

- The Huffman codes for each character.
- The original text encoded using the Huffman codes.
- The encoded text decoded back to its original form.

## How to Compile and Run

To compile the program, ensure you have a C++ compiler installed. Use the following command:

```bash
g++ -o HuffmanEncoderDecoder HuffmanEncoderDecoder.cpp
```

To run the program, execute the compiled binary:

./HuffmanEncoderDecoder
