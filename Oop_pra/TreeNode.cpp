/*
Ϊ�������ʵ�ֹ��캯���ͱ�Ҫ�Ŀ������Ƴ�Ա
*/

#include<string>
using namespace std;
class TreeNode
{
public:
	TreeNode() :value(""), count(1), left(nullptr), right(nullptr) {};
	TreeNode(const string& s = string(), TreeNode* l = nullptr, TreeNode* r = nullptr)
		:value(s), left(l), right(r), count(1) {};
	~TreeNode();

private:
	string value;
	int count;
	TreeNode* left;
	TreeNode* right;
};

class BinTree {
	BinTree() :root(nullptr) {};
	BinTree(TreeNode* s) :root(s) {};
private:
	TreeNode* root;
};