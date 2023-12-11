#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Object.h"
#include "EventMgr.h"
#include "ItemSpawner.h"
#include "KeyMgr.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"

bool m_isDie;
Vec2 m_vCurPos;

Monster::Monster(Object* target, float speed, int hp)
	: m_target(target), m_fSpeed(speed), m_iHp(hp)
{
	Object::SetName(L"Monster");

	m_target = target;
	m_fSpeed = speed;
	m_iHp = hp;
}

Monster::~Monster()
{
}

void Monster::Update()
{
	m_vCurPos = GetPos();
	Vec2 vTargetPos = m_target->GetPos();
	Vec2 moveDir = (vTargetPos - m_vCurPos).Normalize();

	m_vCurPos = m_vCurPos + (moveDir * m_fSpeed);

	SetPos(m_vCurPos);
	GetAnimator()->Update();
}

void Monster::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player") // 레이저 이름 정하면 바꾸기
	{
		SetDie();
	}
}

void Monster::ExitCollision(Collider* _pOther)
{
}

void Monster::StayCollision(Collider* _pOther)
{
}

void Monster::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Monster::SetDie()
{
	m_fSpeed = 0;

	ItemSpawner* itemSpawner = new ItemSpawner();
	itemSpawner->RandomItemSpawn(m_vCurPos);

	EventMgr::GetInst()->DeleteObject(this);
}
