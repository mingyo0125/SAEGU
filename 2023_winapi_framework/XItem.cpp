#include "pch.h"
#include "XItem.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "Scene.h"

XItem::XItem(Vec2 spawnPos)
	:Item(spawnPos)
{
	Object::SetName(L"XItem");
	_spawnPos = spawnPos;

	CreateCollider();
	GetCollider()->SetScale(Vec2(10, 10));
}

XItem::~XItem()
{
}

void XItem::EnterCollision(Collider* _pOther)
{
	Object* collisionObj = _pOther->GetObj();
	if (collisionObj->GetName() == L"Player")
	{
		auto target = SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::DEFAULT);
		for (int i = 0; i < target.size(); i++)
		{
			if (target[i]->GetName() == L"Effecter")
			{
				ItemEffecter* itemEffecter = (ItemEffecter*)target[i];
				itemEffecter->EffectToPlayer(this);
				break;
			}
		}
	}
	EventMgr::GetInst()->DeleteObject(this);
}

void XItem::Render(HDC _dc)
{
	Component_Render(_dc);
	Vec2 renderPos = Camera::GetInst()->GetRenderPos(_spawnPos);

	Texture* i_texture = ResMgr::GetInst()->TexLoad(L"Item", L"Texture\\XItem.bmp");

	int Width = i_texture->GetWidth();
	int Height = i_texture->GetHeight();

	BitBlt(_dc
		, (int)(renderPos.x - renderPos.x / 2)
		, (int)(renderPos.y - renderPos.y / 2)
		, Width, Height, i_texture->GetDC()
		, 0, 0, SRCCOPY);

	Component_Render(_dc);
}
