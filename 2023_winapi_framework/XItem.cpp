#include "pch.h"
#include "XItem.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "EventMgr.h"

Player* player;
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
		player->Speed -= level_up_speed_value;
		onEffective = false;
		EventMgr::GetInst()->DeleteObject(this);
	}
}

void XItem::EnterCollision(Collider* _pOther)
{
	if (onEffective) return;

	const Object* collisionObj = _pOther->GetObj();
	if (collisionObj->GetName() == L"Player")
	{
		UseItem((Player*)collisionObj);
	}
}

void XItem::UseItem(Player* p)
{
	player = p;
	player->Speed += level_up_speed_value;
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
