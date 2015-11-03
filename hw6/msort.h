#include <vector>

template <class T, class Comparator>
void merge(std::vector<T> & vector, int first, int mid, int last, Comparator comp){
	std::vector<T> tempVector;
	tempVector.resize(vector.size());
	//Initialize local indexes
	int f1 = first; //Beginning of first subarray
	int l1 = mid; //End of first subarray
	int f2 = mid+1; //Beginning of second subarray
	int l2 = last; //End of second subarray

	int index = f1;

	for(; (f1 <= l1) && (f2 <= l2); ++index){
		if(comp(vector[f1], vector[f2])){
			tempVector[index] = vector[f1];
			++f1;
		}else{
			tempVector[index] = vector[f2];
			++f2;
		}
	}

	for(; f1 <= l1; ++f1, ++index){
		tempVector[index] = vector[f1];
	}

	for(; f2 <= l2; ++f2, ++index){
		tempVector[index] = vector[f2];
	}

	for(index = first; index <= last; ++index){
		vector[index] = tempVector[index];
	}
}

template <class T, class Comparator>
void mergeSort(std::vector<T> & vector, int first, int last, Comparator comp){
	if(first < last){
		int mid = (first + last) / 2;

		//left half
		mergeSort(vector, first, mid, comp);

		//right half
		mergeSort(vector, mid+1, last, comp);

		//merge
		merge(vector, first, mid, last, comp);
	}
}


template <class T, class Comparator>
void mergeSort(std::vector<T> & vector, Comparator comp){
	mergeSort(vector, 0, vector.size()-1, comp);
}