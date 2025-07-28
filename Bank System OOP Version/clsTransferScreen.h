#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsTransferScreen : protected clsScreen
{
private :
    static void _PrintClient(clsBankClient Client) {
        cout << "___________________________\n";
        cout << "\tClient Card\n";
        cout << "___________________________\n";
        cout << "Full Name    : " << Client.FullName() << endl;
        cout << "Acc  Number  : " << Client.AccountNumber() << endl;
        cout << "Acc  Balance : " << Client.AccountBalance << endl;
        cout << "___________________________\n";
    }

    static clsBankClient _FindAndValidateClient(string message) {
        string AccountNumber;
        cout << message;
        AccountNumber = clsInputValidate::ReadString<string>();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString<string>();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
        {
            _PrintClient(Client1);
        }
        else
        {
            cout << "\\nClient Was not Found :-(\\n";
        }
        return Client1;
    }

    static double _ReadAndValidateAmount(clsBankClient Client1) {
        double Amount = 0;
        cout << "\n Enter Transfer  Amount ? ";
        Amount = clsInputValidate::ReadNumberBetween<double>(1.0,
            Client1.GetAccountBalance(),
            "Amount Exceeds the available balance , Enter another amount ?");
        return Amount;
    }

    static void _PerformOperation(clsBankClient &Client1  , clsBankClient &Client2 , double amount) {
        cout << "\nAre you sure you want to perform this transaction [Y/N] : ";
        char Answer = 'n';
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            Client1.Withdraw(amount);
            Client2.Deposit(amount);
            cout << "Transfer Done successfully\n";
            _PrintClient(Client1);
            _PrintClient(Client2);
        }
        else {
            return;
        }
    }

    static  string _GetTransferRecord(clsBankClient Client1  , clsBankClient Client2 ,double Amount ,
        string Delim = "#//#") {
        string TransferRecord = "";
        TransferRecord += clsDate::DateToString(clsDate()) + " - ";
        TransferRecord += clsDate::GetCurrentDateTime() + Delim;
        TransferRecord += Client1.AccountNumber() + Delim;
        TransferRecord += Client2.AccountNumber() + Delim;
        TransferRecord += to_string(Amount) + Delim;
        TransferRecord += to_string(Client2.AccountBalance) + Delim;
        TransferRecord += to_string(Client1.AccountBalance) + Delim;
        TransferRecord += CurrentUser.UserName;
        return TransferRecord;
    }

    static void _AddDataLineToFile(string  stDataLine, string FileName = "TransferLog.txt")
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static void _SaveTransferOperation(clsBankClient Client1  , clsBankClient Client2  , double Amount) {
        _AddDataLineToFile(_GetTransferRecord(Client1,Client2,Amount));
    }

public :

    static void ShowTransferScreen() {
        _DrawScreenHeader("Transfer Screen");
        clsBankClient Client1 = _FindAndValidateClient("Enter Account Number to Transfer From : ");
        clsBankClient Client2 = _FindAndValidateClient("Enter Account Number to Transfer To   : ");

        double Amount = _ReadAndValidateAmount(Client1);

        _PerformOperation(Client1, Client2, Amount);
        _SaveTransferOperation(Client1, Client2, Amount);
    }
};

