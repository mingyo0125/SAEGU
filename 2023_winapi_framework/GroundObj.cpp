#include "pch.h"
#include "GroundObj.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "Camera.h"

GroundObj::GroundObj(Vec2 pos)
{
	myPos = pos;
}

GroundObj::~GroundObj()
{

}

void GroundObj::Render(HDC _dc)
{
	Vec2 renderPos = Camera::GetInst()->GetRenderPos(myPos);

	Texture* i_texture = ResMgr::GetInst()->TexLoad(L"Ground", L"Texture\\Ground.bmp");

	int Width = i_texture->GetWidth();
	int Height = i_texture->GetHeight();

	BitBlt(_dc
		, (int)(renderPos.x - renderPos.x / 2)
		, (int)(renderPos.y - renderPos.y / 2)
		, Width, Height, i_texture->GetDC()
		, 0, 0, SRCCOPY);
}
