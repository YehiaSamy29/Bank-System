#pragma once
#include "clsScreen.h"
#include "clsTransferScreen.h"
#include "clsBankClient.h"
#include <iostream>
#include <string>
class clsTransferLog : protected clsScreen
{
    static void PrintTransferRecordLine(clsBankClient::strTransfeRegister TransferRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferRecord.Date;
        cout << "| " << setw(10) << left << TransferRecord.SourseAccountNumber;
        cout << "| " << setw(10) << left << TransferRecord.DestinationAccountNumber;
        cout << "| " << setw(10) << left << TransferRecord.Amount;
        cout << "| " << setw(15) << left << TransferRecord.destBalanceAfter;
        cout << "| " << setw(15) << left << TransferRecord.srcBalanceAfter;
        cout << "| " << setw(15) << left << TransferRecord.UserName;
    }

public:
    static void ShowTransferLogScreen() {
        vector <clsBankClient::strTransfeRegister> vTransferRecords = clsBankClient::GetTransferRegisterRecords();
        string Title = "\t  Transfer Log List  Screen ";
        string SubTitle = "\t    (" + to_string(vTransferRecords.size()) + ") Records(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << " Date/Time";
        cout << "| " << left << setw(10) << " s.Acct";
        cout << "| " << left << setw(10) << " d.Acct";
        cout << "| " << left << setw(10) << " Amount";
        cout << "| " << left << setw(15) << " s.Balance";
        cout << "| " << left << setw(15) << " d.Balance";
        cout << "| " << left << setw(15) << " User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________________\n" << endl;

        if (vTransferRecords.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient::strTransfeRegister Record : vTransferRecords)
            {

                PrintTransferRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________________\n" << endl;
    }
};

