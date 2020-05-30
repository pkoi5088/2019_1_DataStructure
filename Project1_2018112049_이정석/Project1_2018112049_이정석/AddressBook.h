#include <string>

using namespace std;

static string month[12] = { "January", "Feburary", "March", "April", "May", "June", "July",
   "August", "September", "October", "November", "December" };
//���� ����� �Ѱ� �迭

static string m[12] = { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY",
   "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };
//���� ����� �Ѱ� �迭(�빮�ڹ���)

static int countMon[12] = { 0, };
//�� ���� ī��Ʈ

static bool isLeapYear(int year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;		// Leap year
	else
		return false;		// Normal years
}
//�����ΰ�?

static int DaysOfMonth[2][12] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },	//����� �⵵
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }	//����
};
//�޿� ���� �� ��

static void upper(string& n) {
	for (int i = 0; i < n.size(); i++) {
		if (n[i] >= 97 && n[i] <= 122) {
			n[i] = n[i] - 32;
		}
	}
}
//�ҹ��� >> �빮�� ����ȯ

template<class DT>
class AddressBook;

template<class DT>
class ListNode {//ListNode
private:
	ListNode(DT& Name, DT& Phone, DT& Birth, ListNode* next, ListNode* prior);//������

	bool strange();//�ش� ��尡 �̻��Ѱ�?

	DT name, phone;//�̸��� �ڵ�����ȣ
	int d, m, y;//����

	ListNode* next;//���� ���
	ListNode* prior;//�������

	friend class AddressBook<DT>;
};

template<class DT>
class AddressBook {//��ȭ��ȣ��
public:
	AddressBook();//������
	~AddressBook();//�Ҹ���

	//��� ����
	void insert(ListNode<DT>* node);//����
	void remove(ListNode<DT>* node);//����

	//��ȭ��ȣ�� ����
	void read();//�����б�
	void add();//��ȭ��ȣ �߰�
	void remove();//��ȭ��ȣ ����
	void write();//���� �����
	void select();//�� ����
	void clear();//����
	void showStructure();//���

	bool empty();//����°�?
	bool full();//���� á�°�?(Double Linked List�� false)

private:
	ListNode<DT>* head;//ó�� ������
	ListNode<DT>* end;//�� ������
	int cnt;//��������
};