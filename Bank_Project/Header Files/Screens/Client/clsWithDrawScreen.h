#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"

class clsWithDrawScreen : protected clsScreen
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

    static string _ReadAccountNumber()
    {
        string AccNumber = clsInputValidate::ReadString();
        return AccNumber;
    }

public:
    static void ShowWithDrawScreen()
    {
        _DarwScreenHeader("\t WithDraw Screen .");

        cout << "\nEnter Account Number Please : ? ";
        string AccNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExists(AccNumber))
        {
            cout << "\nClient With Accnumber : [" << AccNumber << "] Does Not Exist <>  [:-(]..... || Try Another one >>>> ? : ";
            AccNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccNumber);
        _PrintClientCard(Client);

        double WithDrawAmount = 0;
        cout << "\nPlease Enter WithDraw Amount ? ";
        WithDrawAmount = clsInputValidate::ReadDoubleNum("Error Num [:(] ... Enter Avalid Num : ");

        char Option;
        cout << "\nAre you sure you want to performe this transaction [y/n] ? ";
        cin >> Option;

        if (Option == 'Y' || Option == 'y')
        {
            if (Client.WithDraw(WithDrawAmount))
            {
                Client.WithDraw(WithDrawAmount);
                cout << "\nAmount WithDrew Successfully.\n";
                cout << "\nNew Balance is >>> [" << Client.AccountBalance() << "]  .\n";
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << WithDrawAmount;
                cout << "\nYour Balance is: " << Client.AccountBalance();
            }
        }
        else
        {
            cout << "\nOperation Was Cancelled .\n";
        }
    }
};