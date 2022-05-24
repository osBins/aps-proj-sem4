#include "algorithms/fibonacci.h"
#include "algorithms/huffman.cpp"
#include "algorithms/lz77.h"
#include "algorithms/arithmetic.h"
#include "algorithms/shannon_fano.h"

//fwd declarations
char boolToChar(bool b);

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
        << "the compressed string took   : "
        << cr.encodedLen
        << "bits" << endl
        << "the compression ratio was : "
        << cr.ratio
        << "%" << endl;
}

comparisonResult getCompressionResult(
    const string &original,
    const string &encoded)
{
    comparisonResult cr;
    cr.originalLen = stringToBinS(original).length();
    cr.encodedLen = encoded.length();
    cr.ratio = ((
                    (float)cr.originalLen - (float)cr.encodedLen) /
                (float)cr.originalLen) *
               100;
    return cr;
}
