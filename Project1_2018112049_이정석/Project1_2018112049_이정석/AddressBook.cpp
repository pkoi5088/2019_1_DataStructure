#include "AddressBook.h"
#include <iostream>
#include <fstream>

using namespace std;

template<class DT>
ListNode<DT>::ListNode(DT& Name, DT& Phone, DT& Birth, ListNode* next, ListNode* prior) {//ListNode ������
	name = Name;//�̸�
	phone = Phone;//��ȣ

	m = ((int)Birth[0] - '0') * 10 + (int)Birth[1] - '0';//�迭���� ����
	d = ((int)Birth[3] - '0') * 10 + (int)Birth[4] - '0';
	y = ((int)Birth[6] - '0') * 1000 +
		((int)Birth[7] - '0') * 100 +
		((int)Birth[8] - '0') * 10 +
		((int)Birth[9] - '0');

	this->next = next;//�������
	this->prior = prior;//���� ���
}

template<class DT>
bool ListNode<DT>::strange() {//��尡 �̻��Ѱ�
	if ((m < 1 || m>12) || (d > DaysOfMonth[isLeapYear(y)][m - 1] || d < 0)) {
		return true;//���� 1�̸� 12�ʰ��ų� ���� �޿� ���� ������ �� 
	}
	return false;//�ƴϸ� ����
}

template<class DT>
AddressBook<DT>::AddressBook() {//��ȭ��ȣ�� ������
	head = end = NULL;
	cnt = 0;
}

template<class DT>
AddressBook<DT>::~AddressBook() {//�Ҹ���
	clear();
}

template<class DT>
void AddressBook<DT>::insert(ListNode<DT>* node) {//��� ����
	if (end == NULL) {//���� NULL�̴� = List�� ����ִ�
		head = end = node;
	}
	else {//�ƴϸ� ������ �ֱ�
		end->next = node;
		node->prior = end;
		end = end->next;
	}
}

template<class DT>
void AddressBook<DT>::remove(ListNode<DT>* node) {//��� ����
	if (!empty()) {//�������������
		if (node->prior == NULL && node->next == NULL) {//���������� ���� ��带 ������ ��
			delete head;//head�� delete
			head = end = NULL;//NULL�� �ʱ�ȭ
		}
		else if (node->next == NULL) {//���� ���κ��� ������ ��
			ListNode<DT>* tmp = end;//�ӽó�� tmp
			end = end->prior;//end�� ������ �̵�
			end->next = NULL;//end�� next�� NULL
			delete tmp;//tmp ����
		}
		else if (node->prior == NULL) {//�� ó������ ������ ��
			ListNode<DT>* tmp = head;//�ӽó�� tmp
			head = head->next;//head�� next���̵�
			head->prior == NULL;//prior�� NULL
			delete tmp;//tmp ����
		}
		else {//����ִ°� ����
			ListNode<DT>* tmp = node;//�ӽó�� tmp
			node->prior->next = node->next;//���� ������ ������ ����
			node->next->prior = node->prior;//������ ���� ������ ��
			delete tmp;//tmp ����
		}
	}
}

template<class DT>
void AddressBook<DT>::read() {//���� �б�
	string fileName, in_name, in_phone, in_birth;
	cout << "Enter the name of the file : ";
	cin.ignore();
	getline(cin, fileName);//�����̸� �Է�

	ifstream in(fileName + ".txt");
	if (in.is_open()) {
		clear();//����
		bool c = false;
		while (!in.eof()) {//���� ������
			getline(in, in_name);//�̸�
			getline(in, in_phone);//��ȭ��ȣ
			getline(in, in_birth);//���� �Է�
			in.ignore();
			
			if (in_name.size() != 0 && in_phone.size() != 0 && in_birth.size() != 0) {
				//�Է��� �������̸�
				ListNode<DT>* tmp = new ListNode<DT>(in_name, in_phone, in_birth, NULL, NULL);
				//������
				if (tmp->strange()) {
					//��尡 �̻��ϸ�
					delete tmp;//����
					c = true;//�̻��Ѱ� üũ����
				}
				else {//�����̸�
					insert(tmp);//����
					countMon[tmp->m - 1]++;//count�ϱ�
					cnt++;
				}
			}
			else {
				c = true;
			}
		}
		if (c)//�̻��Ѱ��� ����������
			cout << "Strange information exists!" << endl;
		showStructure();//���
		in.close();
	}
	else {//������ �ȿ��ȴ�!
		cout << "File Can't Open!" << endl;
	}
}

