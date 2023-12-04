#include "pch.h"
#include "XItem.h"
#include "ResMgr.h"
#include "Texture.h"

XItem::XItem(Vec2 spawnPos)
	:Item(spawnPos)
{
	_spawnPos = spawnPos;

}
XItem::~XItem()
{

}

void XItem::EnterCollision(Collider* _pOther)
{
	UseItem();
}

void XItem::UseItem()
{
}

void XItem::Render(HDC _dc)
{
	Texture* i_texture = ResMgr::GetInst()->TexLoad(L"Item", L"Texture\\XItem.bmp");

	int Width = i_texture->GetWidth();
	int Height = i_texture->GetHeight();

	BitBlt(_dc
		, (int)(_spawnPos.x - _spawnPos.x / 2)
		, (int)(_spawnPos.y - _spawnPos.y / 2)
		, Width, Height, i_texture->GetDC()
		, 0, 0, SRCCOPY);
}
