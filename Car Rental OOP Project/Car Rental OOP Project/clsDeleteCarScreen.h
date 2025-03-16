#pragma once
#include"clsScreen.h"
#include"clsCars.h"
#include"clsInputValidate.h"

class clsDeleteCarScreen:protected clsScreen
{
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
	static void ShowDeleteCarScreen()
	{
		_DrawHeaderScreen("\tDelete Car Screen");
		string PlateNum;
		cout << "\nEnter plate Number:";
		PlateNum = clsInputValidate::ReadString();
		while (!clsCars::IsCarExist(PlateNum))
		{
			cout << "\nThis car is not exist ,choose another one:";
			PlateNum = clsInputValidate::ReadString();
		}
		clsCars Car = clsCars::Find(PlateNum);
		char Answer = 'n';
		cout << "\nAre you sure you want to delete this car:(y/n):";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			if (Car.Delete())
			{
				cout << "\nCustomer Deleted successfully!";
				_PrintCarInfo(Car);
			}
			else
			{
				cout << "\nERROR,this customer was not deleted";
			}
		}
	}
};

