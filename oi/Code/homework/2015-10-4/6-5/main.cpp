#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

int Next(const string &data,const string &target,int size,int start){
	for (int index=start;
	     index<data.size();
	     index++) {
	    for (int i=index,j=0;
	         i<data.size();
	         i++,j++) {
	        if (data[i]!=target[j]) {
	            break;
	        }

	        if (j+1==size) {
	            return index;
	        }
	    }  // for
	}  // for

	return -1;
}

int KmpSearch(const string &data,const string &target){

}

int Next(const string &data,const string &target){
	return Next(data,target,target.size(),0);
}

#define TEST_KMP(data,target) assert(KmpSearch((data),(target))==Next((data),(target)));

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	TEST_KMP("a","a");
	TEST_KMP("ab","a");
	TEST_KMP("ba","a");
	TEST_KMP("b","a");
	TEST_KMP("I'm still a teenager! Don't shout at me!","teenager");
	TEST_KMP("kill fill killl filll kill killll fill","killll");
	TEST_KMP("What the fuck! What the funk! What the fork!","fork");
	TEST_KMP("Hehehehehehehehehe233hehe2333hehe","233");
	TEST_KMP("Big jump.....................arrived jumpx...ju....jup....jumpxy...OK","jumpxy");
	TEST_KMP("What happeded to you?","happeded to");
	TEST_KMP("12314983621548379568176631784986312754781632718123442135431531115","1234");
	TEST_KMP("Not found","404");
	TEST_KMP("C++ is better than Pascal.","better than");
	TEST_KMP("Yi Qun Pi Min Kuai Han Wo Ye Ye!!!! ----Sun Zi!","Pi Min");
	TEST_KMP("anbasjkbvjvndhbvhfbvabhsvhbcctvmkjnafjkbdakjvhbjkbar","cctv");
	TEST_KMP("%&^%$&^%&*!@$^#%^#%$%*#%#%%$#@%@#%@%@%@%","%#%%$");

	return 0;
}