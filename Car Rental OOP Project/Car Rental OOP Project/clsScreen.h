#pragma once
#include<iostream>
#include<iomanip>
#include"Global.h"

using namespace std;

class clsScreen
{
protected:
	static void _DrawHeaderScreen(string Title, string SubTitle="")
	{
		cout << setw(20) << left << "" << "\t\t=======================================================\n\n";
		cout << setw(20) << left << "" << "\t\t\t\t" << Title << endl;
		if(SubTitle!="")
		{
			cout << setw(20) << left << "" << "\t\t\t\t" << SubTitle << endl << endl;
		}
		cout << setw(20) << left << "" << "\t\t=======================================================\n";
		cout << setw(20) << left << "" << "\t\tAdmin:" << CurrentAdmin.UserName << endl;
		cout << setw(20) << left << "" << "\t\tDtae:" << clsDate::DateToString(clsDate::GetSystemDate()) << endl;
		cout << setw(20) << left << "" << "\t\t=======================================================\n";
	}

	static bool CheckAccessRight(clsAdmins::enPermissions Permission)
	{
		if (!CurrentAdmin.CheckAccessPermission(Permission))
		{
			cout << setw(20) << left << "------------------------------------------------------------------------\n";
			cout << setw(20) << left << "\t\t\tAccess denied!Contact your manager!\n";
			cout << setw(20) << left << "------------------------------------------------------------------------\n";
			return false;
		}
		return true;
	}
};

