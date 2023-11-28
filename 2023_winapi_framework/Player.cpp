#include "pch.h"
#include "Core.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "EventMgr.h"
Player::Player()
	: m_pTex(nullptr)
	, m_pTex2(nullptr)
	, Hp(0)
	, MaxHp(10)
	, isKeyPressing(false)
{
	//m_pTex = new Texture;
	//wstring strFilePath = PathMgr::GetInst()->GetResPath();
	//strFilePath += L"Texture\\plane.bmp";
	//m_pTex->Load(strFilePath);

	m_pTex = ResMgr::GetInst()->TexLoad(L"PlayerRight", L"Texture\\hero_walk.bmp");
	m_pTex2 = ResMgr::GetInst()->TexLoad(L"PlayerLeft", L"Texture\\hero_walk2.bmp");
	m_pTexIdle = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\hero_walk_12.bmp");
	
	Hp = &MaxHp; //Hp �ʱ�ȭ
	isKeyPressing = false;
	

	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	// ������ �� 20�� �ФФ� ������;�ӳ���;������
	CreateAnimator(); 
	GetAnimator()->CreateAnim(L"Player_Right", m_pTex, Vec2(0.f, 0.f),
		Vec2(128.f, 125.f), Vec2(128.f, 0.f), 11, 0.1f);
	GetAnimator()->CreateAnim(L"Player_Left", m_pTex2, Vec2(0.f, 0.f),
		Vec2(128.f, 125.f), Vec2(127.f, 0.f), 11, 0.1f);
	//GetAnimator()->PlayAnim(L"Player_Front",true);

	/*CreateAnimator();
	GetAnimator()->CreateAnim(L"Jiwoo_Front", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);*/

	//// ������ �ǵ帮��
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// �ϳ���
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// ������ �� 
	//for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->SetFrameOffset(i, Vec2(0.f, 20.f));
}
Player::~Player()
{ 
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	Vec2 vPos = GetPos();

	if (KEY_PRESS(KEY_TYPE::A))
	{
		vPos.x -= 100.f * fDT;
		GetAnimator()->PlayAnim(L"Player_Left", false);
		isKeyPressing = true;
	}
	if (KEY_PRESS(KEY_TYPE::D))
	{
		vPos.x += 100.f * fDT;
		GetAnimator()->PlayAnim(L"Player_Right", false);
		isKeyPressing = true;
	}
	if (KEY_PRESS(KEY_TYPE::W))
	{
		vPos.y -= 100.f * fDT;
		if (KEY_PRESS(KEY_TYPE::A))
		{
			GetAnimator()->PlayAnim(L"Player_Left", false);
		}
		else
		{
			GetAnimator()->PlayAnim(L"Player_Right", false);
		}
		isKeyPressing = true;
	}
	if (KEY_PRESS(KEY_TYPE::S))
	{
		vPos.y += 100.f * fDT;
		if (KEY_PRESS(KEY_TYPE::A))
		{
			GetAnimator()->PlayAnim(L"Player_Left", false);
		}
		else
		{
			GetAnimator()->PlayAnim(L"Player_Right", false);
		}
		isKeyPressing = true;
	}
	if (KEY_DOWN(KEY_TYPE::LBUTTON))
	{
		CreateBullet();
		//ResMgr::GetInst()->Play(L"Shoot");
	}
	else
	{
		isKeyPressing = false;
	}
	if(KEY_PRESS(KEY_TYPE::CTRL))
		GetAnimator()->PlayAnim(L"Jiwoo_Attack", false, 1);
	SetPos(vPos);
	GetAnimator()->Update();
}

void Player::CreateBullet()
{
	Bullet* pBullet = new Bullet;
	Vec2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 5.f;

	POINT pMousePos = KeyMgr::GetInst()->GetMousePos();

	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f,25.f));
//	pBullet->SetDir(M_PI / 4 * 7);
//	pBullet->SetDir(120* M_PI / 180);
	//pBullet->SetDir(Vec2(10.f,15.f));
	pBullet->SetDir((Vec2((float)pMousePos.x, (float)pMousePos.y)) - vBulletPos);
	pBullet->SetName(L"Player_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}

void Player::Render(HDC _dc)
{
	if (!isKeyPressing)
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		int Width = m_pTexIdle->GetWidth();
		int Height = m_pTexIdle->GetHeight();
		// 1. �⺻ �ű��
		BitBlt(_dc
			, (int)(vPos.x - vScale.x / 2) - 11
			, (int)(vPos.y - vScale.y / 2) - 11
			, Width, Height, m_pTexIdle->GetDC()
			, 0, 0, SRCCOPY);
	}
	
	//// 2. ���� �Ⱦ��
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,0,255));

	//// 3. Ȯ�� �� ���
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width ,Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, SRCCOPY);

	// 4. ȸ��
	// �ﰢ�Լ�, ȸ�����
	//Plgblt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, RGB(255, 0, 255));
	Component_Render(_dc);
}

void Player::MinusHp(int damage)
{
	*Hp -= damage;
	if (*Hp >= 0)
	{
		Die();
	}
}

void Player::Die()
{
	//������ �Ұ͵�.
	EventMgr::GetInst()->DeleteObject(this);
}
