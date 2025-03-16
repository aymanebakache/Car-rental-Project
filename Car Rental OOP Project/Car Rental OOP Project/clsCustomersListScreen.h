#pragma once
#include"clsScreen.h"
#include"clsCustomer.h"

class clsCustomersListScreen:protected clsScreen
{
private:
	static void _PrintCustomerObject(clsCustomer Customer)
	{
		cout << setw(8) << left << "" << "|" << setw(8) << left << Customer.Id()<<
			"|" << setw(20) << left << Customer.FullName() <<
			"|" << setw(20) << left << Customer.Email <<
			"|" << setw(12) << left << Customer.Phone<<
			"|" << setw(20) << left << Customer.Car <<
			"|" << setw(12) << left << Customer.StartDateRent <<
			"|" << setw(12) << left << Customer.EndDateRent <<
			"|" << setw(15) << left << Customer.Invoice << endl;
	}

public:
	static void ShowCustomersList()
	{
		vector<clsCustomer> vCustomers = clsCustomer::GetCustomersList();
		string Title = "\t Customers List Screen";
		string SubTitle = "\t (" + to_string(vCustomers.size()) + ") customer(s).";
		_DrawHeaderScreen(Title, SubTitle);
		cout << setw(8) << left << "" << "--------------------------------------------------------------------------------------------"<<
			"----------------------------\n";
		cout << setw(8) << left << "" << "|" << setw(8) << left << "Id" <<
			"|" << setw(20) << left << "Full Name" << 
			"|" << setw(20) << left << "Email" << 
			"|" << setw(12) << left << "Phone" << 
			"|" << setw(20) << left << "Car Details" <<
			"|" << setw(12) << left << "From" <<
			"|" << setw(12) << left << "To" <<
			"|" << setw(15) << left << "Cost($)" << endl;
		cout << setw(8) << left << "" << "--------------------------------------------------------------------------------------------" <<
			"----------------------------\n";
		if (vCustomers.size() == 0)
		{
			cout << setw(15) << left << "" << "No Customer available in the system\n";
		}
		else
		{
			for (clsCustomer C : vCustomers)
			{
				_PrintCustomerObject(C);
				cout << setw(8) << left << "" << "--------------------------------------------------------------------------------------------" <<
					"----------------------------\n";
			}
		}
	}
};

