#pragma once
#include "PersonList.h"

namespace elections {

class CandidatesArray
{
	// A Dynamic Array of district pointers and candidates.
	// Used to store lists of candidates by division into districts.

private:
	struct Tuple {
		const District* district;
		PersonList candidateList;
	};

	Tuple** _arr;
	int _logSize;
	int _pysSize;
	
	bool resize(int new_size);
	bool checkValidIdx(int idx) const;
public:
	CandidatesArray(int size = 0);
	CandidatesArray(const CandidatesArray&) = delete;
	~CandidatesArray();

	// return list of candidates according to the district id received
	PersonList& get(int district_id); 
    const PersonList& get(int district_id) const;
  
	// add empty list to the next empty cell
	bool add(const District* district);

	int getLength() const { return _logSize; }
	bool setLength(int new_size);

	// return list of candidates according to the index received
	Tuple& operator[](int idx);
	const Tuple& operator[](int idx) const;

	bool save(std::ostream& out) const;

	friend std::ostream& operator<<(std::ostream& os, const CandidatesArray& c_arr);
};


}
