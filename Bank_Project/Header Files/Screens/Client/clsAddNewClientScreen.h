#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"
#include "../../Core/clsUser.h"

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient &Client)
    {
        string input = "";
        cout << "\n\nEnter FirstName : ";
        input = clsInputValidate::ReadString();
        Client.SetFirstName(input);

        cout << "\nEnter LastName : ";
        input = clsInputValidate::ReadString();
        Client.SetLastName(input);

        cout << "\nEnter Email : ";
        input = clsInputValidate::ReadString();
        Client.SetEmail(input);

        cout << "\nEnter Phone : ";
        input = clsInputValidate::ReadString();
        Client.SetPhoneNumber(input);

        cout << "\nEnter Password : ";
        input = clsInputValidate::ReadString();
        Client.SetPinCode(input);

        cout << "\nEnter Balance : ";
        input = clsInputValidate::ReadString();
        Client.SetAccountBalance(stof(input));
    }

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
    static void ShowAddNewClientScreen()
    {
        if(!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return ;// this will exit the function and it will not continue
        }

        system("cls");
        _DarwScreenHeader("\t Add New Client Screen .");

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetNewBankClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClientCard(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFalidEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
        }
    }
};