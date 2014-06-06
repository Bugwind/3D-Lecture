
#include "stdafx.h"


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

private:
	graphic::cLight m_light;

	graphic::cVertexBuffer m_vtxBuff;
	graphic::cIndexBuffer m_idxBuff;
	graphic::cMaterial m_mtrl;
	graphic::cTexture m_texture;

	graphic::cModel m_model;
	

	string m_filePath;

	POINT m_curPos;
	bool m_LButtonDown;
	Matrix44 g_rotateTm;

	Vector3 m_camPos;
	Vector3 m_lookAtPos;
};

INIT_FRAMEWORK(cViewer);



// ���ؽ� ����ü
struct Vertex
{
	Vertex() {}
	Vertex(float x0, float y0, float z0) : p(Vector3(x0, y0, z0)), n(Vector3(0,0,0))
		,u(-100), v(-100)
	{}
	Vector3 p;
	Vector3 n;
	float u,v;
	static const DWORD FVF;
};
//���ؽ� ����ü ����.
const DWORD Vertex::FVF  = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;


cViewer::cViewer()
{
	m_windowName = L"Viewer";
	const RECT r = {0, 0, 800, 600};
	m_windowRect = r;
	m_LButtonDown = false;
}

cViewer::~cViewer()
{
}


bool cViewer::OnInit()
{
	DragAcceptFiles(m_hWnd, TRUE);

	//ReadModelFile("../media/cube.dat", m_vtxBuff, m_idxBuff, m_texture);
	m_filePath = "../media/data.dat";
	m_model.Create( m_filePath );

	m_mtrl.InitWhite();

	Vector4 color(1,1,1,1);
	m_light.Init( graphic::cLight::LIGHT_DIRECTIONAL, color * 0.4f, color, color * 0.6f, Vector3(0,-1,0));
	m_light.Bind(0);


	Matrix44 V;
	m_camPos = Vector3(0,0,-500);
	m_lookAtPos = Vector3(0,0,0);
	Vector3 dir = m_lookAtPos - m_camPos;
	dir.Normalize();
	V.SetView(m_camPos, dir, Vector3(0,1,0));
	graphic::GetDevice()->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&V);


	const int WINSIZE_X = 1024;		//�ʱ� ������ ���� ũ��
	const int WINSIZE_Y = 768;	//�ʱ� ������ ���� ũ��
	Matrix44 proj;
	proj.SetProjection(D3DX_PI * 0.5f, (float)WINSIZE_X / (float) WINSIZE_Y, 1.f, 1000.0f) ;
	graphic::GetDevice()->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&proj) ;


	graphic::GetDevice()->LightEnable (
		0, // Ȱ��ȭ/ ��Ȱ��ȭ �Ϸ��� ���� ����Ʈ ���� ���
		true); // true = Ȱ��ȭ �� false = ��Ȱ��ȭ

	return true;
}


void cViewer::OnUpdate(const float elapseT)
{
	m_model.Move(elapseT);
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
		y += elapseT * 0.03f;
		// ������ 2*PI �� �̸��� 0���� �ʱ�ȭ�Ѵ�.
		if (y >= 6.28f)
			y = 0;

		Matrix44 rx, ry, r;
		rx.SetRotationX(MATH_PI/4.f); 	// x������ 45�� ȸ����Ų��.
		ry.SetRotationY(y); // y������ ȸ��
		r = rx*ry;

		Matrix44 tm;
		tm = r * g_rotateTm;
		//graphic::GetDevice()->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&tm);

		//m_mtrl.Bind();
		//m_texture.Bind(0);
		//m_idxBuff.Bind();
		//m_vtxBuff.Bind();
		//graphic::GetDevice()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 
		//	m_vtxBuff.GetVertexCount(), 0, m_idxBuff.GetFaceCount());

		m_model.SetTM(tm);
		m_model.Render();

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
	switch (message)
	{
	case WM_DROPFILES:
		{
			HDROP hdrop = (HDROP)wParam;
			char filePath[ MAX_PATH];
			const UINT size = DragQueryFileA(hdrop, 0, filePath, MAX_PATH);
			if (size == 0) 
				return;// handle error...

			m_filePath = filePath;
			//m_texture.Clear();
			//m_vtxBuff.Clear();
			//m_idxBuff.Clear();
			//ReadModelFile(filePath, m_vtxBuff, m_idxBuff, m_texture);
			m_model.Create(filePath);
		}
		break;

	case WM_MOUSEWHEEL:
		{
			int fwKeys = GET_KEYSTATE_WPARAM(wParam);
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			//dbg::Print( "%d %d", fwKeys, zDelta);

			Matrix44 V;
			m_camPos.z += (zDelta<0)? -50 : 50;
			Vector3 dir = m_lookAtPos - m_camPos;
			dir.Normalize();
			V.SetView(m_camPos, dir, Vector3(0,1,0));
			graphic::GetDevice()->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&V);
		}
		break;

	case WM_KEYDOWN:
		if (wParam == VK_F5) // Refresh
		{
			 if (m_filePath.empty())
				 return;
			// m_texture.Clear();
			//m_vtxBuff.Clear();
			//m_idxBuff.Clear();
			//ReadModelFile(m_filePath, m_vtxBuff, m_idxBuff, m_texture);
			 m_model.Create(m_filePath);
		}
		else if (wParam == VK_TAB)
		{
			static bool flag = false;
			graphic::GetDevice()->SetRenderState(D3DRS_CULLMODE, flag);
			graphic::GetDevice()->SetRenderState(D3DRS_FILLMODE, flag? D3DFILL_SOLID : D3DFILL_WIREFRAME);
			flag = !flag;
		}
		break;

	case WM_LBUTTONDOWN:
		{
			m_LButtonDown = true;
			m_curPos.x = LOWORD(lParam);
			m_curPos.y = HIWORD(lParam);
		}
		break;

	case WM_LBUTTONUP:
		m_LButtonDown = false;
		break;

	case WM_MOUSEMOVE:
		if (m_LButtonDown)
		{
			POINT pos;
			pos.x = LOWORD(lParam);
			pos.y = HIWORD(lParam);

			const int x = pos.x - m_curPos.x;
			const int y = pos.y - m_curPos.y;

			Matrix44 mat1;
			mat1.SetRotationY( -x * 0.01f );
			Matrix44 mat2;
			mat2.SetRotationX( -y * 0.01f );

			m_curPos = pos;

			g_rotateTm *= (mat1 * mat2);
		}
		break;
	}
}

