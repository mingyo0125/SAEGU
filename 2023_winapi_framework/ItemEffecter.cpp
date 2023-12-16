#include "pch.h"
#include "ItemEffecter.h"
#include "TimeMgr.h"
#include "Camera.h"

ItemEffecter::ItemEffecter(Object* p)
	: pObject(p), level_up_speed_value(50), onXEffective(false), xCurT(0), limitTime(2)
{
	Object::SetName(L"Effecter");
	pObject = p;
}

ItemEffecter::~ItemEffecter()
{
}

void ItemEffecter::EffectToPlayer()
{
	if (onXEffective) return;
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
			MessageBox(NULL, L"Your debugging message here", L"Debug Info", MB_OK | MB_ICONINFORMATION);
			pObject->SetSpeed(pObject->GetSpeed() - level_up_speed_value);
			onXEffective = false;
		}
	}
}
