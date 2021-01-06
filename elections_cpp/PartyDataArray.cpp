#include <iostream>
#include "PartyDataArray.h"
using namespace std;

namespace elections {

PartyDataArray::PartyDataArray(int size) :
_arr(new Tuple*[size]), _logSize(0), _pysSize(size){
}

PartyDataArray::~PartyDataArray() {
    for (int i = 0; i < _logSize; ++i)
        delete _arr[i];
    delete[] _arr;
}

PartyDataArray::PartyDataArray(const PartyDataArray& other) : PartyDataArray(other._logSize){
    for (int i = 0; i < other._logSize; ++i){
        Tuple* tp = other._arr[i];
        _arr[i] = new Tuple{tp->party, tp->votes, tp->candidates};
    }
}

bool PartyDataArray::resize(int new_size) {
    Tuple** temp = new Tuple*[new_size];
    
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

PartyDataArray::Tuple& PartyDataArray::get(int id) {  
    Tuple* p = nullptr;

    for (int i = 0; i < _logSize && !p; i++)
    {
        if (_arr[i]->party->getId() == id)
            p = _arr[i];
    }
    
    if (p == nullptr)
        exit(1);
    
    return *p;
}

const PartyDataArray::Tuple& PartyDataArray::get(int id) const {
    Tuple* p = nullptr;
    
    for (int i = 0; i < _logSize && !p; i++)
    {
        if (_arr[i]->party->getId() == id)
            p = _arr[i];
    }
    
    if (p == nullptr)
        exit(1);
    
    return *p;
}

bool PartyDataArray::set(int idx, Party* p, int votes, int candidates) {
    if (checkValidIdx(idx)) {
        *(_arr[idx]) = {p, votes, candidates};
        return true;
    }
    return false;
}

const PartyDataArray::Tuple& PartyDataArray::add(Party* p) {
    if (_logSize == _pysSize) {
        resize(_logSize * 2 + 1);
    }
    
    _arr[_logSize] = new Tuple{p, 0, 0};
    ++_logSize;
    return *(_arr[_logSize - 1]);
}

bool PartyDataArray::setLength(int new_size) {
    if (new_size > _pysSize) {
        resize(new_size);
    }
    _logSize = new_size;
    return true;
}

PartyDataArray::Tuple& PartyDataArray::operator[](int idx) {
    checkValidIdx(idx);
    return *(_arr[idx]);
}

const PartyDataArray::Tuple& PartyDataArray::operator[](int idx) const {
    checkValidIdx(idx);
    return *(_arr[idx]);
}

bool PartyDataArray::checkValidIdx(int idx) const {
    if (idx >= _logSize || idx < 0) {
        exit(1); // index error
    }
    return true;
}


int PartyDataArray::getPartyIdWithMaxVotes() const {
    if (_logSize == 0){
        cout << "Can't get max value from an empty array!!" << endl;
        return -1;
    }
    
    int max_val = _arr[0]->votes, max_idx = 0;
    
    for (int i = 1; i < _logSize; i++) {
        if (_arr[i]->votes > max_val) {
            max_val = _arr[i]->votes;
            max_idx = i;
        }
    }
    return _arr[max_idx]->party->getId();
}

void PartyDataArray::sortArrayByCandidates() {
    bubbleSort(_arr, _logSize);
}

void PartyDataArray::bubbleSort(Tuple** arr, int size)
{
    int i, j;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size-i-1; j++){
            if (arr[j]->candidates < arr[j+1]->candidates){
                Tuple* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}




}
