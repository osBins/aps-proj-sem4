#include <bits/stdc++.h>
using namespace std;

char boolToChar(bool b)
{
    return b ? '1' : '0';
}

bool charToBool(char c)
{
    return c == '0' ? 0 : 1;
}

string readTextFile(string fileName)
{
    fstream file;
    file.open(fileName, ios::in);
    string text;
    if (file.is_open())
    {
        string temp;
        while (!file.eof())
        {
            getline(file, temp);
            text += temp;
            text.push_back('\n');
        }
        text.pop_back();
        file.close();
    }
    // cout<<text<<endl;
    return text;
}

char binSToChar(string s)
{
    bitset<8> charB(0);
    for (int i = 0; i < s.length(); i++)
    {
        charB[i] = charToBool(s[i]);
    }
    char a = (char)charB.to_ulong();
    return a;
}

// group bits into 1 byte groups and make chars from them
string binStrToByteStr(string binS)
{
    string byteS;
    int sItr = 0;
    while (sItr < binS.length())
    {
        // cout<<binS.substr(sItr, 8)<<endl;
        char c = binSToChar(binS.substr(sItr, 8));
        byteS.push_back(c);
        sItr += 8;
    }
    int extraBits = 8 - binS.length() % 8;
    // cout<<"extra bits = "<<extraBits<<endl;
    bitset<8> extraBitsCount(extraBits); // extra bits at the end
    char endPadding = (char)extraBitsCount.to_ulong();
    byteS.insert(byteS.begin(), endPadding); // inserting padding count at the begining
    return byteS;
}

string byteStrToBinStr(string byteS)
{
    char endPadding;
    int sItr = 0;
    endPadding = byteS[sItr];
    // cout<<(int)endPadding;
    sItr++;
    string bitS;
    for (; sItr < byteS.length(); sItr++)
    {
        // cout<<byteS[sItr];
        bitset<8> bits(byteS[sItr]);
        string temp = bits.to_string();
        reverse(temp.begin(), temp.end());
        bitS += temp;
    }
    bitS = bitS.substr(0, bitS.length() - endPadding);
    return bitS;
}

void writeToFile(string filename, string s)
{
    ofstream file;
    file.open(filename, ios::out);
    if (file.is_open())
    {
        file << s;
        file.close();
    }
}
