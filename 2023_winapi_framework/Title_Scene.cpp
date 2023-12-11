#include "pch.h"
#include "Title_Scene.h"
#include "ResMgr.h"
#include "Texture.h"

void Title_Scene::Init()
{
}

void Title_Scene::Update()
{
}

void Title_Scene::Render(HDC _dc)
{
	Texture* title_Texture = ResMgr::GetInst()->TexLoad(L"Title", L"Texture\\Title.bmp");

	int width = title_Texture->GetWidth();
	int height = title_Texture->GetHeight();

	BitBlt(_dc, 0, 0,
		   width, height, title_Texture->GetDC(), 0, 0, SRCCOPY);
}

void Title_Scene::Release()
{
}
