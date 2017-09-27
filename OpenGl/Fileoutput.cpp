#include "Fileoutput.h"
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <sstream>
#include <string>
#include <string.h>

using namespace std;

static string filenamevar;
Fileoutput::Fileoutput()
{

}

Fileoutput::Fileoutput(std::string filename)
{

	filenamevar = filename;
	//Create file
	ofstream myfile(filename);
	ifstream inputfile;
	inputfile.open(filename);
	string title = "Cycle Start, Cycle End, Duration, Draw Call Start, Draw Call End, Duration ";
	//inputfile << std::derp;

	ofstream outputfile;
	outputfile.open(filename);
	outputfile << title.c_str()<<endl;
}

Fileoutput::Fileoutput(long long drawcyclestartv, long long drawcycleendv, long long drawcallstartv, long long drawcallendv)
{
	long long dura, durb;
	dura = drawcallendv-drawcallstartv;
	durb = drawcycleendv-drawcyclestartv;

	std::stringstream entry;
	entry << drawcallstartv << "," << drawcycleendv << "," << durb << "," << drawcallstartv << "," << drawcallendv << "," << dura<<endl;
	ofstream file;
	file.open(filenamevar, ios::out | ios::app | ios::binary);
	file << entry.str();

}

Fileoutput::~Fileoutput()
{
}

void Fileoutput::work() {
	

}