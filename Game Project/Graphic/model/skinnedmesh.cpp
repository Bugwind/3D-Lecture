
#include "stdafx.h"
#include "skinnedmesh.h"

using namespace graphic;


cSkinnedMesh::cSkinnedMesh(const int id, const vector<Matrix44> &palette, const sRawMesh &raw) : 
	cMesh(id, raw)
,	m_palette(palette)
{

}

cSkinnedMesh::~cSkinnedMesh()
{

}


void cSkinnedMesh::Render(const Matrix44 &parentTm)
{

}


// �ȷ�Ʈ ����.
void cSkinnedMesh::ApplyPalette()
{

}
