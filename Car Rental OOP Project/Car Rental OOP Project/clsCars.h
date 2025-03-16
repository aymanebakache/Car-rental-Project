#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"clsString.h"
#include"Global.h"
#include"clsDate.h"

using namespace std;
class clsCars
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _Name;
	int    _Model;
	string _PlateNum;
	short  _Capacity;
	string _Colour;
	float  _RatePerDay;
	bool _MarkForDelete = false;

	static clsCars _ConvertLineToCarObject(string Line, string Seperator = "#//#")
	{
		vector<string> vLine = clsString::Split(Line, Seperator);
		return clsCars(enMode::UpdateMode, vLine[0], stoi(vLine[1]), vLine[2], stoi(vLine[3]), vLine[4],
			stof(vLine[5]));
	}

	static string _ConvertCarObjectToLine(clsCars Car, string Seperator = "#//#")
	{
		string Line = "";
		Line += Car.Name + Seperator;
		Line += to_string(Car.Model) + Seperator;
		Line += Car.PlateNum() + Seperator;
		Line += to_string(Car.Capacity) + Seperator;
		Line += Car.Colour + Seperator;
		Line += to_string(Car.RatePerDay);
		return Line;
	}

	static vector<clsCars> _LoadDataCarsFromFile()
	{
		vector<clsCars> vCars;
		string Line;
		fstream MyFile;
		MyFile.open(CarsFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCars Car = _ConvertLineToCarObject(Line);
				vCars.push_back(Car);
			}
			MyFile.close();
		}
		return vCars;
	}

	static void _SaveDataCarsToFile(vector<clsCars> vCars)
	{
		string Line;
		fstream MyFile;
		MyFile.open(CarsFile, ios::out);
		if (MyFile.is_open())
		{
			for (clsCars C : vCars)
			{
				if (!C.MarkedToDeleted())
				{
					Line = _ConvertCarObjectToLine(C);
					MyFile << Line << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsCars> vCars = _LoadDataCarsFromFile();
		for (clsCars& C : vCars)
		{
			if (C.PlateNum() == PlateNum())
			{
				C = *this;
			}
		}
		_SaveDataCarsToFile(vCars);
	}

	void _AddNewCar()
	{
		_AddNewLineToFile(_ConvertCarObjectToLine(*this));
	}

	void _AddNewLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open(CarsFile, ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	static clsCars _GetEmptyCarObject()
	{
		return clsCars(enMode::EmptyMode, "", 0 , "", 0, "",0);
	}

public:
	clsCars(enMode Mode, string Name, int Model, string PlateNum, short Capacity, string Colour, float RatePerDay)
	{
		_Mode = Mode;
		_Name = Name;
		_Model = Model;
		_PlateNum = PlateNum;
		_Capacity = Capacity;
		_Colour = Colour;
		_RatePerDay = RatePerDay;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	bool MarkedToDeleted()
	{
		return _MarkForDelete;
	}

	void SetName(string Name)
	{
		_Name = Name;
	}
	string GetName()
	{
		return _Name;
	}
	__declspec(property(get = GetName, put = SetName)) string Name;
	
	void SetModel(int Model)
	{
		_Model = Model;
	}
	int GetModel()
	{
		return _Model;
	}
	__declspec(property(get = GetModel, put = SetModel)) int Model;
	
	string PlateNum()
	{
		return _PlateNum;
	}

	void SetCapacity(short Capacity)
	{
		_Capacity = Capacity;
	}
	short GetCapacity()
	{
		return _Capacity;
	}
	__declspec(property(get = GetCapacity, put = SetCapacity)) short Capacity;
	
	void SetColour(string Colour)
	{
		_Colour = Colour;
	}
	string GetColour()
	{
		return _Colour;
	}
	__declspec(property(get = GetColour, put = SetColour)) string Colour;

	void SetRatePerDay(float RatePerDay)
	{
		_RatePerDay = RatePerDay;
	}
	float GetRatePerDay()
	{
		return _RatePerDay;
	}
	__declspec(property(get = GetRatePerDay, put = SetRatePerDay)) float RatePerDay;

	string CarDetail()
	{
		return Name + " " + to_string(Model) + ":" + _PlateNum;
	}

	static clsCars Find(string PlateNum)
	{
		string Line;
		fstream MyFile;
		MyFile.open(CarsFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCars Car = _ConvertLineToCarObject(Line);
				if (Car.PlateNum() == PlateNum)
				{
					MyFile.close();
					return Car;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCarObject();
	}

	static clsCars Find(string PlateNum,string CarName)
	{
		string Line;
		fstream MyFile;
		MyFile.open(CarsFile, ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCars Car = _ConvertLineToCarObject(Line);
				if (Car.PlateNum() == PlateNum && Car.Name==CarName)
				{
					MyFile.close();
					return Car;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCarObject();
	}

	enum enSaveResults { svFaildEmpty = 0, svSucceeded = 1, svFaildExist = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsCars::EmptyMode:
		{
			return svFaildEmpty;
			break;
		}
		case clsCars::UpdateMode:
		{
			_Update();
			return  enSaveResults::svSucceeded;
			break;
		}
		case clsCars::AddNewMode:
		{
			if (clsCars::IsCarExist(PlateNum()))
			{
				return enSaveResults::svFaildExist;
			}
			else
			{
				_AddNewCar();
				_Mode == enMode::UpdateMode;
				return  enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}

	static bool IsCarExist(string Id)
	{
		clsCars Car = Find(Id);
		return !Car.IsEmpty();
	}

	bool Delete()
	{
		vector<clsCars> vCars = _LoadDataCarsFromFile();
		for (clsCars& C : vCars)
		{
			if (C.PlateNum() == PlateNum())
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveDataCarsToFile(vCars);
		*this = _GetEmptyCarObject();
		return true;
	}

	static clsCars GetAddNewCarObject(string PlateNum)
	{
		return clsCars(enMode::AddNewMode, "", 0, PlateNum, 0, "", 0);
	}

	static vector<clsCars> GetCarsList()
	{
		return _LoadDataCarsFromFile();
	}

	float RentCalculatorOfCar(string StartRentDate, string EndRentDate)
	{
		clsDate Date1 = clsDate(StartRentDate);
		clsDate Date2 = clsDate(EndRentDate);
		int Days = clsDate::GetDifferenceInDays(Date1, Date2, true);
		return this->RatePerDay * Days;
	}
};

