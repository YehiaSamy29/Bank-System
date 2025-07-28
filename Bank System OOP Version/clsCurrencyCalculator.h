#pragma once
#include "clsScreen.h"
#include "ClsString.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iostream>
class clsCurrencyCalculator : protected clsScreen
{
private :
	static clsCurrency _FindandValidateCurrency(short currencynumber = 1) {
		cout << "Please Enter Currency [" << currencynumber << "] Code :";
		string CurrencyCode = clsInputValidate::ReadString<string>();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "Currency Not Found Please Enter Another Code :";
			CurrencyCode = clsInputValidate::ReadString<string>();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}
	static void _PrintCurrency(clsCurrency Currency , string Title) {
		cout << "\n" << Title << "\n";
		cout << "\n____________________________\n";
		cout << "Country     : " << Currency.Country() << endl;
		cout << "Code        : " << Currency.CurrencyCode() << endl;
		cout << "Name        : " << Currency.CurrencyName() << endl;
		cout << "Rate (1$) = : " << Currency.Rate() << endl;
		cout << "\n____________________________\n\n";
	}

	static void _PerformCalculation(clsCurrency Currency1, clsCurrency Currency2, float Amount) {
		_PrintCurrency(Currency1,"Convert From :");
		float DollerValue = Currency1.ConvertToUSD(Amount);
		cout << Amount << " " << Currency1.CurrencyCode() << " = " <<DollerValue << " USD\n";
		if (Currency2.CurrencyCode() != "USD") {
			_PrintCurrency(Currency2,"Convert To :");
			cout << DollerValue << " USD = " <<
				Currency1.ConvertToOtherCurrency(Amount, Currency2) << " " << Currency2.CurrencyCode() << endl;
		}
	}
public:
	static void ShwCurrencyCalculatorScreen() {
		char Recalculate = 'y';
		while (toupper(Recalculate) == 'Y') {
			system("cls");
		   _DrawScreenHeader("Currency Calculator Screen");
			clsCurrency Currency1 = _FindandValidateCurrency();
			clsCurrency Currency2 = _FindandValidateCurrency(2);
			cout << "Enter Amount to Exchange : ";
			float Amount = clsInputValidate::ReadNumber<float>();
			_PerformCalculation(Currency1, Currency2, Amount);
			cout << "Do you want perform another calculation [Y/N] : ";
			cin >> Recalculate;
		}
	}
};

