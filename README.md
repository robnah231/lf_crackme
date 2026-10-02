# lf_crackme
Crackme: https://crackmes.one/crackme/5ab77f5633c5d40ad448c2f0

## Analysis
I started by analyzing the executable and identified the error message: "Nope, thats not it!". This message is displayed when the entered username and serial key combination is invalid.

Using Binary Ninja, I located the error string through static analysis. However, the decompiled code was difficult to follow, so I switched to dynamic analysis using x64dbg to get a better understanding of the validation process.

I searched for references to the error message and examined the surrounding instructions. During this process, I also located the success message at address 00401290.

I then worked backwards through the instructions until I found the message "Username must have at least 4 chars...". Since the serial validation takes place after the username length check, I placed a breakpoint at this location and stepped through the execution.

Eventually, I identified a loop beginning at address 004011C7. By examining the instructions inside this loop, I was able to determine how the program generates the individual characters of the valid serial key.

## Key Generation Logic
After analyzing the loop, I determined that the serial key is generated using a hard-coded seed string: _r <()<1-Z2[l5,^

The program uses the following algorithm:

First, it checks that the username contains at least four characters. If it does not, the program displays an error message and stops generating the key.

The seed string is copied into a result buffer.

The program then iterates over the username and seed string, using the longer of the two strings to determine the number of iterations.

During each iteration, it takes the corresponding username character and seed character. If either string has been exhausted, the indexing wraps around using the modulo operator.

The two characters are converted to unsigned bytes and combined using a bitwise XOR operation.

The XOR result is reduced using modulo 25.

Finally, 65 (0x41, the ASCII value of uppercase 'A') is added to produce an uppercase alphabetic character.

Each generated character replaces the corresponding character in the seed buffer.

Once the loop finishes, the program prints the resulting serial key in groups of four characters, separated by dashes.

## Keygen Implementation
Using the algorithm identified during the reverse engineering process, I implemented a key generator in C.

The program prompts the user for a username, checks that it meets the minimum length requirement, and generates the corresponding serial key using the same XOR and modulo operations as the original executable.

The generated key is then displayed in groups of four characters, separated by dashes, to match the expected serial key format.

To compile the program, I used GCC with the following command:

```gcc -Wall -Wextra -o keygen keygen.c```
