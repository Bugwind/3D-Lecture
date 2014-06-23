#pragma once


// CModelView ���Դϴ�.

class CModelView : public CView
{
public:
	CModelView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CModelView();

	CPoint m_mousePos;

	void Init();
	void Render();
	void UpdateCamera();


protected:
	graphic::cModel *m_model;

	string m_filePath;

	POINT m_curPos;
	bool m_LButtonDown;
	bool m_RButtonDown;
	Matrix44 m_rotateTm;

	Vector3 m_camPos;
	Vector3 m_lookAtPos;



public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


