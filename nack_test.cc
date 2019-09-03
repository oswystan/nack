/*
 **************************************************************************************
 *       Filename:  nack_test.cc
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2019-09-03 11:21:52
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <iostream>
#include "nack.h"

using namespace std;

template<typename T>
void PrintArray(T& a) {
    for (auto &i : a) {
        cout << i << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    NackModule nack(3);
    //uint16_t seq[] = {1, 2, 3, 6, 7, 11, 12, 13, 14, 15, 10, 16, 17, 18};
    uint16_t seq[] = { 65530, 65532, 65533, 65535, 1, 3, 5, 7, 9, 10, 11, 12, 13, 14, 15, 16};

    PrintArray(seq);
    vector<uint16_t> nl;
    for (int i = 0; i < sizeof(seq)/sizeof(seq[0]); ++i) {
        nack.HandleSequence(seq[i], nl);
        if (nl.size()) {
            cout << seq[i] << "\t:";
            PrintArray(nl);
        }
    }
    return 0;
}

/********************************** END **********************************************/

