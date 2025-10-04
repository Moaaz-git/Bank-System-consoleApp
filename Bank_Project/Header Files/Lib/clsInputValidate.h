#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "clsString.h"
#include "clsDate.h"
#include <ctime>

using namespace std;

class clsInputValidate
{
private:
public:
    static bool IsNumberBetween(int NumToTest, int from, int to)
    {
        return (NumToTest >= from && NumToTest <= to);
    }

    static bool IsNumberBetween(double NumToTest, double from, double to)
    {
        return (NumToTest >= from && NumToTest <= to);
    }

    static bool IsDateBetween(clsDate DateToTest, clsDate Date1, clsDate Date2)
    {
        if (clsDate::CompareDates(Date1, Date2) == clsDate::After)
        {
            clsDate::SwapDates(Date1, Date2);
        }
        return ((clsDate::CompareDates(DateToTest, Date1) == clsDate::After || clsDate::CompareDates(DateToTest, Date1) == clsDate::Equal) &&
                (clsDate::CompareDates(DateToTest, Date2) == clsDate::Before || clsDate::CompareDates(DateToTest, Date2) == clsDate::Equal));
    }

    static int ReadIntNum(string Message)
    {

        int num = 0;
        while (true)
        {
            cin >> num;

            if (cin.fail())
            {

                cout << Message << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                break;
            }
        }

        return num;
    }

    static short ReadShortNum(string Message)
    {

        short num = 0;
        while (true)
        {
            cin >> num;

            if (cin.fail())
            {

                cout << Message << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                break;
            }
        }

        return num;
    }

    static double ReadDoubleNum(string Message)

    {

        double num = 0;
        while (true)
        {
            cin >> num;

            if (cin.fail())
            {

                cout << Message << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                break;
            }
        }

        return num;
    }

    static float ReadFloatNum(string Message)

    {

        float num = 0;
        while (true)
        {
            cin >> num;

            if (cin.fail())
            {

                cout << Message << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                break;
            }
        }

        return num;
    }

    static int ReadIntNumBetween(int from, int to, string Message)
    {
        int Num = ReadIntNum("Invalid Num Try again  [:-(] \n");

        while (!IsNumberBetween(Num, from, to))
        {
            cout << Message << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Num = ReadIntNum("Invalid Num Try again  [:-(] \n");
        }

        return Num;
    }

    static short ReadShortNumBetween(short from, short to, string Message)
    {
        short Num = ReadShortNum("Invalid Num Try again  [:-(] \n");

        while (!IsNumberBetween(Num, from, to))
        {
            cout << Message << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Num = ReadShortNum("Invalid Num Try again  [:-(] \n");
        }

        return Num;
    }

    static double ReadDoubleNumBetween(double from, double to, string Message)
    {
        double Num = ReadDoubleNum("Invalid Num Try again  [:-(] \n");

        while (!IsNumberBetween(Num, from, to))
        {
            cout << Message << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Num = ReadIntNum("Invalid Num Try again  [:-(] \n");
        }

        return Num;
    }

    static bool IsValidDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }

    static string ReadString()
    {
        string Line = "";

        getline(cin >> ws, Line);

        return Line;
    }
};
