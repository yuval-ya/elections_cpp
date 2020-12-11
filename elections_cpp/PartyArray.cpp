#include "PartyArray.h"
#include <iostream>
using namespace std;


PartyArray::PartyArray(int size) :
	_arr(new Party*[size]), _log_size(size), _pys_size(size){
}

PartyArray::~PartyArray() {
	for (int i = 0; i < _log_size; i++)
	{
		delete _arr[i];
	}
	delete[] _arr;
}
bool PartyArray::resize(int new_size) {
	Party** temp = new Party*[new_size];

	int copy = _log_size <= new_size ? _log_size : new_size;
	for (int i = 0; i < copy; ++i)
		temp[i] = _arr[i];

	for (int j = copy; j < _log_size; j++) {
		delete _arr[j];
	}

	delete[] _arr;
	_arr = temp;
	this->_pys_size = new_size;
	return true;
}

Party& PartyArray::get(int id) {
	check_valid_idx(id - 1);
	return *_arr[id - 1];
}

bool PartyArray::set(int idx, Party* d) {
	if (check_valid_idx(idx)) {
		_arr[idx] = d;
		return true;
	}
	return false;
}

const Party& PartyArray::add(const Party& d) {
	if (_log_size == _pys_size) {
		resize(_log_size * 2 + 1);
	}

	_arr[_log_size] = new Party(d);
	++_log_size;
	return *_arr[_log_size - 1];
}

bool PartyArray::set_length(int new_size) {
	if (new_size > _pys_size) {
		resize(new_size);
	}
	_log_size = new_size;
	return true;
}

Party& PartyArray::operator[](int idx) {
	check_valid_idx(idx);
	return *_arr[idx];
}

const Party& PartyArray::operator[](int idx) const {
	check_valid_idx(idx);
	return *_arr[idx];
}

void PartyArray::print() const {
	for (int i = 0; i < _log_size; i++)
	{
		cout << *_arr[i] << endl;
		cout << _arr[i]->get_candidates_array() << endl;
	}
}

bool PartyArray::add_district_to_party() {
	for (int i = 0; i < _log_size; i++)
	{
		_arr[i]->add_district_to_candidates_arr();
	}
	return true;
}

bool PartyArray::check_valid_idx(int idx) const {
	if (idx >= _log_size || idx < 0) {
		exit(1); // index error
	}
	return true;
}



void PartyArray::merge(Party** arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int i, j;
    Party** L = new Party*[n1];
    Party** R = new Party*[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    int k = l;
    i = j = 0;

    while (i < n1 && j < n2) {
        if (L[i]->get_total_candidates() >= R[j]->get_total_candidates())
        {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}


void PartyArray::mergeSort(Party** arr,int l,int r){
    if(l >= r){
        return;//returns recursively
    }
    int m = (l+r-1)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

