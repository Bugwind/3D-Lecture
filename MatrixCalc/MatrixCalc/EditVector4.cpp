// EditVector4.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MatrixCalc.h"
#include "EditVector4.h"
#include "afxdialogex.h"


// CEditVector4 ��ȭ �����Դϴ�.

//IMPLEMENT_DYNAMIC(CEditVector4, CDialogEx)

CEditVector4::CEditVector4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditVector4::IDD, pParent)
{

}

CEditVector4::~CEditVector4()
{
}

void CEditVector4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditVector4, CDialogEx)
END_MESSAGE_MAP()


// CEditVector4 �޽��� ó�����Դϴ�.
