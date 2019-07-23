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
