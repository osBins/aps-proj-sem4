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
    string s = "hello_hello_lol";
    cout<<"original string"<<endl;
    cout<<s<<endl;
    string encodedS = encode(s);
    cout<<"encoded string"<<endl;
    cout<<encodedS<<endl;
    string decodedS = decode(encodedS);
    cout<<"decoded string"<<endl;
    cout<<decodedS<<endl;
    cout<<endl;
    comparisonResult cr = compare(s,encodedS);
    cout<<cr;
    
}