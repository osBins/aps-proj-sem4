#include <bits/stdc++.h>
using namespace std;
// fwd declarations
// struct comparisonResult;
// comparisonResult getCompressionResult(
//     const string &original,
//     const string &encoded);

char boolToChar(bool b)
{
    return b ? '1' : '0';
}

bool charToBool(char c)
{
    return c == '0' ? 0 : 1;
}

int get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(), "rb");
    fseek(p_file, 0, SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
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

string readBinFile(string filename)
{
    size_t size = get_file_size(filename);
    fstream file;
    file.open(filename, ios::in | ios::binary);
    char *binS = (char *)malloc(size * (sizeof(char)));
    file.read(binS, size);
    string s;
    for (int i = 0; i < size; i++)
    {
        s.push_back(binS[i]);
    }
    return s;
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
    if(endPadding == 8)
    {
        endPadding = 0;
    }
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
    file.open(filename, ios::out | ios::binary);
    const char *binS = s.c_str();
    size_t sizeBinS = s.size();
    file.write(binS, sizeBinS);
}