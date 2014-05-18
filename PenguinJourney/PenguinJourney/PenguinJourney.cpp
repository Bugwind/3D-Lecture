#include <windows.h>
#include "math/Math.h"
#include "DrawTriangle.h"
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int WINSIZE_X = 800;		//�ʱ� ������ ���� ũ��
const int WINSIZE_Y = 600;	//�ʱ� ������ ���� ũ��
const int WINPOS_X = 0; //�ʱ� ������ ���� ��ġ X
const int WINPOS_Y = 0; //�ʱ� ������ ���� ��ġ Y

HWND g_hWnd;
vector<Vector3> g_vertices;
vector<Vector3> g_normals;
vector<int> g_indices;
Matrix44 g_matWorld;
Matrix44 g_matLocal;
Vector3 g_PenguinPos(0,0,-300);
Vector3 g_PenguinVel(0, 0, 3000.f);

const int MAX_GROUND = 6;
vector<Vector3> g_groundVtx;
vector<Vector3> g_groundNormals;
vector<int> g_groundIdx;
vector<Matrix44> g_matGrounds(MAX_GROUND);

vector<Vector3> g_obstructVtx;
vector<Vector3> g_obstructNormals;
vector<int> g_obstructdIdx;
vector<Matrix44> g_matObstructs(MAX_GROUND);

bool g_Stop = false;

Matrix44 g_matView;
Matrix44 g_matProjection;
Matrix44 g_matViewPort;
Vector3 g_cameraPos(0,300,-1000);
Vector3 g_cameraLookat(0,0,1000);



// �ݹ� ���ν��� �Լ� ������ Ÿ��
LRESULT CALLBACK WndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam );
void MainLoop(int elapse_time);
void	Render(HWND hWnd);
void	Paint(HWND hWnd, HDC hdc);
void	ComputeNormals(const vector<Vector3> &vertices, const vector<int> &indices, vector<Vector3> &normals);
bool ReadModelFile( const string &fileName, vector<Vector3> &vertices, vector<int> &indices, vector<Vector3> &normals );
bool Init();

int APIENTRY WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	wchar_t className[32] = L"Sample";
	wchar_t windowName[32] = L"Sample";

	//������ Ŭ���� ���� ����
	//���� �̷��� ������ ����ڴ� ��� ����
	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;			//�����쿡�� ����ϴ� ������ �޸𸮼���( �׳� 0 �̴�  �Ű澲������ )
	WndClass.cbWndExtra = 0;			//�����쿡�� ����ϴ� ������ �޸𸮼���( �׳� 0 �̴�  �Ű澲������ )
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);		//������ ������
	WndClass.hCursor = LoadCursor( NULL, IDC_ARROW );			//�������� Ŀ����� ����
	WndClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );		//����������ܸ�� ����
	WndClass.hInstance = hInstance;				//���α׷��ν��Ͻ��ڵ� 
	WndClass.lpfnWndProc = (WNDPROC)WndProc;			//������ ���ν��� �Լ� ������
	WndClass.lpszMenuName = NULL;						//�޴��̸� ������ NULL
	WndClass.lpszClassName = className;				//���� �ۼ��ϰ� �ִ� ������ Ŭ������ �̸�
	WndClass.style	 = CS_HREDRAW | CS_VREDRAW;	//������ �׸��� ��� ���� ( ����� ����ɶ� ȭ�鰻�� CS_HREDRAW | CS_VREDRAW )

	//������ �ۼ��� ������ Ŭ�������� ���
	RegisterClass( &WndClass );

	//������ ����
	//������ ������ �ڵ��� �������� g_hWnd �� �޴´�.
	HWND hWnd = CreateWindow(
		className,				//�����Ǵ� �������� Ŭ�����̸�
		windowName,				//������ Ÿ��Ʋ�ٿ� ��µǴ� �̸�
		WS_OVERLAPPEDWINDOW,	//������ ��Ÿ�� WS_OVERLAPPEDWINDOW
		WINPOS_X,				//������ ���� ��ġ X 
		WINPOS_Y,				//������ ���� ��ġ Y
		WINSIZE_X,				//������ ���� ũ�� ( �۾������� ũ�Ⱑ �ƴ� )
		WINSIZE_Y,				//������ ���� ũ�� ( �۾������� ũ�Ⱑ �ƴ� )
		GetDesktopWindow(),		//�θ� ������ �ڵ� ( ���α׷����� �ֻ��� ������� NULL �Ǵ� GetDesktopWindow() )
		NULL,					//�޴� ID ( �ڽ��� ��Ʈ�� ��ü�� �������ΰ�� ��Ʈ�� ID �� ��	
		hInstance,				//�� �����찡 ���� ���α׷� �ν��Ͻ� �ڵ�
		NULL					//�߰� ���� NULL ( �Ű���� )
		);

	g_hWnd = hWnd;

	//�����츦 ��Ȯ�� �۾����� ũ��� �����
	RECT rcClient = { 0, 0, WINSIZE_X, WINSIZE_Y };
	AdjustWindowRect( &rcClient, WS_OVERLAPPEDWINDOW, FALSE );	//rcClient ũ�⸦ �۾� �������� �� ������ ũ�⸦ rcClient �� ���ԵǾ� ���´�.

	//������ ũ��� ������ ��ġ�� �ٲپ��ش�.
	SetWindowPos( hWnd, NULL, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, 
		SWP_NOZORDER | SWP_NOMOVE );

	Init();

	ShowWindow( hWnd, nCmdShow );

	//�޽��� ����ü
	MSG msg;		
	ZeroMemory( &msg, sizeof( MSG ) );

	int oldT = GetTickCount();
	while (msg.message != WM_QUIT)
	{
		//PeekMessage �� �޽��� ť�� �޽����� ��� ���α׷��� ���߱� �ʰ� ������ �ȴ�.
		//�̶� �޽���ť�� �޽����� ������ false �� ���ϵǰ� �޽����� ������ true �� �����̵ȴ�.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage( &msg ); //���� Ű���� �� ���ڸ� �����Ͽ� WM_CHAR �޽����� �߻���Ų��.
			DispatchMessage( &msg );  //�޾ƿ� �޽��� ������ ������ ���ν��� �Լ��� �����Ų��.
		}
		else
		{
			const int curT = GetTickCount();
			const int elapseT = curT - oldT;
			if (elapseT > 10)
			{
				oldT = curT;
				MainLoop(elapseT);	
			}
		}
	}

	return 0;
}


