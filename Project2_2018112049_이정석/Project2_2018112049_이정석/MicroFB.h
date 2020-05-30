#include <string>

using namespace std;

template <class DT>
class MicroFB;
template <class DT>
class Person;

template<class DT>
class NameNode {//�� Person��ü�� �� NameNode
private:
	NameNode(DT& name);//������

	DT name;
	NameNode<DT>* nextName;//LinkedNode
	NameNode<DT>* priorName;//DoubleLinked

	friend class Person<DT>;
	friend class MicroFB<DT>;
};

template<class DT>
class Person {//Person��ü
private:
	Person(DT& name);//������

	void insert(NameNode<DT>* node);//Node���� �Լ�
	void remove(NameNode<DT>* node);//Node���� �Լ�
	bool isExist(string name);//name�� �����ϴ°�? >> name�� ģ���ΰ�?

	DT name;
	Person<DT>* nextPerson;//LinkedNode
	Person<DT>* priorPerson;//Double
	NameNode<DT>* headPerson;//�� ����� ģ�����List�� ������
	NameNode<DT>* endPerson;

	friend class MicroFB<DT>;
};

template<class DT>
class MicroFB {//MicroFaceBook
public:
	MicroFB();//������
	~MicroFB();//�Ҹ���

	void insert(Person<DT>* node);//Node���� �Լ�
	void remove(Person<DT>* node);//Node���� �Լ�
	void clear();//Person��������

	void add(string name);//����߰�
	void follow(string name1, string name2);//ģ���α�
	void unfollow(string name1, string name2);//ģ������
	void printFriend(string name);//ģ�����
	void isFriend(string name1, string name2);//ģ���ΰ�?

private:
	Person<DT>* head;//PersonList
	Person<DT>* end;
};