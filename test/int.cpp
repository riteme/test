#include "int.h"
#include<string>

int evaluate(const int2048_t &num) {
    int2048_t a=num;
    int w=0;
    for(int t=1;t<=11;t++){
        int2048_t x=a>>(1<<t-1);
        if(!w){
            std::string s;
            for(int i=2048;i--;)s.push_back('0'+(i%(1<<t)<t));
            a=a&s;x=x&s;
            w=(1<<t)-t;
        }
        a=a+x;w--;
    }
    a=a&int2048_t("11111111111");
    int l=0,r=2048,mid;
    while(r-l>1){
        mid=l+r>>1;
        std::string s;
        for(int i=12;i--;)s.push_back('0'+(mid>>i&1));
        a<s?r=mid:l=mid;
    }
    return l;
}
