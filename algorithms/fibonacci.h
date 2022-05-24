using namespace std;
#include <iostream>
using namespace std;

// To limit on the largest Fibonacci number to be used
#define N 30
namespace fibonacci
{

    /* Array to store fibonacci numbers. fib[i] is going
    to store (i+2)'th Fibonacci number*/
    int fib[N];

    // Stores values in fib and returns index of the largest
    // fibonacci number smaller than n.
    int largestFiboLessOrEqual(int n)
    {
        fib[0] = 1; // Fib[0] stores 2nd Fibonacci No.
        fib[1] = 2; // Fib[1] stores 3rd Fibonacci No.

        // Keep Generating remaining numbers while previously
        // generated number is smaller
        int i;
        for (i = 2; fib[i - 1] <= n; i++)
            fib[i] = fib[i - 1] + fib[i - 2];

        // Return index of the largest fibonacci number
        // smaller than or equal to n. Note that the above
        // loop stopped when fib[i-1] became larger.
        return (i - 2);
    }

    /* Returns pointer to the char string which corresponds to
    code for n */
    char *fibonacciEncoding(int n)
    {
        int index = largestFiboLessOrEqual(n);

        // allocate memory for codeword
        char *codeword = (char *)malloc(sizeof(char) * (index + 3));

        // index of the largest Fibonacci f <= n
        int i = index;

        while (n)
        {
            // Mark usage of Fibonacci f (1 bit)
            codeword[i] = '1';

            // Subtract f from n
            n = n - fib[i];

            // Move to Fibonacci just smaller than f
            i = i - 1;

            // Mark all Fibonacci > n as not used (0 bit),
            // progress backwards
            while (i >= 0 && fib[i] > n)
            {
                codeword[i] = '0';
                i = i - 1;
            }
        }

        // additional '1' bit
        codeword[index + 1] = '1';
        codeword[index + 2] = '\0';

        // return pointer to codeword
        return codeword;
    }
    struct symbol
    {
        string fibCode;
        unsigned char symbol;
    };

    string Binary(int n)
    {
        // array to store binary number
        int binaryNum[32];

        // counter for binary array
        int i = 0;
        while (n > 0)
        {

            // storing remainder in binary array
            binaryNum[i] = n % 2;
            n = n / 2;
            i++;
        }
        string binS;
        // printing binary array in reverse order
        for (int j = i - 1; j >= 0; j--)
        {
            binS += to_string(binaryNum[j]);
        }
        return binS;
    }

    string encode(string seq)
    {
        int seqLength = seq.length();
        int ascii[seqLength];

        for (int i = 0; i < seqLength; i++)
        {
            ascii[i] = int(seq[i]);
        }

        int fibonacci[seqLength];
        for (int i = 0; i < seqLength; i++)
        {
            fibonacci[i] = long(fibonacciEncoding(ascii[i]));
        }
        string encodedS;
        for (int i = 0; i < seqLength; i++)
        {
            encodedS += Binary(fibonacci[i]);
        }
        return encodedS;
    }
    string decode(string text)
    {
    }
}