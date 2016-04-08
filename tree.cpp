#include<iostream>
#include<cstdio>
#pragma warning(disable:4996)
using namespace std;
#define MAX 10100000
#define Alpha 0.75
#define MID(l,r) (l+r)>>1
int max(int x, int y) {
	if (x > y) return x;
	else return y;
}
class ScaTree{
private:
	struct Node {
		int size;
		int value;
		int data;
		Node* Left;
		Node* Right;

		void New(int value, int data) {
			this->value = value;
			this->data = data;
			this->size = 1;
			this->Left = NULL;
			this->Right = NULL;
		}
	};

	Node  s_node[MAX];
	Node* s_cache[MAX];
	Node* s_root;
	int   s_cnt;
	int   s_size;

	Node* NewNode(int value, int data) {
		s_size++;
		s_node[s_size].New(value, data);
		return &s_node[s_size];
	}
	Node* Search(Node* node, int value) {
		if (value < node->value) {
			return Search(node->Left, value);
		}
		else if (value > node->value) {
			return Search(node->Right, value);
		}
		else return node;
	}
	int   size(Node* node) {
		if (node) return node->size;
		else return 0;
	}
	void  UpData(Node* node) {
		if (node) {
			node->size = size(node->Left) + size(node->Right) + 1;
		}
	}
	void  FollowMid(Node* node) {
		if (!node) return;
		FollowMid(node->Left);
		s_cnt++;
		s_cache[s_cnt] = node;
		FollowMid(node->Right);
	}

	Node* Rebulid(int l, int r) {
		if (l > r) return NULL;
		Node* node;
		int mid = MID(l, r);
		node = s_cache[mid];
		node->Left = Rebulid(l, mid - 1);
		node->Right = Rebulid(mid + 1, r);
		UpData(node);
		return node;
	}
	void  Sca(Node* &node, int value) {
		if (!node) return;
		if (value < node->value) {
			if (size(node->Left)>size(node)*Alpha) {
				s_cnt = 0;
				FollowMid(node);
				node = Rebulid(1,s_cnt);
				return;
			}
			Sca(node->Left, value);
		}
		else {
			if (size(node->Right)>size(node)*Alpha) {
				s_cnt = 0;
				FollowMid(node);
				node = Rebulid(1, s_cnt);
				return;
			}
			Sca(node->Right, value);
		}
	}
	void  Insert(Node* &node, int value, int data, bool Need) {
		if (!node) {
			node = NewNode(value, data);
			return;
		}
		if (value < node->value) {
			Insert(node->Left, value, data, Need);
			UpData(node);
		}
		else if (value > node->value) {
			Insert(node->Right, value, data, Need);
			UpData(node);
		}
		else {
			node->data = data;
		}
		if (Need && max(size(node->Left), size(node->Right)) > Alpha*size(node)) {
			s_cnt = 0;
			FollowMid(node);
			node = Rebulid(1, s_cnt);
			Need = false;
		}
	}


public:
	void  Insert(int value, int data) {
		Insert(s_root, value, data, true);
		//Sca(s_root, value);
	}
	Node* Search(int value) {
		return Search(s_root, value);
	}
};
ScaTree s;
inline int read()
{
	int x = 0;
	int f = 1;
	char ch = getchar();
	while (ch<'0' || ch>'9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x*f;
}
int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	char ch;
	while (scanf("%c", &ch) != EOF) {
		if (ch == 'A') {
			int ID = read();
			int Value = read();
			s.Insert(ID, Value);

		}
		else
			if (ch == 'Q') {
				int ID = read();
				printf("%d\n", s.Search(ID)->data);
			}
	}
	//system("pause");
}

