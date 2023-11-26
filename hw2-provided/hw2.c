// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define MAX_BIT_POSITION 32

// Cache for storing FizzBuzz results for each bit position
char cache[MAX_BIT_POSITION][3];

// Initialize the cache with FizzBuzz results
void preComputeResults() {
    // TODO: For every possible position, pre-compute its corresponding string output
	// Make sure to handle the case where you will not replace the bit with Z, R, or U
	// Your advancedBitwiseFizzBuzz() code should know when to use the replacement and when to use the bit
    // Use 'Z' for numbers divisible by 3 and 5, 'R' for divisible by 3, and 'U' for divisible by 5
    cache[0][0] = 'S';
    for(int i  = 1; i < MAX_BIT_POSITION; i++){
        if((MAX_BIT_POSITION-1-i)%15 == 0){
            cache[i][0] = 'Z';}
        else if((MAX_BIT_POSITION-1-i)%3 == 0){
            cache[i][0] = 'R';}
        else if((MAX_BIT_POSITION-1-i)%5 == 0){
            cache[i][0] = 'U';}
        else{cache[i][0] = '1';}
    }
}

// Retrieve the FizzBuzz result for a specific bit position
char* getFizzBuzzForBit(int position) {
    // TODO: Return the FizzBuzz result for the given position from the cache
    return *(cache+position);
}

// Perform the advanced Bitwise FizzBuzz logic on the given number
void advancedBitwiseFizzBuzz(int32_t N) {
    // TODO: Implement the advanced Bitwise FizzBuzz logic
    // - For each bit in the number, apply the FizzBuzz logic
    // - Replace the MSb with 'S' if it's set
    // - Print each bit or its FizzBuzz result
    // - Format the output with a space every four bits

	// Each bitstring should be outputted from Left -> Right, MSb -> LSb
	// Index 0 of the bitstring should be the LSb
	// E.g., 
	// 1  0  0 1 0 0 0 1 1 1 0 0   <=== bitstring
	// 11 10 9 8 7 6 5 4 3 2 1 0   <=== indices'
    for(int i = 0; i < MAX_BIT_POSITION; i++)
    {
        if((N >>(MAX_BIT_POSITION-1-i))&0xFF)
        {
            char c = *(getFizzBuzzForBit(i));
            printf("%c",c);
        }
        else{printf("%d",0);}

        if(((i+1)%4==0)&&(i!=0)){printf(" ");}
    }

}

// Main function to run the program
int main(int argc, char *argv[]) {
    // TODO: Parse the command line argument to get the input number
    // Use strtol to convert the string to a long integer
    // Check if the number is within the range of a 32-bit signed integer
	// If so, print "Number out of range for a 32-bit integer\n"

    printf("%s\n", argv[1]);
    char *remaining;
    long l = strtol(argv[1], &remaining, 10); 
    if(l>INT_MAX||l<INT_MIN){
        printf("Number out of range for a 32-bit integer\n");
        return EXIT_FAILURE;
    }
    int32_t n = (int32_t)l;

    // TODO: Initialize the cache
    preComputeResults();
    // TODO: Call advancedBitwiseFizzBuzz with the parsed number
	// Make sure the number is an int32_t
    advancedBitwiseFizzBuzz(n);



    return 0;
}
