#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../clsGlobal.h"
#include "../../Lib/clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n______________________________";
        cout << "\nFullName    : " << Client.FullName();
        cout << "\nAcc, Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance();
        cout << "\n______________________________\n\n\n";
    }
    
    static string _ReadAccountNumber(string message)
    {
        string AccountNumber;
        cout << message;
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }
    
    static double _ReadAmount(clsBankClient SourceClient)
    {
        double Amount;
        
        cout << "\nEnter Transfer Amount? ";
        
        Amount = clsInputValidate::ReadDoubleNum("Error enter valid num ? ");
        
        while (Amount > SourceClient.AccountBalance())
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDoubleNum("Error enter valid num ? ");
        }
        return Amount;
    }
    
    public:
    static void ShowTrasferScreen()
    {
        _DarwScreenHeader("\t  Transfer Screen .");
        
        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From: "));
        
        _PrintClientCard(SourceClient);
        
        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer To: "));
        
        _PrintClientCard(DestinationClient);
        
        double AmountToTranfer = _ReadAmount(SourceClient);
        
        char Option = 'n';
        cout << "\nAre You sure you want to performe this transaction ? [y/n] ";
        cin >> Option;
        
        if (Option == 'Y' || Option == 'y')
        {
            if (SourceClient.Transfer(AmountToTranfer, DestinationClient,CurrentUser.UserName()))
            {
                cout << "\n\n______________________________\n";
                cout << "\nTransfer done successfully   [:-)] ...\n";
            }
            else
            {
                cout << "\nTransfer Faild   [:-(] ...\n";
            }

            _PrintClientCard(SourceClient);
            _PrintClientCard(DestinationClient);
        }
    }
};
