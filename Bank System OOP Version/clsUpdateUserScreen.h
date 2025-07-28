#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen :protected clsScreen

{
private:


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

public:

    static void ShowUpdateUserScreen()
    {

        _DrawScreenHeader("\tUpdate User Screen");

        string UserName = "";

        cout << "\nPlease Enter User UserName: ";
        UserName = clsInputValidate::ReadString<string>();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nAccount number is not found, choose another one: ";
            UserName = clsInputValidate::ReadString<string>();
        }

        clsUser User1 = clsUser::Find(UserName);

        User1.Print();

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";


            _ReadUserInfo(User1);

            clsUser::enSaveResults SaveResult;

            SaveResult = User1.Save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";

                User1.Print();
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;

            }

            }

        }

    }
};
