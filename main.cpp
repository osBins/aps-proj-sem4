#include <bits/stdc++.h>
#include "algorithms.h"
using namespace std;

int main()
{
    /*
    Molshree                Huffman
    Arpit                   Range coding
    Yathansh                LZ77
    Simran                  Fibonacci
    Nishttha                Shannon Fano
    */
    string s = "hello how are you? hello hello hello yaa";
    string encodedS = lz77::encode(s);
    string decodedS = lz77::decode(encodedS);
    cout<<decodedS<<endl;
    comparisonResult cr = compare(s, encodedS);

}