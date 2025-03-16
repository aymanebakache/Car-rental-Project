#pragma once
#include"clsScreen.h"
#include"clsCustomer.h"
#include"clsInputValidate.h"

class clsFindCustomerScreen:protected clsScreen
{
private:
	static void _PrintCustomerInfo(clsCustomer Customer)
	{
		cout << "\nCustomer Info:";
		cout << "\n----------------------\n";
		cout << "\nId:" << Customer.Id() << endl;
		cout << "\nFirst Name:" << Customer.FirstName << endl;
		cout << "\nLast Name:" << Customer.LastName << endl;
		cout << "\nEmail:" << Customer.Email << endl;
		cout << "\nPhone:" << Customer.Phone << endl;
		cout << "\nPassword:" << Customer.Password << endl;
		cout << "\nCar Detail:" << Customer.Car << endl;
		cout << "\nStart Rent:" << Customer.StartDateRent << endl;
		cout << "\nEnd Rent:" << Customer.EndDateRent << endl;
		cout << "\nCost in($):" << Customer.Invoice << endl;
		cout << "\n-----------------------------\n";
	}
public:
	static void ShowFindCustomerScreen()
	{
		_DrawHeaderScreen("\tFind Customer Screen");
		string Id;
		cout << "\nEnter Id:";
		Id = clsInputValidate::ReadString();
		while (!clsCustomer::IsCustomerExist(Id))
		{
			cout << "\nThis Id doesn't exist in DB ,choose another one:";
			Id = clsInputValidate::ReadString();
		}
		clsCustomer Customer = clsCustomer::Find(Id);
		if (Customer.IsEmpty())
		{
			cout << "\nCustomer was not found!";
		}
		else
		{
			cout << "Customer was found!";
		}
		_PrintCustomerInfo(Customer);
	}
};

