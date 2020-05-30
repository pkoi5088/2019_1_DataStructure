#include "MicroFB.h"
#include <iostream>

//----------NameNode---------------

template<class DT>
NameNode<DT>::NameNode(DT& name) {//생성자
	this->name = name;//이름설정
	nextName = priorName = NULL;//포인터 초기화
}

//------------Person---------------

template<class DT>
Person<DT>::Person(DT& name) {//생성자
	this->name = name;//이름설정
	nextPerson = priorPerson = NULL;//포인터초기화
	headPerson = endPerson = NULL;
}

template<class DT>
void Person<DT>::insert(NameNode<DT>* node) {//노드삽입
	if (endPerson == NULL) {//List가 비어있으면
		headPerson = endPerson = node;//head와 end는 node
	}
	else {//비어있지 않으면
		endPerson->nextName = node;//끝에 삽입
		node->priorName = endPerson;//node의 전은 end
		endPerson = endPerson->nextName;//end이동
	}
}

template<class DT>
void Person<DT>::remove(NameNode<DT>* node) {//노드제거 함수
	if (endPerson != NULL) {//노드가 비어있지 않으면
		if (node->priorName == NULL && node->nextName == NULL) {
			//단하나있을때
			delete node;
			headPerson = endPerson = NULL;
			//포인터 초기화
		}
		else if (node->nextName == NULL) {
			//끝에있는것일때
			endPerson = endPerson->priorName;//end옮기기
			endPerson->nextName = NULL;//end다음은 NULL
			delete node;
		}
		else if (node->priorName == NULL) {
			//제일처음것일때
			headPerson = headPerson->nextName;//head옮기기
			headPerson->priorName = NULL;//head의 전은 NULL
			delete node;
		}
		else {//중간삭제
			node->priorName->nextName = node->nextName;//노드연산
			node->nextName->priorName = node->priorName;
			delete node;
		}
	}
}

template<class DT>
bool Person<DT>::isExist(string name) {
	NameNode<DT>* tmp = headPerson;//처음부터
	while (tmp != NULL) {//NULL일때까지
		if (tmp->name == name)//이름이 같으면
			return true;//참
		tmp = tmp->nextName;//다음으로
	}
	return false;
}

//------------MicroFB---------------

template<class DT>
MicroFB<DT>::MicroFB() {//생성자
	head = end = NULL;//포인터초기화
}

template<class DT>
MicroFB<DT>::~MicroFB() {
	clear();
}

template<class DT>
void MicroFB<DT>::insert(Person<DT>* node) {//Person삽입 함수
	if (end == NULL) {//비어있으면
		head = end = node;//Person설정
	}
	else {//아니면
		end->nextPerson = node;//끝에 Person삽입
		node->priorPerson = end;//node의 전은 end
		end = end->nextPerson;//end이동
	}
}

template<class DT>
void MicroFB<DT>::remove(Person<DT>* node) {//Person제거 함수
	if (end != NULL) {//비어있지않으면
		if (node->priorPerson == NULL && node->nextPerson == NULL) {
			//하나있을때
			delete node;
			head = end = NULL;
			//포인터수정
		}
		else if (node->nextPerson == NULL) {
			//끝에일때
			end = end->priorPerson;//포인터연산
			end->nextPerson = NULL;
			delete node;
		}
		else if (node->priorPerson == NULL) {
			//처음일때
			head = head->nextPerson;//포인터연산
			head->priorPerson = NULL;
			delete node;
		}
		else {
			//중간일때
			node->priorPerson->nextPerson = node->nextPerson;//포인터연산
			node->nextPerson->priorPerson = node->priorPerson;
			delete node;
		}
	}
}

template<class DT>
void MicroFB<DT>::clear() {//비우기
	Person<DT>* tmp = head;//처음부터
	while (tmp != NULL) {//끝까지
		head = head->nextPerson;//이동후
		delete tmp;//삭제
		tmp = head;
	}
	head = end = NULL;//포인터 초기화
}

template<class DT>
void MicroFB<DT>::add(string name) {//사람추가
	Person<DT>* p = head;//있는지 찾기
	while (p != NULL) {//처음부터
		if (p->name == name)//이름이있으면 포인터그대로
			break;
		p = p->nextPerson;
	}

	if (p != NULL) {//존재하면
		cout << name << " is already exist! - Can't add()" << endl;
	}
	else {//아니면
		cout << "Added " << name << endl;
		p = new Person<DT>(name);//새로만들어서
		insert(p);//삽입
	}
}

