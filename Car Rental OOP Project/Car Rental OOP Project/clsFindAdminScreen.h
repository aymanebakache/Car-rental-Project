#pragma once
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsAdmins.h"

class clsFindAdminScreen:protected clsScreen
{
private:
	static void _PrintAdminInfo(clsAdmins Admin)
	{
		cout << "\nAdmin Info:";
		cout << "\n----------------------\n";
		cout << "\nId:" << Admin.Id() << endl;
		cout << "\nFirst Name:" << Admin.FirstName << endl;
		cout << "\nLast Name:" << Admin.LastName << endl;
		cout << "\nEmail:" << Admin.Email << endl;
		cout << "\nPhone:" << Admin.Phone << endl;
		cout << "\nUsername:" << Admin.UserName << endl;
		cout << "\nPassword:" << Admin.Password << endl;
		cout << "\nPermissions:" << Admin.Permissions << endl;
		cout << "\n-----------------------------\n";
	}
public:
	static void ShowFindAdminScreen()
	{
		_DrawHeaderScreen("\tFind Admin Screen");
		string Id;
		cout << "\nEnter Id:";
		Id = clsInputValidate::ReadString();
		while (!clsAdmins::IsAdminExist(Id))
		{
			cout << "\nThis Id doesn't exist in DB ,choose another one:";
			Id = clsInputValidate::ReadString();
		}
		clsAdmins Admin = clsAdmins::Find(Id);
		if (Admin.IsEmpty())
		{
			cout << "\Admin was not found!";
		}
		else
		{
			cout << "Admin was found!";
		}
		_PrintAdminInfo(Admin);
	}
};

