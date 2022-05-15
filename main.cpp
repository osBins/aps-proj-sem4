#include <bits/stdc++.h>
#include "algorithms.h"
#include "utility.h"
using namespace std;

void handleCompression()
{
    string filename;
    cout << "enter name of the file to be compressed: ";
    getline(cin, filename);

    cout << "enter the algorithm for compression: " << endl
         << "1. huffman" << endl
         << "2. shannon-fano" << endl
         << "3. lz77" << endl
         << "4. arithmetic" << endl
         << "5. diagram" << endl
         << "choice: ";
    string algoChoice;
    getline(cin, algoChoice);
    if (algoChoice == "1" || algoChoice == "huffman")
    {
    }
    else if (algoChoice == "2" || algoChoice == "shannon-fano")
    {
    }
    else if (algoChoice == "3" || algoChoice == "lz77")
    {
        comparisonResult cr = compressFile(filename, "lz77");
        cout << cr << endl;
    }
    else if (algoChoice == "4" || algoChoice == "arithmetic")
    {
    }
    else if (algoChoice == "5" || algoChoice == "diagram")
    {
    }
    else
    {
        cout << "choose a valid option" << endl;
    }
}

void handleDecompression()
{
}

void cli()
{
    char cdChoice;
    cout << "do you want to compress or decompress? (c/d) : ";
    cin >> cdChoice;
    fflush(stdin);
    cout << endl;
    switch (cdChoice)
    {
    case 'c':
        handleCompression();
        break;
    case 'd':
        handleDecompression();
        break;
    default:
        cout << "please choose a valid option" << endl;
        break;
    }
}

int main()
{
    /*
    Molshree                Huffman
    Arpit                   Range coding
    Yathansh                LZ77
    Simran                  Fibonacci
    Nishttha                Shannon Fano
    */
    cli();
    // using namespace lz77;
    // string text = readBinFile("test.txt");
    // // cout<<text<<endl;
    // string encodedS = encode(text);
    // // cout << encodedS << endl;
    // comparisonResult cr = getCompressionResult(text, encodedS);
    // cout << cr << endl;

    // string byteS = binStrToByteStr(encodedS);
    // writeToFile("test.lz77", byteS);

    // byteS = readBinFile("test.lz77");
    // string binS = byteStrToBinStr(byteS);
    // // cout<<binS<<endl;
    // string decodedS = decode(encodedS);
    // // cout<<decodedS<<endl;
    // writeToFile("decoded.txt", decodedS);
}