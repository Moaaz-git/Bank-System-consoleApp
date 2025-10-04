#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"
#include "../../Core/clsUser.h"

class clsFindClientScreen : protected clsScreen
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
    static void ShowFindClientScreen()
    {
        if(!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return ;// this will exit the function and it will not continue
        }

        system("cls");

        _DarwScreenHeader("\t Find Client Screnn .");

        string AccountNumber = "";
        cout << "Please Enter Client Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        if (!clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nOpss Account Number Is Not Found     [:(] ......\n\n\n";
        }
        else
        {
            cout<<"\n\nClient Found     [:-)]   : ____________________________\n\n";
            clsBankClient Client = clsBankClient::Find(AccountNumber);

            _PrintClientCard(Client);
        }
    }
};