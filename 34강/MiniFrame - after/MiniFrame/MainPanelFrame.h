#pragma once


// CMainPanel �������Դϴ�.

class CMainPanelFrame : public CMiniFrameWnd
{
public:
	CMainPanelFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMainPanelFrame();
	void Init();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


