#pragma once


// CTilePanel ��ȭ �����Դϴ�.

class CTilePanel : public CDialogEx
{
public:
	CTilePanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTilePanel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_TILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
