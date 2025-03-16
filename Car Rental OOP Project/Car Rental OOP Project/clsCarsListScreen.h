#pragma once
#include"clsScreen.h"
#include"clsCars.h"
#include"clsInputValidate.h"

class clsCarsListScreen:protected clsScreen
{
private:
	static void _PrintCarObject(clsCars Car)
	{
		cout << setw(10) << left << "" << "|" << setw(30) << left << Car.Name <<
			"|" << setw(15) << left << Car.Model <<
			"|" << setw(15) << left << Car.PlateNum() <<
			"|" << setw(15) << left << Car.Capacity <<
			"|" << setw(15) << left << Car.Colour <<
			"|" << setw(15) << left << Car.RatePerDay <<endl;
	}

public:
	static void ShowCarsList()
	{
		vector<clsCars> vCars = clsCars::GetCarsList();
		string Title = "\t Cars List Screen";
		string SubTitle = "\t (" + to_string(vCars.size()) + ") car(s).";
		_DrawHeaderScreen(Title, SubTitle);
		cout << setw(10) << left << "" << "--------------------------------------------------------------------------------------------" <<
			"----------------------------\n";
		cout << setw(10) << left << "" << "|" << setw(30) << left << "Name" <<
			"|" << setw(15) << left << "Model" <<
			"|" << setw(15) << left << "Plate Num" <<
			"|" << setw(15) << left << "Capacity" <<
			"|" << setw(15) << left << "Colour" <<
			"|" << setw(15) << left << "Rate per day" << endl;
		cout << setw(10) << left << "" << "--------------------------------------------------------------------------------------------" <<
			"----------------------------\n";
		if (vCars.size() == 0)
		{
			cout << setw(15) << left << "" << "No Customer available in the system\n";
		}
		else
		{
			for (clsCars C : vCars)
			{
				_PrintCarObject(C);
				cout << setw(10) << left << "" << "--------------------------------------------------------------------------------------------" <<
					"----------------------------\n";
			}
		}
	}
};

