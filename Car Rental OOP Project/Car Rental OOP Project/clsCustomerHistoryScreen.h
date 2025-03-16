#pragma once
#include"clsScreen.h"
#include"clsCustomer.h"
#include"clsInputValidate.h"

class clsCustomerHistoryScreen :protected clsScreen
{
private:
	static void _PrintCustomerObject(clsCustomer Customer)
	{
		cout << setw(8) << left << "" << "|" << setw(20) << left << Customer.FullName() << "|" << setw(20) << left << Customer.Car <<
			"|" << setw(15) << left << Customer.StartDateRent <<
			"|" << setw(15) << left << Customer.EndDateRent <<
			"|" << setw(15) << left << Customer.Invoice << endl;
	}

public:
	static void ShowCustomerHisoryList()
	{
		_DrawHeaderScreen("\tCustomer History Screen");
		string Id;
		cout << "\nEnter Id:";
		Id = clsInputValidate::ReadString();
		vector<clsCustomer> vCustomers = clsCustomer::GetRentalHistoryListOfCustomer(Id);
		string Title = "\t Customers List Screen";
		string SubTitle = "\t (" + to_string(vCustomers.size()) + ") customer(s).";
		_DrawHeaderScreen(Title, SubTitle);
		cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------\n";
		cout << setw(8) << left << "" << "|" << setw(20) << left << "Full Name" << "|" << setw(20) << left << "Car Details" <<
			"|" << setw(15) << left << "From" <<
			"|" << setw(15) << left << "To" <<
			"|" << setw(15) << left << "Cost($)" << endl;
		cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------\n";
		if (vCustomers.size() == 0)
		{
			cout << setw(15) << left << "" << "No history available in the system for this customer\n";
		}
		else
		{
			for (clsCustomer C : vCustomers)
			{
				_PrintCustomerObject(C);
				
			}
		}
		cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------\n";
	}
};

