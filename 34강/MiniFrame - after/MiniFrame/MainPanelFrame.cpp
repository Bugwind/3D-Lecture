// MainPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "MainPanelFrame.h"
#include "MainPanel.h"


// CMainPanel

CMainPanelFrame::CMainPanelFrame()
{
	
}

CMainPanelFrame::~CMainPanelFrame()
{
}


BEGIN_MESSAGE_MAP(CMainPanelFrame, CMiniFrameWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMainPanel �޽��� ó�����Դϴ�.
void CMainPanelFrame::Init()
{
	CMainPanel *panel = new CMainPanel();
	panel->Create(CMainPanel::IDD, this);
	panel->ShowWindow(SW_SHOW);

}


void CMainPanelFrame::OnSize(UINT nType, int cx, int cy)
{
	CMiniFrameWnd::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
