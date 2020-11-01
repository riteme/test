#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef pair<int,int> PI;

int fw1, fw2, bk1, bk2;
bool found;

const int maxv = 1000001;

vector<int> G[maxv],H[maxv],GS[maxv],HS[maxv];
static vector<int> marked(maxv,-1);

void check_vertex(vector<int> *G1, vector<int> *G2, int vertex, bool rev = false)
{
    vector<PI> temp;
    for(int c : G1[vertex])
        for(int x : G2[c])
            if (x!=vertex)
                temp.push_back(PI(x,c));
//    fprintf(stderr,"%d %d\n",vertex,temp.size());
    for(PI p : temp)
        if (marked[p.first]!=-1)
        {
            found = true;
            fw1 = vertex;
            fw2 = p.first;
            bk1 = p.second;
            bk2 = marked[p.first];
            if (rev)
            {
                swap(fw1,bk1);
                swap(fw2,bk2);
            }
            break;
        } else
            marked[p.first] = p.second;
    for(PI p : temp)
        marked[p.first] = -1;
}


struct node
{
    int parent;
    int children[26];
};

int trie_add(vector<node> &trie, int p, char c)
{
    node y;
    for(int i=0; i<26; i++)
        y.children[i] = -1;
    y.parent = p;
    if (p!=-1)
        trie[p].children[c] = trie.size();
    trie.push_back(y);
}

int trie_insert(vector<node> &trie, int x, char c)
{
    c -= 'a';
    if (trie[x].children[c]!=-1)
        return trie[x].children[c];
    else
        trie_add(trie,x,c);
    return trie.size()-1;
}

void print(vector<node> & trie, int y, bool rev)
{
    if (y==0)
        return;
    int x = trie[y].parent;
    char c = 0;
    for(int i=0; i<26; i++)
        if (trie[x].children[i] == y)
            c = 'a'+i;
    if (rev) cout << c;
    print(trie,x,rev);
    if (!rev) cout << c;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int TT;
    cin >> TT;
    while(TT--)
    {
        int w;
        cin >> w;
        vector<node> ftrie,btrie;
        trie_add(ftrie,-1,0);
        trie_add(btrie,-1,0);
        int e = 0;
        for(int i=0; i<w; i++)
        {
            vector<int> fnodes(1,0), bnodes(1,0);
            string A;
            cin >> A;
            int x = 0;
            for(int k=0; k<A.size(); k++)
            {
                x = trie_insert(ftrie,x,A[k]);
                fnodes.push_back(x);
            }
            x = 0;
            for(int k=A.size()-1; k>=0; k--)
            {
                x = trie_insert(btrie,x,A[k]);
                bnodes.push_back(x);
            }
            for(int k=1; k<A.size(); k++)
            {
//                cout << fnodes[k] << " " << bnodes[k] << endl;
                G[fnodes[k]].push_back(bnodes[A.size()-k]);
                H[bnodes[k]].push_back(fnodes[A.size()-k]);
                e++;
            }
        }
        int vg = ftrie.size();
        int vh = btrie.size();
        int magic = sqrt(e);
/*        for(int i=0; i<vg; i++)
        {
            cout << i << " ";
            print(ftrie,i,false);
            cout << endl;
            for (int x : G[i])
            {
                cout << "-> " << x << " "; 
                print(btrie,x,true);
                cout << endl;
            }    
        } */
//        for(int i=0; i<vg; i++)
//            sort(G[i].begin(),G[i].end());
        found = false;
        for(int i=0; i<vg && !found; i++)
            if (G[i].size()>=magic)
            {
//                cerr << G[i].size() << endl;
                check_vertex(G,H,i);
            }
        for(int i=0; i<vh && !found; i++)
            if (H[i].size()>=magic)
            {
//                cerr << H[i].size() << endl;
                check_vertex(H,G,i,true);
            }
        for(int i=0; i<vg; i++)
            if (G[i].size()<magic)
                for(int j :G[i])
                    if (H[j].size()<magic)
                    {
                        GS[i].push_back(j);
                        HS[j].push_back(i);
                    }
        for(int i=0; i<vg && !found; i++)
            check_vertex(GS,HS,i);
        if (!found)
            cout << "NO" << endl;
        else
        {
            cout << "YES" << endl;
            print(ftrie,fw1,false);
            cout << '_';
            print(btrie,bk1,true);
            cout << " ";
            print(ftrie,fw2,false);
            cout << '_';
            print(btrie,bk2,true);
            cout << endl;
            print(ftrie,fw1,false);
            cout << '_';
            print(btrie,bk2,true);
            cout << " ";
            print(ftrie,fw2,false);
            cout << '_';
            print(btrie,bk1,true);
            cout << endl;
        }
        for(int i=0; i<max(vg,vh); i++)
        {
            G[i].clear();
            H[i].clear();
            GS[i].clear();
            HS[i].clear();
        }
    }
}
