#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString<string>();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString<string>();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString<string>();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString<string>();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString<string>();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }


    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List [Y/N] ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {

            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client [Y/N] ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client [Y/N] ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client [Y/N] ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client [Y/N] ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions [Y/N] ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users [Y/N] ?";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow Login Register List [Y/N] ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {

            Permissions += clsUser::enPermissions::pLoginRegister;
        }
        return Permissions;
    }

public:

    static void ShowAddNewUserScreen()
    {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString<string>();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString<string>();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            NewUser.Print();
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }
};
