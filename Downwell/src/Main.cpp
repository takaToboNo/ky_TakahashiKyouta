#include "Main.h"

//‰¼
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SceneManager* pSceneManager = new SceneManager();

	pSceneManager->Initialize();
	
	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{
		assert(ClearDrawScreen() == 0);
		pSceneManager->Update();

		pSceneManager->Draw();
		assert(ScreenFlip() == 0);
	}

	pSceneManager->Finalize();

	return 0; 
}