#include<bits/stdc++.h>
using namespace std;

int i = 0, f, l;
string input;

int processX()
{
    while (i < l - 1)
    {
        if (input[i] == 'b' && (input[i + 1] == 'b' || input[i + 1] == 'c'))
            i = i + 2;
        else
            return 0;
    }
    return 1;
}

void processA()
{
    if (input[i] == 'a')
    {
        i++;
        if (l == 2 && input[l - 1] == 'd')
            f = 1;
        else
        {
            if (processX() && input[l - 1] == 'd')
                f = 1;
            else
                f = 0;
        }
    }
    else
        f = 0;
}

int main()
{
    cout << "Enter string: ";
    getline(cin, input);
    l = input.length();
    processA();
    if (f)
        cout << "The string is accepted";
    else
        cout << "The string is not accepted";
    return 0;
}
