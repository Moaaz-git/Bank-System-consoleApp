#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"

class clsFindUserScreen : protected clsScreen
{
private:
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
    static void ShowFindUserScreen()
    {
        _DarwScreenHeader("\t Find User Screen .");
        
        string UserName = "";
        cout << "\nEnter UserName Please : ? ";
        UserName = clsInputValidate::ReadString();
        
        while (!clsUser::IsUserExsists(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        
        clsUser User = clsUser::Find(UserName);
        
        if (!User.IsEmpty())
        {
            cout << "\n\nUser Found   [:-)]      : ";
            cout << "\n______________________________ \n";
            _PrintUser(User);
        }
        else
        {
            cout << "\n\nOOps [:-(],  User Is Not Found ";
        }
    }
};