template<class DT>
void AddressBook<DT>::add() {//��ȭ��ȣ �߰�
	if (full()) {
		cout << "AdressBook is Full!" << endl;
	}
	else {
		string in_name, in_phone, in_birth;
		cout << "Add an entry : " << endl;
		cout << "Name : ";//�̸� �Է�
		cin.ignore();
		getline(cin, in_name);
		cout << "Phone : ";//��ȭ��ȣ �Է�
		getline(cin, in_phone);
		cout << "Birthday : ";//���� �Է�
		getline(cin, in_birth);

		if (in_name.size() != 0 && in_phone.size() != 0 && in_birth.size() != 0) {
			//�Է��� �̻��ϸ�
			ListNode<DT>* tmp = new ListNode<DT>(in_name, in_phone, in_birth, NULL, NULL);
			//������
			if (tmp->strange()) {
				//��尡 �̻��ϸ� ����
				delete tmp;
				cout<<"\nThe information you entered is not valid!\n" << endl;
				//����� �Է��� ������ �̻��մϴ�!
			}
			else {//�����̸�
				insert(tmp);//����
				countMon[tmp->m - 1]++;//ī��Ʈ
				cnt++;
			}
		}
		else {//�Է��� ������ �̻��ϸ� ���
			cout << "\nThe information you entered is not valid!\n" << endl;
		}
	}
	showStructure();//���
}

template<class DT>
void AddressBook<DT>::remove() {//��ȭ��ȣ ����
	if (empty()) {//���������
		cout << "AdressBook is Empty!" << endl;
	}
	else {//�ƴϸ�
		string in_name;
		cout << "Remove an entry : " << endl;
		cout << "Name : ";
		cin.ignore();
		getline(cin, in_name);//�̸� �Է�

		ListNode<DT>* tmp = head;//ó������
		while (tmp != NULL) {//NULL�ƴҶ�����
			if (tmp->name == in_name) {//�̸��� ������
				countMon[tmp->m - 1]--;//ī��Ʈ ����
				cnt--;
				remove(tmp);//�������
				tmp = NULL;
				break;//�ݺ���Ż��
			}
			tmp = tmp->next;
		}
	}
	showStructure();//���
}

template<class DT>
void AddressBook<DT>::write() {//���� �����
	string out_name;
	cout << "Enter the name of the file : ";
	cin >> out_name;//�� ���� �̸�
	ofstream o(out_name + ".txt");

	ListNode<DT>* tmp = head;//ó������
	while (tmp != NULL) {//tmp�� NULL�� �ƴҵ���
		o << tmp->name << endl;
		o << tmp->phone << endl;
		o.width(2);//���� �Էº�
		o.fill('0');
		o << tmp->m << '/';
		o.width(2);
		o.fill('0');
		o << tmp->d << '/';
		o.width(4);
		o.fill('0');
		o.fill('0');
		o.fill('0');
		o.fill('0');
		o << tmp->y << endl;
		if (tmp->next != NULL)//�����ʰ� �ƴϸ� ���� �ű��
			o << endl;
		tmp = tmp->next;
	}
	cout << "The list is written into " << out_name << "." << endl;//����� ��
}

template<class DT>
void AddressBook<DT>::select() {//�ް���
	string s;
	int i;
	cout << "Enter the selected month : ";
	cin.ignore();
	getline(cin, s);
	upper(s);//�ҹ��ڸ� �빮�ڷ�!
	for (i = 0; i < 12; i++) {//�� ã��
		if (s == m[i])
			break;
	}
	
	if (i != 12) {//���� �����ϸ�
		cout << "Total number of birthdays in " << month[i] << " : " << countMon[i] << endl;
		ListNode<DT>* tmp = head;//ó������
		while (tmp != NULL) {//������
			if (tmp->m == i + 1) {//���� ������ ���
				cout << tmp->name << endl << tmp->phone << endl;
				cout.width(2);
				cout.fill('0');
				cout << tmp->m << '/';
				cout.width(2);
				cout.fill('0');
				cout << tmp->d << '/';
				cout.width(4);
				cout.fill('0');
				cout.fill('0');
				cout.fill('0');
				cout.fill('0');
				cout << tmp->y << endl << endl;
			}
			tmp = tmp->next;
		}
	}
	else {//�Է��� �߸�������
		cout << "Strange Month!!" << endl;
	}
}

template<class DT>
void AddressBook<DT>::clear() {//��ȭ��� �����
	ListNode<DT>* tmp = head;//ó������
	while (tmp != NULL) {//delete����
		head = head->next;
		delete tmp;
		tmp = head;
	}
	head = end = NULL;//NULL�� �ʱ�ȭ
	cnt = 0;
	for (int i = 0; i < 12; i++) {//ī��Ʈ �ʱ�ȭ
		countMon[i] = 0;
	}
}

template<class DT>
bool AddressBook<DT>::empty() {
	return (head == NULL);
}

template<class DT>
bool AddressBook<DT>::full() {
	return false;
}

template<class DT>
void AddressBook<DT>::showStructure() {//���
	cout << "Total number of entries in the list : " << cnt << endl;
	//����Ʈ���ִ� ��ü ����
	if (cnt != 0) {//0���� �ƴϸ�
		cout << "Number of birthdays in" << endl;
		for (int i = 0; i < 12; i++) {//�� ������ ���
			if (countMon[i] != 0)
				cout << "\t" << month[i] << " : " << countMon[i] << endl;
		}
	}
}