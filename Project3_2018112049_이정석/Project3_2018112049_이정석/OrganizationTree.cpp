#include "OrganizationTree.h"
#include <iostream>

TreeNode::TreeNode(string& name, TreeNode* high) {//Node������
	this->name = name;
	this->high = high;
}

OrganizationTree::OrganizationTree(string& name) {//������������
	root = new TreeNode(name, NULL);//BOSS����
	people.push_back(name);//�����Ͽ� �߰�
}

void OrganizationTree::hire(string& super, string& sub) {//���
	bool c_s, c_b;//check_super check_sub ����
	c_s = isExist(super); c_b = isExist(sub);

	if (!c_s&&c_b)//����� �������� �ʰ� ���ϰ� �̹� �����ϸ�
		cout << super << " does not exist and " << sub << " does!" << endl;
	else if (!c_s)//����� �������� ������
		cout << super << " does not exist!" << endl;
	else if (c_b)//���ϰ� �̹� �����ϸ�
		cout << sub << " dost exist!" << endl;
	else {//�ƴϸ�
		hireSub(root, super, sub);//����ϱ�
		cout << super << " hires " << sub << endl;
	}
}

void OrganizationTree::hireSub(TreeNode* p, string& super, string& sub) {
	if (p != NULL) {//p�� NULL�� �ƴϸ�
		if (p->name != super) {//����� �ƴϸ�
			for (int i = 0; i < p->sub.size(); i++)
				hireSub(p->sub[i], super, sub);//���Ͽ��� �ٽ� ����
		}
		else {//����̸�
			p->sub.push_back(new TreeNode(sub, p));//������� ���ϸ� �߰�
			people.push_back(sub);//�����Ͽ� �߰�
		}
	}
}

void OrganizationTree::fire(string& name) {//�ذ�
	bool c = isExist(name);//check

	if (!c)//�������� ������
		cout << name << " does not exist!" << endl;
	else {//�����ϸ�
		fireSub(root, name);//�ذ��ϱ�
		eraseName(name);
		cout << "Fire " << name << endl;
	}
}

void OrganizationTree::fireSub(TreeNode* p, string& name) {
	if (p != NULL) {//p�� NULL�� �ƴϸ�
		if (p->name != name) {//ã�� ����� �ƴϸ�
			for (int i = 0; i < p->sub.size(); i++)//���Ͽ��� ã�´�
				fireSub(p->sub[i], name);
		}
		else {//ã������
			if (p == root) {//������°� BOSS��
				if (p->sub.size() == 0) {//BOSSȥ���� ��
					delete p;
					root = NULL;
				}//���ϰ� ���� ��
				else {
					p->name = p->sub[0]->name;
					fireSub(p->sub[0], p->sub[0]->name);
				}
			}//BOSS�� �ƴϸ�
			else {
				if (p->sub.size() == 0) {//���ϰ� ���� ��
					//������� p�� ã��
					vector<TreeNode*>::iterator iter = p->high->sub.begin();
					for (; iter != p->high->sub.end(); iter++) {
						if ((*iter)->name == name)
							break;
					}

					if ((*iter)->name == name) {//���ϸ�Ͽ��� �����
						p->high->sub.erase(iter);
					}

					delete p;//p�� �����
				}
				else {//���ϰ� ������
					p->name = p->sub[0]->name;//�̸��ٲٰ�
					fireSub(p->sub[0], p->sub[0]->name);//�ٲۺ��ϸ� �ذ�
				}
			}
		}
	}
}

void OrganizationTree::print() {//���=
	cout << "--------------------------" << endl;
	printSub(root, 0);
	cout << "--------------------------" << endl;
}

void OrganizationTree::printSub(TreeNode* p, int n) {
	if (p != NULL) {//p�� NULL�� �ƴϸ�
		for (int i = 0; i < n; i++)//n�� �� level
			cout << "+";//level��ŭ +���
		cout << p->name << endl;//�̸� ���
		for (int i = 0; i < p->sub.size(); i++) {//���������� ���ؼ� ���
			printSub(p->sub[i], n + 1);
		}
	}
}

void OrganizationTree::set() {
	string input;
	cout << "Tree is Empty!\nInput CEO Name : ";
	cin >> input;
	root = new TreeNode(input, NULL);//BOSS����
	people.push_back(input);//�����Ͽ� �߰�
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

bool OrganizationTree::isExist(string& name) {//�����ϴ°�
	for (int i = 0; i < people.size(); i++) {//��Ͽ���
		if (people[i] == name)//�̸��� ������
			return true;//true
	}
	return false;//false
}

void OrganizationTree::eraseName(string& name) {//�̸� �����
	vector<string>::iterator iter = people.begin();//���ó������
	for (; iter != people.end(); iter++) {//ã�´�
		if ((*iter) == name)
			break;
	}

	if ((*iter) == name)//�̸��̰�����
		people.erase(iter);//�����
}