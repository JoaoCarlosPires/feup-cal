/*
 * Change.cpp
 */

#include "Change.h"
#include <string>
#include <iostream>
string calcChange(int m, int numCoins, int *coinValues)
{

    if (m == 0) return "";

    string to_return = "";
    string to_return2 = "";

    int how_many;

    for (int k = numCoins-1; k>0; k--) {
        if (m%coinValues[k] == 0) {
            how_many = m/coinValues[k];
            for (int j  = 0; j< how_many; j++) {
                to_return2+= to_string(coinValues[k])+";";
            }
            break;
        }
    }

    int i = numCoins-1;
    while (m>0 && i >= 0) {
        if (m/coinValues[i] >= 1){
            how_many = m/coinValues[i];
            m-=(how_many*coinValues[i]);
            for (int t  = 0; t< how_many; t++) {
                to_return+= to_string(coinValues[i])+";";
            }
        }
        i--;
    }

    if (to_return2.length() < to_return.length() && to_return2 != "") {
        return to_return2;
    }

    if (to_return == "") {
        return "-";
    }

    return to_return;
}


