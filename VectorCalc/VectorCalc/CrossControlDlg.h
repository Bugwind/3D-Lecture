#pragma once


// CCrossControlDlg ��ȭ �����Դϴ�.

class CCrossControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCrossControlDlg)

public:
	CCrossControlDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCrossControlDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_CROSS_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
