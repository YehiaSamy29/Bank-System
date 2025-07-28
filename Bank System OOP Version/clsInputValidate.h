#pragma once
#include "ClsString.h"
#include "ClsDate.h"
class clsInputValidate
{
public :
	template <typename Number>
	static bool IsNumberBetween(Number number, Number from, Number to) {
		return (number >= from && number <= to);
	}
	static bool IsDateBetween(clsDate Date1, clsDate startfrom, clsDate enddate) {
		return ((clsDate::IsDate1AfterDate2(Date1, startfrom) 
			&& clsDate::IsDate1BeforeDate2(Date1, enddate)) ||
			(clsDate::IsDate1BeforeDate2(Date1, startfrom) 
				&& clsDate::IsDate1AfterDate2(Date1, enddate)));
	}
	template <typename T> static T ReadNumber(string message = "Enter Valid Input : ") {
		T number;
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << message;
			cin >> number;
		}
		return number;
	}
	template <typename T> static T ReadString() {
		T word;
		cin >> ws;
		getline(cin, word);
		return word;
	}
	template <typename T> static T ReadNumberBetween(T from, T to , string Message = "Enter Valid Number :") {
		T number = ReadNumber<T>();
		while (!IsNumberBetween(number, from, to)) {
			cout << Message;
			number = ReadNumber<T>(Message);
		}
		return number;
	}
	static bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}
};

