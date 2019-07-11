#pragma once

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 385

#define MAX_COMPONENTS 32


#define SDL_CHECK(x) if(x == nullptr) { std::cout << "Error: " << SDL_GetError() << '\n';}

struct Vector2
{
	float m_x;
	float m_y;
};