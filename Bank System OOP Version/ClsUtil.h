#pragma once
#include <iostream>
#include <string>
#include "ClsDate.h"
#include "ClsString.h"

using namespace std;
class clsUtil {
public:
    static void Srand() {
        srand((unsigned)time(NULL));
    }
    static int RandomNumber(int From, int To) {
        int Number = rand() % (To - From + 1) + From;
        return Number;
    }
     enum enCharType {
        SamallLetter = 1,
        CapitalLetter = 2,
        SpecialCharacter = 3,
        Digit = 4
        , MixChars = 5
    };
    static char GetRandomCharacter(enCharType Type) {
        if (Type == enCharType::MixChars) {
            int number = RandomNumber(1, 4);
            Type = enCharType(number);
        }
        switch (Type) {
        case enCharType::CapitalLetter:
            return char(RandomNumber(65, 90));
            break;
        case enCharType::SamallLetter:
            return char(RandomNumber(97, 122));
            break;
        case enCharType::SpecialCharacter:
            return char(RandomNumber(33, 47));
            break;
        case enCharType::Digit:
            return char(RandomNumber(48, 57));
            break;
        }
    }
    static string GenerateWord(enCharType type, short size) {
        string word = "";
        for (int i = 1; i <= size; i++) {
            word += GetRandomCharacter(type);
        }
        return word;
    }
    static string GenerateKey(enCharType type, short sizeofword = 4) {
        int counter = 4;

        string key = "";
        while (counter > 0) {
            counter--;
            key += GenerateWord(type, sizeofword);
            if (counter % 1 == 0 && counter != 0) {
                key += '-';
            }
        }
        return key;
    }
    static void GenerateKeys(int numberofkeys, enCharType type) {
        for (int i = 1; i <= numberofkeys; i++) {
            cout << "Key [ " << i << " ] Is :" << GenerateKey(type) << endl;
        }
    }
    static void Swap(int& a, int& b) {
        int temp;
        temp = a;
        a = b;
        b = temp;
    }
    static void Swap(float& a, float& b) {
        float temp;
        temp = a;
        a = b;
        b = temp;
    }
    static void Swap(double& a, double& b) {
        double temp;
        temp = a;
        a = b;
        b = temp;
    }
    static void Swap(string& a, string& b) {
        string temp;
        temp = a;
        a = b;
        b = temp;
    }
    static void Swap(clsDate &Date1, clsDate &Date2) {
        clsDate::SwapDates(Date1, Date2);
    }
    static void FillArrayWithRandomNumbers(int arr[100], int size , int from , int to) {
        for (int i = 0; i < size; i++) {
            arr[i] = RandomNumber(from,to);
        }
    } 
    static void FillArrayWithRandomWords(string arr[100], int size, enCharType type, short length) {
        for (int i = 0; i < size; i++) {
            arr[i] = GenerateWord(type, length);
        }
    }
    static void FillArrayWithRandomKeys(string arr[100], int size, enCharType type) {
        for (int i = 0; i < size; i++) {
            arr[i] = GenerateKey(type);
        }
    }
    static string Tabs(int numberoftabs) {
        string tabs = "";
        for (int i = 1; i <= numberoftabs; i++) {
            tabs +=  "\t";
        }
        return tabs;
    }
    static void ShuffleArray(int arr[100], int size) {
        for (int i = 0; i < size; i++) {
            Swap(arr[RandomNumber(1, (size - 1))],
                arr[RandomNumber(1, (size - 1))]);
        }
    }
    static void ShuffleArray(string arr[100], int size) {
        for (int i = 0; i < size; i++) {
            Swap(arr[RandomNumber(1, (size - 1))],
                arr[RandomNumber(1, (size - 1))]);
        }
    }
    static string EncryptText(string name, short encryptkey) {
        for (int i = 0; i <= name.length(); i++) {
            name[i] = char((int)name[i] + encryptkey);
        }
        return name;
    }
    static string DecryptText(string word, short encryptkey) {
        for (int i = 0; i <= word.length(); i++) {
            word[i] = char((int)word[i] - encryptkey);
        }
        return word;
    }
    static  string NumberToText(int Number) {
        if (Number == 0) {
            return " ";
        }
        if (Number >= 1 && Number <= 19) {
            string arr[] = { "","One","Two","Three","Four"
            ,"Five","Six","Seven",
            "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
            "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
            return arr[Number];
        }
        if (Number >= 20 && Number <= 99) {
            string arr[] = { "", "" ,"Twenty","Thirty","Fourty","Fifty"
            ,"Sixty","Seventy","Eighty","Ninety" };
            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }
        if (Number >= 100 && Number <= 199) {
            return "One Hundred " + NumberToText(Number % 100);
        }
        if (Number >= 200 && Number <= 999) {
            return NumberToText(Number / 100) + " Hundred " +
                NumberToText(Number % 100);
        }
        if (Number >= 1000 && Number <= 1999) {
            return "One Thousand " + NumberToText(Number % 1000);
        }
        if (Number >= 2000 && Number <= 999999) {
            return NumberToText(Number / 1000) + " Thousand " +
                NumberToText(Number % 1000);
        }
        if (Number >= 1000000 && Number <= 1999999) {
            return "One Million " + NumberToText(Number % 1000000);
        }
        if (Number >= 2000000 && Number <= 999999999) {
            return NumberToText(Number / 1000000) + " Million " +
                NumberToText(Number % 1000000);
        }
        if (Number >= 1000000000 && Number <= 1999999999) {
            return "One Billion " + NumberToText(Number % 1000000000);
        }
        else {
            return NumberToText(Number / 1000000000) + " Billion " +
                NumberToText(Number % 1000000000);
        }
    }

};