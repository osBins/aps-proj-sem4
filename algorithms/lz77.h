#include <bits/stdc++.h>
#define SEARCH_BUFFER_LEN 63 // search buffer length = 2^n-1 or n bits
#define SEARCH_BIT_LEN 6
#define LA_BUFFER_LEN 15 // look ahead buffer length = 2^n-1 or n bits
#define LA_BIT_LEN 4
#define CHAR_BIT_LEN 8
using namespace std;

namespace lz77
{
    template <int len>
    void printArr(array<char, len> &arr)
    {
        for (auto x : arr)
        {
            if (x == '\n')
                cout << "\\n"
                     << ".";
            cout << x << ".";
        }
    }

    template <class Type, int len>
    void arrShiftLeft(array<Type, len> &arr)
    {
        for (int i = 1; i < len; i++)
        {
            arr[i - 1] = arr[i];
        }
    }

    char boolToChar(bool b)
    {
        return b ? '1' : '0';
    }

    int customChar(char a)
    {
        return a - 97;
    }

    struct Token
    {
        int offset;
        int length;
        char next;
        Token()
        {
            offset = 0;
            length = 0;
            next = '\0';
        }
        string toBinS() // serilize to binary
        {
            /*
                1 bit for denoting if match was found, 0 for not found and 1 for found
                n bit offset -> max offset = 2^n
                n bit length -> max len = 2^n
                8 bit next char -> full bin seq
            */
            bitset<SEARCH_BIT_LEN> offsetB(offset);
            bitset<LA_BIT_LEN> lengthB(length);
            bitset<CHAR_BIT_LEN> charB(next);
            string binS; // final binary representation of token

            if (offset == 0) // did not find a match hence put 0 infront of normal ascii representation
            {
                binS += '0';
                for (int i = 0; i < charB.size(); i++)
                {
                    binS.push_back(boolToChar(charB[i]));
                }
            }
            else // found a match hence put 1 before the encoded information
            {
                binS += '1';
                for (int i = 0; i < offsetB.size(); i++)
                {
                    binS.push_back(boolToChar(offsetB[i]));
                }

                for (int i = 0; i < lengthB.size(); i++)
                {
                    binS.push_back(boolToChar(lengthB[i]));
                }

                for (int i = 0; i < charB.size(); i++)
                {
                    binS.push_back(boolToChar(charB[i]));
                }
            }
            return binS;
        }
        friend ostream &operator<<(ostream &out, Token &tk);
    };
    ostream &operator<<(ostream &out, Token &tk)
    {
        out
            << "Token"
            << " <"
            << "o:"
            << tk.offset
            << ", l:"
            << tk.length
            << ", n:"
            << (tk.next == '\n' ? "\\n" : "" + tk.next)
            << ">";
    }

    struct SearchResult // result of searching the lookAheadBuffer in the searchBuffer
    {
        bool found;
        int idx;
        int len;
        SearchResult()
        {
            found = false;
            idx = INT_MAX;
            len = 0;
        }
    };

    SearchResult search(
        const array<char, SEARCH_BUFFER_LEN> &searchBuffer,
        const array<char, LA_BUFFER_LEN> &lookAheadBuffer,
        int fillAmmount)
    {
        int LABItr = 0; // lookaheadbuffer iterator
        int SBItr = 0;  // searchbuffer iterator
        SearchResult res;
        while (
            SBItr < searchBuffer.size() &&
            LABItr < fillAmmount)
        {
            if (lookAheadBuffer[LABItr] == searchBuffer[SBItr])
            {
                res.found = true;
                res.idx = SBItr;
                int l = 0;
                while (LABItr < fillAmmount &&
                       lookAheadBuffer[LABItr] == searchBuffer[SBItr])
                {
                    l++;
                    LABItr++;
                    SBItr++;
                }
                res.len = l;
                break;
            }
            SBItr++;
        }
        return res;
    }

