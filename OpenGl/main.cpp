#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "Shader.h"
#include "mesh.h"
#include "transform.h"
#include "GL\glut.h"
#include "Texture.h"
#include "camera.h"
#include <string.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include "main.h"
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include "Fileoutput.h"
#include <vector>
#include <random>
#include <chrono>
#include <map>
#include "nvapi\nvapi.h"
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> 
#include <ratio>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

using namespace std;


//#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
//#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049

int mousex, mousey, oldmousex = 0, oldmousey = 0;
float movethisx = 0, movethisy = 0;
glm::vec2 oldmotionpos;
glm::vec2 newmousepos;
glm::vec2 oldmousepos;
SDL_Event ex;
bool isDown = false;


int hei = GetSystemMetrics(SM_CYSCREEN)-(GetSystemMetrics(SM_CYSCREEN)/3);
int wid = GetSystemMetrics(SM_CXSCREEN) - (GetSystemMetrics(SM_CXSCREEN) / 3);
int width;
int height;

#define WIDTH wid
#define HEIGHT hei

float rnd(float range)
{
	return range * (rand() / double(RAND_MAX));
}

std::mt19937 rndGenerator((unsigned)time(NULL));
std::uniform_real_distribution<float> uniformDist(0.0f, 1.0f);
 float frameTimer;

struct modeldata {
	glm::mat4 model;
	glm::vec3 pos;
	glm::vec3 rotation;
	glm::vec3 scaler;
	float rotationSpeed;
	float rotationDir;
	float Speed;
	float scale;
	float deltaT;
	float stateT = 0;
};


