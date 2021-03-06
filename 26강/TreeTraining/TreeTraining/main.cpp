
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct sNode
{
	string name;
	sNode* left;
	sNode* right;

	sNode() {left=NULL, right=NULL;}
	sNode(const string &n) : name(n) {left=NULL, right=NULL;}
	sNode(const string &n, sNode *_l, sNode *_r) :
		name(n), left(_l), right(_r) {}
};

void print(sNode *node)
{
	if (!node)
		return;

	print(node->left);
	print(node->right);
	cout << node->name << endl;
}

void main()
{
	sNode *root = new sNode( "1",
		new sNode("2", 
			new sNode("4", NULL, NULL),
			new sNode("5", NULL, NULL)
			),
		new sNode("3", 
			new sNode("6", NULL, NULL),
			new sNode("7", NULL, NULL)
			)
		);

	print(root);
}