    vector<Token> lz77Encode(string s)
    {
        // s+="##";
        array<char, SEARCH_BUFFER_LEN> searchBuffer = {'\0'};
        array<char, LA_BUFFER_LEN> lookAheadBuffer = {'\0'};
        vector<Token> resultVec;
        int fillAmmount = 0; // fill of the lookAheadBuffer
        int sItr = 0;
        int tempItr = 0;
        for ( // for loop for initializing the lookAheadBuffer
            ;
            sItr < s.length() &&
            tempItr < lookAheadBuffer.size();
            sItr++)
        {
            lookAheadBuffer[tempItr] = s[sItr];
            tempItr++;
            fillAmmount++;
            // cout<<"reading "<<s[sItr]<<endl;
        }
        while (fillAmmount > 1)
        {
            // printArr<SEARCH_BUFFER_LEN>(searchBuffer);
            // cout << "|";
            // printArr<LA_BUFFER_LEN>(lookAheadBuffer);
            // cout << endl;
            SearchResult sRes = search(
                searchBuffer,
                lookAheadBuffer,
                fillAmmount);
            bool found = sRes.found;
            int idx = sRes.idx;
            int length = sRes.len;
            // cout<<"idx: "<<idx<<" length: "<<length<<endl;
            if (!found)
            {
                Token tk;
                tk.length = 0;
                tk.next = lookAheadBuffer[0];
                tk.offset = 0;

                arrShiftLeft<char, searchBuffer.size()>(searchBuffer);
                searchBuffer[searchBuffer.size() - 1] = lookAheadBuffer[0];
                arrShiftLeft<char, lookAheadBuffer.size()>(lookAheadBuffer);
                fillAmmount--;

                if (sItr < s.length())
                {
                    lookAheadBuffer[fillAmmount] = s[sItr];
                    // cout<<"reading "<<s[sItr]<<endl;
                    sItr++;
                    fillAmmount++;
                }
                else
                {
                    lookAheadBuffer[fillAmmount] = '\0';
                }
                // cout << tk << endl;
                resultVec.push_back(tk);
            }
            else
            {
                Token tk;
                tk.length = length;
                tk.offset = searchBuffer.size() - idx;

                for (int shiftItr = 0; shiftItr < length; shiftItr++) // left shift searchBuffer and lookAheadBuffer
                {
                    arrShiftLeft<char, searchBuffer.size()>(searchBuffer);

                    // printArr<lookAheadBuffer.size()>(lookAheadBuffer);
                    // cout<<endl;

                    searchBuffer[searchBuffer.size() - 1] = lookAheadBuffer[0];
                    arrShiftLeft<char, lookAheadBuffer.size()>(lookAheadBuffer);

                    if (sItr < s.length()) // if more elements left in the string
                    {
                        fillAmmount--; // as left shifted the lookAheadBuffer
                        lookAheadBuffer[fillAmmount] = s[sItr];
                        // cout<<"reading "<<s[sItr]<<endl;
                        sItr++;        // increment the string iterator
                        fillAmmount++; // one element added to the lookAheadBuffer
                    }
                    else // no elements left in the string
                    {
                        lookAheadBuffer[fillAmmount] = '\0';
                        fillAmmount--; // as the size of the buffer decreases;
                    }
                }
                tk.next = lookAheadBuffer[0];
                { // one extra shift left on both buffers
                    arrShiftLeft<char, searchBuffer.size()>(searchBuffer);
                    searchBuffer[searchBuffer.size() - 1] = lookAheadBuffer[0];
                    arrShiftLeft<char, lookAheadBuffer.size()>(lookAheadBuffer);

                    if (sItr <= s.length()) // if more elements left in the string
                    {
                        fillAmmount--; // as left shifted the lookAheadBuffer
                        lookAheadBuffer[fillAmmount] = s[sItr];
                        // cout<<"reading "<<s[sItr]<<endl;
                        sItr++;        // increment the string iterator
                        fillAmmount++; // one element added to the lookAheadBuffer
                    }
                    else // no elements left in the string
                    {
                        lookAheadBuffer[fillAmmount] = '\0';
                        fillAmmount--; // as the size of the buffer decreases;
                    }
                }
                // cout << tk << endl;
                resultVec.push_back(tk);
            }
        }
        // printArr<SEARCH_BUFFER_LEN>(searchBuffer);
        // cout << "|";
        // printArr<LA_BUFFER_LEN>(lookAheadBuffer);
        // cout << endl;
        return resultVec;
    }

