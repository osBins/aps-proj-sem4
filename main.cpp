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

    using namespace lz77;
    string text = readBinFile("test.txt");
    // cout<<text<<endl;
    string encodedS = encode(text);
    // cout << encodedS << endl;
    comparisonResult cr = getCompressionResult(text, encodedS);
    cout << cr << endl;

    string byteS = binStrToByteStr(encodedS);
    writeToFile("test.lz77", byteS);

    byteS = readBinFile("test.lz77");
    string binS = byteStrToBinStr(byteS);
    // cout<<binS<<endl;
    string decodedS = decode(encodedS);
    // cout<<decodedS<<endl;
    writeToFile("decoded.txt", decodedS);
}