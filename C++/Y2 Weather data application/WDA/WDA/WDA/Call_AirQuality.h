#pragma once
#include "Call.h"
class Call_AirQuality : public Call
{
	
public:
	Call_AirQuality(Location _loc);
	string Decode_Param();
};

