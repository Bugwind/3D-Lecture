
#include "stdafx.h"
#include <fstream>


class cViewer : public framework::cGameMain
{
public:
	cViewer();
	virtual ~cViewer();

	virtual bool OnInit() override;
	virtual void OnUpdate(const float elapseT) override;
	virtual void OnRender(const float elapseT) override;
	virtual void OnShutdown() override;
	virtual void MessageProc( UINT message, WPARAM wParam, LPARAM lParam) override;


protected:
	bool ReadModelFile( const string &fileName, 
		graphic::cVertexBuffer &vtxBuff, int &vtxSize,  
		graphic::cIndexBuffer &idxBuff, int &faceSize );


private:
	graphic::cVertexBuffer m_vtxBuff;
	graphic::cIndexBuffer m_idxBuff;
	graphic::cMaterial m_mtrl;
	graphic::cLight m_light;
	int m_VtxSize;
	int m_FaceSize;
};

INIT_FRAMEWORK(cViewer);


const int WINSIZE_X = 1024;		//�ʱ� ������ ���� ũ��
const int WINSIZE_Y = 768;	//�ʱ� ������ ���� ũ��
const int WINPOS_X = 0; //�ʱ� ������ ���� ��ġ X
const int WINPOS_Y = 0; //�ʱ� ������ ���� ��ġ Y


// ���ؽ� ����ü
struct Vertex
{
	Vertex() {}
	Vertex(float x0, float y0, float z0) : p(Vector3(x0, y0, z0)), n(Vector3(0,0,0)) {}
	Vector3 p;
	Vector3 n;
	static const DWORD FVF;
};
//���ؽ� ����ü ����.
const DWORD Vertex::FVF  = D3DFVF_XYZ | D3DFVF_NORMAL;


cViewer::cViewer()
{
	m_windowName = L"Viewer";
	const RECT r = {0, 0, 800, 600};
	m_windowRect = r;
}

cViewer::~cViewer()
{
}


bool cViewer::OnInit()
{
	ReadModelFile("vase.dat", m_vtxBuff, m_VtxSize, m_idxBuff, m_FaceSize);

	m_mtrl.InitRed();

	Vector4 color(1,1,1,1);
	m_light.Init( graphic::cLight::LIGHT_DIRECTIONAL, color * 0.4f, color, color * 0.6f, Vector3(1,0,0));

	Matrix44 V;
	Vector3 dir = Vector3(0,0,0)-Vector3(0,0,-5);
	dir.Normalize();
	V.SetView(Vector3(0,0,-500), dir, Vector3(0,1,0));
	graphic::GetDevice()->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&V);

	Matrix44 proj;
	proj.SetProjection(D3DX_PI * 0.5f, (float)WINSIZE_X / (float) WINSIZE_Y, 1.f, 1000.0f) ;
	graphic::GetDevice()->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&proj) ;

	m_light.Bind(0);

	graphic::GetDevice()->LightEnable (
		0, // Ȱ��ȭ/ ��Ȱ��ȭ �Ϸ��� ���� ����Ʈ ���� ���
		true); // true = Ȱ��ȭ �� false = ��Ȱ��ȭ

	return true;
}


void cViewer::OnUpdate(const float elapseT)
{

}


void cViewer::OnRender(const float elapseT)
{
	//ȭ�� û��
	if (SUCCEEDED(graphic::GetDevice()->Clear( 
		0,			//û���� ������ D3DRECT �迭 ����		( ��ü Ŭ���� 0 )
		NULL,		//û���� ������ D3DRECT �迭 ������		( ��ü Ŭ���� NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	//û�ҵ� ���� �÷��� ( D3DCLEAR_TARGET �÷�����, D3DCLEAR_ZBUFFER ���̹���, D3DCLEAR_STENCIL ���ٽǹ���
		D3DCOLOR_XRGB(255, 255, 255),			//�÷����۸� û���ϰ� ä���� ����( 0xAARRGGBB )
		1.0f,				//���̹��۸� û���Ұ� ( 0 ~ 1 0 �� ī�޶󿡼� ���ϰ���� 1 �� ī�޶󿡼� ���� �� )
		0					//���ٽ� ���۸� ä�ﰪ
		)))
	{
		//ȭ�� û�Ұ� ���������� �̷�� ���ٸ�... ������ ����
		graphic::GetDevice()->BeginScene();

		static float y = 0;
		y += elapseT;
		// ������ 2*PI �� �̸��� 0���� �ʱ�ȭ�Ѵ�.
		if (y >= 6.28f)
			y = 0;

		Matrix44 rx, ry, r;
		rx.SetRotationX(MATH_PI/4.f); 	// x������ 45�� ȸ����Ų��.
		ry.SetRotationY(y); // y������ ȸ��
		r = rx*ry;
		graphic::GetDevice()->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);

		m_mtrl.Bind();
		m_idxBuff.Bind();
		m_vtxBuff.Bind();
		graphic::GetDevice()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_VtxSize, 0, m_FaceSize);


		//������ ��
		graphic::GetDevice()->EndScene();
		//�������� �������� �������� ���� ȭ������ ����
		graphic::GetDevice()->Present( NULL, NULL, NULL, NULL );
	}
}


void cViewer::OnShutdown()
{

}


void cViewer::MessageProc( UINT message, WPARAM wParam, LPARAM lParam)
{

}


bool cViewer::ReadModelFile( const string &fileName, graphic::cVertexBuffer &vtxBuff, int &vtxSize,  
	graphic::cIndexBuffer &idxBuff, int &faceSize )
{
	using namespace std;
	ifstream fin(fileName.c_str());
	if (!fin.is_open())
		return false;

	string vtx, vtx_eq;
	int numVertices;
	fin >> vtx >> vtx_eq >> numVertices;

	if (numVertices <= 0)
		return  false;

	vtxSize = numVertices;

	// ���ؽ� ���� ����.
	if (!vtxBuff.Create(vtxSize, sizeof(Vertex), Vertex::FVF))
		return false;

	// ���ؽ� ���� �ʱ�ȭ.
	Vertex* vertices = (Vertex*)vtxBuff.Lock();
	float num1, num2, num3;
	for (int i = 0; i < numVertices; i++)
	{
		fin >> num1 >> num2 >> num3;
		vertices[i] = Vertex(num1, num2, num3);
	}
	vtxBuff.Unlock();


	string idx, idx_eq;
	int numIndices;
	fin >> idx >> idx_eq >> numIndices;

	if (numIndices <= 0)
		return false;

	faceSize = numIndices;

	idxBuff.Create(numIndices);

	WORD *indices = (WORD*)idxBuff.Lock();
	int num4, num5, num6;
	for (int i = 0; i < numIndices*3; i+=3)
	{
		fin >> num4 >> num5 >> num6;
		indices[ i] = num4;
		indices[ i+1] = num5;
		indices[ i+2] = num6;	
	}
	idxBuff.Unlock();

	return true;
}
