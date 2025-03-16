#pragma once
#include"clsScreen.h"
#include"clsCars.h"
#include"clsInputValidate.h"

class clsUpdateCarScreen :protected clsScreen
{
private:
	static void _ReadCarInfo(clsCars& Car)
	{
		cout << "\nEnter Name:";
		Car.Name = clsInputValidate::ReadString();
		cout << "\nEnter Model:";
		Car.Model = clsInputValidate::ReadShortNumber();
		cout << "\nEnter Capacity:";
		Car.Capacity = clsInputValidate::ReadShortNumber();
		cout << "\nEnter Colour:";
		Car.Colour = clsInputValidate::ReadString();
		cout << "\nEnter Rate per day:";
		Car.RatePerDay = clsInputValidate::ReadFloatNumber();
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
	static void ShowUpdateCarScreen()
	{
		_DrawHeaderScreen("Update Car Screen");
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
		cout << "\nAre you sure you want to update this car:(y/n):";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			cout << "\n---Updating car--\n";
			_ReadCarInfo(Car);
			clsCars::enSaveResults Saved = Car.Save();
			switch (Saved)
			{
			case clsCars::svFaildEmpty:
				cout << "\nERROR!Update car is not saved because it's empty";
				break;
			case clsCars::svSucceeded:
				cout << "\nCar is updated successfully";
				_PrintCarInfo(Car);
				break;
			}
		}
	}
		
	

};