    string lz77ToStringEncode(vector<Token> tokens)
    {
        string encodedS;
        for (int i = 0; i < tokens.size(); i++)
        {
            encodedS += tokens[i].toBinS();
        }
        return encodedS;
    }

    template <int len>
    bitset<len> readBits(int sItr, string s)
    {
        // cout<<s[sItr]<<endl;
        bitset<len> bits;
        int bitsItr = 0;
        int endSItr = sItr + len;
        for (; sItr < endSItr; sItr++)
        {
            // cout<<s[sItr];
            bits[bitsItr] = (bool)(s[sItr] - 48);
            bitsItr++;
        }
        // cout<<endl;
        return bits;
    }

    pair<Token, int> decodeToken(int sItr, string s) // return the token and the new string itr
    {
        // cout<<sItr<<endl;
        if (s[sItr] == '0') // token is in ascii value
        {
            sItr++;
            bitset<CHAR_BIT_LEN> charB = readBits<CHAR_BIT_LEN>(sItr, s);
            sItr += CHAR_BIT_LEN;

            Token tk;
            tk.length = 0;
            tk.offset = 0;
            char asciiChar = (char)(charB.to_ulong());

            tk.next = asciiChar;
            // cout<<charB.to_string()<<endl;
            // cout<<tk<<endl;
            return make_pair(tk, sItr);
        }
        else // token is encoded offset,length,ascii value of next char
        {    // offset, length, next char

            sItr++;

            bitset<SEARCH_BIT_LEN> offsetB = readBits<SEARCH_BIT_LEN>(sItr, s);
            sItr += SEARCH_BIT_LEN;
            int offset = offsetB.to_ulong();

            bitset<LA_BIT_LEN> lengthB = readBits<LA_BIT_LEN>(sItr, s);
            sItr += LA_BIT_LEN;
            int length = lengthB.to_ulong();

            bitset<CHAR_BIT_LEN> charB = readBits<CHAR_BIT_LEN>(sItr, s);
            sItr += CHAR_BIT_LEN;
            char asciiChar = (char)(charB.to_ulong());

            Token tk;
            tk.offset = offset;
            tk.length = length;
            tk.next = asciiChar;
            // cout<<tk<<endl;
            return make_pair(tk, sItr);
        }
    }
    vector<Token> stringTolz77(string s)
    {
        vector<Token> resVec;
        int sItr = 0;
        while (sItr < s.length())
        {
            pair<Token, int> tokenRes = decodeToken(sItr, s);
            // cout<<tokenRes.first<<endl;
            sItr = tokenRes.second;
            resVec.push_back(tokenRes.first);
        }
        return resVec;
    }

    string lz77ToStringDecode(vector<Token> tokens)
    {
        string resS;
        int tkItr = 0;
        while (tkItr < tokens.size())
        {
            Token tk = tokens[tkItr];
            if (tk.length == 0)
            {
                resS.push_back(tk.next);
                tkItr++;
                continue;
            }
            else
            {
                int itr = resS.length();
                for (int i = 0; i < tk.offset; i++)
                {
                    itr--;
                }
                string temp;
                for (int i = 0; i < tk.length; i++)
                {
                    temp.push_back(resS[itr]);
                    itr++;
                }
                resS += temp;
                resS.push_back(tk.next);
                tkItr++;
            }
        }

        return resS;
    }
    string encode(string s)
    {
        vector<Token> tokens = lz77Encode(s);
        string encoded = lz77ToStringEncode(tokens);
        return encoded;
    }

    string decode(string s)
    {
        vector<Token> decodedTokens = stringTolz77(s);
        string decoded = lz77ToStringDecode(decodedTokens);
        return decoded;
    }
}