#pragma once
#include"clsScreen.h"
#include"clsAdmins.h"
#include"FilesNames.h"

class clsLoginAdminsListScreen:protected clsScreen
{
private:
	static void _PrintLoginRegisterObject(clsAdmins::stLogin stLoginRecord)
	{
		cout << setw(10) << left << "" << "|" << setw(25) << left << stLoginRecord.DateTime <<
			"|" << setw(20) << left << stLoginRecord.Username <<
			"|" << setw(15) << left << stLoginRecord.Password <<
			"|" << setw(15) << left << stLoginRecord.Permission <<endl;
	}

public:
	static void ShowLoginAdminsListScreen()
	{
		vector<clsAdmins::stLogin> vLogins = clsAdmins::GetLoginAdminsList();
		string Title = "\t Login Admins List Screen";
		string SubTitle = "\t (" + to_string(vLogins.size()) + ") login(s).";
		_DrawHeaderScreen(Title, SubTitle);
		cout << setw(10) << left << "" << "----------------------------------------------------------------------------------\n";
		cout << setw(10) << left << "" << "|" << setw(25) << left << "Date & Time" <<
			"|" << setw(20) << left << "Username" <<
			"|" << setw(15) << left << "Password" <<
			"|" << setw(15) << left << "Permission" <<endl;
		cout << setw(10) << left << "" << "----------------------------------------------------------------------------------\n";
		if (vLogins.size() == 0)
		{
			cout << setw(20) << left << "" << "No Login happened in the system\n";
		}
		else
		{
			for (clsAdmins::stLogin L : vLogins)
			{
				_PrintLoginRegisterObject(L);
				cout << setw(10) << left << "" << "---------------------------------------------------------------------------\n";
			}
		}
	}
};

