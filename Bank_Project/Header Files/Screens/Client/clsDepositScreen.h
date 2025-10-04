#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"


class clsDepositScreen : protected clsScreen
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
    static void ShowDepositScreen()
    {
        _DarwScreenHeader("\t Deposit Screen .");

        cout << "\nEnter Account Number Please : ? ";
        string AccNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExists(AccNumber))
        {
            cout << "\nClient With Accnumber : [" << AccNumber << "] Does Not Exist <>  [:-(]..... || Try Another one >>>> ? : ";
            AccNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccNumber);
        _PrintClientCard(Client);

        double DepositAmount = 0;
        cout << "\nPlease Enter Deposit Amount ? ";
        DepositAmount = clsInputValidate::ReadDoubleNum("Error Num [:(] ... Enter Avalid Num : ");

        char Option;
        cout << "\nAre you sure you want to performe this transaction [y/n] ? ";
        cin >> Option;

        if (Option == 'Y' || Option == 'y')
        {
            Client.Deposit(DepositAmount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance is >>> [" << Client.AccountBalance() << "]  .\n";
        }
        else
        {
            cout << "\nOperation Was Cancelled .\n";
        }
    }
};