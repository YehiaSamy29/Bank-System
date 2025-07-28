#pragma once
#include "clsScreen.h"
#include "ClsString.h"
#include "clsUser.h"
class clsLoginRigesterScreen : protected clsScreen
{
private :
    static void PrintLoginRecordLine(clsUser::stlLoginRegister LoginRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRecord.Date;
        cout << "| " << setw(20) << left << LoginRecord.Username;
        cout << "| " << setw(20) << left << LoginRecord.Password;
        cout << "| " << setw(10) << left << LoginRecord.Permissions;
    }

public :
	static void ShowLoginRgisterScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;
        }

        vector <clsUser::stlLoginRegister> vLoginRecords = clsUser::GetLoginRegisterRecords();
        string Title = "\t  Login Register List Screen ";
        string SubTitle = "\t    (" + to_string(vLoginRecords.size()) + ") Records(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << " Date/Time";
        cout << "| " << left << setw(20) << " UserName";
        cout << "| " << left << setw(20) << " Password";
        cout << "| " << left << setw(10) << " Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRecords.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsUser::stlLoginRegister Record : vLoginRecords)
            {

                PrintLoginRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

