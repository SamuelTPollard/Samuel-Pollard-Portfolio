#pragma once
#include "Call.h"
class Call_Historical : public Call
{

public:
	Call_Historical(Location _loc);
	string Decode_Param();
};

