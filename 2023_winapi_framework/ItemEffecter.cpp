#include "pch.h"
#include "ItemEffecter.h"
#include "TimeMgr.h"

ItemEffecter::ItemEffecter(Object* p)
	: pObject(p), level_up_speed_value(50), onXEffective(false), xCurT(0), limitTime(2)
{
	Object::SetName(L"Effecter");
	pObject = p;
}

ItemEffecter::~ItemEffecter()
{
}


void ItemEffecter::EffectToPlayer(Object* obj)
{
	if (obj->GetName() == L"XItem" && !onXEffective)
	{
		pObject->SetSpeed(pObject->GetSpeed() + level_up_speed_value);
		onXEffective = true;
	}
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
