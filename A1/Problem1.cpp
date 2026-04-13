// File Name: Problem1.cpp
// Project: CS 170 Assignment 1 Problem 1
// Author: Gogi Benny
// Date: Tuesday, March 10, 2026
//
// Purpose: Generate a random even integer from the interval [4, 32768],
// store it dynamically, and find/print two prime integers that sum to it.
//
// Major Items:
// - Global constants for symmetric bounds
// - Explicit cast to avoid implicit conversion
// - Dynamic memory allocation
// - Pass by pointer with const int* evenNumberPtr for function printPrimeSum (EXTRA)
// - Version control using Git & GitHub:
//   https://github.com/dozothebozo/CS170/blob/main/Problem1.cpp (EXTRA)

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// function prototypes
int* createEvenRandomInteger();
bool isPrime(int n);
void printPrimeSum(const int* evenNumberPtr);

// global declarations of constants
const int RANDOM_MIN = 4;
const int RANDOM_MAX = 32768;

int main() {
    // explicit cast time to avoid implicit conversion
    srand(static_cast<unsigned int>(time(0)));

    int* evenNumberPtr = createEvenRandomInteger();

    cout << "Generated even integer: " << *evenNumberPtr << '\n';

    printPrimeSum(evenNumberPtr);

    delete evenNumberPtr;

    return 0;
}

/**
   Creates a dynamically allocated random even integer.
   @return a pointer to the generated random even integer
*/
int* createEvenRandomInteger() {
    // dynamically allocate memory for the random integer
    int* randomPtr = new int;

    // generates an even number between [4, 32768]
    *randomPtr = RANDOM_MIN + (rand() % ((RANDOM_MAX - RANDOM_MIN) / 2 + 1)) * 2;

    return randomPtr;
}

/**
   Determines if a given integer is a prime number.
   @param n the integer to check if it is prime
   @return true if the integer is prime, and false otherwise
*/
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    if (n == 2) {
        return true;
    }

    if (n % 2 == 0) {
        return false;
    }

    for (int i = 3; i <= n / 2; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

/**
   Finds and prints two prime numbers that add up to a given even integer.
   @param evenNumberPtr a constant pointer to the random even integer
*/
void printPrimeSum(const int* evenNumberPtr) {
    int prime1 = 2;
    int prime2 = 2;

    // 4 is the only case where the prime sum is 2 + 2
    if (*evenNumberPtr != 4) {
        for (int i = 3; i <= *evenNumberPtr / 2; i += 2) {
            // solve for difference where i + complement = *evenNumberPtr
            int complement = *evenNumberPtr - i;

            // if both are prime, they form the required sum
            if (isPrime(i) && isPrime(complement)) {
                prime1 = i;
                prime2 = complement;
                break;
            }
        }
    }

    cout << "Prime sum: " << prime1 << " + " << prime2 << " = " << (prime1 + prime2) << '\n';
}
