#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL/SDL.h> // Include SDL Functions
#include <string>
#include <GL/glew.h>
#include<glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>


class display
{
public:
	// Takes width,height and title from constructor
	display(int width, int height, const std::string& title);
	void drawText(float x, float y, void *font, char *string);
	void Clear(float r, float g, float b, float a);
	void fps();
	int keypress();
	//glm::vec2 updateCameraPosxy();
	//bool isMouseDown();
	// red, green, blue, alpha
	void Update(); // update function, controls to see if the window is closed and double buffering
	bool isClosed(); // method to see if the window is closed
	virtual ~display();

protected:
private:
	display(const display& other) {}
	void operator =(const display& other) {}

	SDL_Window* m_window; // SDL window stored as a pointer
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

#endif // DISPLAY_H

