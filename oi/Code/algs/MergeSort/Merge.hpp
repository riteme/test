#ifndef MERGE_HPP
#define MERGE_HPP
    
template <typename T>
class Merge
{
public:
	Merge(T target){
		a=target;
		aux=target;
	}
	~Merge()=default;
	
	T Sort(){
		SortImpl(0,a.size());
		return a;
	}

private:

	void SortImpl(unsigned left,unsigned right){
		if (right<=left) {
		    return;
		}

		unsigned mid=(left+right)/2;
		SortImpl(left,mid);
		SortImpl(mid+1,right);
		MergeImpl(left,mid,right);
	}

	void MergeImpl(unsigned left,unsigned mid,unsigned right){
		// T &ax=*a;

		for (unsigned index=left;
		     index<=right;
		     index++) {
		    aux[index]=a[index];
		}  // for
		
		unsigned i=left,j=mid+1;
		for (unsigned k=left;
		     k<=right;
		     k++) {
		    if(i>mid) a[k]=aux[j++];
			else if(j>right)  a[k]=aux[i++];
			else if(aux[i]<aux[j]) a[k]=aux[i++];
			else a[k]=aux[j++];
		}  // for 
	}

	T aux;
	T a;
};

#endif  // MERGE_HPP
