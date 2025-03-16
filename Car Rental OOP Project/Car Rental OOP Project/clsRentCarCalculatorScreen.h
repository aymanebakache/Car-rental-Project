#pragma once
#include"clsScreen.h"
#include"clsCars.h"
#include"clsInputValidate.h"
#include"clsDate.h"

class clsRentCarCalculatorScreen:protected clsScreen
{
private:
	static string _ReadDate(string Message)
	{
		string stDate;
		bool ValidDate=true;
		bool FutureDate = true;
		do
		{
			cout << Message;
			stDate = clsInputValidate::ReadString();
			clsDate Date = clsDate(stDate);
			ValidDate = Date.IsValidDate(Date);
			FutureDate = !Date.IsDateBeforeDate2(clsDate::GetSystemDate());
		} while (!ValidDate || !FutureDate);
		return stDate;
	}

	static int _ReadDaysOfRent()
	{
		string Date1, Date2;
		do
		{
			cout << "\n----The First Date:-----\n";
			Date1 = _ReadDate("\nEnter a valid START Date of Rent:");
			cout << "\n----The Second Date:-----\n";
			Date2 = _ReadDate("\nEnter a valid END Date of Rent:");
			clsDate d1 = clsDate(Date1);
		}while (clsDate::IsDate1BeforeDate2(clsDate(Date2), clsDate(Date1)));
		int Days = clsDate::GetDifferenceInDays(clsDate(Date1), clsDate(Date2), true);
		return Days;
	}

	static void _PrintCarInfo(clsCars Car)
	{
		cout << "\nCar Info:";
		cout << "\n----------------------\n";
		cout << "\nName:" << Car.Name << endl;
		cout << "\nModel:" << Car.Model << endl;
		cout << "\nPlate Number:" << Car.PlateNum() << endl;
		cout << "\nCapacity:" << Car.Capacity << endl;
		cout << "\nColour:" << Car.Colour << endl;
		cout << "\nRate per day:" << Car.RatePerDay << endl;
		cout << "\n-----------------------------\n";
	}
public:
	static void ShowRentCalculatorScreen()
	{
		_DrawHeaderScreen("\tRent Calculator Screen");
		string PlateNum;
		cout << "\nEnter plate Number:";
		PlateNum = clsInputValidate::ReadString();
		while (!clsCars::IsCarExist(PlateNum))
		{
			cout << "\nThis car is not exist ,choose another one:";
			PlateNum = clsInputValidate::ReadString();
		}
		clsCars Car = clsCars::Find(PlateNum);
		if (Car.IsEmpty())
		{
			cout << "\nCar was not found!\n";
			return;
		}
		else
		{
			cout << "\nCar was found\n";
		}
		_PrintCarInfo(Car);
		int Days = _ReadDaysOfRent();
		float Cost = Days * Car.RatePerDay;
		cout << "\nThe cost's rent of "<<Days<<" days is :" << Cost << "$\n";

	}
};

