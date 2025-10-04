#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "iomanip"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << "\t| " << setw(15) << left << Client.AccountNumber();
        cout << "\t| " << setw(40) << left << Client.FullName();
        cout << "\t| " << setw(12) << left << Client.AccountBalance();
    }

public:
    static void ShowTotalBalances()
    {

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DarwScreenHeader(Title, SubTitle);

        cout << "\n\t_______________________________________________________";
        cout << "____________________________________________________\n"
             << endl;

        cout << "\t| " << left << setw(15) << "Accout Number";
        cout << "\t| " << left << setw(40) << "Client Name";
        cout << "\t| " << left << setw(12) << "Balance";
        cout << "\n\t_______________________________________________________";
        cout << "____________________________________________________\n"
             << endl;

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {
                PrintClientRecordBalanceLine(Client);
                cout << endl;
            }
        cout << "\n\t_______________________________________________________";
        cout << "____________________________________________________\n"
             << endl;

        cout << setw(8) << left << "" << "\t\t\t\t\t    Total Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(TotalBalances) << ")";
    }
};