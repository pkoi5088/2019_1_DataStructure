#include <string>

using namespace std;

template <class DT>
class MicroFB;
template <class DT>
class Person;

template<class DT>
class NameNode {//각 Person객체에 들어갈 NameNode
private:
	NameNode(DT& name);//생성자

	DT name;
	NameNode<DT>* nextName;//LinkedNode
	NameNode<DT>* priorName;//DoubleLinked

	friend class Person<DT>;
	friend class MicroFB<DT>;
};

template<class DT>
class Person {//Person객체
private:
	Person(DT& name);//생성자

	void insert(NameNode<DT>* node);//Node삽입 함수
	void remove(NameNode<DT>* node);//Node제거 함수
	bool isExist(string name);//name이 존재하는가? >> name과 친구인가?

	DT name;
	Person<DT>* nextPerson;//LinkedNode
	Person<DT>* priorPerson;//Double
	NameNode<DT>* headPerson;//각 사람은 친구목록List를 가진다
	NameNode<DT>* endPerson;

	friend class MicroFB<DT>;
};

template<class DT>
class MicroFB {//MicroFaceBook
public:
	MicroFB();//생성자
	~MicroFB();//소멸자

	void insert(Person<DT>* node);//Node삽입 함수
	void remove(Person<DT>* node);//Node제거 함수
	void clear();//Person목록지우기

	void add(string name);//사람추가
	void follow(string name1, string name2);//친구맺기
	void unfollow(string name1, string name2);//친구끊기
	void printFriend(string name);//친구출력
	void isFriend(string name1, string name2);//친구인가?

private:
	Person<DT>* head;//PersonList
	Person<DT>* end;
};