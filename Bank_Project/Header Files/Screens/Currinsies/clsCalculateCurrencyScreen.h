#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsCurrency.h"

class clsCalculateCurrencyScreen : protected clsScreen
{
private:
    static float _ReadAmount()
    {
        cout << "\nRead Amount To Exhange : ";
        float Amount = clsInputValidate::ReadFloatNum("Error Enter Avalid Number ? ");

        return Amount;
    }

    static void _PrindCurrencyCard(string Title, clsCurrency &Currency)
    {
        cout << "\n" << Title;
        cout << "\n__________________________________";
        cout << "\nCountrey    : " << Currency.Country();
        cout << "\nCode        : " << Currency.CurrencyCode();
        cout << "\nName        : " << Currency.CurrencyName();
        cout << "\nRate(1$) =  : " << Currency.Rate();
        cout << "\n__________________________________\n\n";
    }

    static clsCurrency _GetCurrency(string message)
    {
        string CurrencyCode = " ";
        cout << "\n"
             << message << endl;
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nOops Currency Not Exist Try Again ? ";
            CurrencyCode = clsInputValidate::ReadString();
        }
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        return Currency;
    }

    static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {
        _PrindCurrencyCard("Convert From : ", CurrencyFrom);

        float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

        cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInUSD << " $USD \n";

        if (CurrencyTo.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting From USD to \n";

        _PrindCurrencyCard("To : ", CurrencyTo);

        float AmountInCurrencyTO = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

        cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInCurrencyTO << " " << CurrencyTo.CurrencyCode() << " \n";
    }

public:
    static void ShowCalculateCurrencyScreen()
    {
        char OptionOfAnotherOp = 'n';
        do
        {
            system("cls");

            _DarwScreenHeader("\t Calculate Currency Screen .");
            clsCurrency Currency_From = _GetCurrency("Pleas Enter Currency 1 Code :");
            clsCurrency Currency_To = _GetCurrency("Pleas Enter Currency 2 Code :");

            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, Currency_From, Currency_To);

            cout << "\n\nDo You Want to Performe another calcualation? [y/n] ?";
            cin >> OptionOfAnotherOp;

        } while (OptionOfAnotherOp == 'y' || OptionOfAnotherOp == 'Y');
    }
};