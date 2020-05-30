#include <string>

using namespace std;

static string month[12] = { "January", "Feburary", "March", "April", "May", "June", "July",
   "August", "September", "October", "November", "December" };
//달을 영어로 한것 배열

static string m[12] = { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY",
   "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };
//달을 영어로 한것 배열(대문자버전)

static int countMon[12] = { 0, };
//달 개수 카운트

static bool isLeapYear(int year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;		// Leap year
	else
		return false;		// Normal years
}
//윤년인가?

static int DaysOfMonth[2][12] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },	//평번한 년도
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }	//윤년
};
//달에 대한 일 수

static void upper(string& n) {
	for (int i = 0; i < n.size(); i++) {
		if (n[i] >= 97 && n[i] <= 122) {
			n[i] = n[i] - 32;
		}
	}
}
//소문자 >> 대문자 형변환

template<class DT>
class AddressBook;

template<class DT>
class ListNode {//ListNode
private:
	ListNode(DT& Name, DT& Phone, DT& Birth, ListNode* next, ListNode* prior);//생성자

	bool strange();//해당 노드가 이상한가?

	DT name, phone;//이름과 핸드폰번호
	int d, m, y;//생일

	ListNode* next;//다음 노드
	ListNode* prior;//이전노드

	friend class AddressBook<DT>;
};

template<class DT>
class AddressBook {//전화번호부
public:
	AddressBook();//생성자
	~AddressBook();//소멸자

	//노드 연산
	void insert(ListNode<DT>* node);//삽입
	void remove(ListNode<DT>* node);//제거

	//전화번호부 연산
	void read();//파일읽기
	void add();//전화번호 추가
	void remove();//전화번호 제거
	void write();//파일 덮어쓰기
	void select();//달 고르기
	void clear();//비우기
	void showStructure();//출력

	bool empty();//비었는가?
	bool full();//가득 찼는가?(Double Linked List라서 false)

private:
	ListNode<DT>* head;//처음 포인터
	ListNode<DT>* end;//끝 포인터
	int cnt;//개수새기
};