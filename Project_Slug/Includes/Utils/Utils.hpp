#pragma once

//--------------------------------------------------
// Windows
//--------------------------------------------------
constexpr static size_t kWindowWidth	= 1024;
constexpr static size_t kWindowHeight	= 768;
constexpr static size_t kBoundaryWidth	= 384;
constexpr static size_t kBoundaryHeight = 288;

//--------------------------------------------------
// Sprites
//--------------------------------------------------
constexpr static size_t SPRITE_WIDTH	= 72;
constexpr static size_t SPRITE_HEIGHT	= 72;

//--------------------------------------------------
// Macros
//--------------------------------------------------
#define SDL_CHECK(x) if(x == nullptr) { std::cout << "Error: " << SDL_GetError() << '\n';}

//--------------------------------------------------
// Parameters
//--------------------------------------------------
constexpr static unsigned int kMovingSpeed = 300;

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
