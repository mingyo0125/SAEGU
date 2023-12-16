#include "pch.h"
#include "GameOver_Scene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "Texture.h"

void GameOver_Scene::Init()
{
}

void GameOver_Scene::Update()
{
	if (KEY_DOWN(KEY_TYPE::ENTER))
	{
		SceneMgr::GetInst()->LoadScene(L"Start_Scene"); 
	}
}

void GameOver_Scene::Render(HDC _dc)
{
	Texture* title_Texture = ResMgr::GetInst()->TexLoad(L"Black", L"Texture\\BlackScreen.bmp");

	int width = title_Texture->GetWidth();
	int height = title_Texture->GetHeight();

	BitBlt(_dc, 0, 0,
		width, height, title_Texture->GetDC(), 0, 0, SRCCOPY);

	SetBkMode(_dc, TRANSPARENT);
	SetTextAlign(_dc, TA_CENTER);
	SetTextColor(_dc, RGB(255, 255, 255));

	TextOut(_dc, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 20,
		TEXT("GameOver... "), 12);

	TextOut(_dc, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
		TEXT("Press Enter to Restart"), 22);
}

void GameOver_Scene::Release()
{
}
