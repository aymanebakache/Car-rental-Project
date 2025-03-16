#pragma once
#include"clsScreen.h"
#include"clsAdmins.h"
#include"clsInputValidate.h"

class clsAddNewAdminScreen:protected clsScreen
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
	static void ShowAddNewAdminScreen()
	{
		_DrawHeaderScreen("Add New Admin Screen");
		string Id;
		cout << "\nEnter Id:";
		Id = clsInputValidate::ReadString();
		while (clsAdmins::IsAdminExist(Id))
		{
			cout << "\nThis Id is already used ,choose another one:";
			Id = clsInputValidate::ReadString();
		}
		clsAdmins NewAdmin = clsAdmins::GetAddNewAdminObject(Id);
		_ReadAdminInfo(NewAdmin);
		clsAdmins::enSaveResults Saved = NewAdmin.Save();
		switch (Saved)
		{
		case clsAdmins::svFaildEmpty:
			cout << "\nERROR!New customer is not saved because it's empty";
			break;
		case clsAdmins::svSucceeded:
			cout << "\nNew customer is saved successfully";
			_PrintAdminInfo(NewAdmin);
			break;
		case clsAdmins::svFaildExist:
			cout << "\nERROR!New customer is not saved because it's exist";
			break;
		}
	}
};

