#include <bits/stdc++.h>

using namespace std;

namespace lz77
{
    const int SEARCH_BIT_LEN = 5;
    const int SEARCH_BUFFER_LEN = 30;// search buffer length = 2^n or n bits
    const int LA_BIT_LEN = 3;
    const int LA_BUFFER_LEN = 7;// look ahead buffer length = 2^n or n bits
    const int CHAR_BIT_LEN = 5; // representing only 26 lower case letters

    using namespace std;
    string encode(string text)
    {
    }
    string decode(string text)
    {
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
                8 bit offset -> max offset = 256
                4 bit length -> max len = 16
                8 bit next char -> full bin seq
            */
            bitset<SEARCH_BIT_LEN> offsetB(offset);
            bitset<LA_BIT_LEN> lengthB(length);
            bitset<CHAR_BIT_LEN> charB(customChar(next));
            string binS; // final binary representation of token

            for (int i = 0; i < offsetB.size(); i++)
                binS.push_back(boolToChar(offsetB[i]));

            for (int i = 0; i < lengthB.size(); i++)
                binS.push_back(boolToChar(lengthB[i]));

            for (int i = 0; i < charB.size(); i++)
                binS.push_back(boolToChar(charB[i]));

            return binS;
        }
    };

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
        while (SBItr < searchBuffer.size() && LABItr < fillAmmount)
        {
            if (lookAheadBuffer[LABItr] == searchBuffer[SBItr])
            {
                res.found = true;
                res.idx = SBItr;
                int l = 0;
                while (lookAheadBuffer[LABItr] == searchBuffer[SBItr])
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
        array<char, SEARCH_BUFFER_LEN> searchBuffer = {'\0'};
        array<char, LA_BUFFER_LEN> lookAheadBuffer = {'\0'};
        vector<Token> resultVec;
        int fillAmmount = 0; // fill of the lookAheadBuffer
        int sItr = 0;
        int tempItr = 0;
        for ( // for loop for initializing the lookAheadBuffer
            ;
            sItr < s.length() && tempItr < lookAheadBuffer.size();
            sItr++)
        {
            lookAheadBuffer[tempItr] = s[sItr];
            tempItr++;
            fillAmmount++;
        }
        while (fillAmmount > 0)
        {
            SearchResult sRes = search(searchBuffer, lookAheadBuffer, fillAmmount);
            bool found = sRes.found;
            int idx = sRes.idx;
            int length = sRes.len;
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
                    lookAheadBuffer[fillAmmount] = s[sItr++];
                    fillAmmount++;
                }
                else
                {
                    lookAheadBuffer[fillAmmount] = '\0';
                }
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
                    searchBuffer[searchBuffer.size() - 1] = lookAheadBuffer[0];
                    arrShiftLeft<char, lookAheadBuffer.size()>(lookAheadBuffer);
                    fillAmmount--;          // as left shifted the lookAheadBuffer
                    if (sItr <= s.length()) // if more elements left in the string
                    {
                        lookAheadBuffer[fillAmmount] = s[sItr];
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
                { // fix this thing
                    arrShiftLeft<char, searchBuffer.size()>(searchBuffer);
                    searchBuffer[searchBuffer.size() - 1] = lookAheadBuffer[0];
                    arrShiftLeft<char, lookAheadBuffer.size()>(lookAheadBuffer);
                    fillAmmount--;          // as left shifted the lookAheadBuffer
                    if (sItr <= s.length()) // if more elements left in the string
                    {
                        lookAheadBuffer[fillAmmount] = s[sItr];
                        sItr++;        // increment the string iterator
                        fillAmmount++; // one element added to the lookAheadBuffer
                    }
                    else // no elements left in the string
                    {
                        lookAheadBuffer[fillAmmount] = '\0';
                        fillAmmount--; // as the size of the buffer decreases;
                    }
                }
                resultVec.push_back(tk);
            }
        }
        return resultVec;
    }

    string lz77ToString(vector<Token> tokens)
    {
        string encodedS;
        for (int i = 0; i < tokens.size(); i++)
        {
            encodedS += tokens[i].toBinS();
        }
        return encodedS;
    }

    vector<Token> StringTolz77(string s)
    {
    }
}