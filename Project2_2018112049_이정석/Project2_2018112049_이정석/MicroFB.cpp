#include "MicroFB.h"
#include <iostream>

//----------NameNode---------------

template<class DT>
NameNode<DT>::NameNode(DT& name) {//������
	this->name = name;//�̸�����
	nextName = priorName = NULL;//������ �ʱ�ȭ
}

//------------Person---------------

template<class DT>
Person<DT>::Person(DT& name) {//������
	this->name = name;//�̸�����
	nextPerson = priorPerson = NULL;//�������ʱ�ȭ
	headPerson = endPerson = NULL;
}

template<class DT>
void Person<DT>::insert(NameNode<DT>* node) {//������
	if (endPerson == NULL) {//List�� ���������
		headPerson = endPerson = node;//head�� end�� node
	}
	else {//������� ������
		endPerson->nextName = node;//���� ����
		node->priorName = endPerson;//node�� ���� end
		endPerson = endPerson->nextName;//end�̵�
	}
}

template<class DT>
void Person<DT>::remove(NameNode<DT>* node) {//������� �Լ�
	if (endPerson != NULL) {//��尡 ������� ������
		if (node->priorName == NULL && node->nextName == NULL) {
			//���ϳ�������
			delete node;
			headPerson = endPerson = NULL;
			//������ �ʱ�ȭ
		}
		else if (node->nextName == NULL) {
			//�����ִ°��϶�
			endPerson = endPerson->priorName;//end�ű��
			endPerson->nextName = NULL;//end������ NULL
			delete node;
		}
		else if (node->priorName == NULL) {
			//����ó�����϶�
			headPerson = headPerson->nextName;//head�ű��
			headPerson->priorName = NULL;//head�� ���� NULL
			delete node;
		}
		else {//�߰�����
			node->priorName->nextName = node->nextName;//��忬��
			node->nextName->priorName = node->priorName;
			delete node;
		}
	}
}

template<class DT>
bool Person<DT>::isExist(string name) {
	NameNode<DT>* tmp = headPerson;//ó������
	while (tmp != NULL) {//NULL�϶�����
		if (tmp->name == name)//�̸��� ������
			return true;//��
		tmp = tmp->nextName;//��������
	}
	return false;
}

//------------MicroFB---------------

template<class DT>
MicroFB<DT>::MicroFB() {//������
	head = end = NULL;//�������ʱ�ȭ
}

template<class DT>
MicroFB<DT>::~MicroFB() {
	clear();
}

template<class DT>
void MicroFB<DT>::insert(Person<DT>* node) {//Person���� �Լ�
	if (end == NULL) {//���������
		head = end = node;//Person����
	}
	else {//�ƴϸ�
		end->nextPerson = node;//���� Person����
		node->priorPerson = end;//node�� ���� end
		end = end->nextPerson;//end�̵�
	}
}

template<class DT>
void MicroFB<DT>::remove(Person<DT>* node) {//Person���� �Լ�
	if (end != NULL) {//�������������
		if (node->priorPerson == NULL && node->nextPerson == NULL) {
			//�ϳ�������
			delete node;
			head = end = NULL;
			//�����ͼ���
		}
		else if (node->nextPerson == NULL) {
			//�����϶�
			end = end->priorPerson;//�����Ϳ���
			end->nextPerson = NULL;
			delete node;
		}
		else if (node->priorPerson == NULL) {
			//ó���϶�
			head = head->nextPerson;//�����Ϳ���
			head->priorPerson = NULL;
			delete node;
		}
		else {
			//�߰��϶�
			node->priorPerson->nextPerson = node->nextPerson;//�����Ϳ���
			node->nextPerson->priorPerson = node->priorPerson;
			delete node;
		}
	}
}

template<class DT>
void MicroFB<DT>::clear() {//����
	Person<DT>* tmp = head;//ó������
	while (tmp != NULL) {//������
		head = head->nextPerson;//�̵���
		delete tmp;//����
		tmp = head;
	}
	head = end = NULL;//������ �ʱ�ȭ
}

template<class DT>
void MicroFB<DT>::add(string name) {//����߰�
	Person<DT>* p = head;//�ִ��� ã��
	while (p != NULL) {//ó������
		if (p->name == name)//�̸��������� �����ͱ״��
			break;
		p = p->nextPerson;
	}

	if (p != NULL) {//�����ϸ�
		cout << name << " is already exist! - Can't add()" << endl;
	}
	else {//�ƴϸ�
		cout << "Added " << name << endl;
		p = new Person<DT>(name);//���θ���
		insert(p);//����
	}
}

