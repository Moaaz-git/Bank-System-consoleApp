// Fixed version of clsString.h
// - Removed MSVC-only __declspec(property)
// - Made loops/indexes safe (use size_t)
// - Added missing includes and proper casting for <cctype> functions
// - Improved robustness for empty inputs in Join/Split/Trim functions

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class clsString
{
private:
    string _Value;

public:
    clsString() : _Value("") {}

    clsString(const string &Value) : _Value(Value) {}

    void SetValue(const string &Value) { _Value = Value; }
    string GetValue() const { return _Value; }

    // Removed: __declspec(property(...)) because it's MSVC-only and not portable

    // Length (returns short to keep API backwards compatible, but note that
    // very long strings may overflow short)
    static short Length(const string &S1)
    {
        return static_cast<short>(S1.length());
    }

    short Length() const
    {
        return static_cast<short>(_Value.length());
    }

    static short CountWords(string S1)
    {
        const string delim = " ";
        short Counter = 0;
        size_t pos = 0;
        string sWord;

        while ((pos = S1.find(delim)) != string::npos)
        {
            sWord = S1.substr(0, pos);
            if (!sWord.empty())
                Counter++;

            S1.erase(0, pos + delim.length());
        }

        if (!S1.empty())
            Counter++;

        return Counter;
    }

    short CountWords() const
    {
        return CountWords(_Value);
    }

    static string UpperFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;
        for (size_t i = 0; i < S1.length(); ++i)
        {
            unsigned char ch = static_cast<unsigned char>(S1[i]);
            if (ch != ' ' && isFirstLetter)
            {
                S1[i] = static_cast<char>(std::toupper(ch));
            }
            isFirstLetter = (ch == ' ');
        }
        return S1;
    }

    void UpperFirstLetterOfEachWord()
    {
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static string LowerFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;
        for (size_t i = 0; i < S1.length(); ++i)
        {
            unsigned char ch = static_cast<unsigned char>(S1[i]);
            if (ch != ' ' && isFirstLetter)
            {
                S1[i] = static_cast<char>(std::tolower(ch));
            }
            isFirstLetter = (ch == ' ');
        }
        return S1;
    }

    void LowerFirstLetterOfEachWord()
    {
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static string UpperAllString(string S1)
    {
        for (size_t i = 0; i < S1.length(); ++i)
        {
            S1[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(S1[i])));
        }
        return S1;
    }

    void UpperAllString()
    {
        _Value = UpperAllString(_Value);
    }

    static string LowerAllString(string S1)
    {
        for (size_t i = 0; i < S1.length(); ++i)
        {
            S1[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(S1[i])));
        }
        return S1;
    }

    void LowerAllString()
    {
        _Value = LowerAllString(_Value);
    }

    static char InvertLetterCase(char char1)
    {
        unsigned char ch = static_cast<unsigned char>(char1);
        return static_cast<char>(std::isupper(ch) ? std::tolower(ch) : std::toupper(ch));
    }

    static string InvertAllLettersCase(string S1)
    {
        for (size_t i = 0; i < S1.length(); ++i)
            S1[i] = InvertLetterCase(S1[i]);
        return S1;
    }

    void InvertAllLettersCase()
    {
        _Value = InvertAllLettersCase(_Value);
    }

    enum enWhatToCount
    {
        SmallLetters = 0,
        CapitalLetters = 1,
        All = 3
    };

    static short CountLetters(const string &S1, enWhatToCount WhatToCount = enWhatToCount::All)
    {
        if (WhatToCount == enWhatToCount::All)
            return static_cast<short>(S1.length());

        short Counter = 0;
        for (size_t i = 0; i < S1.length(); ++i)
        {
            unsigned char ch = static_cast<unsigned char>(S1[i]);
            if (WhatToCount == enWhatToCount::CapitalLetters && std::isupper(ch))
                Counter++;
            if (WhatToCount == enWhatToCount::SmallLetters && std::islower(ch))
                Counter++;
        }
        return Counter;
    }

    static short CountCapitalLetters(const string &S1)
    {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); ++i)
            if (std::isupper(static_cast<unsigned char>(S1[i])))
                Counter++;
        return Counter;
    }

    short CountCapitalLetters() const
    {
        return CountCapitalLetters(_Value);
    }

    static short CountSmallLetters(const string &S1)
    {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); ++i)
            if (std::islower(static_cast<unsigned char>(S1[i])))
                Counter++;
        return Counter;
    }

    short CountSmallLetters() const
    {
        return CountSmallLetters(_Value);
    }

    static short CountSpecificLetter(const string &S1, char Letter, bool MatchCase = true)
    {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); ++i)
        {
            if (MatchCase)
            {
                if (S1[i] == Letter)
                    Counter++;
            }
            else
            {
                if (std::tolower(static_cast<unsigned char>(S1[i])) == std::tolower(static_cast<unsigned char>(Letter)))
                    Counter++;
            }
        }
        return Counter;
    }

    short CountSpecificLetter(char Letter, bool MatchCase = true) const
    {
        return CountSpecificLetter(_Value, Letter, MatchCase);
    }

    static bool IsVowel(char Ch1)
    {
        Ch1 = static_cast<char>(std::tolower(static_cast<unsigned char>(Ch1)));
        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }

    static short CountVowels(const string &S1)
    {
        short Counter = 0;
        for (size_t i = 0; i < S1.length(); ++i)
            if (IsVowel(S1[i]))
                Counter++;
        return Counter;
    }

    short CountVowels() const
    {
        return CountVowels(_Value);
    }

    static vector<string> Split(string S1, const string &Delim)
    {
        vector<string> vString;
        size_t pos = 0;
        string sWord;
        if (Delim.empty())
        {
            // if delimiter is empty, return whole string
            vString.push_back(S1);
            return vString;
        }

        while ((pos = S1.find(Delim)) != string::npos)
        {
            sWord = S1.substr(0, pos);
            if (!sWord.empty())
                vString.push_back(sWord);
            S1.erase(0, pos + Delim.length());
        }
        if (!S1.empty())
            vString.push_back(S1);
        return vString;
    }

    vector<string> Split(const string &Delim) const
    {
        return Split(_Value, Delim);
    }

    static string TrimLeft(const string &S1)
    {
        for (size_t i = 0; i < S1.length(); ++i)
        {
            if (S1[i] != ' ')
                return S1.substr(i);
        }
        return string();
    }

    void TrimLeft()
    {
        _Value = TrimLeft(_Value);
    }

    static string TrimRight(const string &S1)
    {
        if (S1.empty())
            return string();
        for (size_t i = S1.length(); i-- > 0;)
        {
            if (S1[i] != ' ')
                return S1.substr(0, i + 1);
        }
        return string();
    }

    void TrimRight()
    {
        _Value = TrimRight(_Value);
    }

    static string Trim(const string &S1)
    {
        return TrimLeft(TrimRight(S1));
    }

    void Trim()
    {
        _Value = Trim(_Value);
    }

    static string JoinString(const vector<string> &vString, const string &Delim)
    {
        if (vString.empty())
            return string();
        string S1;
        for (size_t i = 0; i < vString.size(); ++i)
        {
            S1 += vString[i];
            if (i + 1 < vString.size())
                S1 += Delim;
        }
        return S1;
    }

    static string JoinString(const string arrString[], short Length, const string &Delim)
    {
        if (Length <= 0)
            return string();
        string S1;
        for (short i = 0; i < Length; ++i)
        {
            S1 += arrString[i];
            if (i + 1 < Length)
                S1 += Delim;
        }
        return S1;
    }

    static string ReverseWordsInString(const string &S1)
    {
        vector<string> vString = Split(S1, " ");
        if (vString.empty())
            return string();
        string S2;
        for (auto it = vString.rbegin(); it != vString.rend(); ++it)
        {
            if (!S2.empty())
                S2 += ' ';
            S2 += *it;
        }
        return S2;
    }

    void ReverseWordsInString()
    {
        _Value = ReverseWordsInString(_Value);
    }

    static string ReplaceWord(string S1, const string &StringToReplace, const string &sReplaceTo, bool MatchCase = true)
    {
        vector<string> vString = Split(S1, " ");
        for (string &s : vString)
        {
            if (MatchCase)
            {
                if (s == StringToReplace)
                    s = sReplaceTo;
            }
            else
            {
                if (LowerAllString(s) == LowerAllString(StringToReplace))
                    s = sReplaceTo;
            }
        }
        return JoinString(vString, " ");
    }

    string ReplaceWord(const string &StringToReplace, const string &sReplaceTo)
    {
        return ReplaceWord(_Value, StringToReplace, sReplaceTo);
    }

    static string RemovePunctuations(const string &S1)
    {
        string S2;
        for (size_t i = 0; i < S1.length(); ++i)
        {
            if (!std::ispunct(static_cast<unsigned char>(S1[i])))
                S2 += S1[i];
        }
        return S2;
    }

    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
    }
};
