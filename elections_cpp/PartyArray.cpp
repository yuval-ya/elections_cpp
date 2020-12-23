#include "PartyArray.h"
#include <iostream>
using namespace std;

namespace elections {


PartyArray::PartyArray(int size) :
_arr(new Party*[size]), _logSize(0), _pysSize(size){
}

PartyArray::~PartyArray() {

    delete[] _arr;
}

void PartyArray::makeEmpty() {
	for (int i = 0; i < _logSize; i++)
	{
		delete _arr[i];
	}
	_logSize = 0;
}

bool PartyArray::resize(int new_size) {
    Party** temp = new Party*[new_size];
    
    int copy = _logSize <= new_size ? _logSize : new_size;
    for (int i = 0; i < copy; ++i)
        temp[i] = _arr[i];
    for (int j = copy; j < _logSize; j++) {
        delete _arr[j];
    }
    delete[] _arr;
    _arr = temp;
    this->_pysSize = new_size;
    return true;
}

const Party& PartyArray::get(int id) const {    
    Party* p = nullptr;

    for (int i = 0; i < _logSize && !p; i++)
    {
        if (_arr[i]->getId() == id)
            p = _arr[i];
    }
    
    if (p == nullptr)
        exit(1);
        
    return *p;
}

Party& PartyArray::get(int id) {
    checkValidIdx(id - 1);
    
    Party* p = nullptr;

    if (_arr[id - 1]->getId() == id)
        p = _arr[id - 1];

    for (int i = 0; i < _logSize && !p; i++)
    {
        if (_arr[i]->getId() == id)
            p = _arr[i];
    }
    
    if (p == nullptr)
        exit(1);
        
    return *p;
}

bool PartyArray::set(int idx, Party* p) {
    if (checkValidIdx(idx)) {
        _arr[idx] = p;
        return true;
    }
    return false;
}

Party& PartyArray::add(Party* party) {
    if (_logSize == _pysSize) {
        resize(_logSize * 2 + 1);
    }
    
	_arr[_logSize] = party;
    ++_logSize;
    return *_arr[_logSize - 1];
}


bool PartyArray::setLength(int new_size) {
    if (new_size > _pysSize) {
        resize(new_size);
    }
    _logSize = new_size;
    return true;
}

Party& PartyArray::operator[](int idx) {
    checkValidIdx(idx);
    return *_arr[idx];
}

const Party& PartyArray::operator[](int idx) const {
    checkValidIdx(idx);
    return *_arr[idx];
}

void PartyArray::print() const {
    for (int i = 0; i < _logSize; i++)
    {
        cout << *_arr[i] << endl;
        cout << _arr[i]->getCandidatesArray() << endl;
    }
}

bool PartyArray::addDistrictToParty(const District* district) {
    for (int i = 0; i < _logSize; i++)
    {
		_arr[i]->getCandidatesArray().add(district);
    }
    return true;
}

bool PartyArray::checkValidIdx(int idx) const {
    if (idx >= _logSize || idx < 0) {
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
        if (L[i]->getTotalCandidates() >= R[j]->getTotalCandidates())
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

}
