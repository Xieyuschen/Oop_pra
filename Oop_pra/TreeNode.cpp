/*
Ϊ�������ʵ�ֹ��캯���ͱ�Ҫ�Ŀ������Ƴ�Ա
*/

#include<string>
using namespace std;
class TreeNode
{
public:
	TreeNode() : value(string()), count(new int(1)), left(nullptr), right(nullptr) { }
	TreeNode(const TreeNode& rhs) : value(rhs.value), count(rhs.count), left(rhs.left), right(rhs.right) { ++* count; }

	//д�������캯����ʱ������Ҫ���������������ֵ��Ϊ��������ָ����Ϊ
	//���ڽڵ���˵����ϣ��������ָ����Ϊ���������ֵ��Ϊ�Ļ���Ҳ����ÿ�ο�����������ָ����п���

	~TreeNode() {
		if (-- * count == 0) {
			delete left;
			delete right;
			delete count;
		}
	}

private:
	string value;
	//���뱣֤���еĿ�����ָ��һ���ط�����ôָ��������Ȼ����Ҫ
	int *count;
	TreeNode* left;
	TreeNode* right;
};

class BinTree {
	BinTree() :root(nullptr) {};
	BinTree(TreeNode* s) :root(s) {};
private:
	TreeNode* root;
};