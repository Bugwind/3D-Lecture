#pragma once

#include "3DView.h"


class CDotProductView : public C3DView
{
public:
	CDotProductView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CDotProductView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.


public:
	virtual void Render(HDC hdc) override;


protected:
	DECLARE_MESSAGE_MAP()
};
