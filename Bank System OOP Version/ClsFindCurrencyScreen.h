#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iostream>
#include <string>
#include "clsInputValidate.h"

class ClsFindCurrencyScreen : protected clsScreen
{
static void _PrintResult(clsCurrency Currency){
	if (Currency.IsEmpty()) {
		cout << "\nCurrency Not Found.\n";
	}
	else {
		cout << "\nCurrency Found : -)\n";
		Currency.PrintCurrency();
	}
}
static void _FindCurreny(short Choice) {
	if (Choice == 1) {
		cout << "Enter Currency Code :";
		string CurrencyCode = clsInputValidate::ReadString<string>();
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintResult(Currency);
	}
	else {
		cout << "Enter Country  :";
		string Country = clsInputValidate::ReadString<string>();
		clsCurrency Currency = clsCurrency::FindByCountry(Country);
		_PrintResult(Currency);
	}
}
public :
	static void ShowFindCurrencyScreen() {
		_DrawScreenHeader("Find Currency Screen");
		cout << " Find By : [1] Code or [2] Country ?";
		short Choice = clsInputValidate::ReadNumberBetween<short>
		(1, 2,"Enter Valid Choice :\nFind By : [1] Code or [2] Country ?");
		_FindCurreny(Choice);
	}
};

