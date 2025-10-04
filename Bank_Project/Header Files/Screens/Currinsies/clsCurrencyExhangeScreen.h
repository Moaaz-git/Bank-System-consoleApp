#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsCurrency.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRate.h"
#include "clsCalculateCurrencyScreen.h"

class clsCurrencyExhangeScreen : protected clsScreen
{
private:
    enum enCurrenciesMenueOptions
    {
        eList = 1,
        eFind = 2,
        eUpdate = 3,
        eCalculate = 4,
        eShowMainMenue = 5
    };

    static short ReadCurrenciesMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Option = clsInputValidate::ReadShortNumBetween(1, 5, "Enter Number between 1 to 5? ");
        return Option;
    }

    static void _ShowListScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen() ;
    }

    static void _ShowUpdateScreen()
    {
        clsUpdateCurrencyRate::ShowUpdateCurrencyScreen() ;
    }

    static void _ShowCalculateScreen()
    {
        clsCalculateCurrencyScreen::ShowCalculateCurrencyScreen();
    }

    static void _GoBackToCurrencyScreen()
    {
        cout << "\n\nPress any key to go back To Currency Exhange Main Menue...";
        system("pause>0");
        ShowCurrencyExhangeScreen();
    }

    static void _PerformCurrenciesMenueOption(enCurrenciesMenueOptions Option)
    {

        switch (Option)
        {
        case enCurrenciesMenueOptions::eList:
        {
            system("cls");
            _ShowListScreen();
            _GoBackToCurrencyScreen();
            break;
        }
        case enCurrenciesMenueOptions::eFind:
        {
            system("cls");
            _ShowFindScreen();
            _GoBackToCurrencyScreen();
            break;
        }

        case enCurrenciesMenueOptions::eUpdate:
        {
            system("cls");
            _ShowUpdateScreen();
            _GoBackToCurrencyScreen();
            break;
        }

        case enCurrenciesMenueOptions::eCalculate:
        {
            system("cls");
            _ShowCalculateScreen();
            _GoBackToCurrencyScreen();
            break;
        }

        case enCurrenciesMenueOptions::eShowMainMenue:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    };

public:
    static void ShowCurrencyExhangeScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pCurrency))
        {
            return; // this will exit the function and it will not continue
        }

        system("cls");
        _DarwScreenHeader("    Currency Exhange Main Screen .");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exhange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrenciesMenueOption((enCurrenciesMenueOptions)ReadCurrenciesMenueOption());
    }
};