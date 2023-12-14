#include "pch.h"
#include "BatMonster.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"

BatMonster::BatMonster(Object* target, float speed, int hp)
	:Monster(target, speed, hp)
{
	hp = 2;
	m_moveTexture = ResMgr::GetInst()->TexLoad(L"BatEnemyIdle", L"Texture\\FlyEnemyIdle.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnim(L"BatEnemy_Idle", m_moveTexture, Vec2(0, 0), Vec2(120, 100), Vec2(120, 0), 6, 0.1f);
	GetAnimator()->PlayAnim(L"BatEnemy_Idle", true, 999);
	CreateCollider();
}

BatMonster::~BatMonster()
{
}
