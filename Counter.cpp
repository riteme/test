/**********************************
    Problem: NOI2004 郁闷的出纳员
    Date:    2016. 05. 14
**********************************/
// #include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
struct Node {
    int Parent;
    int Left;
    int Right;
    int Val;
    int Size;
};

static Node s[200005];

static int root, Index, Max;     // Max是工资最多的人
static int N, MIN, Ans, Change;  // Change是工资变动

void Clean(int &Index) {
    for (int i = 0; i <= Index; i++) {
        s[i].Parent = 0;
        s[i].Left = 0;
        s[i].Right = 0;
        s[i].Val = 0;
        s[i].Size = 0;
    }
    root = -1;
    Index = 0;
    Max = -10000000;
}

int Getsize(int p) {
    if (p > 0)
        return s[p].Size;
    return 0;
}

void Update(int p) {
    s[p].Size = 1;
    s[p].Size += Getsize(s[p].Left);
    s[p].Size += Getsize(s[p].Right);
}

void ZIG(int p, int parent, int grand) {
    s[parent].Parent = p;
    s[parent].Left = s[p].Right;
    s[s[parent].Left].Parent = parent;
    s[p].Parent = grand;
    s[p].Right = parent;
    if (grand > 0) {
        if (parent == s[grand].Left)
            s[grand].Left = p;
        else
            s[grand].Right = p;
    }
    Update(parent);
    Update(p);
}

void ZAG(int p, int parent, int grand) {
    s[parent].Parent = p;
    s[parent].Right = s[p].Left;
    s[s[parent].Right].Parent = parent;
    s[p].Parent = grand;
    s[p].Left = parent;
    if (grand > 0) {
        if (parent == s[grand].Left)
            s[grand].Left = p;
        else
            s[grand].Right = p;
    }
    Update(parent);
    Update(p);
}

void ZIGZIG(int p) {
    ZIG(s[p].Parent, s[s[p].Parent].Parent, s[s[s[p].Parent].Parent].Parent);
    ZIG(p, s[p].Parent, s[s[p].Parent].Parent);
}

void ZAGZAG(int p) {
    ZAG(s[p].Parent, s[s[p].Parent].Parent, s[s[s[p].Parent].Parent].Parent);
    ZAG(p, s[p].Parent, s[s[p].Parent].Parent);
}

void ZIGZAG(int p) {
    ZIG(p, s[p].Parent, s[s[p].Parent].Parent);
    ZAG(p, s[p].Parent, s[s[p].Parent].Parent);
}

void ZAGZIG(int p) {
    ZAG(p, s[p].Parent, s[s[p].Parent].Parent);
    ZIG(p, s[p].Parent, s[s[p].Parent].Parent);
}

void Splay(int p, int des) {
    if (p == des)
        return;
    while (true) {
        int parent = s[p].Parent;
        int grand = s[parent].Parent;
        if (parent == des) {
            if (p == s[parent].Left)
                ZIG(p, parent, grand);
            else
                ZAG(p, parent, grand);
            break;
        } else {
            if (p == s[parent].Left && parent == s[grand].Left)
                ZIGZIG(p);
            else if (p == s[parent].Right && parent == s[grand].Right)
                ZAGZAG(p);
            else if (p == s[parent].Left && parent == s[grand].Right)
                ZIGZAG(p);
            else
                ZAGZIG(p);
            if (grand == des)
                break;
        }
    }
    if (des == root)
        root = p;
}

void NewNode(int p, int val, int fa) {
    s[p].Parent = fa;
    s[p].Left = -1;
    s[p].Right = -1;
    s[p].Val = val;
    s[p].Size = 1;
}

void Insert(int val) {
    int p = root;
    int fa = 0;
    while (p > 0) {
        fa = p;
        if (val < s[p].Val)
            p = s[p].Left;
        else
            p = s[p].Right;
    }
    p = ++Index;
    if (val <= s[fa].Val)
        s[fa].Left = p;
    else
        s[fa].Right = p;
    NewNode(p, val, fa);
    if (root < 0)
        root = p;
    while (p != root) {
        p = s[p].Parent;
        s[p].Size++;
    }
}

void Mid_search(int p) {
    if (p < 0)
        return;
    Mid_search(s[p].Left);
    printf("s[%d] = %d\n", p, s[p].Val);
    Mid_search(s[p].Right);
}

void Delete() {
    Ans += Getsize(s[root].Left);
    root = s[root].Right;
    s[root].Parent = 0;
}

int Query(int k) {
    if (Getsize(root) < k)
        return -1;
    int p = root;
    while (true) {
        int Rsize = Getsize(s[p].Right);
        if (Rsize + 1 == k)
            return (((s[p].Val + Change) / 10) + MIN);
        if (Rsize >= k)
            p = s[p].Right;
        else {
            p = s[p].Left;
            k = k - Rsize - 1;
        }
    }
}

int main() {
    freopen("Input.in", "r", stdin);
    freopen("s.out", "w", stdout);
    scanf("%d%d", &N, &MIN);
    root = -1;
    Index = 0;
    Change = 0;
    Ans = 0;
    Max = -10000000;
    while (N--) {
        int k;
        char opt[2];
        scanf("%s%d", opt, &k);
        if (opt[0] == 'I' && k >= MIN) {
            k -= MIN;  //初始工资，不能小于0
            k *= 10;
            k -= Change;  //将工资换算成没有经过任何加减的值
            if (k > Max)
                Max = k;
            Insert(k);
            Splay(Index, root);
            /*
            for(int i=1; i<=Index; i++)
            {
                printf("#        %d:\n", i);
                printf("Parent = %d\n", s[i].Parent);
                printf("Val = %d\n", s[i].Val);
                printf("Left = %d\n", s[i].Left);
                printf("Right = %d\n", s[i].Right);
                printf("Size = %d\n", s[i].Size);
                printf("----------------------------------------\n");
            }
            printf("==============================================\n");
            cout<<"root = "<<root<<endl;
            cout<<"Index = "<<Index<<endl;
            Mid_search(root);
            printf("==============================================\n");*/
        } else if (opt[0] == 'A')
            Change += (k * 10);
        else if (opt[0] == 'S') {
            Change -= (k * 10);
            if (Max + Change < 0) {
                Ans += s[root].Size;
                Clean(Index);
            } else {
                Insert(-1 - Change);
                Splay(Index, root);
                Delete();
                /*for(int i=1; i<=Index; i++)
                {
                    printf("#        %d:\n", i);
                    printf("Parent = %d\n", s[i].Parent);
                    printf("Val = %d\n", s[i].Val);
                    printf("Left = %d\n", s[i].Left);
                    printf("Right = %d\n", s[i].Right);
                    printf("Size = %d\n", s[i].Size);
                    printf("----------------------------------------\n");
                }
                printf("==============================================\n");
                cout<<"root = "<<root<<endl;
                cout<<"Index = "<<Index<<endl;
                Mid_search(root);*/
            }
        } else if (opt[0] == 'F')
            printf("%d\n", Query(k));
    }
    printf("%d\n", Ans);
    fclose(stdin); fclose(stdout);
    return 0;
}
