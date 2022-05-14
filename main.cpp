#include <bits/stdc++.h>
#include "algorithms.h"
// #include "utility.h"
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
    // string s = "hello how are you? hello hello hello yaa";
    // string encodedS = lz77::encode(s);
    // string decodedS = lz77::decode(encodedS);
    // cout<<decodedS<<endl;
    // comparisonResult cr = compare(s, encodedS);


    using namespace lz77;
    string text = readTextFile("test.txt");
    cout<<text<<endl;
    string encodedS = encode(text);
    // cout << encodedS << endl;
    comparisonResult cr = getCompressionResult(text,encodedS);
    cout<<cr<<endl;

    string byteS = binStrToByteStr(encodedS);
    writeToFile("test.lz77",byteS);

    byteS = readTextFile("test.lz77");
    string binS = byteStrToBinStr(byteS);
    // cout<<binS<<endl;
    string decodedS = decode(binS);
    cout<<decodedS<<endl;
    writeToFile("decoded.txt",decodedS);
}