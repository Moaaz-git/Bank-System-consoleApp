#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"

class clsAddNewUser : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser &User)
    {

        string Input = "";

        cout << "\nEnter FirstName: ";
        Input = clsInputValidate::ReadString();
        User.SetFirstName(Input);

        cout << "\nEnter LastName: ";
        Input = clsInputValidate::ReadString();
        User.SetLastName(Input);

        cout << "\nEnter Email: ";
        Input = clsInputValidate::ReadString();
        User.SetEmail(Input);

        cout << "\nEnter Phone: ";
        Input = clsInputValidate::ReadString();
        User.SetPhoneNumber(Input);

        cout << "\nEnter Password: ";
        Input = clsInputValidate::ReadString();
        User.SetPassword(Input);

        cout << "\nEnter Permission: ";
        int Per = _ReadPermissionsToSet();
        User.SetPermissions(Per);
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

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nLogin Registers? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegisters;
        }

        cout << "\nCurrency Exhange? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pCurrency;
        }

        return Permissions;
    }

public:
    static void ShowAddNewUser()
    {
        _DarwScreenHeader("\t AddNew User Screen .");

        string UserName = "";
        cout << "\nEnter Anew UserName Please : ? ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExsists(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResults;
        SaveResults = NewUser.Save();

        switch (SaveResults)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;
        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;
        }
        }
    }
};