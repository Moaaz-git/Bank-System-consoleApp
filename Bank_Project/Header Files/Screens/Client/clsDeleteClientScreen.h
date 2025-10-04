#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"
#include "../../Core/clsUser.h"

class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n______________________________";
        cout << "\nFirstName   : " << Client.FirstName();
        cout << "\nLastName    : " << Client.LastName();
        cout << "\nFullName    : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.PhoneNumber();
        cout << "\nAcc, Number : " << Client.AccountNumber();
        cout << "\nPassWord    : " << Client.PinCode();
        cout << "\nBalance     : " << Client.AccountBalance();
        cout << "\n______________________________\n\n\n";
    }

public:
    static void ShowDeleteClientScreen()
    {
        if(!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return ;// this will exit the function and it will not continue
        }

        system("cls");
        _DarwScreenHeader("\t Delete Clients Screen .");

        string AccountNumber = "";
        cout << "Please Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nAccount Number Is Not Found [:-(] , Please Chooce Another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _PrintClientCard(Client);

        cout << "\n\nDo You Want To Delete This Client ?  [Y/N]: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.DeleteClient())
            {
                cout << "\nClient Deleted Successfully :-)\n";

                _PrintClientCard(Client);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }
};