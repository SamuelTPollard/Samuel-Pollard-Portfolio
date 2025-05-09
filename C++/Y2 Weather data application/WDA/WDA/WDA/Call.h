#pragma once
#include "Location.h"

class Call
{
private:
	string source = "", presource = "";
	Location loc;

public:
	Call();
	Call(Location _loc);
	void Make();
	Location GetLoc(string locname);
	virtual string Decode_Param();
	void SetLocation(Location _loc);
	void SetSource(string _source, string _presource);
	void ChooseParams(string& params, string tail, string name, vector<string> paramsvec);
	void TimeType(string& params);
	void Forecastlength(string& params);
	void TimeInterval(string& params);
};

bool ValidDate(string date);
bool DateAfter(string sdate, string edate);
vector<int> SplitDate(string date);

