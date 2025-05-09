#pragma once
#include "Call.h"
class Call_Forecast : public Call
{

public:
	Call_Forecast(Location _loc);
	string Decode_Param();
};

