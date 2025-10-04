#pragma once

#include <iostream>
#include "../clsGlobal.h"
#include "../Core/clsUser.h"
#include "../Lib/clsDate.h"

using namespace std;

class clsScreen
{
protected:
    static void _DarwScreenHeader(string Title, string SubTitle = "")
    {

        clsDate Date = clsDate::GetSystemDate();

        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout<< "\t\t\t\t\tUser : "<<CurrentUser.UserName() <<endl;
        cout<< "\t\t\t\t\tDate : "<<Date.DateToString() <<"\n\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Required)
    {
        if (!CurrentUser.CheckAccessPermission(Required))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
    }
};