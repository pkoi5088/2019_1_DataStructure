#include <vector>
#include <string>

using namespace std;

class OrganizationTree;

class TreeNode {
	TreeNode(string& name, TreeNode* high);//������

	string name;//�̸�
	TreeNode* high;//��� ���
	vector<TreeNode*> sub;//���� ��� ����

	friend class OrganizationTree;
};

class OrganizationTree {//������
public:
	OrganizationTree(string& name);//������

	void hire(string& super, string& sub);//���
	void fire(string& name);//�ذ�
	void print();//���
	void set();
	bool isEmpty();
	void printPeople();

private:
	void hireSub(TreeNode* p, string& super, string& sub);//���Sub
	void fireSub(TreeNode* p, string& name);//�ذ�Sub
	void printSub(TreeNode* p, int n);//���Sub
	bool isExist(string& name);//�����ϴ°�?
	void eraseName(string& name);//�̸������

	vector<string> people;//�����ϴ� �̸� �����ϱ�
	TreeNode* root;//BOSS
};