#pragma once

#include <iostream>
#include "iomanip"
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "Client/clsClientListScreen.h"
#include "Client/clsAddNewClientScreen.h"
#include "Client/clsDeleteClientScreen.h"
#include "Client/clsUpdateClientScreen.h"
#include "Client/clsFindClientScreen.h"
#include "Client/clsTransactionMenue.h"
#include "User/clsMangeUsersMeneu.h"
#include "User/clsLoginRegisterScreen.h"
#include "Currinsies/clsCurrencyExhangeScreen.h"
#include "../clsGlobal.h"

class clsMainScreen : protected clsScreen
{

private:
    enum enMainMenueOpthions
    {
        enListClients = 1,
        enAddNewClient = 2,
        enDeleteClient = 3,
        enUpdateClient = 4,
        enFindClient = 5,
        enShowTransactionsMenue = 6,
        enMangeUsers = 7,
        enLoginList = 8,
        enCurrency = 9,
        enExit = 10
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Option = clsInputValidate::ReadShortNumBetween(1, 10, "Enter Number between 1 to 10? ");
        return Option;
    }

    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsListScreen();
    }

    static void _ShowAddNewClientsScreen()
    {
        // cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        // cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        // cout << "\nUpdate Client Screen Will be here...\n";

        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        // cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        // cout << "\nTransactions Menue Will be here...\n";
        clsTransactionMenue::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        // cout << "\nUsers Menue Will be here...\n";
        clsMangeUsersMeneu::ShowMangeUsersScreen();
    }

    // static void _ShowEndScreen()
    // {
    //     cout << "\nEnd Screen Will be here...\n";
    // }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("","");
    }

    static void _ShowLoginListScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyScreen()
    {
        clsCurrencyExhangeScreen::ShowCurrencyExhangeScreen();
    }

    static void _PerfromMainMenueOption(enMainMenueOpthions enOption)
    {
        switch (enOption)
        {
        case enMainMenueOpthions::enListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enAddNewClient:
        {
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enDeleteClient:
        {
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enUpdateClient:
        {
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enFindClient:
        {
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enShowTransactionsMenue:
        {
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enMangeUsers:
        {
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enLoginList:
        {
            system("cls");
            _ShowLoginListScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enCurrency:
        {
            system("cls");
            _ShowCurrencyScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOpthions::enExit:
        {
            system("cls");
            _Logout();
            break;
        }
        }
    }

public:
    static void ShowMainMenue()
    {
        system("cls");
        _DarwScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Registers.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exhange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption(enMainMenueOpthions(_ReadMainMenueOption()));
    }
};