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

    // testing lz77 encoding
    using namespace lz77;
    string s = "lol lol lol how are you lol lol lol are you a lol how are you my friend";
    cout << s << endl;
    vector<Token> tokens = lz77Encode(s);
    string encoded = lz77ToString(tokens);
    cout << "length of original string in binary: "; // << endl;
    cout << stringToBinS(s).length() << endl;
    cout << "length of string after compression in binary: "; // << endl;
    cout << encoded.length() << endl;
}