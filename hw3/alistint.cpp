#include "alistint.h"
#include "iostream"

AListInt::AListInt(){
	_size = (unsigned int) 0;
	_cap = (unsigned int) 5;

	_data = new int[_cap];
}

AListInt::AListInt(int cap){
	_size = (unsigned int) 0;
	_cap = (unsigned int) cap;

	_data = new int[cap];
}

AListInt::~AListInt(){
	delete [] _data;
}

AListInt::AListInt(const AListInt& other){
	_data = new int[other.size()];

	_size = (unsigned int) other.size();
	_cap = (unsigned int) other.size();

	for(int i = 0; i < (int) _size; i++){
		_data[i] = other.get(i);
	}
}

AListInt& AListInt::operator=(const AListInt& other){
	delete [] _data;
	_data = new int[other.size()];

	_size = (unsigned int) other.size();
	_cap = (unsigned int) other.size();

	for(int i = 0; i < (int) _size; i++){
		_data[i] = other.get(i);
	}
	return *this;
}

int AListInt::size() const{
	return _size;
}

bool AListInt::empty() const{
	return _size == 0;
}

void AListInt::insert(int pos, const int& val){
	if((unsigned int) pos > _size || pos < 0){
		return;
	}

	if(_size == _cap){
		resize();
	}

	//Right shift
	if(_size > 0){
		for(int i = (int)_size; i > pos; i--){
			_data[i] = _data[i-1];
		}
	}


	_size++;
	_data[pos] = val;
}

void AListInt::remove(int pos){
	if((unsigned int) pos > _size-1 || pos < 0){
		return;
	}

	if((unsigned int) pos < _size-1 && _size>1){
		//Shift left the values
		for(int i = (int)_size-2; i >= pos; i--){
			_data[i] = _data[i+1];
		}
	}

	_size--;
}

void AListInt::set(int position, const int& val){
	if((unsigned int) position > _size-1 || position < 0){
		return;
	}

	_data[position] = val;
}

int& AListInt::get(int position){
	if(_size == 0){
		std::cerr << "called get with index " << position << " which is out of bounds. Program will crash\n" << std::endl;
	}

	//Invalid position
	if((unsigned int) position > _size-1 || position < 0){
		return _data[0];
	}

	return _data[position];
}

int const & AListInt::get(int position) const{
	if(_size == 0){
		std::cerr << "called get with index " << position << " which is out of bounds. Program will crash\n" << std::endl;
	}

	//Invalid position
	if((unsigned int) position > _size-1 || position < 0){
		return _data[0];
	}

	return _data[position];
}

int const & AListInt::operator[](int position) const{
	return get(position);
}

int& AListInt::operator[](int position){
	return get(position);
}

AListInt AListInt::operator+(const AListInt& other) const{
	AListInt newList(_size + other.size());
	
	//Insert all the elements from both lists
	int i = 0;
	for(int j = 0; j < size(); j++, i++){
		newList.insert(i, get(j));
	}
	for(int j = 0; j < other.size(); j++, i++){
		newList.insert(i, other.get(j));
	}

	return newList;
}

void AListInt::resize(){
	int* newData = new int[_cap * 2];

	//Copy the values
	for(unsigned int i = 0; i < _cap; i++){
		newData[i] = _data[i];
	}

	//Free the old array
	delete [] _data;

	//Update pointers
	_data = newData;
	_cap*=2;
}