/*
为下面的类实现构造函数和必要的拷贝控制成员
*/

#include<string>
using namespace std;
class TreeNode
{
public:
	TreeNode() : value(string()), count(new int(1)), left(nullptr), right(nullptr) { }
	TreeNode(const TreeNode& rhs) : value(rhs.value), count(rhs.count), left(rhs.left), right(rhs.right) { ++* count; }

	//写拷贝构造函数的时候，我需要分析这个类是有类值行为还是有类指针行为
	//对于节点来说，我希望它具有指针行为，如果具有值行为的话，也就是每次拷贝都给它的指针进行拷贝

	~TreeNode() {
		if (-- * count == 0) {
			delete left;
			delete right;
			delete count;
		}
	}

private:
	string value;
	//必须保证所有的拷贝都指向一个地方，那么指针理所当然必须要
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