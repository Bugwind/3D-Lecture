
#include "stdafx.h"
#include "node.h"

using namespace graphic;


cNode::cNode( const int id)
{

}

cNode::~cNode()
{

}


bool cNode::Move(const float elapseTime)
{

	return true;
}

void cNode::Render()
{
	
}


// ��带 �ڽ����� �߰��Ѵ�.
bool cNode::InsertChild(cNode *node)
{
	RETV(!node, false);
	RETV(FindNode(node->GetId()), false); // Already Exist
	
	m_children.push_back(node);
	return true;
}


// �ڽ� ��� �߿� id �� ���� ��尡 �ִٸ� �����Ѵ�.
cNode* cNode::FindNode(const int id)
{
	if (GetId() == id)
		return this;

	BOOST_FOREACH (auto node, m_children)
	{


	}

	return NULL;
}


bool cNode::RemoveNode(const int id)
{

	return true;
}


void cNode::Clear()
{

}
