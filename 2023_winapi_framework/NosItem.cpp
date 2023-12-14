#include "pch.h"
#include "NosItem.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "Camera.h"

NosItem::NosItem(Vec2 spawnPos)
	:Item(spawnPos)
{
	_spawnPos = spawnPos;
	i_texture = ResMgr::GetInst()->TexLoad(L"Item", L"Texture\\NosItem.bmp");


}
NosItem::~NosItem()
{

}

void NosItem::EnterCollision(Collider* _pOther)
{
	const Object* collisionObj = _pOther->GetObj();
	if (collisionObj->GetName() == L"Player")
	{
		UseItem((Player*)collisionObj);
	}
}

void NosItem::UseItem(Object* p)
{
}

void NosItem::Render(HDC _dc)
{
	Vec2 renderPos = Camera::GetInst()->GetRenderPos(_spawnPos);

	int Width = i_texture->GetWidth();
	int Height = i_texture->GetHeight();

	BitBlt(_dc
		, (int)(renderPos.x - renderPos.x / 2)
		, (int)(renderPos.y - renderPos.y / 2)
		, Width, Height, i_texture->GetDC()
		, 0, 0, SRCCOPY);
}
