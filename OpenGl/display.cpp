#include "display.h"
#include <iostream>
#include <GL/glew.h>
#include <SDL\SDL.h>
#include <GL\glut.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>
#include "windows.h"
#include<glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "camera.h"


//frame counter vars
const int SCREEN_FPS = 30; 
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;



display::display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING); // Initialises everything
	//m_window
	//Set bits per channel
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//Buffer size per pixel based on sizes above
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	// Allocate resources for drawing two windows
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// title converted to a c string, initlisation pos , x/y, width and height, window type
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);
	
	//Initalse glew
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "Glew Failed" << std::endl;
	}
	m_isClosed = false;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	
}


display::~display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit(); // quits everything
}


void display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);

}

bool display::isClosed()
{
	return m_isClosed;
}


void display::fps()
{
	// Fps counter
	static const int fpsSamples = 10;
	static float frameTimes[fpsSamples];
	static int currentframe = 0;
	float fps;
	float maxFps = 30.0f;
	static float prevTicks = SDL_GetTicks();
	float currentTicks = SDL_GetTicks();
	
	float frameTime = currentTicks - prevTicks;
	frameTimes[currentframe % fpsSamples] = frameTime;
	
	//Count here to stop division by 0
	currentframe++;

	prevTicks = currentTicks;
	int count;
	if (currentframe < fpsSamples)
	{
		count = currentframe;
	}
	else
	{
		count = fpsSamples;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;
	
	//divide by 0
	if (frameTimeAverage > 0)
	{
		fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		fps = 30.0f;
	}
	

	static int framecount = 0;
	framecount++;
	if (framecount == 10)
	{
		//std::cout << fps << std::endl;
		framecount = 0;
	}
}


bool mouseDown = false;

glm::vec2 movement;
glm::vec2 newPos;
glm::vec3 rotation = glm::vec3();
glm::vec3 camFront;
SDL_Event e;


void display::Update()
{
	//update function
	SDL_GL_SwapWindow(m_window);
}
	

int display::keypress()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_isClosed = true;
			//return "derp";
		}

		switch (e.key.keysym.sym)
		{

		case SDL_KEYUP:
		{
			return 1;
			//Camera.moveRight();
			//
			break;
		}
		case SDL_KEYDOWN:
		{
			return 2;
			//;
			break;
		}
		case SDLK_LEFT:
		{
			return 3;
			//
			break;
		}
		case SDLK_RIGHT:
		{
			return 4;
			//
			break;
		}
		case SDLK_q:
		{
			return 5;
			//
			break;
		}

		case SDLK_a:
		{
			return 6;
			//
			break;
		}

		case SDLK_w:
		{
			return 7;
			//
			break;

		}
		{
		case SDLK_e:
			return 8;
			//
			break;
		}
		{
		case SDLK_s:
			return 9;
			break;
		}

		{
		case SDLK_x:
			return 10;
			break;
		}

		}
	}
}

	void drawText(float x, float y, void *font, char *string) {
		char *c;
		glRasterPos2f(x, y);

		for (c = string; *c != ' '; c++) {
			glutBitmapCharacter(font, *c);
		}
	}

