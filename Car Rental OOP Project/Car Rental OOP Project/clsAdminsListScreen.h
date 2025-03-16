#pragma once
#include"clsScreen.h"
#include"clsAdmins.h"
#include<iomanip>

class clsAdminsListScreen :protected clsScreen
{
private:
	static void _PrintAdminObject(clsAdmins Admin)
	{
		cout <<" \n" << setw(8) << left << "" << "|" << setw(8) << left << Admin.Id() <<
			"|" << setw(20) << left << Admin.FullName() <<
			"|" << setw(25) << left << Admin.Email <<
			"|" << setw(12) << left << Admin.Phone <<
			"|" << setw(15) << left << Admin.UserName <<
			"|" << setw(12) << left << Admin.Password <<
			"|" << setw(10) << left << Admin.Permissions ;
	}

public:
	static void ShowAdminsListScreen()
	{
		vector<clsAdmins> vAdmins = clsAdmins::GetAdminsList();
		string Title = "\t Admins List Screen";
		string SubTitle = "\t (" + to_string(vAdmins.size()) + ") admin(s).";
		_DrawHeaderScreen(Title, SubTitle);
		cout << setw(8) << left << "" << "----------------------------------------------------------------------------------------------------------------\n";
		cout <<"\n" << setw(8) << left << "" << "|" << setw(8) << left << "Id" <<
			"|" << setw(20) << left << "Full Name" <<
			"|" << setw(25) << left << "Email" <<
			"|" << setw(12) << left << "Phone" <<
			"|" << setw(15) << left << "Username" <<
			"|" << setw(12) << left << "Password" <<
			"|" << setw(10) << left << "Permissions" ;
		cout <<endl << setw(8) << left << "" << "----------------------------------------------------------------------------------------------------------------";
		if (vAdmins.size() == 0)
		{
			cout << setw(15) << left << "" << "No admin available in the system\n";
		}
		else
		{
			for (clsAdmins A : vAdmins)
			{
				_PrintAdminObject(A);
				
			}
		}
		cout <<endl<< setw(8) << left << "" << "----------------------------------------------------------------------------------------------------------------";
	}
};

