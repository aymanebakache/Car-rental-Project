#pragma once
#include"clsScreen.h"
#include"clsCustomer.h"
#include"clsInputValidate.h"

class clsUpdateCustomerScreen :protected clsScreen
{
private:
	static void _ReadCustomerInfo(clsCustomer& Customer)
	{
		cout << "\nEnter First Name:";
		Customer.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name:";
		Customer.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email:";
		Customer.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone:";
		Customer.Phone = clsInputValidate::ReadString();
		cout << "\nEnter Password:";
		Customer.Password = clsInputValidate::ReadString();
		cout << "\nEnter Car Detail:";
		Customer.Car = clsInputValidate::ReadString();
		do
		{
			cout << "\nEnter First Date:";
			Customer.StartDateRent = clsInputValidate::ReadString();
			cout << "\nEnter Second Date:";
			Customer.EndDateRent = clsInputValidate::ReadString();
		} while (!clsDate::IsValidDate(clsDate(Customer.StartDateRent)) || !clsDate::IsValidDate(clsDate(Customer.EndDateRent)) ||
			clsDate::IsDate1AfterDate2(clsDate(Customer.StartDateRent), clsDate(Customer.EndDateRent)));
		cout << "\nEnter Cost in ($):";
		Customer.Invoice = clsInputValidate::ReadFloatNumber();
	}

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
		cout << "\nPeroid Rent:" << Customer.RentPeriod() << endl;
		cout << "\nCost in($):" << Customer.Invoice << endl;
		cout << "\n-----------------------------\n";
	}
public:
	static void ShowUpdateCustomerScreen()
	{
		_DrawHeaderScreen("Update Customer Screen");
		string Id;
		cout << "\nEnter Id:";
		Id = clsInputValidate::ReadString();
		while (!clsCustomer::IsCustomerExist(Id))
		{
			cout << "\nThis Id is not exist in DB ,choose another one:";
			Id = clsInputValidate::ReadString();
		}
		clsCustomer Customer = clsCustomer::Find(Id);
		_PrintCustomerInfo(Customer);
		char Answer = 'n';
		cout << "\nDo you sure you want to update this customer:";
		cin >> Answer;
		if(tolower(Answer)=='y')
		{
			cout << "let's update this customer:";
			cout << "\n-------------------------";
			_ReadCustomerInfo(Customer);
			clsCustomer::enSaveResults Saved = Customer.Save();
			switch (Saved)
			{
			case clsCustomer::svFaildEmpty:
				cout << "\nERROR!customer is not saved because it's empty";
				break;
			case clsCustomer::svSucceeded:
				cout << "\nCustomer is saved successfully";
				_PrintCustomerInfo(Customer);
				break;
			}
		}
	}

};

