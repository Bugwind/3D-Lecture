
// VectorCalcDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"

class CDotProductView;

// CVectorCalcDlg ��ȭ ����
class CVectorCalcDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CVectorCalcDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VECTORCALC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	CDotProductView *m_pView;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CTabCtrl m_TabCtrl;
	afx_msg void OnSelchangeTabCalc(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
