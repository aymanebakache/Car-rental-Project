#pragma once
#include"clsScreen.h"
#include"clsCars.h"
#include"clsInputValidate.h"

class clsFindCarScreen:protected clsScreen
{
private:
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
	static void ShowFindCarScreen()
	{
		_DrawHeaderScreen("\tFind Car Screen");
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
			cout << "\nCar was not found!";
		}
		else
		{
			cout << "\nCuar was found!";
		}
		_PrintCarInfo(Car);
	}
};

