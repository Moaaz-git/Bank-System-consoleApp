#pragma once

#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "iomanip"
#include "../../Lib/clsString.h"
#include "../../Core/clsUser.h"

class clsClientListScreen : protected clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << "\t| " << setw(15) << left << Client.AccountNumber();
        cout << "\t| " << setw(20) << left << Client.FullName();
        cout << "\t| " << setw(12) << left << Client.PhoneNumber();
        cout << "\t| " << setw(20) << left << Client.Email();
        cout << "\t| " << setw(10) << left << Client.PinCode();
        cout << "\t| " << setw(12) << left << Client.AccountBalance();
    }

public:
    static void ShowClientsListScreen()
    {
        if(!CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return ;// this will exit the function and it will not continue
        }

        vector<clsBankClient> vClients;
        vClients = clsBankClient::GetClientsList();

        string subtitle ="\t   (" + to_string(vClients.size()) + ") Client(s) .";

        _DarwScreenHeader("\tClients List Screen ", subtitle);

        cout << "\n\t_______________________________________________________";
        cout << "__________________________________________________________\n"
             << endl;

        cout << "\t| " << left << setw(15) << "Accout Number";
        cout << "\t| " << left << setw(20) << "Client Name";
        cout << "\t| " << left << setw(12) << "Phone";
        cout << "\t| " << left << setw(20) << "Email";
        cout << "\t| " << left << setw(10) << "Pin Code";
        cout << "\t| " << left << setw(12) << "Balance";
        cout << "\n\t_______________________________________________________";
        cout << "__________________________________________________________\n"
             << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\t\tNo Clients Available In the System!";
        else
        {
            for (clsBankClient Client : vClients)
            {

                _PrintClientRecordLine(Client);
                cout << endl;
            }
        }

        cout << "\n\t_______________________________________________________";
        cout << "__________________________________________________________\n"
             << endl;
     }
};