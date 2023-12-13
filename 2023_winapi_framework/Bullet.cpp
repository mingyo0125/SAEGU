#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"
#include "Camera.h"

Bullet::Bullet()
//	: m_fDir(-1.f)
	: m_fTheta(0.f)
	, m_vDir(Vec2(0.f,0.f))
	, m_pTex1(nullptr)
{
	Object::SetName(L"Bullet");
	m_pTex1 = ResMgr::GetInst()->TexLoad(L"Bullet1", L"Texture\\Bullet.bmp");
	
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

	//ELLIPSE_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
	TransparentBlt(_dc
		, (int)(renderPos.x - vScale.x / 2)
		, (int)(renderPos.y - vScale.y / 2)
		, Width, Height, m_pTex1->GetDC()
		, 0, 0, Width,Height, RGB(255,0,255));
	Component_Render(_dc);
}
