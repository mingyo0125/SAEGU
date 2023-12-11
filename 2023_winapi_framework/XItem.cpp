#include "pch.h"
#include "XItem.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "EventMgr.h"

Object* player;
float curT;
float level_up_speed_value = 50;
float onEffectTime = 2;
bool onEffective;

XItem::XItem(Vec2 spawnPos)
	:Item(spawnPos)
{
	_spawnPos = spawnPos;

}
XItem::~XItem()
{
}

void XItem::Update()
{
	if (!onEffective) return;

	curT += fDT;
	if (curT > onEffectTime)
	{
		player->SetSpeed(player->GetSpeed() - level_up_speed_value);
		onEffective = false;
		EventMgr::GetInst()->DeleteObject(this);
	}
}

void XItem::EnterCollision(Collider* _pOther)
{
	if (onEffective) return;

	Object* collisionObj = _pOther->GetObj();
	if (collisionObj->GetName() == L"Player")
	{
		UseItem(collisionObj);
	}
}

void XItem::UseItem(Object* p)
{
	player = p;
	p->SetSpeed(p->GetSpeed() + level_up_speed_value);
}

void XItem::Render(HDC _dc)
{
	if (onEffective) return;

	Texture* i_texture = ResMgr::GetInst()->TexLoad(L"Item", L"Texture\\XItem.bmp");

	int Width = i_texture->GetWidth();
	int Height = i_texture->GetHeight();

	BitBlt(_dc
		, (int)(_spawnPos.x - _spawnPos.x / 2)
		, (int)(_spawnPos.y - _spawnPos.y / 2)
		, Width, Height, i_texture->GetDC()
		, 0, 0, SRCCOPY);
}
