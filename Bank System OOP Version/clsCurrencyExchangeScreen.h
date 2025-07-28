#pragma once
#include "clsScreen.h"
#include "ClsString.h"
#include "clsInputValidate.h"
#include "clsCurrencyListScreen.h"
#include "ClsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculator.h"
#include <iomanip>
#include <iostream>
class clsCurrencyExchangeScreen : protected clsScreen 
{
    enum enCurrencyExchangeOptions {eListCurrencies = 1 , eFindCurrency = 2 ,eUpdateRate = 3 , 
    eCurrencyCalculator = 4 , eMainMenue = 5};
    static short ReadCurrencyExchangeMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>
        (1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }
    static void _ShowListCurrenciesScreen() {
        clsCurrencyListScreen::ShowCurrenciesListScreen();
    }
    static void _ShowFindCurrencyScreen() {
        ClsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static  void _ShowUpdateRateScreen() {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    static void _ShowCurrencyCalculatorScreen() {
        clsCurrencyCalculator::ShwCurrencyCalculatorScreen();
    }
    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowCurrencyExchangeMainMenue();
    }
    static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeOptions Option) {

        switch (Option)
        {
        case enCurrencyExchangeOptions::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enCurrencyExchangeOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enCurrencyExchangeOptions::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enCurrencyExchangeOptions::eCurrencyCalculator: {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enCurrencyExchangeOptions::eMainMenue: {
        }
        }
    }
public :
	static void ShowCurrencyExchangeMainMenue() {
        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformCurrencyExchangeMenueOption((enCurrencyExchangeOptions)ReadCurrencyExchangeMenueOption());
	}
};