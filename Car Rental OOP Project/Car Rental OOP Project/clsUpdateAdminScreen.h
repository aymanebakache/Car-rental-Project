#pragma once
#include"clsScreen.h"
#include"clsAdmins.h"
#include"clsInputValidate.h"

class clsUpdateAdminScreen:protected clsScreen
{
private:
	static void _ReadAdminInfo(clsAdmins& Admin)
	{
		cout << "\nEnter First Name:";
		Admin.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name:";
		Admin.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email:";
		Admin.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone:";
		Admin.Phone = clsInputValidate::ReadString();
		cout << "\nEnter Username:";
		Admin.UserName = clsInputValidate::ReadString();
		cout << "\nEnter Password:";
		Admin.Password = clsInputValidate::ReadString();
		cout << "\n------Permissions:------";
		Admin.Permissions = _ReadAdminPermissions();
	}

	static int _ReadAdminPermissions()
	{
		int Permissions = 0;
		char Answer = 'n';
		cout << "\nDo you want to get full access to main menue?(y/n)?";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			return -1;
		}
		cout << "\n-----Do you want to get access to:------";

		cout << "\nManage customers:";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsAdmins::eManageCustomers;
		}

		cout << "\nManage admins:";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsAdmins::eManageAdmins;
		}

		cout << "\nManage cars:";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions += clsAdmins::eManageCars;
		}
		return Permissions;
	}

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
	static void ShowUpdateAdminScreen()
	{
		_DrawHeaderScreen("Update Admin Screen");
		string Id;
		cout << "\nEnter Id:";
		Id = clsInputValidate::ReadString();
		while (!clsAdmins::IsAdminExist(Id))
		{
			cout << "\nThis Id was not found ,choose another one:";
			Id = clsInputValidate::ReadString();
		}
		clsAdmins Admin = clsAdmins::Find(Id);
		_ReadAdminInfo(Admin);
		char Answer = 'n';
		cout << "\are you sure to update this Admin?(y/n)?";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			clsAdmins::enSaveResults Saved = Admin.Save();
			switch (Saved)
			{
			case clsAdmins::svFaildEmpty:
			{
				cout << "\nERROR!The admin is not saved because it's empty";
				break;
			}
			case clsAdmins::svSucceeded:
			{
				cout << "\nAdmin Updated successfully";
				_PrintAdminInfo(Admin);
				break;
			}
			}
		}
	}
};

