#include<bits/stdc++.h>
using namespace std;

bool isExpn(const string& inp, int& index);
bool isTerm(const string& inp, int& index);
bool isFactor(const string& inp, int& index);
bool isNUM(const string& inp, int& index);
bool isID(const string& inp, int& index);

bool isID(const string& inp, int& index)
{
    if (inp[index] >= 'a' && inp[index] <= 'z')
    {
        index++;
        return true;
    }
    return false;
}

bool isNUM(const string& inp, int& index)
{
    if (inp[index] >= '0' && inp[index] <= '9')
    {
        index++;
        return true;
    }
    return false;
}

bool isFactor(const string& inp, int& index)
{
    if (inp[index] == '(')
    {
        index++;
        if (isExpn(inp, index))
        {
            if (inp[index] == ')')
            {
                index++;
                return true;
            }
        }
        return false;
    }
    return isID(inp, index) || isNUM(inp, index);
}

bool isTerm(const string& inp, int& index)
{
    if (isFactor(inp, index))
    {
        while (index < inp.length() && (inp[index] == '*' || inp[index] == '/'))
        {
            index++;
            if (!isFactor(inp, index))
                return false;
        }
        return true;
    }
    return false;
}

bool isExpn(const string& inp, int& index)
{
    if (isTerm(inp, index))
    {
        while (index < inp.length() && (inp[index] == '+' || inp[index] == '-'))
        {
            index++;
            if (!isTerm(inp, index))
                return false;
        }
        return true;
    }
    return false;
}

int main()
{
    string inp;
    cout << "Enter arithmetic expression: ";
    getline(cin, inp);

    int index = 0;
    if (isExpn(inp, index) && index == inp.length())
        cout << "The arithmetic expression is accepted.";
    else
        cout << "The arithmetic expression is not accepted";

    return 0;
}
