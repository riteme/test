#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct Tree {
    LL data;
    int child[10], children;
    int leaf;
    Tree() {
        leaf = children = data = 0;
        memset(child, 0, sizeof(child));
    }
    Tree operator=(const Tree& x) {  //¶¨Òå¸³Öµ·ûºÅ
        Tree y;
        data = x.data;
        children = x.children;
        memcpy(child, x.child, sizeof(x.child));
        leaf = x.leaf;
        return *this;
    }
    bool operator>(
        Tree x) {  //¶¨Òå¸÷ÖÖÂß¼­¹ØÏµ£¬ÒÔ¹©ÓÅÏÈ¶ÓÁÐÊ¹ÓÃ£¬Ö÷Òª±È½ÏÊý¾Ý´óÐ¡
        if (data > x.data)
            return true;
        return false;
    }
    bool operator<(Tree x) {
        if (data > x.data || data == x.data)
            return false;
        return true;
    }
    bool operator==(Tree x) {
        if (data > x.data || data < x.data)
            return false;
        return true;
    }
    bool operator>=(Tree x) {
        if (data < x.data)
            return false;
        return true;
    }
    bool operator<=(Tree x) {
        if (data > x.data)
            return false;
        return true;
    }
} tree[1000001];  //´¢´æÊ÷
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct comp {  //ÓÅÏÈ¶ÓÁÐµÄ±È½Ï
    bool operator()(Tree x, Tree y) {
        if (x.data > y.data)
            return true;
        if (x.data == y.data && x.leaf < y.leaf)
            return true;  //Õâ¸öµØ·½ÒªÓÅÏÈÑ¡Ôñ×ÓÒ¶½Úµã
        return false;
    }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LL n, k, cur, lens, depth,
    max_depth;                                   //Á½¸öÊäÈë£¬Ö¸Ïòµ±Ç°µÄ´¢´æÊ÷µÄÊý×éµÄ×îºóÒ»¸öÔªËØ£¬µ±Ç°×Ü±àÂë³¤¶È£¬µ±Ç°Ê÷µÄÉî¶È£¬×î´óÉî¶È£¨×î³¤±àÂë³¤¶ÈµÄ×îÐ¡Öµ£©
priority_queue<Tree, vector<Tree>, comp> nsort;  // ÅÅÐòÓÃÓÅÏÈ¶ÓÁÐ£¬Ö±½Ó´¢´æÊ÷
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void dfs(int now_tree) {                      //±éÀú¸÷½Úµã
    if (!tree[now_tree].children) {           //Èç¹ûÊÇ×Ó½Úµã
        lens += tree[now_tree].data * depth;  //¼ÆËã±àÂë×Ü³¤¶È
        if (depth > max_depth)
            max_depth = depth;  //ÕÒµ½×î´óÉî¶È
        return;
    }
    for (int i = 1; i <= tree[now_tree].children; i++) {
        depth++;                       //Éî¶È
        dfs(tree[now_tree].child[i]);  //±éÀú×Ó½Úµã
        depth--;                       //Éî¶È
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void work(int nums) {  //È¡³önums¸öÔªËØ½¨Á¢Ò»¸ö¸¸Ç×½ÚµãµÄ×Ó½Úµã
    Tree x;
    int curn = 0;
    for (int i = 1; i <= nums; i++) {  //²»´¢´æ¸¸Ç×½áµã
        Tree y;
        y = nsort.top();
        nsort.pop();
        tree[++cur] = y;  //ÓÃÊý×é´¢´æ½Úµã
        x.child[++curn] = cur;
        x.data += y.data;  // HuffmanÊ÷½¨Á¢¸¸Ç×½Úµã
    }
    x.children = nums;
    nsort.push(x);  //Ñ¹Èë¸¸Ç×½Úµã
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        LL ns;
        Tree x;
        cin>>ns;
        x.data=ns;
        x.leaf=1;
        nsort.push(x);//ÊäÈëÊý¾Ý£¬²¢Ñ¹ÈëÓÅÏÈ¶ÓÁÐ 
    }
    work((n-2)%(k-1)+2);//±£Ö¤×îºóÒ»²ãµÄ½ÚµãÊýÊ¹Ê÷Âú×ã×îÓÅ½á¹¹ 
    while(nsort.size()>=k){//Ö±µ½Ê£×îºóÒ»¿ÃÊ÷ 
        work(k);
    }
    tree[++cur]=nsort.top();//´¢´æ¸ù½Úµã 
    nsort.pop();
    dfs(cur);
    cout<<lens<<endl<<max_depth;//Êä³ö 
    return 0;
}
