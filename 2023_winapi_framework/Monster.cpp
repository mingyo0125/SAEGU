#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Object.h"
#include "EventMgr.h"

Monster::Monster(Object* target, float speed, int hp) 
	: m_target(target), m_fSpeed(speed), m_iHp(hp)
{
	m_target = target;
	m_fSpeed = speed;
	m_iHp = hp;

	CreateCollider();
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vec2 vCurPos = GetPos();
	Vec2 vTargetPos = m_target->GetPos();
	Vec2 moveDir = (vTargetPos - vCurPos).Normalize();

	vCurPos = vCurPos + (moveDir * m_fSpeed);

	SetPos(vCurPos);
}

void Monster::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player_Bullet")
	{
		// 昏力贸府秦林搁蹬.
		m_iHp--;
		if(m_iHp<=0)
			EventMgr::GetInst()->DeleteObject(this);
	}
}

void Monster::ExitCollision(Collider* _pOther)
{
}

void Monster::StayCollision(Collider* _pOther)
{
}
