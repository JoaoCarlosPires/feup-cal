/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <vector>
#include <string>
#include <iostream>

string calcSum(int* sequence, int size)
{
    string to_return;
    int s, aux_s, ind, aux_ind;
    for (int i = 0; i < size; i++) {
        s = 0;
        aux_s = 0;
        ind = 0;
        for (int k = 0; k < size-i; k++) {
            aux_s = sequence[k];
            aux_ind = 1;
            for (int j = 0; j < i; j++) {
                aux_s+=sequence[k+aux_ind];
                aux_ind++;
            }
            if (k == 0) {
                s = aux_s;
                ind = 0;
            } else if (aux_s<s) {
                s = aux_s;
                ind = k;
            }
        }
        to_return += to_string(s) + "," + to_string(ind) + ";";
    }

	return to_return;
}

