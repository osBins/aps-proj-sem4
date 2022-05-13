#include "algorithms/fibonacci.h"
#include "algorithms/huffman.h"
#include "algorithms/lz77.h"
#include "algorithms/arithmetic.h"
#include "algorithms/shannon_fano.h"

char boolToChar(bool b)
{
    return b ? '1' : '0';
}

bool charToBool(char c)
{
    return c == '0' ? 0 : 1;
}

char binSToChar(string s)
{
    bitset<8> charB;
    int itr = 0;
    for (; itr < s.length(); itr++)
    {
        charB[itr] = charToBool(s[itr]);
    }
    for (int i = 0; i < 8 - itr; i++)
    {
        charB[itr++] = 0;
    }
    char c = (char)(charB.to_ulong());
    return c;
}



string stringToBinS(string s)
{
    string binS;
    for (int i = 0; i < s.length(); i++)
    {
        bitset<8> charB(s[i]);
        for (int j = 0; j < charB.size(); j++)
        {
            binS.push_back(boolToChar(charB[i]));
        }
    }
    return binS;
}

string binSToString(string s)
{
}

struct comparisonResult
{
    int originalLen;
    int encodedLen;
    float ratio;
    friend ostream &operator<<(ostream &out, comparisonResult &cr);
};

ostream &operator<<(ostream &out, comparisonResult &cr)
{
    out << "<- The comparison result ->" << endl
        << "the original string took  : "
        << cr.originalLen
        << "bits" << endl
        << "the encoded string took   : "
        << cr.encodedLen
        << "bits" << endl
        << "the compression ratio was : "
        << cr.ratio
        << "%" << endl;
}

comparisonResult compare(
    const string &original,
    const string &encoded)
{
    comparisonResult cr;
    cr.originalLen = stringToBinS(original).length();
    cr.encodedLen = encoded.length();
    cr.ratio = ((float)cr.originalLen - (float)cr.encodedLen) / (float)cr.originalLen;
    return cr;
}


//file io needs a lot of fixing
typedef string FileName;

string encodeFile(FileName fileName)
{
    fstream file;
    string s;
    file.open(fileName, ios::in);
    if (file.is_open())
    {
        string temp;
        while (getline(file, temp))
            s += temp + '\n';
        file.close();
    }
    string encodedS = lz77::encode(s);
    return encodedS;
}

void writeBinTofile(FileName filename, string s)
{
    fstream file;
    file.open(filename, ios::out);
    if (file.is_open())
    {
        int sItr = 0;
        while (sItr < s.length())
        {
            char c = binSToChar(s.substr(sItr, 8));
            sItr += 8;
            file << c;
        }
        file.close();
    }
}

string decodeFromFile(FileName fileName)
{
    fstream file;
    string s;
    file.open(fileName, ios::in);
    if (file.is_open())
    {
        string temp;
        while (getline(file, temp))
            s += temp + '\n';
        file.close();
    }
    string binS;
    for(auto x: s)
    {
        bitset<8> charB(x);
        string temp = charB.to_string();
        reverse(temp.begin(),temp.end());
        binS+=temp;
    }
    // cout<<binS<<endl;
    string decodedS = lz77::decode(binS);
    return decodedS;
}