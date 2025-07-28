#pragma once
#include "ClsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
class clsUpdateCurrencyRateScreen : protected clsScreen
{
	static bool _MakeSureForUpdate() {
		string Answer;
		cout << "Are you sure want to update the rate of this Currency [Y/N] :";
		Answer = clsInputValidate::ReadString<string>();
		return (clsString::UpperAllString(Answer) == "Y");
	}
public:
	static void ShowUpdateCurrencyRateScreen(){
		_DrawScreenHeader("Update Currency Screen");
		cout << "Enter Currency Code :";
		string CurrencyCode = clsInputValidate::ReadString<string>();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString<string>();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		Currency.PrintCurrency();
		if (!_MakeSureForUpdate())
			return;
		cout << "\nUpdate Currency Rate :\n______________________\n";
		cout << "Enter New Rate :";
		float NewRate = clsInputValidate::ReadNumber<float>();
		Currency.UpdateRate(NewRate);
		Currency.PrintCurrency();
	}
};

