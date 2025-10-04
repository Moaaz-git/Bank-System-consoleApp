#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "clsDate.h"

using namespace std;

class clsUtil
{

private:
public:
    enum enCharType
    {
        CapitalLetter = 1,
        SmallLetter = 2,
        Digit = 3,
        SpecialChar = 4,
        Mix = 5
    };

    static void Srand()
    {
        srand(unsigned(time(NULL)));
    }

    static int RandomNum(int From, int To)
    {
        return rand() % ((To - From) + 1) + From;
    }

    static char GetRandomChar(clsUtil::enCharType Type)
    {

        switch (Type)
        {
        case clsUtil::enCharType::CapitalLetter:
        {
            return char(RandomNum(65, 90));
        }
        case clsUtil::enCharType::SmallLetter:
        {
            return char(RandomNum(97, 122));
        }
        case clsUtil::enCharType::Digit:
        {
            return char(RandomNum(48, 57));
        }
        case clsUtil::enCharType::SpecialChar:
        {
            return char(RandomNum(33, 47));
        }

        case clsUtil::enCharType::Mix:
        {
            int num = RandomNum(1, 4);
            return GetRandomChar(static_cast<enCharType>(num));
        }

        default:
            return '?';
        }
    }

    static string GenerateWord(clsUtil::enCharType Type, int NumOfChars)
    {

        string word = "";

        for (size_t i = 0; i < NumOfChars; i++)
        {
            word += GetRandomChar(Type);
        }

        return word;
    }

    static string GenerateKey(clsUtil::enCharType Type)
    {

        string word = "";

        word += GenerateWord(Type, 4) + '-';
        word += GenerateWord(Type, 4) + '-';
        word += GenerateWord(Type, 4) + '-';
        word += GenerateWord(Type, 4);

        return word;
    }

    static void GenerateKeys(int NumOfKeys, clsUtil::enCharType Type)
    {

        string word = "";

        for (size_t i = 0; i < NumOfKeys; i++)
        {
            word = GenerateKey(Type);
            cout << "\n"
                 << "Key [" << i + 1 << "] : " << word;
        }
    }

    static void Swap(int &num1, int &num2)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }

    static void Swap(double &num1, double &num2)
    {
        double temp = num1;
        num1 = num2;
        num2 = temp;
    }

    static void Swap(string &num1, string &num2)
    {
        string temp = num1;
        num1 = num2;
        num2 = temp;
    }

    static void Swap(clsDate &Dat1, clsDate &Dat2)
    {
        clsDate temp = Dat1;
        Dat1 = Dat2;
        Dat2 = temp;
    }

    static void ShuffleArray(int arr[], int size)
    {
        for (size_t i = 0; i < size; i++)
        {
            // int randIndex = RandomNum(0, size - 1);
            // int temp = arr[randIndex];
            // arr[randIndex] = arr[i];
            // arr[i] = temp;
            Swap(arr[RandomNum(0, size - 1)], arr[i]);
        }
    }

    static void ShuffleArray(string arr[], int size)
    {
        for (size_t i = 0; i < size; i++)
        {
            // int randIndex = RandomNum(0, size - 1);
            // string temp = arr[randIndex];
            // arr[randIndex] = arr[i];
            // arr[i] = temp;
            Swap(arr[RandomNum(0, size - 1)], arr[i]);
        }
    }

    static void FillArrayWithRandomNumbers(int arr[], int size, int From, int To)
    {
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = RandomNum(From, To);
        }
    }

    static void FillArrayWithRandomWords(string arr[], int size, clsUtil::enCharType Type, int LengthOfWord)
    {
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = GenerateWord(Type, LengthOfWord);
        }
    }

    static void FillArrayWithRandomKeys(string arr[], int size, clsUtil::enCharType Type)
    {
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = GenerateKey(Type);
        }
    }

    static string Tabs(short NumOfTabs)
    {
        string S1 = "";
        for (size_t i = 0; i < NumOfTabs; i++)
        {
            S1 += "\t";
        }

        return S1;
    }

    static string EncryptText(string Text, short EncryptionKey = 2)
    {

        for (size_t i = 0; i < Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey = 2)
    {

        for (size_t i = 0; i < Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptionKey);
        }

        return Text;
    }

    static string NumberToText(int Number)
    {
        if (Number == 0)
        {
            return " ";
        }
        if (Number >= 0 && Number <= 19)
        {
            string arr[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
                            "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                            "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

            return arr[Number] + " ";
        }
        if (Number >= 20 && Number <= 99)
        {
            string arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }
        if (Number >= 100 && Number <= 199)
        {
            return "OneHundred " + NumberToText(Number % 100);
        }
        if (Number >= 200 && Number <= 999)
        {
            return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }
        if (Number >= 1000 && Number <= 1999)
        {
            return "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }
};