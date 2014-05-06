// CEditMatrix4x4 ��ȭ �����Դϴ�.
//
#pragma once

#include "CommonDataInterface.h"

class CEditMatrix4x4 : public CDialogEx, public CommonDataInterface
{
	DECLARE_DYNAMIC(CEditMatrix4x4)

public:
	CEditMatrix4x4(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEditMatrix4x4();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MATRIX_4X4 };

	virtual void SetIdentity() override;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	float m_11;
	float m_12;
	float m_13;
	float m_14;

	float m_21;
	float m_22;
	float m_23;
	float m_24;

	float m_31;
	float m_32;
	float m_33;
	float m_34;

	float m_41;
	float m_42;
	float m_43;
	float m_44;
};
