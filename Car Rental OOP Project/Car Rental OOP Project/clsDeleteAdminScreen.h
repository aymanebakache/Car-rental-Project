#pragma once
#include"clsScreen.h"
#include"clsAdmins.h"
#include"clsInputValidate.h"

class clsDeleteAdminScreen:protected clsScreen
{
private:
	static void _PrintAdminInfo(clsAdmins Admin)
	{
		cout << "\Admin Info:";
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
	static void ShowDeleteAdminScreen()
	{
		_DrawHeaderScreen("\tDelete Admin Screen");
		string Id;
		cout << "\nEnter Id:";
		Id = clsInputValidate::ReadString();
		while (!clsAdmins::IsAdminExist(Id))
		{
			cout << "\nThis Id doesn't exist in DB ,choose another one:";
			Id = clsInputValidate::ReadString();
		}
		clsAdmins Admin = clsAdmins::Find(Id);
		_PrintAdminInfo(Admin);
		char Answer = 'n';
		cout << "\nDo you sure you want to delete this admin:";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			if (Admin.Delete())
			{
				cout << "\nAdmin Deleted successfully!";
				_PrintAdminInfo(Admin);
			}
			else
			{
				cout << "\nERROR,this admin was not deleted";
			}
		}
	}
};

