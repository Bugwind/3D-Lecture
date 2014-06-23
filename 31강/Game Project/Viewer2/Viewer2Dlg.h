
// Viewer2Dlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"


class CModelView;
// CViewer2Dlg ��ȭ ����
class CViewer2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CViewer2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VIEWER2_DIALOG };

	void MainLoop();



protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	HICON m_hIcon;
	bool m_loop;
	CModelView *m_pModelView;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_FileList;
	afx_msg void OnKeydownFileList(NMHDR *pNMHDR, LRESULT *pResult);
};
