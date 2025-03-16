#pragma once
#include"clsScreen.h"
#include"clsCars.h"
#include"clsInputValidate.h"
#include"clsCarsListScreen.h"
#include"clsAddNewCarScreen.h"
#include"clsUpdateCarScreen.h"
#include"clsDeleteCarScreen.h"
#include"clsFindCarScreen.h"
#include"clsRentCarCalculatorScreen.h"

class clsCarsMenueScreen:protected clsScreen
{
private:
private:
	enum enCarsMenueOptions {
		eCarsListScreen = 1, eAddNewCarScreen = 2, eUpdateCarScreen = 3, eDeleteCarScreen = 4,
		eFindCarScreen = 5, eRentCalculatorScreen = 6, eShowMainMenue = 7
	};

	static short _ReadCarMenueOption()
	{
		short Option;
		cout << setw(30) << left << "" << "\t\tEnter the option you want to do?[1 to 7]?";
		Option = clsInputValidate::ReadShortNumberBetween(1, 7, "This Option is not available,choose available one:");
		return Option;
	}

	static void _GoBackToMainMenue()
	{
		cout << "\n\n\tPress any key to go back to main menue...";
		system("pause>0");
		ShowCarsMenueScreen();
	}

	static void _ShowCarsListScreen()
	{
		//cout << "Customers list will be here";
		clsCarsListScreen::ShowCarsList();
	}

	static void _ShowAddNewCarScreen()
	{
		//cout << "Add new customer will be here";
		clsAddNewCarScreen::ShowAddNewwCarScreen();
	}

	static void _ShowUpdateCarScreen()
	{
		//cout << "Cars menue will be here";
		clsUpdateCarScreen::ShowUpdateCarScreen();
	}

	static void _ShowDeleteCarScreen()
	{
		//cout << "Logout will be here";
		clsDeleteCarScreen::ShowDeleteCarScreen();
	}

	static void _ShowFindCarScreen()
	{
		//cout << "Close screen will be here";
		clsFindCarScreen::ShowFindCarScreen();
	}

	static void _ShowRentCalculatorScreen()
	{
		//cout << "Close screen will be here";
		clsRentCarCalculatorScreen::ShowRentCalculatorScreen();
	}

	static void _PerformCarsMenueOptions(enCarsMenueOptions Option)
	{
		switch (Option)
		{
		case clsCarsMenueScreen::eCarsListScreen:
		{
			system("cls");
			_ShowCarsListScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCarsMenueScreen::eAddNewCarScreen:
		{
			system("cls");
			_ShowAddNewCarScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCarsMenueScreen::eUpdateCarScreen:
		{
			system("cls");
			_ShowUpdateCarScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCarsMenueScreen::eDeleteCarScreen:
		{
			system("cls");
			_ShowDeleteCarScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCarsMenueScreen::eFindCarScreen:
		{
			system("cls");
			_ShowFindCarScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCarsMenueScreen::eRentCalculatorScreen:
		{
			system("cls");
			_ShowRentCalculatorScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCarsMenueScreen::eShowMainMenue:
		{
			break;
		}
		}
	}

public:
	static void ShowCarsMenueScreen()
	{
		if (!CheckAccessRight(clsAdmins::eManageCars))
		{
			return;
		}
		system("cls");
		_DrawHeaderScreen("Cars Menue Screen");

		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		cout << setw(20) << left << "" << "\t\t\t\tCars Menue\n";
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		cout << setw(20) << left << "" << "\t\t\t[1]Cars List\n";
		cout << setw(20) << left << "" << "\t\t\t[2]Add New Car\n";
		cout << setw(20) << left << "" << "\t\t\t[3]Update Cars\n";
		cout << setw(20) << left << "" << "\t\t\t[4]Delete Cars\n";
		cout << setw(20) << left << "" << "\t\t\t[5]Find Cars\n";
		cout << setw(20) << left << "" << "\t\t\t[6]Rent Calculator\n";
		cout << setw(20) << left << "" << "\t\t\t[7]Main Menue\n";
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		_PerformCarsMenueOptions((enCarsMenueOptions)_ReadCarMenueOption());

	}
};

