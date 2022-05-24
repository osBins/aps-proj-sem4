#define CHAR_SIZE 1
#define DEFAULT_LOWER_LIMIT 0
#define DEFAULT_UPPER_LIMIT 1
using namespace std;
namespace arithmetic
{
    struct probChar
    {
        string c;
        float p;
    };
    const int PRECISION = 5;
    map<string, float> charProb = {
        make_pair("0", 0),
        make_pair("a", 0.4),
        make_pair("b", 0.2),
        make_pair("c", 0.2),
        make_pair("d", 0.2)};

    /*
    EVERYTHING BREAKS METHODICALLY IF YOU REMOVE THE IMMEDIATELY NEXT LINE OF CODE
    (but it still somehow gives the right encoded value????)
    */
    // charProb["0"] = 0; //✨ MAGIC ✨

    // charProb["a"] = 0.4;
    // charProb["b"] = 0.2;
    // charProb["c"] = 0.2;
    // charProb["d"] = 0.2;
    int n = 5;

    vector<probChar> charProbArr;

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

    string getString(char x)
    {
        string s(CHAR_SIZE, x);
        return s;
    }

    void cumProb()
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

    void createCumProbArr()
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

    void fillLimitsArr(vector<probChar> &dynamicLimitsArr)
    {
        for (int i = 0; i < n; i++)
        {
            dynamicLimitsArr.push_back(probChar());
            dynamicLimitsArr[i].c = charProbArr[i].c;
            dynamicLimitsArr[i].p = charProbArr[i].p;
        }
    }

    string encode(string text)
    {
        float enc;
        limits lim = {DEFAULT_LOWER_LIMIT, DEFAULT_UPPER_LIMIT};
        cumProb();
        createCumProbArr();

        for (int i = 0; i < text.length(); i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (getString(text[i]) == charProbArr[j].c)
                {
                    float tempLowLim = lim.lowLim;
                    float tempUpLim = lim.upLim;

                    lim.upLim = tempLowLim + (tempUpLim - tempLowLim) * charProbArr[j].p;
                    lim.lowLim = tempLowLim + (tempUpLim - tempLowLim) * charProbArr[j - 1].p;
                }
            }

            if (i == text.length() - 1)
            {
                enc = (lim.upLim + lim.lowLim) / 2;
            }
        }
        return floatToBinary(enc);
    }

    string decode(string encBinary)
    {
        cumProb();
        createCumProbArr();
        float enc = binaryToFloat(encBinary);
        cout << enc << endl
             << encBinary;
        string decodedStr = "";
        limits lim = {DEFAULT_LOWER_LIMIT, DEFAULT_UPPER_LIMIT};

        vector<probChar> dynamicLimitsArr;
        fillLimitsArr(dynamicLimitsArr);

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