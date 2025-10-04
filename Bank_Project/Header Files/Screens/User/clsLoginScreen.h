#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../clsGlobal.h"
#include "../clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
    static bool _Login()
    {
        bool LoginFaild = false;
        short CountFaild = 0;

        cout << "\t\t\t\t\t______________________________________\n\n";

        do
        {
            string Username, Password;
            if (LoginFaild)
            {
                CountFaild++;
                cout << "\n\t\t\t\t\tInvlaid Username/Password!";
                cout << "\n\t\t\t\t\tYou Have " << (3 - CountFaild) << " Trails To Login.\n\n";
            }
            if (CountFaild == 3)
            {
                cout << "\n\t\t\t\t\t______________________________________";
                cout << "\n\n\t\t\t\t\tOops [:-(], You Are Locked After Three Trails .";
                return false;
            }

            cout << "\t\t\t\t\tEnter Username? ";
            cin >> Username;

            cout << "\t\t\t\t\tEnter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        if (!LoginFaild)
        {
            CurrentUser.RegisterLogIn();
        }
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DarwScreenHeader("\t     Login Screen .");
        return _Login();
    }
};