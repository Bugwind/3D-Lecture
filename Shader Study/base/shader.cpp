
#include "base.h"
#include "shader.h"


using namespace graphic;


cShader::cShader() :
	m_effect(NULL) 
,	m_hTechnique(NULL)
{
}


cShader::~cShader()
{
	Clear();
}


void cShader::Clear()
{
	SAFE_RELEASE(m_effect);
}


bool cShader::Create(const string &fileName, const string &technique)
{
	// 쉐이더 파일 읽기
	HRESULT hr;
	LPD3DXBUFFER pErr;
	if (FAILED(hr = D3DXCreateEffectFromFileA(GetDevice(), 
		fileName.c_str(), 
		NULL, NULL, D3DXSHADER_DEBUG , NULL, 
		&m_effect, &pErr))) 
	{
			MessageBoxA( NULL, (LPCSTR)pErr->GetBufferPointer(), "ERROR", MB_OK);
			//DXTRACE_ERR( "CreateEffectFromFile", hr );
			return false;
	}

	m_hTechnique = m_effect->GetTechniqueByName( technique.c_str() );

	return true;
}


void cShader::Begin()
{
	RET(!m_effect);

	m_effect->Begin(NULL, 0);
	m_effect->SetTechnique( m_hTechnique );
}


void cShader::BeginPass(int pass)
{
	RET(!m_effect);

	m_effect->BeginPass(pass);
}


void cShader::EndPass()
{
	RET(!m_effect);

	m_effect->EndPass();
}


void cShader::End()
{
	RET(!m_effect);

	m_effect->End();
}


void cShader::SetMatrix(const string &key, const Matrix44 &mat)
{
	RET(!m_effect);
	if (FAILED(m_effect->SetMatrix( key.c_str(), (D3DXMATRIX*)&mat)))
	{
		MessageBoxA( NULL, "cShader::SetMatrix Error", "ERROR", MB_OK);
	}
}
void cShader::SetTexture(const string &key, cTexture &texture)
{
	RET(!m_effect);
	if (FAILED(m_effect->SetTexture( key.c_str(), texture.GetTexture())))
	{
		MessageBoxA( NULL, "cShader::SetTexture Error", "ERROR", MB_OK);
	}
}
void cShader::SetFloat(const string &key, float val)
{
	RET(!m_effect);
	if (FAILED(m_effect->SetFloat( key.c_str(), val)))
	{
		MessageBoxA( NULL, "cShader::SetFloat Error", "ERROR", MB_OK);
	}	
}
void cShader::SetVector(const string &key, const Vector3 &vec )
{
	RET(!m_effect);
	if (FAILED(m_effect->SetVector( key.c_str(), &D3DXVECTOR4(vec.x, vec.y, vec.z, 1.f))))
	{
		MessageBoxA( NULL, "cShader::SetVector Error", "ERROR", MB_OK);
	}	
}

void cShader::CommitChanges()
{
	RET(!m_effect);
	m_effect->CommitChanges();
}
