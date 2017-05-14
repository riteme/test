#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
using namespace std;
int ans=0;
string to_string(int inp){//转换到字符串 
	stringstream ss;
    string outp;
    ss<<inp;
    ss>>outp;
    return (outp);
}
string zh(int sr){//转换
if (sr>=10) return (to_string(sr)); else return("0"+to_string(sr));
}
bool hwpd(string date0){//回文判断
	bool pd=true;
	for(int j=0;j<=7;j++){
		if(date0[j]!=date0[7-j]){
		pd=false;
		break;	
		}
	}
	return (pd);
} 
string jrk(int year0,int month0,int day0){//接入口
	string y=to_string(year0);
	string m=zh(month0);
	string d=zh(day0); 
	return (y+m+d);
}
void for_day(int b_day,int e_day,int nmonth,int nyear){//天数遍历 
	for(int nday=b_day;nday<=e_day;nday++){
 		if (hwpd(jrk(nyear,nmonth,nday)))ans++;
	}
}
int tscx(int xz,bool sry){//天数查询 
	if(xz==1||xz==3||xz==5||xz==7||xz==8||xz==10||xz==12) return(31);
	if(xz==4||xz==5||xz==9||xz==11) return(30);
	if (xz==2){
		if (sry) return (29); else return (28); 
	}
}
bool rnpd(int year){//闰年判断
	return ((year%4==0&&year%100!=0)||(year%400==0));
}
void zbl(int date11,int date22){//总遍历
	int year1=date11/10000,year2=date22/10000;
	int month1=date11%10000-date11%100,month2=date22%10000-date22%100;
	int day1=date11%100,day2=date22%100; 
	bool ry;
	for (int nyear=year1;nyear<=year2;nyear++){
		ry=rnpd(nyear);
 		if (nyear==year2){
 			if (year1==year2){
 				for (int nmonth=month1;nmonth<=month2;nmonth++){
 					if (nmonth==month1) for_day(day1,tscx(nmonth,ry),nmonth,nyear);
 					else if (nmonth==month2) for_day(1,day2,nmonth,nyear);
 					else for_day(1,tscx(nmonth,ry),nmonth,nyear); 
				 }
			 }else {
			 	for (int nmonth=1;nmonth<=month2;nmonth++){
 					if (nmonth==month1) for_day(day1,tscx(nmonth,ry),nmonth,nyear);
 					else if (nmonth==month2) for_day(1,day2,nmonth,nyear);
 					else for_day(1,tscx(nmonth,ry),nmonth,nyear); 	
			 	}
		 	}
 		}else if(nyear==year1){
 			for (int nmonth=month1;nmonth<=12;nmonth++){
 				if (nmonth==month1) for_day(day1,tscx(nmonth,ry),nmonth,nyear);
 				else if (nmonth==month2) for_day(1,day2,nmonth,nyear);
 				else for_day(1,tscx(nmonth,ry),nmonth,nyear); 
 			}
		 }else {
		 	for (int nmonth=1;nmonth<=12;nmonth++){
 				if (nmonth==month1) for_day(day1,tscx(nmonth,ry),nmonth,nyear);
 				else if (nmonth==month2) for_day(1,day2,nmonth,nyear);
 				else for_day(1,tscx(nmonth,ry),nmonth,nyear); 
 			}
		 }
		}
	}
int main(){
	freopen("date.in","r",stdin);
	freopen("date.out","w",stdout);
	int date1,date2;
	cin>>date1>>date2;
	if(date1==date2){
		if(hwpd(to_string(date1))) ans++;
	} else zbl(date1,date2);
	cout<<ans<<endl;
	return 0;
}
