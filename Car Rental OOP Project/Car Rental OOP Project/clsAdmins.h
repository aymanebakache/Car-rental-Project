#pragma once
#include<vector>
#include<fstream>
#include"clsPerson.h"
#include"clsDate.h"
#include"clsString.h"
#include"FilesNames.h"
#include"clsUtil.h"

class clsAdmins :public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkToDelete = false;

	struct stLogin;

	string _PrepareRegisterLogin(string Seperator="#//#")
	{
		string Line = "";
		Line += clsDate::GetSystemDateTimeString() + Seperator;
		Line += UserName + Seperator;
		Line += clsUtil::EncryptText(Password,2) + Seperator;
		Line += to_string(Permissions);
		return Line;
	}

	static stLogin _ConvertLoginRecordLineToObject(string Line, string Seperator = "#//#")
	{
		stLogin stLoginRecord;
		vector<string> vLine = clsString::Split(Line, Seperator);
		stLoginRecord.DateTime = vLine[0];
		stLoginRecord.Username = vLine[1];
		stLoginRecord.Password = clsUtil::DecryptText(vLine[2], 2);
		stLoginRecord.Permission = stoi(vLine[3]);
		return stLoginRecord;
	}

	static clsAdmins _ConvertLineToAdminObject(string Line, string Seperator = "#//#")
	{
		vector<string> vLine = clsString::Split(Line, Seperator);
		return clsAdmins(enMode::UpdateMode, vLine[0], vLine[1], vLine[2], vLine[3], vLine[4],
			vLine[5], clsUtil::DecryptText(vLine[6], 2), stoi(vLine[7]));
	}

	static string _ConvertAdminObjectToLine(clsAdmins Admin, string Seperator = "#//#")
	{
		string Line = "";
		Line += Admin.Id() + Seperator;
		Line += Admin.FirstName + Seperator;
		Line += Admin.LastName + Seperator;
		Line += Admin.Email + Seperator;
		Line += Admin.Phone + Seperator;
		Line += Admin.UserName + Seperator;
		Line += clsUtil::EncryptText(Admin.Password, 2) + Seperator;
		Line += to_string(Admin.Permissions);
		return Line;
	}

	static vector<clsAdmins> _LoadDataAdminsFromFile()
	{
		vector<clsAdmins> vAdmins;
		string Line;
		fstream MyFile;
		MyFile.open(AdminsFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsAdmins Admin = _ConvertLineToAdminObject(Line);
				vAdmins.push_back(Admin);
			}
			MyFile.close();
		}
		return vAdmins;
	}

	static void _SaveDataAdminsToFile(vector<clsAdmins> vAdmins)
	{
		string Line;
		fstream MyFile;
		MyFile.open(AdminsFile, ios::out);
		if (MyFile.is_open())
		{
			for (clsAdmins A : vAdmins)
			{
				if (!A.MarkedToDeleted())
				{
					Line = _ConvertAdminObjectToLine(A);
					MyFile << Line << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsAdmins> vAdmins = _LoadDataAdminsFromFile();
		for (clsAdmins& A : vAdmins)
		{
			if (A.Id() == Id())
			{
				A = *this;
			}
		}
		_SaveDataAdminsToFile(vAdmins);
	}

	void _AddNewAdmin()
	{
		_AddNewLineToFile(_ConvertAdminObjectToLine(*this));
	}

	void _AddNewLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open(AdminsFile, ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	static clsAdmins _GetEmptyAdminObject()
	{
		return clsAdmins(enMode::EmptyMode, "", "", "", "", "", "", "", 0);
	}




public:

	clsAdmins(enMode Mode, string Id, string FirstName, string LastName, string Email, string Phone, string Username, string Password,
		 int Permissions) :clsPerson(Id, FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	struct stLogin {
		string DateTime;
		string Username;
		string Password;
		int Permission;
	};

	enum enPermissions{eAll=-1,eManageCustomers=2,eManageAdmins=4,eManageCars=8};

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	bool MarkedToDeleted()
	{
		return _MarkToDelete;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName))string UserName;
	
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;
	
	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;

	

	static clsAdmins Find(string Id)
	{
		string Line;
		fstream MyFile;
		MyFile.open(AdminsFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsAdmins Admin = _ConvertLineToAdminObject(Line);
				if (Admin.Id() == Id)
				{
					MyFile.close();
					return Admin;
				}
			}
			MyFile.close();
		}
		return _GetEmptyAdminObject();
	}
	static clsAdmins Find(string Username, string Password)
	{
		string Line;
		fstream MyFile;
		MyFile.open(AdminsFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsAdmins Admin = _ConvertLineToAdminObject(Line);
				if (Admin.UserName == Username && Admin.Password == Password)
				{
					MyFile.close();
					return Admin;
				}
			}
			MyFile.close();
		}
		return _GetEmptyAdminObject();
	}

	enum enSaveResults { svFaildEmpty = 0, svSucceeded = 1, svFaildExist = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsAdmins::EmptyMode:
		{
			return svFaildEmpty;
			break;
		}
		case clsAdmins::UpdateMode:
		{
			_Update();
			return  enSaveResults::svSucceeded;
			break;
		}
		case clsAdmins::AddMode:
		{
			if (clsAdmins::IsAdminExist(Id()))
			{
				return enSaveResults::svFaildExist;
			}
			else
			{
				_AddNewAdmin();
				_Mode == enMode::UpdateMode;
				return  enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}

	static bool IsAdminExist(string Id)
	{
		clsAdmins Admin = Find(Id);
		return !Admin.IsEmpty();
	}

	bool Delete()
	{
		vector<clsAdmins> vAdmins = _LoadDataAdminsFromFile();
		for (clsAdmins& A : vAdmins)
		{
			if (A.Id() == Id())
			{
				A._MarkToDelete = true;
				break;
			}
		}
		_SaveDataAdminsToFile(vAdmins);
		*this = _GetEmptyAdminObject();
		return true;
	}

	static clsAdmins GetAddNewAdminObject(string Id)
	{
		return clsAdmins(enMode::AddMode, Id, "", "", "", "", "", "", 0);
	}

	static vector<clsAdmins> GetAdminsList()
	{
		return _LoadDataAdminsFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (Permission == enPermissions::eAll)
		{
			return true;
		}
		if ((Permission & this->Permissions) == Permission)
		{
			return true;
		}
		return false;
	}
	void RegisterLogineInFile()
	{
		string Line;
		fstream MyFile;
		MyFile.open(LoginFile, ios::out | ios::app);
		if (MyFile.is_open())
		{
			Line = _PrepareRegisterLogin();
			MyFile << Line << endl;
			MyFile.close();
		}
	 }

	static vector<stLogin> GetLoginAdminsList()
	{
		vector<stLogin> vLogins;
		stLogin stLoginRecord;
		string Line;
		fstream MyFile;
		MyFile.open(LoginFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				stLoginRecord = _ConvertLoginRecordLineToObject(Line);
				vLogins.push_back(stLoginRecord);
			}
			MyFile.close();
		}
		return vLogins;

	}

};