//
// ������ ���ν��� �Լ� ( �޽��� ť���� �޾ƿ� �޽����� ó���Ѵ� )
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_ERASEBKGND:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Paint(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
				::DestroyWindow(hWnd);
				break;

			case 'E':
			case 'C':
				{
					Matrix44 mat;
					mat.SetRotationY( (wParam == 'E')? 0.1f : -0.1f);
					g_cameraPos *= mat;
					Vector3 dir = g_cameraLookat - g_cameraPos;
					dir.Normalize();
					g_matView.SetView(g_cameraPos, dir, Vector3(0,1,0));
				}
				break;

			case VK_UP:
			case VK_DOWN:
				{
					//Matrix44 mat;
					//mat.SetRotationX((wParam==VK_UP)? 0.1f : -0.1f);
					//g_matLocal *= mat;
				}
				break;

			case VK_LEFT:
			case VK_RIGHT:
				{
					//Matrix44 mat;
					//mat.SetRotationY((wParam==VK_LEFT)? 0.1f : -0.1f);
					//g_matLocal *= mat;

					//g_PenguinPos.x += (wParam==VK_LEFT)? -10.f : 10.f;
				}
				break;

			case 'P':
				g_Stop = !g_Stop;
				break;
			}

		}
		break;
	case WM_DESTROY: //�����찡 �ı��ȴٸ�..
		PostQuitMessage(0);	//���α׷� ���� ��û ( �޽��� ������ ���������� �ȴ� )
		break;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}


/**
 @brief 
 */
void	MainLoop(int elapse_time)
{
	float static incT = (elapse_time * 0.001f);

	// keyboard
	const float movOffset = 20.f;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_PenguinPos.x += -movOffset;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_PenguinPos.x += movOffset;
	}
	
	const Vector3 mov = (g_Stop)? Vector3(0,0,0) : g_PenguinVel * incT;
	g_PenguinPos += mov;
	Matrix44 matMov;
	matMov.SetTranslate(g_PenguinPos);
	g_matWorld  = matMov;

	g_cameraLookat += mov;
	g_cameraPos += mov;
	Vector3 dir = g_cameraLookat - g_cameraPos;
	dir.Normalize();
	g_matView.SetView(g_cameraPos, dir, Vector3(0,1,0));


	// scroll & generate obstacle
	static int groundFront = 0;
	if (g_matGrounds[ groundFront]._43 < g_cameraPos.z)
	{
		const int backIdx = (groundFront + g_matGrounds.size() - 1) % g_matGrounds.size();
		g_matGrounds[ groundFront]._43 = g_matGrounds[ backIdx]._43 + 600.F;
		
		g_matObstructs[ groundFront]._43 = g_matGrounds[ backIdx]._43 + 600.F;
		g_matObstructs[ groundFront]._41 = (rand() % 500) - 250;

		++groundFront;
		groundFront %= g_matGrounds.size();
	}
	

	// Render
	Render(g_hWnd);
	::InvalidateRect(g_hWnd, NULL, TRUE);
}


