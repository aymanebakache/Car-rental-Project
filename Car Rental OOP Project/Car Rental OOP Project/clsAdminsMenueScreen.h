#pragma once
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsAdmins.h"
#include"clsAdminsListScreen.h"
#include"clsAddNewAdminScreen.h"
#include"clsUpdateAdminScreen.h"
#include"clsDeleteAdminScreen.h"
#include"clsFindAdminScreen.h"
#include"clsLoginAdminsListScreen.h"

class clsAdminsMenueScreen:protected clsScreen
{
private:
	enum enAdminsMenueOptions {
		eAdminsListScreen = 1, eAddNewAdminScreen = 2, eUpdateAdminScreen = 3, eDeleteAdminScreen = 4,
		eFindAdminScreen = 5,eShowLoginAdminsScreen=6, eShowMainMenue = 7
	};

	static short _ReadAdminMenueOption()
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
		ShowAdminsMenueScreen();
	}

	static void _ShowAdminsListScreen()
	{
		//cout << "Admins list will be here";
		clsAdminsListScreen::ShowAdminsListScreen();
	}

	static void _ShowAddNewAdminScreen()
	{
		//cout << "Add new Admin will be here";
		clsAddNewAdminScreen::ShowAddNewAdminScreen();
	}

	static void _ShowUpdateAdminScreen()
	{
		//cout << "Update Admin will be here";
		clsUpdateAdminScreen::ShowUpdateAdminScreen();
	}

	static void _ShowDeleteAdminScreen()
	{
		//cout << "Delete will be here";
		clsDeleteAdminScreen::ShowDeleteAdminScreen();
	}

	static void _ShowFindAdminScreen()
	{
		//cout << "Find screen will be here";
		clsFindAdminScreen::ShowFindAdminScreen();
	}
	
	static void _ShowLoginAdminsListScreen()
	{
		//cout << "Find screen will be here";
		clsLoginAdminsListScreen::ShowLoginAdminsListScreen();
	}



	static void _PerformAdminsMenueOptions(enAdminsMenueOptions Option)
	{
		switch (Option)
		{
		case clsAdminsMenueScreen::eAdminsListScreen:
		{
			system("cls");
			_ShowAdminsListScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsAdminsMenueScreen::eAddNewAdminScreen:
		{
			system("cls");
			_ShowAddNewAdminScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsAdminsMenueScreen::eUpdateAdminScreen:
		{
			system("cls");
			_ShowUpdateAdminScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsAdminsMenueScreen::eDeleteAdminScreen:
		{
			system("cls");
			_ShowDeleteAdminScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsAdminsMenueScreen::eFindAdminScreen:
		{
			system("cls");
			_ShowFindAdminScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsAdminsMenueScreen::eShowLoginAdminsScreen:
		{
			system("cls");
			_ShowLoginAdminsListScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsAdminsMenueScreen::eShowMainMenue:
		{
			break;
		}
		}
	}

public:
	static void ShowAdminsMenueScreen()
	{
		if (!CheckAccessRight(clsAdmins::eManageAdmins))
		{
			return;
		}
		system("cls");
		_DrawHeaderScreen("Admins Menue Screen");

		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		cout << setw(20) << left << "" << "\t\t\t\tAdmins Menue\n";
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		cout << setw(20) << left << "" << "\t\t\t[1]Admins List\n";
		cout << setw(20) << left << "" << "\t\t\t[2]Add New Admin\n";
		cout << setw(20) << left << "" << "\t\t\t[3]Update Admin\n";
		cout << setw(20) << left << "" << "\t\t\t[4]Delete Admin\n";
		cout << setw(20) << left << "" << "\t\t\t[5]Find Admin\n";
		cout << setw(20) << left << "" << "\t\t\t[6]Login Admins List\n";
		cout << setw(20) << left << "" << "\t\t\t[7]Main Menue\n";
		cout << setw(20) << left << "" << "\t\t\t====================================\n";
		_PerformAdminsMenueOptions((enAdminsMenueOptions)_ReadAdminMenueOption());

	}
};

