#include "AddressBook.h"
#include <iostream>
#include <fstream>

using namespace std;

template<class DT>
ListNode<DT>::ListNode(DT& Name, DT& Phone, DT& Birth, ListNode* next, ListNode* prior) {//ListNode 생성자
	name = Name;//이름
	phone = Phone;//번호

	m = ((int)Birth[0] - '0') * 10 + (int)Birth[1] - '0';//배열에서 연산
	d = ((int)Birth[3] - '0') * 10 + (int)Birth[4] - '0';
	y = ((int)Birth[6] - '0') * 1000 +
		((int)Birth[7] - '0') * 100 +
		((int)Birth[8] - '0') * 10 +
		((int)Birth[9] - '0');

	this->next = next;//다음노드
	this->prior = prior;//이전 노드
}

template<class DT>
bool ListNode<DT>::strange() {//노드가 이상한가
	if ((m < 1 || m>12) || (d > DaysOfMonth[isLeapYear(y)][m - 1] || d < 0)) {
		return true;//달이 1미만 12초과거나 일이 달에 맞지 않으면 참 
	}
	return false;//아니면 거짓
}

template<class DT>
AddressBook<DT>::AddressBook() {//전화번호부 생성자
	head = end = NULL;
	cnt = 0;
}

template<class DT>
AddressBook<DT>::~AddressBook() {//소멸자
	clear();
}

template<class DT>
void AddressBook<DT>::insert(ListNode<DT>* node) {//노드 삽입
	if (end == NULL) {//끝이 NULL이다 = List가 비어있다
		head = end = node;
	}
	else {//아니면 끝에서 넣기
		end->next = node;
		node->prior = end;
		end = end->next;
	}
}

template<class DT>
void AddressBook<DT>::remove(ListNode<DT>* node) {//노드 제거
	if (!empty()) {//비어있지많으면
		if (node->prior == NULL && node->next == NULL) {//마지막으로 남은 노드를 제거할 때
			delete head;//head를 delete
			head = end = NULL;//NULL로 초기화
		}
		else if (node->next == NULL) {//가장 끝부분을 제거할 때
			ListNode<DT>* tmp = end;//임시노드 tmp
			end = end->prior;//end는 전으로 이동
			end->next = NULL;//end의 next는 NULL
			delete tmp;//tmp 제거
		}
		else if (node->prior == NULL) {//맨 처음것을 제거할 때
			ListNode<DT>* tmp = head;//임시노드 tmp
			head = head->next;//head는 next로이동
			head->prior == NULL;//prior는 NULL
			delete tmp;//tmp 제거
		}
		else {//가운데있는거 제거
			ListNode<DT>* tmp = node;//임시노드 tmp
			node->prior->next = node->next;//전의 다음은 지금의 다음
			node->next->prior = node->prior;//다음의 전은 지금의 전
			delete tmp;//tmp 제거
		}
	}
}

template<class DT>
void AddressBook<DT>::read() {//파일 읽기
	string fileName, in_name, in_phone, in_birth;
	cout << "Enter the name of the file : ";
	cin.ignore();
	getline(cin, fileName);//파일이름 입력

	ifstream in(fileName + ".txt");
	if (in.is_open()) {
		clear();//비우고
		bool c = false;
		while (!in.eof()) {//파일 끝까지
			getline(in, in_name);//이름
			getline(in, in_phone);//전화번호
			getline(in, in_birth);//생일 입력
			in.ignore();
			
			if (in_name.size() != 0 && in_phone.size() != 0 && in_birth.size() != 0) {
				//입력이 정상적이면
				ListNode<DT>* tmp = new ListNode<DT>(in_name, in_phone, in_birth, NULL, NULL);
				//노드생성
				if (tmp->strange()) {
					//노드가 이상하면
					delete tmp;//삭제
					c = true;//이상한거 체크변수
				}
				else {//정상이면
					insert(tmp);//삽입
					countMon[tmp->m - 1]++;//count하기
					cnt++;
				}
			}
			else {
				c = true;
			}
		}
		if (c)//이상한것을 감지했으면
			cout << "Strange information exists!" << endl;
		showStructure();//출력
		in.close();
	}
	else {//파일이 안열렸다!
		cout << "File Can't Open!" << endl;
	}
}

