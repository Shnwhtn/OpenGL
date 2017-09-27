#include "FpsTimer.h"

FpsTimer::FpsTimer(int averageOfFrames) {
	lastFrame = NULL;
	this->averageOfFrames = averageOfFrames;
	lastFrameTimes = new std::deque<float>(averageOfFrames);
	framesToUpdate = averageOfFrames;
	fpsString = new char[15];
}

void FpsTimer::timeFrame() {
	tempTime = clock();

	if (lastFrame != NULL) {
		if (lastFrameTimes->size() >= averageOfFrames) {
			lastFrameTimes->pop_back();
		}
		lastFrameTimes->push_front(tempTime - lastFrame);
	}
	lastFrame = tempTime;
}


char *FpsTimer::getFps() {
	framesToUpdate--;
	if (lastFrameTimes->size() < averageOfFrames) {
		return "Calculating";
	}

	if (framesToUpdate <= 0) {
		averageFps = 0;
		for (int i = 0; i < lastFrameTimes->size(); i++) {
			averageFps += lastFrameTimes->at(i);
		}
		averageFps /= lastFrameTimes->size();
		averageFps = CLOCKS_PER_SEC / averageFps;
		sprintf(fpsString, "%4.2f FPS", averageFps);
		framesToUpdate = averageOfFrames;
	}
	return fpsString;
}

Printing the FPS on screen
The final step is to print the fps on screen using the following call and function:

drawText(0.2f, 0.5, GLUT_BITMAP_HELVETICA_18, fpsTimer->getFps());

void drawText(float x, float y, void *font, char *string) {
	char *c;
	glRasterPos2f(x, y);

	for (c = string; *c != ''; c++) {
		glutBitmapCharacter(font, *c);
	}
}