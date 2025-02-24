#include<iostream>
#include<string>
using namespace std;
#define Initlen 54

struct LinearList {
	string* lineardata;
	int length;

	LinearList() {
		lineardata = new string[Initlen];
		length = 0;
	}

	void push(string e) {
		lineardata[length] = e;
		length++;
	}

	void Print() {
		for (int i = 0; i < length; i++) {
			cout << lineardata[i] << " ";
		}
		cout << endl;
	}
};

void GiveCard(LinearList& L1) {
	string temp[54] = {
		"A1","A2","A3","A5","A5","A6","A7","A8","A9","A0","AJ","AQ","AK",
		"B1","B2","B3","B5","B5","B6","B7","B8","B9","B0","BJ","BQ","BK",
		"C1","C2","C3","C5","C5","C6","C7","C8","C9","C0","CJ","CQ","CK",
		"D1","D2","D3","D5","D5","D6","D7","D8","D9","D0","DJ","DQ","DK",
		"XX","YY"
	};
	for (int i = 0; i < 54; i++) {
		L1.push(temp[i]);
	}
}

void Fisher_Yates_Shuffle(LinearList& L1, LinearList& L2)
{
	int vis[54] = { 0 };
	//srand((unsigned)time(NULL));
	int k, flag = 0;
	while (1)
	{
		if (flag == 54) break;
		k = rand() % L1.length;
		if (vis[k] == 0) {
			vis[k] = 1;
			L2.push(L1.lineardata[k]);
			flag++;
		}
		else continue;

	}
}

struct RLnode {
	string Listdata;
	RLnode* next;
};
typedef RLnode* RoundList;

struct QueueNode {
	string data;
	QueueNode* next;
};
struct Queue {
	QueueNode* head;
	QueueNode* tail;
	int length;

	Queue() {
		head = new QueueNode;
		tail = head;
		head->next = NULL;
		head->data = "";
		length = 0;
	}

	void Push(string e) {
		if (head->data == "") {
			head->data = e;
		}
		else {
			QueueNode* s = new QueueNode;
			tail->next = s;
			s->data = e;
			s->next = NULL;
			tail = tail->next;
		}
		length++;
	}

	string Top() {
		if (head == NULL) {
			cout << "EMPTY!!!" << endl;
			return "";
		}
		string s;
		s = head->data;
		QueueNode* p = head;
		head = head->next;
		delete p;
		return s;
	}

	void Print() {
		QueueNode* p = head;
		while (head != NULL) {
			cout << head->data << " ";
			head = head->next;
		}
		cout << endl;
		head = p;
	}

	void The_Last_Five_Pokes() {
		while (length > 5) {
			Top();
			length--;
		}
	}

};

struct Stack {
	string data;
	Stack* next;
	int length;
};
typedef Stack* top;

class DoStack {
private:
	top s;
public:
	void Init() {
		s = new Stack;
		s->next = NULL;
		s->data = "";
		s->length = 0;
	}

	void Push(string e) {
		Stack* p = new Stack;
		p->data = e;
		p->next = s->next;
		s->next = p;
		s->length++;
	}

	string Top() {
		string ans = s->next->data;
		Stack* p = s->next;
		s->next = p->next;
		delete p;
		s->length--;
		return ans;
	}

	void Print() {
		Stack* p = s->next;
		while (p != NULL) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

	int Len() {
		return s->length;
	}
};

class DoRL {
private:
	RoundList head;
public:
	void Init() {
		head = new RLnode;
		head->Listdata = "";
		head->next = head;
	}

	void push(string e) {
		if (head->Listdata == "") {
			head->Listdata = e;
		}
		else {
			RLnode* p = head;
			while (head->next != p) {
				head = head->next;
			}
			RLnode* s = new RLnode;
			s->Listdata = e;
			s->next = p;
			head->next = s;
			head = p;
		}
	}

	void Get_Poke_Back(string e) {
		RLnode* s = new RLnode;
		s->Listdata = e;
		s->next = head->next;
		head->next = s;
		head = head->next;
	}

	void Print() {
		cout << head->Listdata << " ";
		RLnode* p = head->next;
		while (p != head) {
			cout << p->Listdata << " ";
			p = p->next;
		}
		cout << endl;
	}

	int Locate() {
		int i = 0;
		int temp = 1;
		RLnode* p = head;
		while (1) {
			if (head->Listdata == "XX" || head->Listdata == "YY") {
				i = temp;
				break;
			}
			head = head->next;
			temp++;
		}
		head = p;
		return i;
	}

	string Ring(Queue& Q, DoStack& S) {
		RLnode* p = head;
		//定位大小王
		int pos = Locate();
		for (int i = 1; i < pos; i++) {
			head = head->next;
		}
		//cout << head->Listdata << endl;
		int m;
		int length = 54;
		cout << "请输入您的m：";
		cin >> m;
		string pan;
		cout << "是否进入附加条件(yes/no):";
		cin >> pan;
		while (length > 1) {
			for (int i = 1; i <= m - 1; i++) {
				head = head->next;
			}
			RLnode* s = head->next;
			//cout << s->Listdata << endl;
			if (s->Listdata[0] == 'A') {
				Q.Push(s->Listdata);
			}

			//打出大小王抽牌回流
			if (pan == "yes") {
				if (s->Listdata != "XX" && s->Listdata != "YY") {
					S.Push(s->Listdata);
				}
				else {
					if (S.Len() <= 5 && S.Len() > 0) {
						for (int i = 0; i < S.Len(); i++) {
							Get_Poke_Back(S.Top());
							length++;
						}
					}
					else if (S.Len() > 5) {
						for (int i = 0; i < 5; i++) {
							Get_Poke_Back(S.Top());
							length++;
						}
					}
					else cout << "EMPTY!!!" << endl;
				}
			}
			head->next = s->next;
			head = head->next;
			delete s;
			length--;
		}
		return head->Listdata;
	}

};

void From_LinearList_To_RLnode(LinearList& L2, DoRL& D) {
	for (int i = 0; i < L2.length; i++) {
		D.push(L2.lineardata[i]);
	}
}


int main() {
	LinearList L1;
	GiveCard(L1);
	cout << "将牌放入顺序表中：" << endl;
	L1.Print();
	LinearList L2;
	Fisher_Yates_Shuffle(L1, L2);
	cout << "打乱牌序后:" << endl;
	L2.Print();
	DoRL D;
	D.Init();
	From_LinearList_To_RLnode(L2, D);
	cout << "将牌放入循环链表中:" << endl;
	D.Print();
	cout << "第一张大小王在：";
	cout << D.Locate() << endl;
	Queue Q;
	DoStack S;
	S.Init();
	cout << D.Ring(Q, S) << endl;
	//D.Print();
	//Q.Print();
	cout << "最后打出的5张A牌：" << endl;
	Q.The_Last_Five_Pokes();
	Q.Print();
	//S.Print();
	return 0;
}