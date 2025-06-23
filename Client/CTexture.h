#pragma once
#include "CResource.h"
class CTexture : public CResource
{
private:
	HDC m_dc;
	HBITMAP m_hBit;

public:
	void Load(const wstring& _strFilePath);

public:
	CTexture();
	~CTexture();

};

