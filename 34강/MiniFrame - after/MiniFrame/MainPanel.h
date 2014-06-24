#pragma once
#include "afxcmn.h"


// CMainPanel ��ȭ �����Դϴ�.
class CTerrainPanel;
class CTilePanel;
class CMainPanel : public CDialogEx
{
public:
	CMainPanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMainPanel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MAINPANEL };

	CTerrainPanel *m_pTerrainPanel;
	CTilePanel *m_pTilePanel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CTabCtrl m_Tab;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
