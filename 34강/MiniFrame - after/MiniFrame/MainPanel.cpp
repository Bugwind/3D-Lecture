// MainPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "MainPanel.h"
#include "afxdialogex.h"
#include "TerrainPanel.h"
#include "TilePanel.h"


// CMainPanel ��ȭ �����Դϴ�.
CMainPanel::CMainPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainPanel::IDD, pParent)
{

}

CMainPanel::~CMainPanel()
{
}

void CMainPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CMainPanel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMainPanel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMainPanel::OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainPanel::OnSelchangeTab1)
END_MESSAGE_MAP()


// CMainPanel �޽��� ó�����Դϴ�.


void CMainPanel::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	CDialogEx::OnOK();
}


void CMainPanel::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	CDialogEx::OnCancel();
}


BOOL CMainPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Tab.InsertItem(0, L"Terrain");
	m_Tab.InsertItem(1, L"Tile");
	m_Tab.InsertItem(2, L"Object");

	m_pTerrainPanel = new CTerrainPanel();
	m_pTerrainPanel->Create(CTerrainPanel::IDD, this);

	m_pTerrainPanel->MoveWindow(CRect(15, 40, 300, 500));
	m_pTerrainPanel->ShowWindow(SW_SHOW);

	m_pTilePanel = new CTilePanel();
	m_pTilePanel->Create(CTilePanel::IDD, this);
	m_pTilePanel->MoveWindow(CRect(15, 40, 300, 500));

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMainPanel::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch (m_Tab.GetCurSel())
	{
	case 0:
		m_pTerrainPanel->ShowWindow(SW_SHOW);
		m_pTilePanel->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pTerrainPanel->ShowWindow(SW_HIDE);
		m_pTilePanel->ShowWindow(SW_SHOW);
		break;
	}
	
	*pResult = 0;
}
