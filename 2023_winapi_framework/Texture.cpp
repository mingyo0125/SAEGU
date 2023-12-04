#include "pch.h"
#include "Texture.h"
#include "Core.h"
#include<assert.h>
Texture::Texture()
	: m_hBit(0)
	, m_hDC(0)
	, m_bitInfo{}
{
}

Texture::~Texture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

void Texture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (m_hBit == NULL)
	{
		MessageBox(nullptr, L"Failed to load image", L"Error", MB_OK | MB_ICONERROR);
	}
	assert(m_hBit);
	m_hDC = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(m_hDC, m_hBit);
	GetObject(m_hBit, sizeof(BITMAP),&m_bitInfo);
}
