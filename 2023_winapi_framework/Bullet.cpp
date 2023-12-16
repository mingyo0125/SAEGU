#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"
#include "Camera.h"
#include "Collider.h"
#include "EventMgr.h"

Bullet::Bullet()
//	: m_fDir(-1.f)
	: m_fTheta(0.f)
	, curTime(0.f)
	, m_vDir(Vec2(0.f, 0.f))
	, m_pTex1(nullptr)
	, m_pPenetrateTex(nullptr)
	, isUnDestroyed(false)
{
	m_pTex1 = ResMgr::GetInst()->TexLoad(L"Bullet1", L"Texture\\NormalBullet.bmp");
	m_pPenetrateTex = ResMgr::GetInst()->TexLoad(L"Bullet2", L"Texture\\PenetrateBullet.bmp");
	Object::SetName(L"Bullet");
	CreateCollider();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();
	//vPos.x += 500.f * fDT * m_fDir;
	//vPos.y += 500.f * fDT * m_fDir;
	//vPos.x += 500.f * fDT * cosf(m_fTheta);
	//vPos.y += 500.f * fDT * sinf(m_fTheta);
	vPos.x += 500.f * fDT * m_vDir.x;
	vPos.y += 500.f * fDT * m_vDir.y;
	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex1->GetWidth();
	int Height = m_pTex1->GetHeight();

	Vec2 renderPos = Camera::GetInst()->GetRenderPos(vPos);

	if (isUnDestroyed)
	{
		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2)
			, (int)(renderPos.y - vScale.y / 2)
			, Width, Height, m_pPenetrateTex->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
	}
	else
	{
		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2)
			, (int)(renderPos.y - vScale.y / 2)
			, Width, Height, m_pTex1->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
	}
	//ELLIPSE_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
	
	Component_Render(_dc);
}

void Bullet::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		if (!isUnDestroyed)
		{
			EventMgr::GetInst()->DeleteObject(this);
		}
	}
}

void Bullet::ExitCollision(Collider* _pOther)
{
}

void Bullet::StayCollision(Collider* _pOther)
{
}
