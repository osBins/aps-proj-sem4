namespace shannon_fanno
{
    using namespace std;
    typedef struct node node;

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
    string encode(unordered_map<char, string> codeMap, string text)
    {
        string encodedS;
        for (auto x : text)
        {
            string temp = codeMap[x];
            encodedS += temp;
        }
        return encodedS;
    }
    string mapToByteStr(unordered_map<char,string> codeMap)
    {
        
    }
    string decode(string text)
    {
    }

}