template<class DT>
void MicroFB<DT>::follow(string name1, string name2) {//친구맺기 함수
	if (name1 == name2) {//입력한 이름이 같으면
		cout << "Same inputs! - Can't follow()!" << endl;
		return;
	}//아니면
	Person<DT> *p1 = NULL, *p2 = NULL, *tmp = head;
	while (tmp != NULL) {//처음부터 끝까지
		if (tmp->name == name1)//name1과같으면 대입
			p1 = tmp;
		if (tmp->name == name2)//name2와같으면 대입
			p2 = tmp;
		tmp = tmp->nextPerson;
	}

	if (p1 == NULL && p2 == NULL) {//둘다 없으면
		cout << name1 << " and " << name2 << " are not exist! - Can't follow()!" << endl;
	}
	else if (p1 == NULL) {//name1이 없으면
		cout << name1 << " is not exist! - Can't follow()!" << endl;
	}
	else if (p2 == NULL) {//name2가 없으면
		cout << name2 << " is not exist! - Can't follow()!" << endl;
	}
	else if (p1->isExist(name2)) {//p1의 친구목록에 name2가 있으면
		cout << name1 << " and " << name2 << " are not friends already! - Can't follow()" << endl;
	}
	else {//다 아니면 친구
		cout << "Followed " << name1 << " and " << name2 << endl;
		NameNode<DT> *n1 = new NameNode<DT>(name1),
					*n2 = new NameNode<DT>(name2);//새로운 NameNode
		p1->insert(n2);//노드삽입
		p2->insert(n1);
	}
}

template<class DT>
void MicroFB<DT>::unfollow(string name1, string name2) {//친구 끊기
	if (name1 == name2) {//입력이 같으면
		cout << "Same inputs! - Can't follow()!" << endl; 
		return;
	}
	Person<DT> *p1 = NULL, *p2 = NULL, *tmp = head;
	while (tmp != NULL) {//이름찾기
		if (tmp->name == name1)
			p1 = tmp;
		if (tmp->name == name2)
			p2 = tmp;
		tmp = tmp->nextPerson;
	}

	if (p1 == NULL && p2 == NULL) {//둘다없으면
		cout << name1 << " and " << name2 << " are not exist! - Can't unfollow()!" << endl;
	}
	else if (p1 == NULL) {//name1이 업으면
		cout << name1 << " is not exist! - Can't unfollow()!" << endl;
	}
	else if (p2 == NULL) {//name2가 없으면
		cout << name2 << " is not exist! - Can't unfollow()!" << endl;
	}
	else if (!p1->isExist(name2)) {//p1에 name2가 없으면
		cout << name1 << " and " << name2 << " are not friends! - Can't unfollow()!" << endl;
	}
	else {//친구 끝기
		cout << "Unfollowed " << name1 << " and " << name2 << endl;
		NameNode<DT> *n1 = p1->headPerson, *n2 = p2->headPerson;
		while (n1 != NULL) {//p1, p2에 대해서 NameNode찾기
			if (n1->name == name2)
				break;
			n1 = n1->nextName;
		}

		while (n2 != NULL) {
			if (n2->name == name1)
				break;
			n2 = n2->nextName;
		}
		//이미 위에서 있는지 없는지 검사했기때문에 무조건 존재한다.
		p1->remove(n1);//Node제거
		p2->remove(n2);
	}
}

template<class DT>
void MicroFB<DT>::printFriend(string name) {//친구 출력
	Person<DT>* p = head;//사람찾기
	while (p != NULL) {
		if (p->name == name)
			break;
		p = p->nextPerson;
	}

	if (p == NULL) {//없으면 존재하지 않는다
		cout << name << " is not exist! - Can't printFriend()!" << endl;
	}
	else if (p->endPerson == NULL) {//친구목록이 비어있으면
		cout << name << " has no friends!" << endl;
	}
	else {//친구가 있으면
		NameNode<DT>* n = p->headPerson;
		cout << name << "'s Friends : ";//name의 친구들 : 
		while (n != NULL) {
			cout << n->name;//친구출력
			if (n->nextName != NULL)//끝이 아니면 쉼표찍기
				cout << ", ";
			n = n->nextName;//다음
		}
		cout << endl;//줄넘기기
	}
}

template<class DT>
void MicroFB<DT>::isFriend(string name1, string name2) {//친구인가
	if (name1 == name2) {//입력이 같을때
		cout << "Same inputs! - Can't follow()!" << endl; 
		return;
	}
	Person<DT> *p1 = NULL, *p2 = NULL, *tmp = head;
	while (tmp != NULL) {//사람찾기
		if (tmp->name == name1)
			p1 = tmp;
		if (tmp->name == name2)
			p2 = tmp;
		tmp = tmp->nextPerson;
	}

	if (p1 == NULL && p2 == NULL) {//둘다 존재하지 않을때
		cout << name1 << " and " << name2 << " are not exist! - Can't isFriend()!" << endl;
	}
	else if (p1 == NULL) {//name1이 없을때
		cout << name1 << " is not exist! - Can't isFriend()!" << endl;
	}
	else if (p2 == NULL) {//name2가 없을때
		cout << name2 << " is not exist! - Can't isFriend()!" << endl;
	}
	else if (p1->isExist(name2)) {//p1의 친구목록에 name2가 있을때
		cout << name1 << " and " << name2 << " are friends!" << endl;
	}
	else {//없을때
		cout << name1 << " and " << name2 << " are not friends!" << endl;
	}
}