#include "pch.h"
#include "NosItem.h"
#include "ResMgr.h"
#include "Texture.h"

NosItem::NosItem(Vec2 spawnPos)
	:Item(spawnPos)
{
	_spawnPos = spawnPos;

}
NosItem::~NosItem()
{

}

void NosItem::EnterCollision(Collider* _pOther)
{
	UseItem();
}

void NosItem::UseItem()
{
}

void NosItem::Render(HDC _dc)
{
	Texture* i_texture = ResMgr::GetInst()->TexLoad(L"Item", L"Texture\\NosItem.bmp");

	int Width = i_texture->GetWidth();
	int Height = i_texture->GetHeight();

	BitBlt(_dc
		, (int)(_spawnPos.x - _spawnPos.x / 2)
		, (int)(_spawnPos.y - _spawnPos.y / 2)
		, Width, Height, i_texture->GetDC()
		, 0, 0, SRCCOPY);
}
