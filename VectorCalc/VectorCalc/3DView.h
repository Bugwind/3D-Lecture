#pragma once



class C3DView : public CView
{
public:
	C3DView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~C3DView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.

public:
	virtual void Render(HDC hdc) { }
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.

protected:
	DECLARE_MESSAGE_MAP()
};
