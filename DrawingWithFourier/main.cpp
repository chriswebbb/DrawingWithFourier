 //O------------------------------------------------------------------------------O
 //| Example "Hello World" Program (main.cpp)                                     |
 //O------------------------------------------------------------------------------O

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <math.h>
#include <vector>
#include <time.h>

#define NUMOFCIRCLES 100000
#define PI 3.1415
#define SCALE 100

//#define 

 //Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
private:

	struct circle 
	{
		float radius = 0.0f;
		std::pair<float, float> centre = { 0.0f,0.0f };
		float theta = 0.0f;
		float period = 0.0f;
	};

	std::vector<circle> Circles;
	std::vector<float>  Graph;

	float fMouseLoc[2];
	bool bMousePress = false;
	int count = 0;

public:
	Example()
	{
		 //Name you application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		 //Called once at the start, so create things here

		srand(time(NULL));

		std::pair<float, float> pC = { 0.0f,0.0f };
		circle c;

		c.centre = { 1280/4, 720/2 };
		c.radius = 0;
		c.theta = (rand() % 360) * (3.1415 / 180);
		c.period = (rand() % 50)/2 + 1;
		Circles.push_back(c);

		//for (int i = 1; i < NUMOFCIRCLES+1; i++) 
		//{
		//	c.centre = { Circles[i].centre.first + Circles[i].radius * cos(Circles[i].theta), Circles[i].centre.second + Circles[i].radius * sin(Circles[i].theta) };
		//	c.radius = (4.0f * PI * SCALE * pow(-1, i - 1)) / (PI * PI * (2.0f * i - 1.0f) * (2.0f * i - 1.0f));
		//	//std::cout << c.radius << std::endl;
		//	c.theta = 0.0f;
		//	c.period = 1.0f / (2.0f * i - 1.0f);
		//	Circles.push_back(c);
		//}


		for (int i = 1; i < NUMOFCIRCLES + 1; i++)
		{
			c.centre = { Circles[i].centre.first + Circles[i].radius * cos(Circles[i].theta), Circles[i].centre.second + Circles[i].radius * sin(Circles[i].theta) };
			c.radius = (4.0f / PI) * SCALE * 1/(2 * i - 1.0f);
			//std::cout << c.radius << std::endl;
			c.theta = 0.0f;
			c.period = 1.0f / (PI * (2*i - 1.0f));
			Circles.push_back(c);
		}


		//for (int i = 1; i < NUMOFCIRCLES + 1; i++) {
		//	c.centre = { 1280 / 4, 720 / 2 };
		//	c.radius = (float)(((rand() % 20) + 1) * 5);
		//	c.theta = (rand() % 360) * (3.1415 / 180);
		//	c.period = (rand() % 50) / 2 + 1;
		//	Circles.push_back(c);
		//}

		//for (int i = 0; i < NUMOFCIRCLES -1; i++)
		//{
		//	c.centre = { Circles[i].centre.first + Circles[i].radius * cos(Circles[i].theta), Circles[i].centre.second + Circles[i].radius * sin(Circles[i].theta) };
		//	c.radius = (float)(((rand() % 20) + 1) * 5);
		//	c.theta = (rand() % 360) * (3.1415 / 180);
		//	c.period = (rand() % 9) + 1;
		//	Circles.push_back(c);
		//}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetMouse(0).bPressed) {
			fMouseLoc[0] = GetMouseX();
			fMouseLoc[1] = GetMouseY();
			bMousePress = true;
		}

		if (GetMouse(1).bPressed) bMousePress = false;

		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);
		//if (bMousePress) {
		//	DrawLine(fMouseLoc[0], fMouseLoc[1], GetMouseX(), GetMouseY(), olc::RED);
		//	DrawCircle(fMouseLoc[0], fMouseLoc[1], sqrt((GetMouseX() - fMouseLoc[0]) * (GetMouseX() - fMouseLoc[0]) + (GetMouseY() - fMouseLoc[1]) * (GetMouseY() - fMouseLoc[1])), olc::RED);
		//}

		//Update the centres of the circles
		for (int j = 0; j < NUMOFCIRCLES-1; j++) 
		{
			Circles[j + 1].centre.first = Circles[j].centre.first + (Circles[j].radius * cos(Circles[j].theta + (0.009f / Circles[j].period) * count));
			Circles[j + 1].centre.second = Circles[j].centre.second + (Circles[j].radius * sin(Circles[j].theta + (0.009f / Circles[j].period) * count));
		}

		for (int k = 0; k < Graph.size(); k++) 
		{
			DrawCircle(k+1280/2, Graph[k], 0, olc::WHITE);
		}

		//Draw said circles
		for (int i = 0; i < NUMOFCIRCLES; i++) 
		{
			DrawCircle(Circles[i].centre.first, Circles[i].centre.second, abs(Circles[i].radius), olc::RED);
			DrawLine(Circles[i].centre.first, Circles[i].centre.second, Circles[i].centre.first + (Circles[i].radius * cos(Circles[i].theta + (0.009f / Circles[i].period) * count)), Circles[i].centre.second + (Circles[i].radius * sin(Circles[i].theta + (0.009f / Circles[i].period) * count)), olc::BLUE);
		}
		
		Graph.insert(Graph.begin(), Circles[NUMOFCIRCLES-1].centre.second + (Circles[NUMOFCIRCLES - 1].radius * sin(Circles[NUMOFCIRCLES - 1].theta + (0.009f / Circles[NUMOFCIRCLES - 1].period) * count)));

		//Draw line

		DrawLine(Circles[NUMOFCIRCLES - 1].centre.first + (Circles[NUMOFCIRCLES - 1].radius * cos(Circles[NUMOFCIRCLES - 1].theta + (0.009f / Circles[NUMOFCIRCLES - 1].period) * count)), Circles[NUMOFCIRCLES - 1].centre.second + (Circles[NUMOFCIRCLES - 1].radius * sin(Circles[NUMOFCIRCLES - 1].theta + (0.009f / Circles[NUMOFCIRCLES - 1].period) * count)), 1280 / 2, Graph[0], olc::BLUE);

		for (int w = 0; w < Graph.size() - 1; w++) 
		{
			DrawLine(w + 1280/2, Graph[w], w + 1 + 1280/2, Graph[w + 1]);
		}

		if (Graph.size() > 1280 / 2) 
		{
			Graph.pop_back();
		}
		
		count++;

		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(1400, 720, 1, 1))
		demo.Start();
	return 0;
}