int main(int argc, char** argv)
{


	bool limitfps = false;
	int ttl = 0;
	// Default no of objects
	int numofobj = 512;
	string locstring;
	std::string locfilestring;

	for (int index = 0; index < argc; ++index)
	{
		if (strncmp(argv[index], "-limitfps",9) == 0)
		{
			limitfps = true;
		}
		if (strncmp(argv[index], "-obj", 4) == 0)
		{
			if (index + 1 < argc)
			{
				string objsize = argv[index + 1];
				try
				{
					numofobj = std::stoi(objsize);
				}
				catch (exception ex)
				{
					cout << "Invalid number of objects enterered, default set to 512";
					int numofobj = 512;
				}
			}
		}
		if (strncmp(argv[index], "-output", 7) == 0)
		{

			if (index + 1 < argc)
			{
				string outputfilename = argv[index + 1];
				try
				{		
					#define OUTPUTFILE
					locfilestring = outputfilename;
					
				}
				catch (exception ex)
				{
					cout << "Invalid Filename";
				}
			}
		}

		if (strncmp(argv[index], "-model", 6) == 0)
		{
			if (argv[index + 1] == NULL)
			{
				cout << "No model name supplied";
				return 0;
			}
			if (index + 1 < argc)
			{
				string modelname = argv[index + 1];
				try
				{

					std::ifstream fin("./model/"+modelname);
					if (fin)
					{
					locstring = "./model/" + (string)modelname;
					}
					if (!fin)
					{
						cout << "model not found";
						return 0;
					}
					
				}
				catch (exception ex)
				{
					cout << "Invalid Filename";
				}
			}
		}

		if (strncmp(argv[index], "-ttl", 6) == 0)
		{
#define TTL
			if (argv[index + 1] == NULL)
			{
				cout << "No time supplied";
				return 0;
			}
			if (index + 1 < argc)
			{
				
				try
				{
					int ttl = (int)argv[index + 1];
					#define TIMER

				}
				catch (exception ex)
				{
					cout << "Invalid Time";
				}
			}
		}
		if (strncmp(argv[index], "-man", 4) == 0)
		{
			cout << "List of flags available"<<endl;
			cout << " --- " << endl;
			cout << "-obj <int> = number of objects rendered" << endl;
			cout << "-limitfps = limits the fps to 30" << endl;
			cout << "-output<filename.csv> = logname output" << endl;
			cout << "-model<modename.obj> = loads model listed in the models directory of the program";
			cout << "-ttl<int> = time to live in int value (mins)";
			return 0;
		}
	}

#ifdef TIMER
	chrono::system_clock::time_point now = chrono::system_clock::now();
	chrono::system_clock::time_point end = now;
	end = now + chrono::minutes(ttl);
#endif

	//ofstream myfile("example.csv");

	display display(WIDTH, HEIGHT, "OpenGL");

	
	
	std::vector<Transform>transform;

	std::vector<modeldata>modeldata;
	transform.resize(numofobj);
	modeldata.resize(numofobj);
	for (uint32_t j = 0; j < numofobj; j++)
	{
		float theta = 2.0f * float(M_PI) * uniformDist(rndGenerator);
		float phi = acos(1.0f - 2.0f * uniformDist(rndGenerator));
		modeldata[j].pos = glm::vec3(sin(phi) * cos(theta), 0.0f, cos(phi)) * 35.0f;
		modeldata[j].pos.y=rand() % 10 + 1;
		transform[j].SetPos(modeldata[j].pos) ;
		modeldata[j].Speed = (rand() % 1 + 10);

		modeldata[j].rotation = glm::vec3(0.0f, rnd(360.0f), 0.0f);
		modeldata[j].deltaT = rnd(1.0f);
		modeldata[j].rotationDir = (rnd(100.0f) < 50.0f) ? 1.0f : -1.0f;
		modeldata[j].rotationSpeed = (2.0f + rnd(4.0f)) * modeldata[j].rotationDir;
		modeldata[j].scale = 0.75f + rnd(0.5f);
		modeldata[j].scaler = glm::vec3(modeldata[j].scale, modeldata[j].scale, modeldata[j].scale);
	}


	#ifdef OUTPUTFILE
	Fileoutput(locfilestring.c_str());

	#endif
	Shader shader("./res/basicShader");
	Mesh mesh2(locstring);
	Texture texture("./texture/blank.jpg");
	Camera camera(glm::vec3(0.1, 1.5, -80), 70.0f, (float)WIDTH / (float)HEIGHT, 0.10f, 1000.0f);

	float movethis = -70;
	float counter = 0.0f;
	bool starttimer = false;
	int qcounter = 0;
	long long drawcyclestartv=NULL, drawcycleendv=NULL,drawcallstartv=NULL,drawcallendv=NULL;
	while (!display.isClosed())

	{
#ifdef OUTPUTFILE
		long long der = NULL;
		qcounter++;
		auto drawcycleend = chrono::time_point_cast<chrono::nanoseconds>(chrono::system_clock::now());
		drawcycleendv = drawcycleend.time_since_epoch().count();
		if(starttimer & qcounter == 10)
		{ 
			Fileoutput(drawcyclestartv, drawcycleendv, drawcallstartv, drawcallendv);
			qcounter = 0;
		}
		starttimer = true;
		auto tStart = std::chrono::high_resolution_clock::now();

#endif
#ifdef TTL
		if (now > end)
		{
			return 0;
		}
#endif
		//FPS time measure
		float startTick = SDL_GetTicks();

		display.Clear(0.0f, 0.0f, 0.2f, 0.0f);
		float deltaT = 0;

#ifdef OUTPUTFILE
		auto drawcallstart = chrono::time_point_cast<chrono::nanoseconds>(chrono::system_clock::now());
		drawcallstartv = drawcallstart.time_since_epoch().count();
#endif



		for (int i = 0; i < numofobj; i++)
		{
			shader.Bind();
			modeldata[i].deltaT += 0.15 * frameTimer;

			modeldata[i].pos.y = sin(glm::radians(deltaT * 360.0f)) * modeldata[i].Speed;
			transform[i].GetRot().y += 0.2f*frameTimer;
			transform[i].SetPos(glm::vec3(modeldata[i].pos.x, modeldata[i].pos.y - sin(glm::radians(modeldata[i].deltaT * 360.0f)) * modeldata[i].Speed, modeldata[i].pos.z));
			if (modeldata[i].deltaT > 1.0f)
			{
				modeldata[i].deltaT -= 1.0f;
			}

			if (modeldata[i].pos.y > 100.0f)
			{
				modeldata[i].pos.y -= 100.0f;
			}
			transform[i].SetScale(modeldata[i].scaler);
			
			shader.Update(transform[i], camera);
			//mesh2.Draw();
			mesh2.Draw();
		}
		
#ifdef OUTPUTFILE
		auto drawcallend = chrono::time_point_cast<chrono::nanoseconds>(chrono::system_clock::now());
		drawcallendv = drawcallend.time_since_epoch().count();
#endif
			//display.fps();
			display.Update();

			switch (display.keypress())
			{
			case 1:
				camera.moveUp();
				break;
			case 2:
				camera.moveBack();
				break;
			case 3:
				camera.moveLeft();
				break;
			case 4:
				camera.moveRight();
				break;
			case 5:
				camera.height();
				break;
			case 6:
				camera.heightdown();
				break;
			case 7:
				camera.rotate(0.1f);
				break;
			case 8:
				camera.rotate(-0.1f);
				break;
			case 9:
				camera.rotateUp(0.1f);
				break;
			case 10:
				camera.rotateUp(-0.1f);
				break;
			}

			float frameTick = SDL_GetTicks() - startTick;
			//Limit fps
			if (limitfps)
			{
				if (1000.0f / 30.0f > frameTick)
				{
					SDL_Delay(1000.0f / 30.0f - frameTick);
				}
			}


			auto tEnd = std::chrono::high_resolution_clock::now();
			auto tDiff = std::chrono::duration<double, std::milli>(tEnd - tStart).count();
			frameTimer = tDiff / 1000.0f;
#ifdef OUTPUTFILE
			auto drawcyclestart = chrono::time_point_cast<chrono::nanoseconds>(chrono::system_clock::now());
			drawcyclestartv = drawcyclestart.time_since_epoch().count();
#endif
		}

		
	
	


	return 0;	

}