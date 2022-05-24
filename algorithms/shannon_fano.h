namespace shannon_fanno
{
    using namespace std;
    typedef struct node node;
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

    struct node
    {
        string sym;
        float pro;
        int arr[20];
        int top;
    };

    // function to find shannon code
    void shannon(int l, int h, node p[])
    {
        float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
        int i, d, k, j;
        if ((l + 1) == h || l == h || l > h)
        {
            if (l == h || l > h)
                return;
            p[h].arr[++(p[h].top)] = 0;
            p[l].arr[++(p[l].top)] = 1;
            return;
        }
        else
        {
            for (i = l; i <= h - 1; i++)
                pack1 = pack1 + p[i].pro;
            pack2 = pack2 + p[h].pro;
            diff1 = pack1 - pack2;
            if (diff1 < 0)
                diff1 = diff1 * -1;
            j = 2;
            while (j != h - l + 1)
            {
                k = h - j;
                pack1 = pack2 = 0;
                for (i = l; i <= k; i++)
                    pack1 = pack1 + p[i].pro;
                for (i = h; i > k; i--)
                    pack2 = pack2 + p[i].pro;
                diff2 = pack1 - pack2;
                if (diff2 < 0)
                    diff2 = diff2 * -1;
                if (diff2 >= diff1)
                    break;
                diff1 = diff2;
                j++;
            }
            k++;
            for (i = l; i <= k; i++)
                p[i].arr[++(p[i].top)] = 1;
            for (i = k + 1; i <= h; i++)
                p[i].arr[++(p[i].top)] = 0;

            // Invoke shannon function
            shannon(l, k, p);
            shannon(k + 1, h, p);
        }
    }

    void sortByProbability(int n, node p[])
    {
        int i, j;
        node temp;
        for (j = 1; j <= n - 1; j++)
        {
            for (i = 0; i < n - 1; i++)
            {
                if ((p[i].pro) > (p[i + 1].pro))
                {
                    temp.pro = p[i].pro;
                    temp.sym = p[i].sym;

                    p[i].pro = p[i + 1].pro;
                    p[i].sym = p[i + 1].sym;

                    p[i + 1].pro = temp.pro;
                    p[i + 1].sym = temp.sym;
                }
            }
        }
    }
    // function to display shannon codes
    void display(int n, node p[])
    {
        int i, j;
        cout << "\n\n\n\tSymbol\tProbability\tCode";
        for (i = n - 1; i >= 0; i--)
        {
            cout << "\n\t" << p[i].sym << "\t\t" << p[i].pro << "\t";
            for (j = 0; j <= p[i].top; j++)
                cout << p[i].arr[j];
        }
    }

    unordered_map<char, int> charFreq(string text)
    {
        unordered_map<char, int> freqMap;
        for (auto c : text)
        {
            if (freqMap.find(c) != freqMap.end())
            {
                freqMap[c] = freqMap[c] + 1;
            }
            else
            {
                freqMap[c] = 1;
            }
        }
        return freqMap;
    }
    unordered_map<char, float> charProb(unordered_map<char, int> freqMap, int len)
    {
        unordered_map<char, float> probMap;
        for (auto x : freqMap)
        {
            probMap[x.first] = (float)x.second / len;
        }
        return probMap;
    }

    unordered_map<char, string> charCode(node *p, int len)
    {
        unordered_map<char, string> codeMap;
        for (int i = 0; i < len; i++)
        {
            char c = p[i].sym[0];
            string code;
            for (int j = 0; j <= p[i].top; j++)
            {
                code += p[i].arr[j] == 0 ? '0' : '1';
            }
            codeMap[c] = code;
        }
        return codeMap;
    }
    string encodeShannon(unordered_map<char, string> codeMap, string text)
    {
        string encodedS;
        for (auto x : text)
        {
            string temp = codeMap[x];
            encodedS += temp;
        }
        return encodedS;
    }
    string codeMapToStr(unordered_map<char, string> codeMap)
    {
        string res;
        for (auto x : codeMap)
        {
            res += x.first;
            string code = x.second;
            string padding = "";
            for (int i = 0; i < 8 - code.length(); i++)
            {
                padding += '0';
            }
            char codeC = stoi(padding + code);
            bitset<8> paddingAmmt(8 - code.length());
            int paddingAmmtI = paddingAmmt.to_ulong();
            int a = paddingAmmtI;
            string paddingAmmtS = to_string(a);
            bitset<8> paddingB(stoi(padding + code));
            char paddingC = paddingB.to_ulong();
            res += paddingAmmtS + paddingC;
        }
        return res;
    }
    string encode(string text)
    {
        // cout << "str len = " << text.length() << endl;
        unordered_map<char, int> freqMap = charFreq(text);
        unordered_map<char, float> probMap = charProb(freqMap, text.length());
        node p[probMap.size()];
        int itr = 0;
        for (auto x : probMap)
        {
            p[itr].sym = x.first;
            p[itr].pro = x.second;
            itr++;
        }
        int n = probMap.size();
        sortByProbability(n, p);

        for (int i = 0; i < n; i++)
            p[i].top = -1;
        shannon(0, n - 1, p);
        unordered_map<char, string> codeMap = charCode(p, n);
        string encodedS = encodeShannon(codeMap, text);
        string byteS = binStrToByteStr(encodedS);
        string codeMapByteS = codeMapToStr(codeMap);
        string finalString = codeMapByteS + byteS;
        return finalString;
    }
    pair<string, char> getCode(char chtr, char paddingCount, char code)
    {
        int padding = paddingCount - '0';
        string codeS;
        bitset<8> codeB(code);
        string codeSTemp = codeB.to_string();
        for (int i = padding - 1; i < 8; i++)
        {
            codeS += codeSTemp[i];
        }
        return make_pair(codeS, chtr);
    }

    // string decode(string encodedS)
    // {

    //     int charcount = encodedS[0];
    //     int counter = 0;
    //     string byteS;
    //     unordered_map<string, char> codeCharMap;
    //     int i;
    //     for (i = 1; i < encodedS && counter < charcount; i++)
    //     {
    //         char chtr = encodedS[i], paddingcount = encodedS[i + 1], code = encodedS[i + 2];
    //         pair<string, char> res = getCode(chtr, paddingcount, code);
    //         codeCharMap[res.first] = res.second;
    //         counter += 1;
    //         i += 3;
    //     }
    //     for (i; i < encodedS; i++)
    //     {
    //         byteS += encodedS[i];
    //     }
    // }

}