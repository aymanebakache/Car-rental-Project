#pragma once
#include"clsScreen.h"
#include"clsCustomer.h"
#include"clsInputValidate.h"
#include"clsCustomersListScreen.h"
#include"clsAddNewCustomerScreen.h"
#include"clsUpdateCustomerScreen.h"
#include"clsDeleteCustomerScreen.h"
#include"clsFindCustomerScreen.h"
#include"clsCustomerHistoryScreen.h"

class clsCustomersMenueScreen:protected clsScreen
{
private:
	enum enCustomersMenueOptions {
		eCustomersListScreen = 1, eAddNewCustomerScreen = 2, eUpdateCustemorScreen = 3, eDeleteCustomerScreen = 4,
		eFindCustomerScreen = 5, eRentalHistoryCustomerList = 6,eShowMainMenue=7
	};

	static short _ReadCustomerMenueOption()
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
		ShowCustomersMenueScreen();
	}

	static void _ShowCustomersListScreen()
	{
		//cout << "Customers list will be here";
		clsCustomersListScreen::ShowCustomersList();
	}

	static void _ShowAddNewCustomerScreen()
	{
		//cout << "Add new customer will be here";
		clsAddNewCustomerScreen::ShowAddNewwCustomerScreen();
	}

	static void _ShowUpdateCustomerScreen()
	{
		//cout << "Cars menue will be here";
		clsUpdateCustomerScreen::ShowUpdateCustomerScreen();
	}

	static void _ShowDeleteCustomerScreen()
	{
		//cout << "Logout will be here";
		clsDeleteCustomerScreen::ShowDeleteCustomerScreen();
	}

	static void _ShowFindCustomerScreen()
	{
		//cout << "Close screen will be here";
		clsFindCustomerScreen::ShowFindCustomerScreen();
	}
	
	static void _ShowRentalHistoryCustomerScreen()
	{
		//cout << "Close screen will be here";
		clsCustomerHistoryScreen::ShowCustomerHisoryList();
	}

	static void _PerformCustomersMenueOptions(enCustomersMenueOptions Option)
	{
		switch (Option)
		{
		case clsCustomersMenueScreen::eCustomersListScreen:
		{
			system("cls");
			_ShowCustomersListScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCustomersMenueScreen::eAddNewCustomerScreen:
		{
			system("cls");
			_ShowAddNewCustomerScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCustomersMenueScreen::eUpdateCustemorScreen:
		{
			system("cls");
			_ShowUpdateCustomerScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCustomersMenueScreen::eDeleteCustomerScreen:
		{
			system("cls");
			_ShowDeleteCustomerScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCustomersMenueScreen::eFindCustomerScreen:
		{
			system("cls");
			_ShowFindCustomerScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCustomersMenueScreen::eRentalHistoryCustomerList:
		{
			system("cls");
			_ShowRentalHistoryCustomerScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsCustomersMenueScreen::eShowMainMenue:
		{
			break;
		}
		}
	}

public:
	static void ShowCustomersMenueScreen()
	{
		if (!CheckAccessRight(clsAdmins::eManageCustomers))
		{
			return;
		}
		system("cls");
		_DrawHeaderScreen("Customers Menue Screen");

		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		cout << setw(20) << left << "" << "\t\t\t\tCustomers Menue\n";
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		cout << setw(20) << left << "" << "\t\t\t[1]Customers List\n";
		cout << setw(20) << left << "" << "\t\t\t[2]Add New Customer\n";
		cout << setw(20) << left << "" << "\t\t\t[3]Update Customer\n";
		cout << setw(20) << left << "" << "\t\t\t[4]Delete Customer\n";
		cout << setw(20) << left << "" << "\t\t\t[5]Find Customer\n";
		cout << setw(20) << left << "" << "\t\t\t[6]Rental History Customer List\n";
		cout << setw(20) << left << "" << "\t\t\t[7]Main Menue\n";
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		_PerformCustomersMenueOptions((enCustomersMenueOptions)_ReadCustomerMenueOption());

	}
};

