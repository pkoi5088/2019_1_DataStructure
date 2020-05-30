#include <vector>
#include <string>

using namespace std;

class OrganizationTree;

class TreeNode {
	TreeNode(string& name, TreeNode* high);//생성자

	string name;//이름
	TreeNode* high;//상관 노드
	vector<TreeNode*> sub;//부하 노드 벡터

	friend class OrganizationTree;
};

class OrganizationTree {//조직도
public:
	OrganizationTree(string& name);//생성자

	void hire(string& super, string& sub);//고용
	void fire(string& name);//해고
	void print();//출력
	void set();
	bool isEmpty();
	void printPeople();

private:
	void hireSub(TreeNode* p, string& super, string& sub);//고용Sub
	void fireSub(TreeNode* p, string& name);//해고Sub
	void printSub(TreeNode* p, int n);//출력Sub
	bool isExist(string& name);//존재하는가?
	void eraseName(string& name);//이름지우기

	vector<string> people;//존재하는 이름 저장하기
	TreeNode* root;//BOSS
};