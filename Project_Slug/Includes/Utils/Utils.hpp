#pragma once

//--------------------------------------------------
// Windows
//--------------------------------------------------
constexpr static size_t WINDOW_WIDTH	= 1280;
constexpr static size_t WINDOW_HEIGHT	= 720;

//--------------------------------------------------
// Sprites
//--------------------------------------------------
constexpr static size_t SPRITE_WIDTH	= 148;
constexpr static size_t SPRITE_HEIGHT	= 148;

//--------------------------------------------------
// Macros
//--------------------------------------------------
#define SDL_CHECK(x) if(x == nullptr) { std::cout << "Error: " << SDL_GetError() << '\n';}

//--------------------------------------------------
// Parameters
//--------------------------------------------------
constexpr static unsigned int kMovingSpeed = 500;

//--------------------------------------------------
// Object related
//--------------------------------------------------
struct Vector2
{
	float m_x;
	float m_y;
};

struct Movement
{
	bool m_up = false;
	bool m_down = false;
	bool m_right = false;
	bool m_left = false;
};

enum class MovingDirection
{
	kUp,
	kDown,
	kRight,
	kLeft
};