template<class DT>
void MicroFB<DT>::follow(string name1, string name2) {//ģ���α� �Լ�
	if (name1 == name2) {//�Է��� �̸��� ������
		cout << "Same inputs! - Can't follow()!" << endl;
		return;
	}//�ƴϸ�
	Person<DT> *p1 = NULL, *p2 = NULL, *tmp = head;
	while (tmp != NULL) {//ó������ ������
		if (tmp->name == name1)//name1�������� ����
			p1 = tmp;
		if (tmp->name == name2)//name2�Ͱ����� ����
			p2 = tmp;
		tmp = tmp->nextPerson;
	}

	if (p1 == NULL && p2 == NULL) {//�Ѵ� ������
		cout << name1 << " and " << name2 << " are not exist! - Can't follow()!" << endl;
	}
	else if (p1 == NULL) {//name1�� ������
		cout << name1 << " is not exist! - Can't follow()!" << endl;
	}
	else if (p2 == NULL) {//name2�� ������
		cout << name2 << " is not exist! - Can't follow()!" << endl;
	}
	else if (p1->isExist(name2)) {//p1�� ģ����Ͽ� name2�� ������
		cout << name1 << " and " << name2 << " are not friends already! - Can't follow()" << endl;
	}
	else {//�� �ƴϸ� ģ��
		cout << "Followed " << name1 << " and " << name2 << endl;
		NameNode<DT> *n1 = new NameNode<DT>(name1),
					*n2 = new NameNode<DT>(name2);//���ο� NameNode
		p1->insert(n2);//������
		p2->insert(n1);
	}
}

template<class DT>
void MicroFB<DT>::unfollow(string name1, string name2) {//ģ�� ����
	if (name1 == name2) {//�Է��� ������
		cout << "Same inputs! - Can't follow()!" << endl; 
		return;
	}
	Person<DT> *p1 = NULL, *p2 = NULL, *tmp = head;
	while (tmp != NULL) {//�̸�ã��
		if (tmp->name == name1)
			p1 = tmp;
		if (tmp->name == name2)
			p2 = tmp;
		tmp = tmp->nextPerson;
	}

	if (p1 == NULL && p2 == NULL) {//�Ѵپ�����
		cout << name1 << " and " << name2 << " are not exist! - Can't unfollow()!" << endl;
	}
	else if (p1 == NULL) {//name1�� ������
		cout << name1 << " is not exist! - Can't unfollow()!" << endl;
	}
	else if (p2 == NULL) {//name2�� ������
		cout << name2 << " is not exist! - Can't unfollow()!" << endl;
	}
	else if (!p1->isExist(name2)) {//p1�� name2�� ������
		cout << name1 << " and " << name2 << " are not friends! - Can't unfollow()!" << endl;
	}
	else {//ģ�� ����
		cout << "Unfollowed " << name1 << " and " << name2 << endl;
		NameNode<DT> *n1 = p1->headPerson, *n2 = p2->headPerson;
		while (n1 != NULL) {//p1, p2�� ���ؼ� NameNodeã��
			if (n1->name == name2)
				break;
			n1 = n1->nextName;
		}

		while (n2 != NULL) {
			if (n2->name == name1)
				break;
			n2 = n2->nextName;
		}
		//�̹� ������ �ִ��� ������ �˻��߱⶧���� ������ �����Ѵ�.
		p1->remove(n1);//Node����
		p2->remove(n2);
	}
}

template<class DT>
void MicroFB<DT>::printFriend(string name) {//ģ�� ���
	Person<DT>* p = head;//���ã��
	while (p != NULL) {
		if (p->name == name)
			break;
		p = p->nextPerson;
	}

	if (p == NULL) {//������ �������� �ʴ´�
		cout << name << " is not exist! - Can't printFriend()!" << endl;
	}
	else if (p->endPerson == NULL) {//ģ������� ���������
		cout << name << " has no friends!" << endl;
	}
	else {//ģ���� ������
		NameNode<DT>* n = p->headPerson;
		cout << name << "'s Friends : ";//name�� ģ���� : 
		while (n != NULL) {
			cout << n->name;//ģ�����
			if (n->nextName != NULL)//���� �ƴϸ� ��ǥ���
				cout << ", ";
			n = n->nextName;//����
		}
		cout << endl;//�ٳѱ��
	}
}

template<class DT>
void MicroFB<DT>::isFriend(string name1, string name2) {//ģ���ΰ�
	if (name1 == name2) {//�Է��� ������
		cout << "Same inputs! - Can't follow()!" << endl; 
		return;
	}
	Person<DT> *p1 = NULL, *p2 = NULL, *tmp = head;
	while (tmp != NULL) {//���ã��
		if (tmp->name == name1)
			p1 = tmp;
		if (tmp->name == name2)
			p2 = tmp;
		tmp = tmp->nextPerson;
	}

	if (p1 == NULL && p2 == NULL) {//�Ѵ� �������� ������
		cout << name1 << " and " << name2 << " are not exist! - Can't isFriend()!" << endl;
	}
	else if (p1 == NULL) {//name1�� ������
		cout << name1 << " is not exist! - Can't isFriend()!" << endl;
	}
	else if (p2 == NULL) {//name2�� ������
		cout << name2 << " is not exist! - Can't isFriend()!" << endl;
	}
	else if (p1->isExist(name2)) {//p1�� ģ����Ͽ� name2�� ������
		cout << name1 << " and " << name2 << " are friends!" << endl;
	}
	else {//������
		cout << name1 << " and " << name2 << " are not friends!" << endl;
	}
}