#pragma once

#include <iostream>
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUser.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include "../../Core/clsUser.h"

class clsMangeUsersMeneu : protected clsScreen
{

private:
    enum enMangeUsersOptions
    {
        enListUsers = 1,
        enAddNewUser = 2,
        enDeleteUser = 3,
        enUpdateUser = 4,
        enFindUser = 5,
        enMainMenue = 6
    };

    static short ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _GoBackToMangeUsersMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Mange Users Menue...\n";

        system("pause>0");
        ShowMangeUsersScreen();
    }

    static void _ShowListUsersScreen()
    {
        // cout << "\nList Users Screen Will Be Here.\n";
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        // cout << "\nAdd New User Screen Will Be Here.\n";
        clsAddNewUser::ShowAddNewUser();
    }

    static void _ShowDeleteUserScreen()
    {
        // cout << "\nDelete User Screen Will Be Here.\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        // cout << "\nUpdate User Screen Will Be Here.\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        // cout << "\nFind User Screen Will Be Here.\n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersMenueOption(enMangeUsersOptions ManageUsersMenueOption)
    {

        switch (ManageUsersMenueOption)
        {
        case enMangeUsersOptions::enListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _GoBackToMangeUsersMenue();
            break;
        }

        case enMangeUsersOptions::enAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToMangeUsersMenue();
            break;
        }

        case enMangeUsersOptions::enDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToMangeUsersMenue();
            break;
        }

        case enMangeUsersOptions::enUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToMangeUsersMenue();
            break;
        }

        case enMangeUsersOptions::enFindUser:
        {
            system("cls");

            _ShowFindUserScreen();
            _GoBackToMangeUsersMenue();
            break;
        }

        case enMangeUsersOptions::enMainMenue:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
    static void ShowMangeUsersScreen()
    {

        if(!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return ;// this will exit the function and it will not continue
        }

        system("cls");
        _DarwScreenHeader("\t  Mange Users Screen .");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Mange Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] AddNew User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersMenueOption(enMangeUsersOptions(ReadManageUsersMenueOption()));
    }
};