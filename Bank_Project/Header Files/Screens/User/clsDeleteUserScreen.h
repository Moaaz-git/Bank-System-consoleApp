#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"

class clsDeleteUserScreen : protected clsScreen
{

private:
    static string _ReadUserName()
    {
        cout << "\nEnter The UserName Please : ? ";
        string UserName = clsInputValidate::ReadString();

        return UserName;
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n______________________________";
        cout << "\nFirstName   : " << User.FirstName();
        cout << "\nLastName    : " << User.LastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email();
        cout << "\nPhone       : " << User.PhoneNumber();
        cout << "\nUser Name   : " << User.UserName();
        cout << "\nPassword    : " << User.Password();
        cout << "\nPermissions : " << User.Permissions();
        cout << "\n______________________________";
    }

public:
    static void ShowDeleteUserScreen()
    {
        _DarwScreenHeader("\t Delete User Screen .");

        string UserName = _ReadUserName();

        while (!clsUser::IsUserExsists(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);

        cout << "\n\nAre You Sure You Want To Delete This User ?  [y/n] ";
        char Option = 'n';

        cin >> Option;

        if (Option == 'Y' || Option == 'y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }
};