#pragma once
#include"clsScreen.h"
#include"clsCars.h"
#include"clsInputValidate.h"

class clsAddNewCarScreen:protected clsScreen
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
		cout << "\nCapacity:" << Car.Capacity<< endl;
		cout << "\nColour:" << Car.Colour << endl;
		cout << "\nRate per day:" << Car.RatePerDay << endl;
		cout << "\n-----------------------------\n";
	}
public:
	static void ShowAddNewwCarScreen()
	{
		_DrawHeaderScreen("Add New Car Screen");
		string PlateNum;
		cout << "\nEnter plate Number:";
		PlateNum = clsInputValidate::ReadString();
		while (clsCars::IsCarExist(PlateNum))
		{
			cout << "\nThis Id is laready used ,choose another one:";
			PlateNum = clsInputValidate::ReadString();
		}
		clsCars NewCar = clsCars::GetAddNewCarObject(PlateNum);
		_ReadCarInfo(NewCar);
		clsCars::enSaveResults Saved = NewCar.Save();
		switch (Saved)
		{
		case clsCars::svFaildEmpty:
			cout << "\nERROR!New car is not saved because it's empty";
			break;
		case clsCars::svSucceeded:
			cout << "\nNew car is saved successfully";
			_PrintCarInfo(NewCar);
			break;
		case clsCars::svFaildExist:
			cout << "\nERROR!New car is not saved because it's exist";
			break;
		}
	}
};