/**
 @brief 
 */
void	Render(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	Paint(hWnd, hdc);
	::ReleaseDC(hWnd, hdc);
}


bool Init()
{
	ReadModelFile("cube.dat", g_vertices, g_indices, g_normals);
	ReadModelFile("plane.dat", g_groundVtx, g_groundIdx, g_groundNormals);
	ReadModelFile("cone.dat", g_obstructVtx, g_obstructdIdx, g_obstructNormals);

	g_matLocal.SetScale(Vector3(0.25f, 0.4f, 0.25f));

	for (int i=0; i < (int)g_matGrounds.size(); ++i)
	{
		Matrix44 matS;
		matS.SetScale(Vector3(10, 10, 10));
		Matrix44 matT;
		matT.SetTranslate(Vector3(10, 10, 550.f*i));
		g_matGrounds[ i] = matS * matT;
	}

	for (int i=0; i < (int)g_matObstructs.size(); ++i)
	{
		Matrix44 matS;
		matS.SetScale(Vector3(3, 3, 3));

		Vector3 pos;
		pos.x = (rand() % 500) - 250;
		pos.z = 550.f * i;
		Matrix44 matT;
		matT.SetTranslate(pos);

		g_matObstructs[ i] = matS * matT;
	}

	Vector3 dir = g_cameraLookat - g_cameraPos;
	dir.Normalize();
	g_matView.SetView(g_cameraPos, dir, Vector3(0,1,0));
	g_matProjection.SetProjection( MATH_PI / 4.f, 1.0f, 1.0f, 100.0f );

	RECT cr;
	::GetClientRect(g_hWnd, &cr);
	g_matViewPort._11 = WINSIZE_X/2;
	g_matViewPort._22 = -WINSIZE_Y/2;
	g_matViewPort._33 = 0;
	g_matViewPort._41 = WINSIZE_X/2;
	g_matViewPort._42 = WINSIZE_Y/2;
	g_matViewPort._43 = 0;

	return true;
}


/**
 @brief 
 @date 2014-04-07
*/
void ComputeNormals(const vector<Vector3> &vertices, const vector<int> &indices, vector<Vector3> &normals)
{
	normals.resize(vertices.size());

	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]];
		Vector3 p2 = vertices[ indices[ i+1]];
		Vector3 p3 = vertices[ indices[ i+2]];

		Vector3 v1 = p2 - p1;
		Vector3 v2 = p3 - p1;
		v1.Normalize();
		v2.Normalize();
		Vector3 n = v1.CrossProduct(v2);
		n.Normalize();

		if (normals[ indices[ i]].IsEmpty())
		{
			normals[ indices[ i]] = n;
		}
		else
		{
			normals[ indices[ i]] += n;
			normals[ indices[ i]] /= 2.f;
		}

		if (normals[ indices[ i+1]].IsEmpty())
		{
			normals[ indices[ i+1]] = n;
		}
		else
		{
			normals[ indices[ i+1]] += n;
			normals[ indices[ i+1]] /= 2.f;
		}

		if (normals[ indices[ i+2]].IsEmpty())
		{
			normals[ indices[ i+2]] = n;
		}
		else
		{
			normals[ indices[ i+2]] += n;
			normals[ indices[ i+2]] /= 2.f;
		}
	}
}


bool ReadModelFile( const string &fileName, vector<Vector3> &vertices, vector<int> &indices, vector<Vector3> &normals )
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

	vertices.resize(numVertices);

	float num1, num2, num3;
	for (int i = 0; i < numVertices; i++)
	{
		fin >> num1 >> num2 >> num3;
		vertices[i] = Vector3(num1, num2, num3);
	}

	string idx, idx_eq;
	int numIndices;
	fin >> idx >> idx_eq >> numIndices;

	if (numIndices <= 0)
		return false;

	indices.resize(numIndices*3);

	int num4, num5, num6;
	for (int i = 0; i < numIndices*3; i+=3)
	{
		fin >> num4 >> num5 >> num6;
		indices[ i] = num4;
		indices[ i+1] = num5;
		indices[ i+2] = num6;	
	}

	ComputeNormals(vertices, indices, normals);
	return true;
}


