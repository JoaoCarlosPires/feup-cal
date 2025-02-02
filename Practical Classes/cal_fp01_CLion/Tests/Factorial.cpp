/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n) {
    if (n <= 1) { return 1; }
    else { return n * factorialRecurs(n - 1); }

}

int factorialDinam(int n) {
    if (n <= 1) { return 1; }
    int factorial = 1;
    for (int i = 2; i <= n; i++) {
        factorial*=i;
    }
    return factorial;
}