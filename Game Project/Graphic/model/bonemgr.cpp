
#include "stdafx.h"
#include "bonemgr.h"
#include "bonenode.h"

using namespace  graphic;


cBoneMgr::cBoneMgr(const int id, const sRawMeshGroup &rawMeshes) :
	m_root(NULL)
,	m_id(id)
{
	m_palette.resize(rawMeshes.bones2.size());

	vector<cBoneNode*> vec(rawMeshes.bones2.size(), NULL);
	for (u_int i=0; i < rawMeshes.bones2.size(); ++i)
	{
		const int id = rawMeshes.bones2[ i].id;
		const int parentId = rawMeshes.bones2[ i].parentId;
		cBoneNode *bone = new cBoneNode(id, m_palette, rawMeshes.bones2[ i]);
		SAFE_DELETE(vec[ id]);
		vec[ id] = bone;

		if (-1 >=  parentId) // root
			m_root = bone;
		else
			vec[ parentId]->InsertChild( bone );
	}

}

cBoneMgr::~cBoneMgr()
{
	Clear();
}


// ���ϸ��̼� ����.
void cBoneMgr::SetAnimation( const sRawAniGroup &rawAnies, int nAniFrame )
{
	SetAnimationRec( m_root, rawAnies, nAniFrame );
}


// �ִϸ��̼� ����.
void cBoneMgr::SetAnimationRec( cBoneNode *node, const sRawAniGroup &rawAnies, int nAniFrame )
{
	RET(!node);
	RET(node->GetId() >= (int)rawAnies.anies.size());

	node->SetAnimation( rawAnies.anies[ node->GetId()], nAniFrame, true );
	BOOST_FOREACH (auto p, node->GetChildren())
	{
		SetAnimationRec((cBoneNode*)p, rawAnies, nAniFrame );
	}
}


// �ִϸ��̼�
bool cBoneMgr::Move(const float elapseTime)
{
	RETV(!m_root, false);
	return m_root->Move(elapseTime);
}


// ���̷��� ���.
void cBoneMgr::Render(const Matrix44 &parentTm)
{
	RET(!m_root);
	m_root->Render(parentTm);
}


// �������� �Ҵ�� ��ü ����.
void cBoneMgr::Clear()
{
	SAFE_DELETE(m_root);
}


// BoneNode ã�Ƽ� ����.
cBoneNode* cBoneMgr::FindBone(const int id)
{
	RETV(!m_root, NULL);
	return (cBoneNode*)m_root->FindNode(id);
}
