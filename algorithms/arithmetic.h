namespace arithmetic
{
#define CHAR_SIZE 1
#define DEFAULT_LOWER_LIMIT 0
#define DEFAULT_UPPER_LIMIT 1
    using namespace std;
    const int PRECISION = 5;

    int floatToInt(float test)
    {
        int precision = pow(10, PRECISION);
        float n = test * precision;
        int res = n;
        return n;
    }

    float intToFloat(int test)
    {
        int precision = pow(10, PRECISION);
        float n = test;
        n /= precision;
        return n;
    }

    string intToBinary(int n)
    {
        bitset<32> intB(n);
        return intB.to_string();
    }

    string floatToBinary(float f)
    {
        return intToBinary(floatToInt(f));
    }

    bool charToBool(char c)
    {
        return c == '0' ? 0 : 1;
    }

    float binaryToFloat(string binS)
    {
        bitset<32> intB;
        reverse(binS.begin(), binS.end());
        for (int i = 0; i < binS.length(); i++)
        {
            intB[i] = charToBool(binS[i]);
        }
        int n = intB.to_ulong();
        return intToFloat(n);
    }

    struct limits
    {
        float lowLim, upLim;
    };

    struct probChar
    {
        string c;
        float p;
    };

    string getString(char x)
    {
        string s(CHAR_SIZE, x);
        return s;
    }

    void cumProb(map<string, float> &charProb)
    {
        map<string, float>::iterator itr;
        float prob = 0;
        for (itr = charProb.begin(); itr != charProb.end(); ++itr)
        {
            itr->second += prob;
            prob = itr->second;
            
            /* Debugger */
            // cout << itr->second << "\n";
        }
    }

    void createCumProbArr(map<string, float> charProb, vector<probChar> &charProbArr)
    {
        map<string, float>::iterator itr;
        int i = 0;
        for (itr = charProb.begin(); itr != charProb.end(); ++itr)
        {
            charProbArr.push_back(probChar());
            charProbArr[i].c = itr->first;
            charProbArr[i].p = itr->second;

            /* Uncomment to DEBUG : Cumulative Probabilities Vector */
            // cout << charProbArr[i].c << " " << charProbArr[i].p << endl;

            i++;
        }
    }

    void fillLimitsArr(vector<probChar> &dynamicLimitsArr, vector<probChar> charProbArr, int n)
    {
        for (int i = 0; i < n; i++)
        {
            dynamicLimitsArr.push_back(probChar());
            dynamicLimitsArr[i].c = charProbArr[i].c;
            dynamicLimitsArr[i].p = charProbArr[i].p;
        }
    }

    string encode(string text, map<string, float> charProb, vector<probChar> &charProbArr, int n)
    {
        float enc;
        limits lim = {DEFAULT_LOWER_LIMIT, DEFAULT_UPPER_LIMIT};
        cumProb(charProb);
        createCumProbArr(charProb, charProbArr);

        for (int i = 0; i < text.length(); i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (getString(text[i]) == charProbArr[j].c)
                {
                    cout << text[i] << " ";
                    float tempLowLim = lim.lowLim;
                    float tempUpLim = lim.upLim;

                    lim.upLim = tempLowLim + (tempUpLim - tempLowLim) * charProbArr[j].p;
                    lim.lowLim = tempLowLim + (tempUpLim - tempLowLim) * charProbArr[j - 1].p;
                    cout << lim.upLim << " " << lim.lowLim << endl;
                }
            }

            if (i == text.length() - 1)
            {
                enc = (lim.upLim + lim.lowLim) / 2;
                cout << "ENCODED VALUE = " << enc << endl;
            }
        }
        return floatToBinary(enc);
    }

    string decode(string encBinary, vector<probChar> charProbArr, int n)
    {
        float enc = binaryToFloat(encBinary);
        string decodedStr = "";
        limits lim = {DEFAULT_LOWER_LIMIT, DEFAULT_UPPER_LIMIT};
        cout << "\nDECODE CALLED\n";

        vector<probChar> dynamicLimitsArr;
        fillLimitsArr(dynamicLimitsArr, charProbArr, n);

        for (int i = 0; i < dynamicLimitsArr.size(); i++)
        {
            for (int j = 0; j < dynamicLimitsArr.size() - 1; j++)
            {

                if (enc > dynamicLimitsArr[j].p && enc < dynamicLimitsArr[j + 1].p)
                {
                    decodedStr += dynamicLimitsArr[j + 1].c;
                    float tempLowLim = lim.lowLim;
                    float tempUpLim = lim.upLim;
                    lim.upLim = dynamicLimitsArr[j + 1].p;
                    lim.lowLim = dynamicLimitsArr[j].p;

                    for (int k = 0; k < dynamicLimitsArr.size(); k++)
                    {
                        dynamicLimitsArr[k].p = lim.lowLim + charProbArr[k].p * (lim.upLim - lim.lowLim);
                    }
                    break;
                }
            }
        }
        return decodedStr;
    }
}