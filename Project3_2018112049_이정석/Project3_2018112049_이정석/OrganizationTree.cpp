#include "OrganizationTree.h"
#include <iostream>

TreeNode::TreeNode(string& name, TreeNode* high) {//Node생성자
	this->name = name;
	this->high = high;
}

OrganizationTree::OrganizationTree(string& name) {//조직도생성자
	root = new TreeNode(name, NULL);//BOSS설정
	people.push_back(name);//사람목록에 추가
}

void OrganizationTree::hire(string& super, string& sub) {//고용
	bool c_s, c_b;//check_super check_sub 변수
	c_s = isExist(super); c_b = isExist(sub);

	if (!c_s&&c_b)//상관이 존재하지 않고 부하가 이미 존재하면
		cout << super << " does not exist and " << sub << " does!" << endl;
	else if (!c_s)//상관이 존재하지 않으면
		cout << super << " does not exist!" << endl;
	else if (c_b)//부하가 이미 존재하면
		cout << sub << " dost exist!" << endl;
	else {//아니면
		hireSub(root, super, sub);//고용하기
		cout << super << " hires " << sub << endl;
	}
}

void OrganizationTree::hireSub(TreeNode* p, string& super, string& sub) {
	if (p != NULL) {//p가 NULL이 아니면
		if (p->name != super) {//상관이 아니면
			for (int i = 0; i < p->sub.size(); i++)
				hireSub(p->sub[i], super, sub);//부하에서 다시 실행
		}
		else {//상관이면
			p->sub.push_back(new TreeNode(sub, p));//상관에서 부하를 추가
			people.push_back(sub);//사람목록에 추가
		}
	}
}

void OrganizationTree::fire(string& name) {//해고
	bool c = isExist(name);//check

	if (!c)//존재하지 않으면
		cout << name << " does not exist!" << endl;
	else {//존재하면
		fireSub(root, name);//해고하기
		eraseName(name);
		cout << "Fire " << name << endl;
	}
}

void OrganizationTree::fireSub(TreeNode* p, string& name) {
	if (p != NULL) {//p가 NULL이 아니면
		if (p->name != name) {//찾는 사람이 아니면
			for (int i = 0; i < p->sub.size(); i++)//부하에서 찾는다
				fireSub(p->sub[i], name);
		}
		else {//찾았으면
			if (p == root) {//지우려는게 BOSS면
				if (p->sub.size() == 0) {//BOSS혼자일 때
					delete p;
					root = NULL;
				}//부하가 있을 때
				else {
					p->name = p->sub[0]->name;
					fireSub(p->sub[0], p->sub[0]->name);
				}
			}//BOSS가 아니면
			else {
				if (p->sub.size() == 0) {//부하가 없을 때
					//상관에서 p를 찾고
					vector<TreeNode*>::iterator iter = p->high->sub.begin();
					for (; iter != p->high->sub.end(); iter++) {
						if ((*iter)->name == name)
							break;
					}

					if ((*iter)->name == name) {//부하목록에서 지운다
						p->high->sub.erase(iter);
					}

					delete p;//p를 지운다
				}
				else {//부하가 있으면
					p->name = p->sub[0]->name;//이름바꾸고
					fireSub(p->sub[0], p->sub[0]->name);//바꾼부하를 해고
				}
			}
		}
	}
}

void OrganizationTree::print() {//출력=
	cout << "--------------------------" << endl;
	printSub(root, 0);
	cout << "--------------------------" << endl;
}

void OrganizationTree::printSub(TreeNode* p, int n) {
	if (p != NULL) {//p가 NULL이 아니면
		for (int i = 0; i < n; i++)//n이 곧 level
			cout << "+";//level만큼 +출력
		cout << p->name << endl;//이름 출력
		for (int i = 0; i < p->sub.size(); i++) {//부하직원에 대해서 출력
			printSub(p->sub[i], n + 1);
		}
	}
}

void OrganizationTree::set() {
	string input;
	cout << "Tree is Empty!\nInput CEO Name : ";
	cin >> input;
	root = new TreeNode(input, NULL);//BOSS설정
	people.push_back(input);//사람목록에 추가
}

bool OrganizationTree::isEmpty() {
	return (people.size() == 0);
}

void OrganizationTree::printPeople() {
	cout << "CEO : " << people[0]<<"\n";
	for (int i = 1; i < people.size(); i++)
		cout << people[i] << " ";
	cout << endl;
}

bool OrganizationTree::isExist(string& name) {//존재하는가
	for (int i = 0; i < people.size(); i++) {//목록에서
		if (people[i] == name)//이름이 있으면
			return true;//true
	}
	return false;//false
}

void OrganizationTree::eraseName(string& name) {//이름 지우기
	vector<string>::iterator iter = people.begin();//목록처음부터
	for (; iter != people.end(); iter++) {//찾는다
		if ((*iter) == name)
			break;
	}

	if ((*iter) == name)//이름이같으면
		people.erase(iter);//지운다
}