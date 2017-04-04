#include <cstdio>
#include <cstdlib>

struct node
{
    int key,value;
    int le,rt,dad;

    int depth;
    int down;

    node()
    {
        key=value=le=rt=dad=0;

        depth=down=0;
    }
};
node s[5000005];
int tot=0,root=1;

void update(int x) {
    if (s[x].le == 0 && s[x].rt == 0)
        s[x].down = x;
    else if (s[s[x].le].depth > s[s[x].rt].depth) {
        s[x].depth = s[s[x].le].dpeth+1;
        s[x].down = s[s[x].le].down;
    } else {
        s[x].depth = s[s[x].rt].depth+1;
        s[x].down = s[s[x].rt].down;
    }
}


char relation(int x)
{
    if(x == s[s[x].dad].le) return 'L';
    if(x == s[s[x].dad].rt) return 'R';

    return '#';
}

void debug()
{
    int i;

    printf("root = %d\n",root);
    for(i=1;i<=tot;i++)
        printf("s[%d] key=%d le=%d rt=%d dad=%d\n",i,s[i].key,s[i].le,s[i].rt,s[i].dad);
    puts("");
}

void rotate(int x)
{
    int dad=s[x].dad,anc=s[dad].dad;

    // printf("rotate %d[%c] anc=%d dad=%d\n",x,relation(x),anc,dad);

    if(relation(x) == 'L')
    {
        s[x].dad=anc;
        if(relation(dad) == 'L') s[anc].le=x;
        if(relation(dad) == 'R') s[anc].rt=x;

        s[dad].le=s[x].rt;
        s[s[x].rt].dad=dad;

        s[dad].dad=x;
        s[x].rt=dad;
    }
    
    else if(relation(x) == 'R')
    {
        s[x].dad=anc;
        if(relation(dad) == 'L') s[anc].le=x;
        if(relation(dad) == 'R') s[anc].rt=x;

        s[dad].rt=s[x].le;
        s[s[x].le].dad=dad;

        s[dad].dad=x;
        s[x].le=dad;
    }

    update(dad);
    update(anc);
    update(x);

    if(s[x].dad == 0) root=x;
}

void splay(int x)
{
    int dad;

    while(root != x)
    {
        dad=s[x].dad;

        if(dad == root) rotate(x);

        else if(relation(x) == relation(dad))
            rotate(dad),rotate(x);
        else
            rotate(x),rotate(x);
    }
}

void insert(int key,int value)
{
    int now=root;
    tot++;

    if(tot == 1)
    {
        s[1].key=key;
        s[1].value=value;
        return;
    }

    while(1)
    {
        if(key < s[now].key)
        {
            if(s[now].le == 0) {s[now].le=tot;goto finish;}
            now=s[now].le;
        }
        else if(key > s[now].key)
        {
            if(s[now].rt == 0) {s[now].rt=tot;goto finish;}
            now=s[now].rt;
        }

        else
        {
            s[now].value=value;
            splay(now);
            return;
        }
    }

    finish:

    // printf("Okay to %d\n",now);
    
    s[tot].key=key,s[tot].value=value;    
    s[tot].dad=now;

    splay(tot);
}


void DBGinit()
{
    // s[4].key=40,s[4].le=2,s[4].rt=0,s[4].dad=0;
    // s[2].key=20,s[2].le=1,s[2].rt=3,s[2].dad=4;
    // s[1].key=10,s[1].le=0,s[1].rt=0,s[1].dad=2;
    // s[3].key=30,s[3].le=0,s[3].rt=0,s[3].dad=2;
    // tot=4;
    // root=4;

    s[1].key=10,s[1].dad=3,s[1].rt=2;
    s[2].key=20,s[2].dad=1;
    s[3].key=30,s[3].le=1;

    tot=3;
    root=3;
}

void ask(int key)
{
    // printf("Ask %d\n",key);
    int now=root;

    while(1)
    {
        if(key == s[now].key) goto finish;

        if(key < s[now].key)
            now=s[now].le;
        else
            now=s[now].rt;
    }

    finish:

    printf("%d\n",s[now].value);

    splay(now);

}

int main(void)
{
    char cmd[10];
    int key,value;

    while(~scanf("%s",cmd))
    {
        if(cmd[0] == 'A') scanf("%d%d",&key,&value),insert(key,value);
        if(cmd[0] == 'D') scanf("%d",&key);
        if(cmd[0] == 'Q') scanf("%d",&key),ask(key);

        // debug();
    }

    return 0;
}
