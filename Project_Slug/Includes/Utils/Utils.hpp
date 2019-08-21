#pragma once

//--------------------------------------------------
// Windows
//--------------------------------------------------
constexpr static size_t s_kWindowWidth	= 1024;
constexpr static size_t s_kWindowHeight	= 768;
constexpr static size_t s_kBoundaryWidth = 288;
constexpr static size_t s_kBoundaryHeight = 216;

//--------------------------------------------------
// Sprites
//--------------------------------------------------
constexpr static size_t s_kSpriteWidth	= 120;
constexpr static size_t s_kSpriteHeight	= 120;
constexpr static size_t s_kTotalAnimSpartan = 4;

//--------------------------------------------------
// Macros
//--------------------------------------------------
#define SDL_CHECK(x) if(x == nullptr) { std::cout << "Error: " << SDL_GetError() << '\n';}

//--------------------------------------------------
// Debug
//--------------------------------------------------
#define DEBUG_POSITION	false
#define DEBUG_CAMERA	true
#define DEBUG_COLLIDER	false
#define DEBUG_WEAPON_SWAP	true

//--------------------------------------------------
// Parameters
//--------------------------------------------------
constexpr static unsigned int s_kMovingSpeed = 300;
constexpr static unsigned int s_kCameraSpeed = 330;

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

	bool IsMoving()
	{
		return m_up || m_down || m_right || m_left;
	}
};

enum class MovingDirection
{
	kUp,
	kDown,
	kRight,
	kLeft
};

enum class AnimationType
{
	kIdle,
	kWalk,
	kAttack,
	kDie
};

/******************************************************

int x = 300;
int y = 300;
int size = 100;

testDest = { x, y, size, size };

m_test[0] = { (testDest.x - size / 2), (testDest.y - size / 2) };
m_test[1] = { (testDest.x - size / 2) + testDest.w, (testDest.y - size / 2) };
m_test[2] = { (testDest.x - size / 2) + testDest.w, (testDest.y - size / 2) + testDest.h };
m_test[3] = { (testDest.x - size / 2), (testDest.y - size / 2) + testDest.h };

SDL_Point Global_Rotate(SDL_Point origin)
{
	const int size = 100;

	SDL_Point transform = { 300, 300 };

	int x = (int)((transform.x) + ((double)origin.y - transform.y) * sin(-sDegree) + ((double)origin.x - transform.x) * cos(sDegree));
	int y = (int)((transform.y) + ((double)origin.y - transform.y) * cos(sDegree) - ((double)origin.x - transform.x) * sin(-sDegree));

	return { x, y };
}

//---- Original ----
// int x = (origin.y * sin(-radian)) + (origin.x * cos(radian0));
// int y = (origin.y * cos(radian))  - (origin.x * sin(-radian));
//int x = (int)((m_transform.GetPositionX()) + ((double)origin.y - m_transform.GetPositionY()) * sin(-degree) + ((double)origin.x - m_transform.GetPositionX()) * cos(degree));
// int y = (int)((m_transform.GetPositionY()) + ((double)origin.y - m_transform.GetPositionY()) * cos(degree) - ((double)origin.x - m_transform.GetPositionX()) * sin(-degree));
//------------------

******************************************************/