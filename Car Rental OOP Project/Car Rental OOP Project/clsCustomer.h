#pragma once
#include<vector>
#include<fstream>
#include"clsPerson.h"
#include"clsDate.h"
#include"clsString.h"
#include"Global.h"

class clsCustomer:public clsPerson
{
private:
	enum enMode{EmptyMode=0,UpdateMode=1,AddMode=2};

	enMode _Mode;
	string _Password;
	string _Car;
	string _StartDateRent;
	string _EndDateRent;
	float _Invoice;
	bool _MarkToDelete = false;

	static clsCustomer _ConvertLineToCustomerObject(string Line, string Seperator = "#//#")
	{
		vector<string> vLine = clsString::Split(Line, Seperator);
		return clsCustomer(enMode::UpdateMode, vLine[0], vLine[1], vLine[2], vLine[3], vLine[4],
			clsUtil::DecryptText(vLine[5], 2), vLine[6], vLine[7], vLine[8], stof(vLine[9]));
	}

	static string _ConvertCustomerObjectToLine(clsCustomer Customer, string Seperator = "#//#")
	{
		string Line = "";
		Line += Customer.Id() + Seperator;
		Line += Customer.FirstName + Seperator;
		Line += Customer.LastName + Seperator;
		Line += Customer.Email + Seperator;
		Line += Customer.Phone + Seperator;
		Line += clsUtil::EncryptText(Customer.Password, 2) + Seperator;
		Line += Customer.Car + Seperator;
		Line += Customer.StartDateRent + Seperator;
		Line += Customer.EndDateRent + Seperator;
		Line +=to_string(Customer.Invoice);
		return Line;
	}

	static vector<clsCustomer> _LoadDataCustomersFromFile()
	{
		vector<clsCustomer> vCustomers;
		string Line;
		fstream MyFile;
		MyFile.open(CustomersFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCustomer Customer = _ConvertLineToCustomerObject(Line);
				vCustomers.push_back(Customer);
			}
			MyFile.close();
		}
		return vCustomers;
	}

	static void _SaveDataCustomersToFile(vector<clsCustomer> vCustomers)
	{
		string Line;
		fstream MyFile;
		MyFile.open(CustomersFile, ios::out);
		if (MyFile.is_open())
		{
			for (clsCustomer C : vCustomers)
			{
				if(!C.MarkedToDeleted())
				{
					Line = _ConvertCustomerObjectToLine(C);
					MyFile << Line << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsCustomer> vCustomers = _LoadDataCustomersFromFile();
		for (clsCustomer& C : vCustomers)
		{
			if (C.Id() == Id())
			{
				C = *this;
			}
		}
		_SaveDataCustomersToFile(vCustomers);
	}

	void _AddNewCustomer()
	{
		_AddNewLineToFile(_ConvertCustomerObjectToLine(*this));
	}

	void _AddNewLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open(CustomersFile, ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}
	
	static clsCustomer _GetEmptyCustomerObject()
	{
		return clsCustomer(enMode::EmptyMode, "", "", "", "", "", "", "", "", "", 0);
	}




public:

	clsCustomer(enMode Mode, string Id, string FirstName, string LastName, string Email, string Phone, string Password, string Car,
		string StartDateRent, string EndDateRent,float Invoice) :clsPerson(Id, FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Password = Password;
		_Car = Car;
		_StartDateRent = StartDateRent;
		_EndDateRent = EndDateRent;
		_Invoice = Invoice;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	bool MarkedToDeleted()
	{
		return _MarkToDelete;
	}

	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword() 
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;
	
	void SetCar(string Car)
	{
		_Car = Car;
	}
	string GetCar()
	{
		return _Car;
	}
	__declspec(property(get = GetCar, put = SetCar)) string Car;
	
	void SetStartDateRent(string StartDateRent)
	{
		_StartDateRent = StartDateRent;
	}
	string GetStartDateRent()
	{
		return _StartDateRent;
	}
	__declspec(property(get = GetStartDateRent, put = SetStartDateRent)) string StartDateRent;
	
	void SetEndDateRent(string EndDateRent)
	{
		_EndDateRent = EndDateRent;
	}
	string GetEndDateRent()
	{
		return _EndDateRent;
	}
	__declspec(property(get = GetEndDateRent, put = SetEndDateRent)) string EndDateRent;

	short RentPeriod()
	{
		clsDate FirstDate = clsDate(_StartDateRent);
		clsDate LastDate = clsDate(_EndDateRent);
		return clsDate::GetDifferenceInDays(FirstDate, LastDate, true);
	}

	void SetInvoice(float Invoice)
	{
		_Invoice = Invoice;
	}
	float GetInvoice()
	{
		return _Invoice;
	}
	__declspec(property(get = GetInvoice, put = SetInvoice)) float Invoice;

	static clsCustomer Find(string Id)
	{
		string Line;
		fstream MyFile;
		MyFile.open(CustomersFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCustomer Customer = _ConvertLineToCustomerObject(Line);
				if (Customer.Id() == Id)
				{
					MyFile.close();
					return Customer;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCustomerObject();
	}
	static clsCustomer Find(string Id,string Password)
	{
		string Line;
		fstream MyFile;
		MyFile.open(CustomersFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCustomer Customer = _ConvertLineToCustomerObject(Line);
				if (Customer.Id() == Id && Customer.Password==Password)
				{
					MyFile.close();
					return Customer;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCustomerObject();
	}

	enum enSaveResults { svFaildEmpty = 0, svSucceeded = 1, svFaildExist = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsCustomer::EmptyMode:
		{
			return svFaildEmpty;
			break;
		}
		case clsCustomer::UpdateMode:
		{
			_Update();
			return  enSaveResults::svSucceeded;
			break;
		}
		case clsCustomer::AddMode:
		{
			if (clsCustomer::IsCustomerExist(Id()))
			{
				return enSaveResults::svFaildExist;
			}
			else
			{
				_AddNewCustomer();
				_Mode == enMode::UpdateMode;
				return  enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}

	static bool IsCustomerExist(string Id)
	{
		clsCustomer Customer = Find(Id);
		return !Customer.IsEmpty();
	}

	bool Delete()
	{
		vector<clsCustomer> vCustomers = _LoadDataCustomersFromFile();
		for (clsCustomer &C : vCustomers)
		{
			if (C.Id() == Id())
			{
				C._MarkToDelete = true;
				break;
			}
		}
		_SaveDataCustomersToFile(vCustomers);
		*this = _GetEmptyCustomerObject();
		return true;
	}

	static clsCustomer GetAddNewCustomerObject(string Id)
	{
		return clsCustomer(enMode::AddMode, Id, "", "", "", "", "", "", "", "", 0);
	}

	static vector<clsCustomer> GetCustomersList()
	{
		return _LoadDataCustomersFromFile();
	}

	static vector<clsCustomer> GetRentalHistoryListOfCustomer(string Id)
	{
		vector<clsCustomer> vCustomers;
		string Line;
		fstream MyFile;
		MyFile.open(CustomersFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile,Line))
			{
				clsCustomer Customer = _ConvertLineToCustomerObject(Line);
				if (Customer.Id() == Id)
				{
					vCustomers.push_back(Customer);
				}
			}
			MyFile.close();
		}
		return vCustomers;
	}

	
};

