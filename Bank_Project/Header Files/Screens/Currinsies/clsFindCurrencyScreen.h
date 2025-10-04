#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"
#include "iomanip"

class clsFindCurrencyScreen : protected clsScreen
{

private:
    enum enFindOption
    {
        ByCode = 1,
        ByCountry = 2
    };

    static short _ReadFindOption()
    {
        short Option;
        cout << "\n\nFind By : [1] Code Or [2] Country ? ";
        Option = clsInputValidate::ReadShortNumBetween(1, 2, "\nError Enter Num [1] Or [2] ? ");

        return Option;
    }

    static void _PrindCurrencyCard(clsCurrency &Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n__________________________________";
        cout << "\nCountrey    : " << Currency.Country();
        cout << "\nCode        : " << Currency.CurrencyCode();
        cout << "\nName        : " << Currency.CurrencyName();
        cout << "\nRate(1$) =  : " << Currency.Rate();
        cout << "\n__________________________________";
    }

    static void _ShowResult(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\n__________________________________\n";
            cout << "\nCurrency Found  [:)]....\n";
            cout << "\n________________________________________________\n";
            _PrindCurrencyCard(Currency);
        }
        else
        {
            cout << "\n__________________________________\n";
            cout << "\nOOps Currency Not Found  [:(]....";
            cout << "\n________________________________________________\n";
            _PrindCurrencyCard(Currency);
        }
    }

public:
    static void ShowFindCurrencyScreen()
    {
        _DarwScreenHeader("\t Find Currency Screen .");

        short Option = _ReadFindOption();

        if (enFindOption(Option) == enFindOption::ByCode)
        {
            string Code = " ";
            cout << "\nPlease Enter CurrencyCode ? ";
            Code = clsInputValidate::ReadString();

            clsCurrency Currency = clsCurrency::FindByCode(Code);

            _ShowResult(Currency);
        }
        if (enFindOption(Option) == enFindOption::ByCountry)
        {
            string Country = " ";
            cout << "\nPlease Enter Country Name ? ";
            Country = clsInputValidate::ReadString();

            clsCurrency Currency_1 = clsCurrency::FindByCountry(Country);

            _ShowResult(Currency_1);
        }
    }
};