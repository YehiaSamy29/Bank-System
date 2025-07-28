#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "ClsDate.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "Trails.h"

class clsLoginScreen :protected clsScreen
{
private:
    static  void _Login()
    {
        bool LoginFaild = false;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                NumberOfTrails--;
                system("cls");
                _DrawScreenHeader("\t  Login Screen");
                cout << "\nInvlaid Username/Password!\n\n";
                if (NumberOfTrails == 0) {
                    cout << "\nYou are Locked after 3 faild trails\n";
                    return;
                }
                cout << "You Have " << NumberOfTrails << " Trails to login.\n";
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        CurrentUser.RegisterLogin();
        NumberOfTrails = 3;
        clsMainScreen::ShowMainMenue();
    }

public:
    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        _Login();
    }

};