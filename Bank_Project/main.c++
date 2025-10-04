#include <iostream>
#include "Header Files/Screens/User/clsLoginScreen.h"
#include "Header Files/Lib/clsUtil.h"
using namespace std;
int main()
{
    // we do this to avoid circular references this about stack consept .
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }


    system("pause>0");
    return 0;
}