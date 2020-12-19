#include "CandidatesArray.h"
using namespace std;

namespace elections {

CandidatesArray::CandidatesArray(int size) : _arr(new PersonList*[size]), _logSize(size), _pysSize(size)
{
    for (int i = 0; i < size; i++)
        _arr[i] = new PersonList;
}

CandidatesArray::~CandidatesArray() {
    for (int i = 0; i < _logSize; i++)
    {
        delete _arr[i];
    }
    delete[] _arr;
}
bool CandidatesArray::resize(int new_size) {

    PersonList** temp = new PersonList*[new_size];

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

PersonList& CandidatesArray::get(int district_id) {
    checkValidIdx(district_id - 1);
    return *_arr[district_id - 1];
}

const PersonList& CandidatesArray::get(int district_id) const {
    checkValidIdx(district_id - 1);
    return *_arr[district_id - 1];
}

bool CandidatesArray::add() {
    if (_logSize == _pysSize) {
        resize(_logSize * 2 + 1);
    }
    _arr[_logSize] = new PersonList();
    _logSize++;
    return true;
}
bool CandidatesArray::setLength(int new_size) {
    if (new_size > _pysSize) {
        resize(new_size);
    }
    _logSize = new_size;
    return true;
}

PersonList& CandidatesArray::operator[](int idx) {
    checkValidIdx(idx);
    return *_arr[idx];
}

const PersonList& CandidatesArray::operator[](int idx) const {
    checkValidIdx(idx);
    return *_arr[idx];
}

ostream& operator<<(ostream& os, const CandidatesArray& c_arr) {
    int size = c_arr.getLength();
    for (int i = 0; i < size; i++) {
        if (c_arr[i].getPersonNumber() > 0) {
            os << "District No." << (i + 1) << " :" << endl;
            os << c_arr[i] << endl;
        }
    }
    return os;
}

bool CandidatesArray::checkValidIdx(int idx) const {
    if (idx >= _logSize || idx < 0) {
        exit(1); // index error
    }
    return true;
}

}
