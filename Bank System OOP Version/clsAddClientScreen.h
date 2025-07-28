#pragma once
class clsAddClientScreen : protected  clsScreen
{
private :
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString<string>();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString<string>();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString<string>();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString<string>();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString<string>();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadNumber<float>();
    }
    static void AddNewClient() {
        cout << "Enter Account Number :";
        string AccountNumber = clsInputValidate::ReadString<string>();
        while (clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount Number Is Already Used, Choose another one : ";
            AccountNumber = clsInputValidate::ReadString<string>();
        }
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResult = NewClient.Save();
        switch (SaveResult) {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Added Successfully :-) \n";
            NewClient .Print();

            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty\n";
            break;
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
    }
public :
    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
       char AddMore = 'n';
        do {
            system("cls");
            _DrawScreenHeader("\t  Add New Client Screen");
            AddNewClient();
            cout << "Do You Want Add More Clients [Y/N] :";
            cin >> AddMore;
        } while (toupper(AddMore) == 'Y');

    }

};

