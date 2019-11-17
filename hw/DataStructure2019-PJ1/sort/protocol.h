#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

struct Pack {
    int i, v;

    bool operator<(const Pack &z) const;
};

extern int n;
extern Pack s[500];

bool is_sorted();
void sort();
void read();
void show();

#endif