void RenderVertices(HDC hdc, const vector<Vector3> &vertices, const Matrix44 &tm)
{
	for (unsigned int i=0; i < vertices.size(); ++i)
	{
		Vector3 p = vertices[ i] * tm;

		if (0 == i)
			MoveToEx(hdc, (int)p.x, (int)p.y, NULL);
		else
			LineTo(hdc, (int)p.x, (int)p.y);
	}
}


void RenderIndices(HDC hdc, const vector<Vector3> &vertices, const vector<int> &indices, 
				   const vector<Vector3> &normals, const Matrix44 &tm, const Matrix44 &vpv)
{
	Vector3 camDir = g_cameraLookat - g_cameraPos;
	camDir.Normalize();

	Rasterizer::Color c0(0,0,255,1);
	Rasterizer::Color c1(255,255,255,1);
	Vector3 lightDir(0,-1,0);
	Vector3 H = -(camDir + lightDir);
	H.Normalize();
	Rasterizer::Color ambient(0,20,0,1);

	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]];
		Vector3 p2 = vertices[ indices[ i+1]];
		Vector3 p3 = vertices[ indices[ i+2]];

		p1 = p1 * tm;
		p2 = p2 * tm;
		p3 = p3 * tm;

		// culling
		Vector3 n1 = normals[ indices[i]].MultiplyNormal(tm);
		Vector3 n2 = normals[ indices[i+1]].MultiplyNormal(tm);
		Vector3 n3 = normals[ indices[i+2]].MultiplyNormal(tm);
		const float dot1 = n1.DotProduct(camDir);
		const float dot2 = n2.DotProduct(camDir);
		const float dot3 = n3.DotProduct(camDir);
		if ((dot1 > 0) && (dot2 > 0) && (dot3 > 0))
			continue;

		p1 = p1 * vpv;
		p2 = p2 * vpv;
		p3 = p3 * vpv;

		Rasterizer::Color color1, color2, color3;
		{
			Rasterizer::Color diffuse = c0 * max(0, n1.DotProduct(-lightDir));
			Rasterizer::Color specular = 0;//c1*pow(n1.DotProduct(H), 16);
			color1 = ambient + diffuse + specular;
		}
		{
			Rasterizer::Color diffuse = c0 * max(0, n2.DotProduct(-lightDir));
			Rasterizer::Color specular = c1*pow(n2.DotProduct(H), 16);
			color2 = ambient + diffuse + specular;
		}
		{
			Rasterizer::Color diffuse = c0 * max(0, n3.DotProduct(-lightDir));
			Rasterizer::Color specular = c1*pow(n3.DotProduct(H), 16);
			color3 = ambient + diffuse + specular;
		}

		Rasterizer::DrawLine(hdc, color1, p1.x, p1.y, color1, p2.x, p2.y);
		Rasterizer::DrawLine(hdc, color1, p1.x, p1.y, color1, p3.x, p3.y);
		Rasterizer::DrawLine(hdc, color1, p3.x, p3.y, color1, p2.x, p2.y);
		//Rasterizer::DrawTriangle(hdc, 
		//	color1, p1.x, p1.y, n1,
		//	color2, p2.x, p2.y, n2,
		//	color3, p3.x, p3.y, n3);
	}
}


/**
 @brief 
 */
void Paint(HWND hWnd, HDC hdc)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmMem = CreateCompatibleBitmap(hdc, rc.right-rc.left, rc.bottom-rc.top);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
	HBRUSH hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	Matrix44 vpv = g_matView * g_matProjection * g_matViewPort;
	RenderIndices(hdcMem, g_vertices, g_indices, g_normals, g_matLocal * g_matWorld, vpv);

	for (int i=0; i < (int)g_matGrounds.size(); ++i)
		RenderIndices(hdcMem, g_groundVtx, g_groundIdx, g_groundNormals, g_matGrounds[ i], vpv);

	for (int i=0; i < (int)g_matObstructs.size(); ++i)
		RenderIndices(hdcMem, g_obstructVtx, g_obstructdIdx, g_obstructNormals, g_matObstructs[ i], vpv);


	BitBlt(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
}

