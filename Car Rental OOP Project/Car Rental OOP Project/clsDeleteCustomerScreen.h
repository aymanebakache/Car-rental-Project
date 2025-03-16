#pragma once
#include"clsScreen.h"
#include"clsCustomer.h"
#include"clsInputValidate.h"

class clsDeleteCustomerScreen:protected clsScreen
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
	static void ShowDeleteCustomerScreen()
	{
		_DrawHeaderScreen("\tDelete Customer Screen");
		string Id;
		cout << "\nEnter Id:";
		Id = clsInputValidate::ReadString();
		while (!clsCustomer::IsCustomerExist(Id))
		{
			cout << "\nThis Id doesn't exist in DB ,choose another one:";
			Id = clsInputValidate::ReadString();
		}
		clsCustomer Customer = clsCustomer::Find(Id);
		_PrintCustomerInfo(Customer);
		char Answer = 'n';
		cout << "\nDo you sure you want to delete this customer:";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			if (Customer.Delete())
			{
				cout << "\nCustomer Deleted successfully!";
				_PrintCustomerInfo(Customer);
			}
			else
			{
				cout << "\nERROR,this customer was not deleted";
			}
		}
	}
};

