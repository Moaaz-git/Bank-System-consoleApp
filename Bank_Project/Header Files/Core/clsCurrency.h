#pragma once;

#include <iostream>
#include <string>
#include "../Lib/clsString.h"
#include <fstream>
#include <vector>

class clsCurrency
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1
    };
    enMode _Mode;

    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    static clsCurrency _ConvertLineToCurrencyObject(string Line, string Delim = "#//#")
    {
        vector<string> vLineInfo = clsString::Split(Line, Delim);

        return clsCurrency(enMode::UpdateMode, vLineInfo[0], vLineInfo[1], vLineInfo[2], stof(vLineInfo[3]));
    }

    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Delim = "#//#")
    {
        string Line = "";

        Line += Currency.Country() + Delim;
        Line += Currency.CurrencyCode() + Delim;
        Line += Currency.CurrencyName() + Delim;
        Line += to_string(Currency.Rate());

        return Line;
    }

    static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencyData)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);

        string Line = "";
        if (MyFile.is_open())
        {
            for (clsCurrency Currency : vCurrencyData)
            {
                Line = _ConvertCurrencyObjectToLine(Currency);
                MyFile << Line << endl;
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsCurrency> vCurrencyData;

        vCurrencyData = _LoadCurrencysDataFromFile();

        for (clsCurrency &C : vCurrencyData)
        {
            if (C.CurrencyCode() == CurrencyCode())
            {
                C = *this;
                break;
            }
        }

        _SaveCurrencyDataToFile(vCurrencyData);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, " ", " ", " ", 0);
    }

    static vector<clsCurrency> _LoadCurrencysDataFromFile()
    {
        vector<clsCurrency> vCurrencyData;
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);

        string Line = "";
        clsCurrency Currency;

        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                Currency = _ConvertLineToCurrencyObject(Line);
                vCurrencyData.push_back(Currency);
            }
            MyFile.close();
        }

        return vCurrencyData;
    }

public:
    clsCurrency() {};
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    static vector<clsCurrency> GetAllUSDRates()
    {
        return _LoadCurrencysDataFromFile();
    }

    // Getters
    string Country() const
    {
        return _Country;
    }

    string CurrencyCode() const
    {
        return _CurrencyCode;
    }

    string CurrencyName() const
    {
        return _CurrencyName;
    }

    float Rate() const
    {
        return _Rate;
    }

    // Setters
    void SetCountry(const string &Country)
    {
        _Country = Country;
    }

    void SetCurrencyCode(const string &CurrencyCode)
    {
        _CurrencyCode = CurrencyCode;
    }

    void SetCurrencyName(const string &CurrencyName)
    {
        _CurrencyName = CurrencyName;
    }

    void SetRate(float Rate)
    {
        _Rate = Rate;
    }

    void _UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static clsCurrency FindByCountry(string CountryName)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);

        string Line = "";
        clsCurrency Currency;
        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                Currency = _ConvertLineToCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country()) == clsString::UpperAllString(CountryName))
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCode(string CurrencyCode)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);

        string Line = "";
        clsCurrency Currency;
        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                Currency = _ConvertLineToCurrencyObject(Line);
                if (Currency.CurrencyCode() == clsString::UpperAllString(CurrencyCode))
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency Currency = FindByCode(CurrencyCode);

        return !Currency.IsEmpty();
    }

    static vector<clsCurrency> GetCurrenciesList()
    {
        vector<clsCurrency> vCurrenciesData = _LoadCurrencysDataFromFile();

        return vCurrenciesData;
    }

    float ConvertToUSD(float Amount)
    {
        return float(Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }

        return float(AmountInUSD * Currency2.Rate());
    }
};