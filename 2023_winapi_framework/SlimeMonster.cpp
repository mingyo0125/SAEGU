#include "pch.h"
#include "SlimeMonster.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"

SlimeMonster::SlimeMonster(Object* target, float speed, int hp)
	:Monster(target, speed, hp)
{
	hp = 1;
	m_moveTexture = ResMgr::GetInst()->TexLoad(L"SlimeEnemyIdle", L"Texture\\Slime_Idle.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnim(L"SlimeEnemy_Idle", m_moveTexture, Vec2(0, 0), Vec2(44, 30), Vec2(44, 0), 9, 0.1f);
	GetAnimator()->PlayAnim(L"SlimeEnemy_Idle", true, 999);
	CreateCollider();
}

SlimeMonster::~SlimeMonster()
{
}
