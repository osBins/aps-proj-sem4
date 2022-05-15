#include <bits/stdc++.h>
#include "algorithms.h"
#include "utility.h"
using namespace std;


comparisonResult compressFile(string filename, string algo)
{
    string fileContents = readBinFile(filename);
    string encodedS;
    string ext;
    if (algo == "lz77")
    {
        encodedS = lz77::encode(fileContents);
    }
    else if (algo == "huff")
    {
        encodedS = huffman::encode(fileContents);
    }
    else if (algo == "fano")
    {
        encodedS = shannon_fanno::encode(fileContents);
    }
    else if (algo == "metic")
    {
        encodedS = arithmetic::encode(fileContents);
    }

    // add option for diagram coding

    comparisonResult cr = getCompressionResult(fileContents, encodedS);
    string byteS = binStrToByteStr(encodedS);

    string outfile;
    outfile += filename;
    outfile += ".";
    outfile += algo;
    writeToFile(outfile, byteS);
    return cr;
}



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
    string inname;
    cout << "enter name of the file to be decompressed: ";
    getline(cin, inname);
    cout<<endl;

    string encodeAlgo;
    auto it = inname.rbegin();
    for(; it!=inname.rend(); it++)
    {
        if(*it == '.')
        {
            break;
        }
        encodeAlgo.push_back(*it);
    }
    it++;
    reverse(encodeAlgo.begin(),encodeAlgo.end());

    string outfileName;
    for(; it!=inname.rend(); it++)
    {
        outfileName.push_back(*it);
    }
    reverse(outfileName.begin(), outfileName.end());

    string fileContents = readBinFile(inname);
    string bitS = byteStrToBinStr(fileContents);

    string decodedS;
    if(encodeAlgo == "lz77")
    {
        decodedS = lz77::decode(bitS);
    }
    else if(encodeAlgo == "huff")
    {

    }
    else if(encodeAlgo == "fano")
    {

    }
    else if(encodeAlgo == "metic")
    {

    }
    writeToFile(outfileName,decodedS);
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
}