#include "Main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameManager gameManager;

	gameManager.Initialize();
	gameManager.Run();
	gameManager.Finalize();

	return 0; 
}