#include "pch.h"
#include "ExplosionEffect.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"

ExpEffect::ExpEffect()
{
	Texture* mytex = ResMgr::GetInst()->TexLoad(L"EXP", L"Texture\\exp.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnim(L"Explosion", mytex, Vec2(0, 0), Vec2(64, 64), Vec2(64, 0), 8, 0.1f);
	GetAnimator()->PlayAnim(L"Explosion", false, 1);
	CreateCollider();
}

ExpEffect::~ExpEffect()
{
}

void ExpEffect::Update()
{
	GetAnimator()->Update();
}
