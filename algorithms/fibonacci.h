// #include <utility.h>
using namespace std;

// To limit on the largest Fibonacci number to be used
#define N 30
int fib[N];
namespace fibonacci
{
    bool charToBool(char c)
    {
        return c == '0' ? 0 : 1;
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
    int largestFibonacci(int n)
    {
        
        fib[0] = 1;
        fib[1] = 2;
        int i;
        for (i = 2; fib[i - 1] <= n; i++)
        {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        return fib[i - 2];
    }
    string encode(string seq)
    {
        int seqLength = seq.length();
        int ascii[seqLength];

        // Converting text to ASCII

        for (int i = 0; i < seqLength; i++)
        {
            ascii[i] = seq[i];
        }

        int fibonacci[seqLength][12];

        // Intialising array
        for (int i = 0; i < seqLength; i++)
        {

            for (int j = 0; j < 12; j++)
            {
                fibonacci[i][j] = 0;
            }
        }
        for (int i = 0; i < seqLength; i++)
        {

            for (int j = 0; j < 12; j++)
            {

                int temp = 0;
                int index = 0;
                temp = largestFibonacci(ascii[i]);

                for (int k = 0; k < N; k++)
                {

                    if (temp == fib[k])
                    {
                        index = k;
                    }
                }

                fibonacci[i][index] = 1;
                ascii[i] = ascii[i] - largestFibonacci(ascii[i]);

                if (ascii[i] == 0)
                {
                    break;
                }
            }
        }
        string s;
        for (int i = 0; i < seqLength; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                s+=to_string(fibonacci[i][j]); 
            }
        }
        return s;
    }
    string decode(string text)
    {
        // string s1 = byteStrToBinStr(text);
    }
}