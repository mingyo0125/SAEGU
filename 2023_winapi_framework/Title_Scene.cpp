#include "pch.h"
#include "Title_Scene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "SelectGDI.h"

void Title_Scene::Init()
{
	ResMgr::GetInst()->AddFont(L"neodgm");
	ResMgr::GetInst()->LoadSound(L"TITLEBGM", L"Sound\\GameTitle.wav", true);
	ResMgr::GetInst()->Play(L"TITLEBGM");
}

void Title_Scene::Update()
{
	if (KEY_DOWN(KEY_TYPE::ENTER))
	{
		SceneMgr::GetInst()->LoadScene(L"Start_Scene");
	}
}

void Title_Scene::Render(HDC _dc)
{
	Texture* title_Texture = ResMgr::GetInst()->TexLoad(L"Title", L"Texture\\Title.bmp");

	int width = title_Texture->GetWidth();
	int height = title_Texture->GetHeight();

	BitBlt(_dc, 0, 0,
		   width, height, title_Texture->GetDC(), 0, 0, SRCCOPY);

	/*AddFontResource(L"강원교육새음");
	SelectObject(_dc )*/

	HFONT myFont = ResMgr::GetInst()->LoadFont(L"neodgm", 40);
	SelectGDI gdi(_dc, myFont);
	
	SetBkMode(_dc, TRANSPARENT);
	SetTextAlign(_dc, TA_CENTER);
	SetTextColor(_dc, RGB(255, 255, 255));

	TextOut(_dc, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
			TEXT("PRESS ENTER TO START"), 20);
}

void Title_Scene::Release()
{
}
