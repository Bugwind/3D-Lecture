#pragma once


// CTerrainPanel ��ȭ �����Դϴ�.

class CTerrainPanel : public CDialogEx
{
public:
	CTerrainPanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTerrainPanel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_TERRAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
