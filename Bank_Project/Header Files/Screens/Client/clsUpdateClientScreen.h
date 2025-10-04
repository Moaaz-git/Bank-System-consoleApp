#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"
#include "../../Core/clsUser.h"

class clsUpdateClientScreen : protected clsScreen
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
    static void ShowUpdateClientScreen()
    {
        if(!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return ;// this will exit the function and it will not continue
        }

        system("cls");

        _DarwScreenHeader("\t Update Clients Screen .");

        string AccountNumber = "";
        cout << "Please Enter Client Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nAccount Number Is Not Found   [:(] , Try Another One !! : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _PrintClientCard(Client);

        cout << "\n\nDo You Want To Update This Client ?  [Y/N]: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\n__________________\n\n";
            cout << "   Update Client : ";
            cout << "\n\n__________________\n";

            _ReadClientInfo(Client);

            clsBankClient::enSaveResults Save;

            Save = Client.Save();

            switch (Save)
            {
            case clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\n\n_________________________________\n\n";
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClientCard(Client);
                break;
            }
            case clsBankClient::enSaveResults::svFalidEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            }
        }
        else
        {
            cout << "\nClient Was not Updated ,    [:-)]     See You Later ......\n";
        }
    }
};