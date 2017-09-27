#pragma once

#include <iostream>


class Fileoutput
{
public:
	Fileoutput();
	Fileoutput(std::string filename);
	Fileoutput(long long drawcyclestartv, long long drawcycleendv, long long drawcallstartv, long long drawcallendv);
	~Fileoutput();
	void work();
};

