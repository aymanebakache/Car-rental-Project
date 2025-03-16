#pragma once
#include"clsScreen.h"
#include"clsMainMenueScreen.h"
#include"Global.h"
#include"clsMainMenueScreen.h"
#include"FilesNames.h"
#include"clsAdmins.h"
class clsLoginScreen:protected clsScreen
{
private:
	static void _Login()
	{
		string Username, Password;
		bool IsLoginFaild = false;
		short Trials = 3;
		do {
			if (IsLoginFaild)
			{
				Trials--;
				cout << "\nUsername/Password incorrect!\n";
				cout << "\nYou have " << Trials << " trials to login!\n";
				if (Trials == 0)
				{
					cout << "\nThe programm is locked\n";
					Close = true;
					return;
				}
			}
			cout << "\nEnter your username:";
			cin >> Username;
			cout << "\nEnter your password:";
			cin >> Password;
			CurrentAdmin = clsAdmins::Find(Username, Password);
			IsLoginFaild = CurrentAdmin.IsEmpty();
			
		} while (IsLoginFaild && Trials > 0);
		CurrentAdmin.RegisterLogineInFile();
		clsMainMenueScreen::ShowMainMenueScreen();
	}

public:
	static void ShowLoginScreen()
	{
		while(!Close){
			system("cls");
			_DrawHeaderScreen("\t  Login Screen");
			_Login();
		}
	}
};

