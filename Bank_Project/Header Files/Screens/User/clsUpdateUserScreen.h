#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsUser.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"

class clsUpdateUserScreen : protected clsScreen
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

    static void _ReadPermissions(clsUser &User)
    {
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
    static void ShowUpdateUserScreen()
    {
        _DarwScreenHeader("\t Update User Screen .");

        string UserName = "";
        cout << "\nEnter UserName Please : ? ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExsists(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);

        char Option_2 = 'n';
        cout << "\n\nDo You Want Just To Update Permissions ? [y/n] ";
        cin >> Option_2;

        if (Option_2 == 'Y' || Option_2 == 'y')
        {
            cout << "\n\nUpdate Permissions Info:";
            cout << "\n____________________\n";

            _ReadPermissions(User);

            clsUser::enSaveResults SaveUser;
            SaveUser = User.Save();

            switch (SaveUser)
            {
            case clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";

                _PrintUser(User);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;
            }
            }

            return;
        }

        cout << "\n\nAre You Sure You Want To Update This User Info ?  [y/n] ";
        char Option = 'n';

        cin >> Option;

        if (Option == 'Y' || Option == 'y')
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _ReadUserInfo(User);

            clsUser::enSaveResults SaveUser;
            SaveUser = User.Save();

            switch (SaveUser)
            {
            case clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";

                _PrintUser(User);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;
            }
            }
        }
    }
};