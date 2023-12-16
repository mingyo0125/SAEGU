#include "pch.h"
#include "NosItem.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ItemEffecter.h"

NosItem::NosItem(Vec2 spawnPos)
	:Item(spawnPos)
{
	Object::SetName(L"NosItem");

	_spawnPos = spawnPos;
	i_texture = ResMgr::GetInst()->TexLoad(L"Item", L"Texture\\NosItem.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vec2(10, 10));
}
NosItem::~NosItem()
{

}

void NosItem::EnterCollision(Collider* _pOther)
{
	const Object* collisionObj = _pOther->GetObj();
	if (collisionObj->GetName() == L"Player")
	{
		auto target = SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::DEFAULT);
		for (int i = 0; i < target.size(); i++)
		{
			if (target[i]->GetName() == L"Effecter")
			{
				ItemEffecter* itemEffecter = (ItemEffecter*)target[i];
				itemEffecter->EffectToPlayer();
				break;
			}
		}
		
	}
}

void NosItem::Render(HDC _dc)
{
	Vec2 renderPos = Camera::GetInst()->GetRenderPos(_spawnPos);

	int Width = i_texture->GetWidth();
	int Height = i_texture->GetHeight();

	BitBlt(_dc
		, (int)((renderPos.x - renderPos.x) / 2)
		, (int)((renderPos.y - renderPos.y) / 2)
		, Width, Height, i_texture->GetDC()
		, 0, 0, SRCCOPY);

	Component_Render(_dc);
}