template<class DT>
void AddressBook<DT>::add() {//전화번호 추가
	if (full()) {
		cout << "AdressBook is Full!" << endl;
	}
	else {
		string in_name, in_phone, in_birth;
		cout << "Add an entry : " << endl;
		cout << "Name : ";//이름 입력
		cin.ignore();
		getline(cin, in_name);
		cout << "Phone : ";//전화번호 입력
		getline(cin, in_phone);
		cout << "Birthday : ";//생일 입력
		getline(cin, in_birth);

		if (in_name.size() != 0 && in_phone.size() != 0 && in_birth.size() != 0) {
			//입력이 이상하면
			ListNode<DT>* tmp = new ListNode<DT>(in_name, in_phone, in_birth, NULL, NULL);
			//노드생성
			if (tmp->strange()) {
				//노드가 이상하면 삭제
				delete tmp;
				cout<<"\nThe information you entered is not valid!\n" << endl;
				//당신이 입력한 정보는 이상합니다!
			}
			else {//정상이면
				insert(tmp);//삽입
				countMon[tmp->m - 1]++;//카운트
				cnt++;
			}
		}
		else {//입력한 정보가 이상하면 출력
			cout << "\nThe information you entered is not valid!\n" << endl;
		}
	}
	showStructure();//출력
}

template<class DT>
void AddressBook<DT>::remove() {//전화번호 제거
	if (empty()) {//비어있으면
		cout << "AdressBook is Empty!" << endl;
	}
	else {//아니면
		string in_name;
		cout << "Remove an entry : " << endl;
		cout << "Name : ";
		cin.ignore();
		getline(cin, in_name);//이름 입력

		ListNode<DT>* tmp = head;//처음부터
		while (tmp != NULL) {//NULL아닐때까지
			if (tmp->name == in_name) {//이름이 같으면
				countMon[tmp->m - 1]--;//카운트 연산
				cnt--;
				remove(tmp);//노드제거
				tmp = NULL;
				break;//반복문탈출
			}
			tmp = tmp->next;
		}
	}
	showStructure();//출력
}

template<class DT>
void AddressBook<DT>::write() {//파일 덮어쓰기
	string out_name;
	cout << "Enter the name of the file : ";
	cin >> out_name;//쓸 파일 이름
	ofstream o(out_name + ".txt");

	ListNode<DT>* tmp = head;//처음부터
	while (tmp != NULL) {//tmp가 NULL이 아닐동안
		o << tmp->name << endl;
		o << tmp->phone << endl;
		o.width(2);//생일 입력부
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
		if (tmp->next != NULL)//끝차례가 아니면 한줄 옮기기
			o << endl;
		tmp = tmp->next;
	}
	cout << "The list is written into " << out_name << "." << endl;//덮어쓰기 끝
}

template<class DT>
void AddressBook<DT>::select() {//달고르기
	string s;
	int i;
	cout << "Enter the selected month : ";
	cin.ignore();
	getline(cin, s);
	upper(s);//소문자를 대문자로!
	for (i = 0; i < 12; i++) {//달 찾기
		if (s == m[i])
			break;
	}
	
	if (i != 12) {//달이 존재하면
		cout << "Total number of birthdays in " << month[i] << " : " << countMon[i] << endl;
		ListNode<DT>* tmp = head;//처음부터
		while (tmp != NULL) {//끝까지
			if (tmp->m == i + 1) {//월이 같으면 출력
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
	else {//입력을 잘못했으면
		cout << "Strange Month!!" << endl;
	}
}

template<class DT>
void AddressBook<DT>::clear() {//전화목록 지우기
	ListNode<DT>* tmp = head;//처음부터
	while (tmp != NULL) {//delete연산
		head = head->next;
		delete tmp;
		tmp = head;
	}
	head = end = NULL;//NULL로 초기화
	cnt = 0;
	for (int i = 0; i < 12; i++) {//카운트 초기화
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
void AddressBook<DT>::showStructure() {//출력
	cout << "Total number of entries in the list : " << cnt << endl;
	//리스트에있는 전체 개수
	if (cnt != 0) {//0개가 아니면
		cout << "Number of birthdays in" << endl;
		for (int i = 0; i < 12; i++) {//각 월별로 출력
			if (countMon[i] != 0)
				cout << "\t" << month[i] << " : " << countMon[i] << endl;
		}
	}
}