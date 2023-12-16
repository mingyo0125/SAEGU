#include "pch.h"
#include "ItemEffecter.h"
#include "TimeMgr.h"
#include "Camera.h"

ItemEffecter::ItemEffecter(Object* p)
	: pObject(p), level_up_speed_value(50), onXEffective(false), xCurT(0), limitTime(2), curMonster(nullptr)
{
	Object::SetName(L"Effecter");
	pObject = p;
}

ItemEffecter::~ItemEffecter()
{
}

void ItemEffecter::EffectToPlayer(Monster* monster)
{
	if (onXEffective) return;
	curMonster = monster;
	pObject->SetSpeed(pObject->GetSpeed() + level_up_speed_value);
	onXEffective = true;
}

void ItemEffecter::Update()
{
	if (onXEffective)
	{
		xCurT += fDT;
		if (xCurT >= limitTime)
		{
			pObject->SetSpeed(pObject->GetSpeed() - level_up_speed_value);
			onXEffective = false;
		}
	}
}

void ItemEffecter::Render(HDC _dc)
{
	if (onXEffective)
	{
		Vec2 vPos = curMonster->GetPos();
		Vec2 renderPos = Camera::GetInst()->GetRenderPos(vPos);
		Vec2 vScale = curMonster->GetScale();

		TextOut(_dc,
			renderPos.x - vScale.x / 2 ,
			renderPos.x - vScale.x / 2 ,
			TEXT("GameOver... "), 12);
	}
}
