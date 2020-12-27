#include "CandidatesArray.h"
using namespace std;

# include "District.h"

namespace elections {

CandidatesArray::CandidatesArray(int size) : _arr(new Tuple*[size]), _logSize(0), _pysSize(size)
{
}

CandidatesArray::~CandidatesArray() {
    for (int i = 0; i < _logSize; i++)
    {
        delete _arr[i];
    }
    delete[] _arr;
}

bool CandidatesArray::resize(int new_size) {

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

PersonList& CandidatesArray::get(int district_id) {
	Tuple* p = nullptr;

	for (int i = 0; i < _logSize && !p; i++)
	{
		if (_arr[i]->district->getId() == district_id)
			p = _arr[i];
	}

	if (p == nullptr)
		exit(1);

	return p->candidateList;
}

const PersonList& CandidatesArray::get(int district_id) const {
	Tuple* p = nullptr;

	for (int i = 0; i < _logSize && !p; i++)
	{
		if (_arr[i]->district->getId() == district_id)
			p = _arr[i];
	}

	if (p == nullptr)
		exit(1);

	return p->candidateList;
}

bool CandidatesArray::add(const District* district) {
    if (_logSize == _pysSize) {
        resize(_logSize * 2 + 1);
    }
    _arr[_logSize] = new Tuple;
	_arr[_logSize]->district = district;
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

CandidatesArray::Tuple& CandidatesArray::operator[](int idx) {
    checkValidIdx(idx);
    return *_arr[idx];
}

const CandidatesArray::Tuple& CandidatesArray::operator[](int idx) const {
    checkValidIdx(idx);
    return *_arr[idx];
}

ostream& operator<<(ostream& os, const CandidatesArray& c_arr) {
    int size = c_arr.getLength();
    for (int i = 0; i < size; i++) {
        if (c_arr[i].candidateList.getPersonCount() > 0) {
            os << "District No." << c_arr[i].district->getId() << " :" << endl;
            os << c_arr[i].candidateList << endl;
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


bool CandidatesArray::save(ostream& out) const{

	out.write(rcastcc(&_logSize), sizeof(_logSize));
	if (!out.good()) {
		std::cout << "Error writing" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < _logSize; i++) {
		int districtID = _arr[i]->district->getId();
		out.write(rcastcc(&districtID), sizeof(districtID));
		if (!out.good()) {
			std::cout << "Error writing" << std::endl;
			exit(-1);
		}
		_arr[i]->candidateList.saveID(out);
	}
	return true;
}
}
