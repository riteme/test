#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cassert>

#include "BinaryTree.hpp"

static int AllocateCount=0;

void *operator new(std::size_t count){
	AllocateCount++;
	return malloc(count);
}

void operator delete(void *ptr){
	AllocateCount--;
	free(ptr);
}

using namespace std;

constexpr unsigned TESTCASE_SIZE= 100000;

int main(int argc, char const *argv[])
{
	cout<<"AllocateCount: "<<AllocateCount<<endl;

	// cout.sync_with_stdio(false);

	int testcases[TESTCASE_SIZE];
	for (int i=0;
	     i<TESTCASE_SIZE;
	     i++) {
	    testcases[i]=i;
	}  // for
	std::random_shuffle(std::begin(testcases),std::end(testcases));

	BinaryTree<int,int> bst;

	cout<<"AllocateCount: "<<AllocateCount<<endl;

	for (auto i : testcases) {
	    bst.Put(i,i+i);
	}  // foreach in testcases

	assert(bst.Size()==TESTCASE_SIZE);

	assert(bst.Get(1)==2);
	assert(bst.Get(233)==466);
	assert(bst.Get(999)==1998);
	assert(bst.Get(TESTCASE_SIZE-1)==2*(TESTCASE_SIZE-1));

	bst.Put(TESTCASE_SIZE,0);

	assert(bst.Size()==TESTCASE_SIZE+1);
	assert(bst.Get(TESTCASE_SIZE)==0);

	// cout<<"AllocateCount: "<<AllocateCount<<endl;
	// cout<<"Size: "<<bst.Size()<<endl;
	// cout<<"RealSize: "<<bst.RealSize()<<endl;
	// bst.Remove(3);
	// bst.Remove(35);
	// bst.Remove(77);
	// bst.Remove(TESTCASE_SIZE);
	// cout<<"AllocateCount: "<<AllocateCount<<endl;
	// cout<<"Size: "<<bst.Size()<<endl;
	// cout<<"RealSize: "<<bst.RealSize()<<endl;

	// assert(bst.Contain(1)==true);
	// assert(bst.Contain(3)==false);
	// assert(bst.Contain(8)==true);
	// assert(bst.Contain(35)==false);
	// assert(bst.Contain(77)==false);
	// assert(bst.Contain(233)==true);
	// assert(bst.Contain(TESTCASE_SIZE)==false);
	// assert(bst.Size()==TESTCASE_SIZE-3);

	assert(bst.Get(1)==2);
	assert(bst.Get(233)==466);
	assert(bst.Get(999)==1998);

	bst.Clear();

	cout<<"AllocateCount: "<<AllocateCount<<endl;
	cout<<"Size: "<<bst.Size()<<endl;
	cout<<"RealSize: "<<bst.RealSize()<<endl;
	assert(bst.Size()==0);
	assert(AllocateCount==0);

	return 0;
}
