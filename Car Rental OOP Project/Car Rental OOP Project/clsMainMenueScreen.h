#pragma once
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsCustomersMenueScreen.h"
#include"clsAdminsMenueScreen.h"
#include"clsCarsMenueScreen.h"
#include"FilesNames.h"

class clsMainMenueScreen:protected clsScreen
{
private:
	enum enMainMenueOptions{eCustomers=1,eAdmins=2,eCars=3,eLogout=4,eClose=5};

	static short _ReadMainMenueOption()
	{
		short Option;
		cout<<setw(30)<<left<<"" << "\t\tEnter the option you want to do?[1 to 5]?";
		Option = clsInputValidate::ReadShortNumberBetween(1, 5, "This Option is not available,choose available one:");
		return Option;
	}

	static void _GoBackToMainMenue()
	{
		cout << "\n\n\tPress any key to go back to main menue...";
		system("pause>0");
		ShowMainMenueScreen();
	}

	static void _ShowCustomersMenueScreen()
	{
		//cout << "Customers menue will be here";
		clsCustomersMenueScreen::ShowCustomersMenueScreen();
	}
	
	static void _ShowAdminsMenueScreen()
	{
		//cout << "Admins menue will be here";
		clsAdminsMenueScreen::ShowAdminsMenueScreen();
	}
	
	static void _ShowCarsMenueScreen()
	{
		//cout << "Cars menue will be here";
		clsCarsMenueScreen::ShowCarsMenueScreen();
	}

	static void _ShowLogoutScreen()
	{
		cout << "Logout will be here";
	}

	static void _ShowCloseScreen()
	{
		cout << "Close screen will be here";
	}

	static void _PerformMainMenueOptions(enMainMenueOptions Option)
	{
		switch (Option)
		{
		case clsMainMenueScreen::eCustomers:
		{
			system("cls");
			_ShowCustomersMenueScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainMenueScreen::eAdmins:
		{
			system("cls");
			_ShowAdminsMenueScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainMenueScreen::eCars:
		{
			system("cls");
			_ShowCarsMenueScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainMenueScreen::eLogout:
		{
			/*system("cls");
			_ShowLogoutScreen();
			_GoBackToMainMenue();*/
			CurrentAdmin = clsAdmins::Find("", "");
			break;
		}
		case clsMainMenueScreen::eClose:
		{
			system("cls");
			_DrawHeaderScreen("The programm was finished and closed!");
			/*_ShowCloseScreen();
			_GoBackToMainMenue();*/
			Close = true;
			break;
		}
		}
	}

public:
	static void ShowMainMenueScreen()
	{
		system("cls");
		_DrawHeaderScreen("Main Menue Screen");
		
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		cout << setw(20) << left << "" << "\t\t\t\t\tMain Menue\n";
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		cout << setw(20) << left << "" << "\t\t\t[1]Customers Menue\n";
		cout << setw(20) << left << "" << "\t\t\t[2]Admins Menue\n";
		cout << setw(20) << left << "" << "\t\t\t[3]Cars Menue\n";
		cout << setw(20) << left << "" << "\t\t\t[4]Logout\n";
		cout << setw(20) << left << "" << "\t\t\t[5]Close\n";
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		_PerformMainMenueOptions((enMainMenueOptions)_ReadMainMenueOption());

	}


};

