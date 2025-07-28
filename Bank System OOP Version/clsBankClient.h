#pragma once
#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include "clsPerson.h"
#include "ClsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1  , AddNewMode = 2};
    enMode _Mode;

    bool _MarkedForDelete = false;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }
    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }

        return vClients;

    }
    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C._MarkedForDelete == false) {
                DataLine = _ConverClientObjectToLine(C);
                MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }
    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveCleintsDataToFile(_vClients);

    }
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;
            MyFile.close();
        }

    }
    void _AddNew()
    { 
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }
    struct strTransfeRegister;
    static strTransfeRegister _ConvertLinetoTransferRegisterObject(string Line, string Seperator = "#//#")
    {
        vector<string> vData;
        vData = clsString::Split(Line, Seperator);
        strTransfeRegister Record;
        Record.Date = vData[0];
        Record.SourseAccountNumber = vData[1];
        Record.DestinationAccountNumber = vData[2];
        Record.Amount = stod(vData[3]);
        Record.destBalanceAfter = stod(vData[4]);
        Record.srcBalanceAfter = stod(vData[5]);
        Record.UserName = CurrentUser.UserName;
        return Record;

    }
    static  vector <strTransfeRegister> _LoadTransferRegisterFromFile()
    {

        vector <strTransfeRegister> vTransferRecords;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                strTransfeRegister Record = _ConvertLinetoTransferRegisterObject(Line);

                vTransferRecords.push_back(Record);
            }

            MyFile.close();

        }

        return vTransferRecords;

    }
 public:
    struct strTransfeRegister {
        string Date;
        string SourseAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double srcBalanceAfter;
        double destBalanceAfter;
        string UserName;
    };


    clsBankClient(enMode Mode, string FirstName, string LastName,
    string Email, string Phone, string AccountNumber, string PinCode,
    float AccountBalance) :
            clsPerson(FirstName, LastName, Email, Phone)

        {
            _Mode = Mode;
            _AccountNumber = AccountNumber;
            _PinCode = PinCode;
            _AccountBalance = AccountBalance;

        }

    bool IsEmpty()
        {
            return (_Mode == enMode::EmptyMode);
        } 
    string AccountNumber()
        {
            return _AccountNumber;
        }
    void SetPinCode(string PinCode)
        {
            _PinCode = PinCode;
        }
    string GetPinCode()
        {
            return _PinCode;
        }
    void SetAccountBalance(float AccountBalance)
        {
            _AccountBalance = AccountBalance;
        }
    float GetAccountBalance()
        {
            return _AccountBalance;
        }

    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

     void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << AccountNumber();
        cout << "\nPassword    : " << PinCode;
        cout << "\nBalance     : " << AccountBalance;
        cout << "\n___________________\n";

    }

    static clsBankClient Find(string AccountNumber)
        {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
                MyFile.close();
            }
            return _GetEmptyClientObject();
        }
    static clsBankClient Find(string AccountNumber, string PinCode)
        {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                    {
                        MyFile.close();
                        return Client;
                    }
                }

                MyFile.close();
            }
            return _GetEmptyClientObject();
        }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists = 2 };
    static bool IsClientExist(string AccountNumber)
        {
            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            return (!Client1.IsEmpty());
        }
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            return enSaveResults::svFaildEmptyObject;
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }

        case enMode::AddNewMode:
        {
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
    }
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }

    }

    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;
    }

    static vector <strTransfeRegister> GetTransferRegisterRecords() {
        return _LoadTransferRegisterFromFile();
    }
};
