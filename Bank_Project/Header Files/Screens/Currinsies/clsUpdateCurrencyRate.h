#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"

class clsUpdateCurrencyRate : protected clsScreen
{
private:
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

    static bool _UpdateCurrencyRate(clsCurrency &Currency)
    {
        cout << "\n\nUpdate Currency Rate : ";
        cout << "\n\n__________________________________________";

        float NewRate = 0;

        cout << "\n\nEnter New Rate : ";
        NewRate = clsInputValidate::ReadFloatNum("Error Enter Valid Num   [:(] ?");

        Currency._UpdateRate(NewRate);

        return true;
    }

public:
    static void ShowUpdateCurrencyScreen()
    {
        _DarwScreenHeader("\t Update Currency Screen .");

        string Code = " ";
        cout << "\nPlease Enter CurrencyCode ? ";
        Code = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(Code))
        {
            cout<<"\nOops Currency Not Exist Try Again ? ";
            Code = clsInputValidate::ReadString();
        }
        clsCurrency Currency = clsCurrency::FindByCode(Code);
        

        _PrindCurrencyCard(Currency);

        char Option = 'n';
        cout << "\n\nAre you sure you want to update the rate of this currency ? [y/n] ";
        cin >> Option;

        if (Option == 'Y' || Option == 'y')
        {
            if (_UpdateCurrencyRate(Currency))
            {
                cout << "\n\n__________________________________________";
                cout << "\n\nCurrency Updated Successfully   [:)]......\n";
                _PrindCurrencyCard(Currency);
            }
            else
            {
                cout << "\n\n__________________________________________";
                cout << "\n\nCurrency Updated  Falid   [:()]......\n";
            }
        }
    }
};