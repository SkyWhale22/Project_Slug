#define GameTest true

#if GameTest
#include <iostream>
#include <Core/Application.hpp>
#include <Core/Singleton.hpp>
#include <Windows.h>
#include <vld.h>

int main(int argc, char* argv[])
{
	Slug::Core::Application* pGame = Slug::Core::Application::GetInstance();

	pGame->AfterInit();

	while (pGame->IsPlaying())
	{
		pGame->Update();
	}

	return 0;
}

#else

#include <iostream>
#include <string>

std::string TestFunc()
{
	return "test";
}

int main()
{
	std::string str = TestFunc();
	std::cout << str << std::endl;
	
	const char* cstr = str.data();
	std::cout << cstr << std::endl;

	return 0;
}

#endif
