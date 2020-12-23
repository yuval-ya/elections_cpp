#pragma once
#include "DistrictLoader.h"
#include "DividedDistrict.h"
#include "UnifiedDistrict.h"

namespace elections {

class DistrictArray
{
	// A Dynamic Array of District Pointers.
	// Used to store Districts by division into district id (index in the array - 1)

private:
	District** _arr;
	int _logSize;
	int _pysSize;
	
	void resize(int new_size);
	void checkValidIdx(int idx) const;
public:
    DistrictArray(int size = 0);
	DistrictArray(std::istream& in);
	DistrictArray(const DistrictArray&) = delete;
	~DistrictArray();

	void makeEmpty();

	// return District according to the id received
	// Notice: get(1) return District No.1
	District& get(int id);
    const District& get(int id) const;
  
    int getLength() const { return _logSize; }
    void setLength(int new_size);
    
	void set(int idx, District* d);
	// add new District to the array in the next empty cell
    District& add(District* d);
	void print() const;

	// return District according to the index received
	// Notice: arr[0] = District No.1
	District& operator[](int idx); 
	const District& operator[](int idx) const;

	// add new cell for Party in each District in the array
	void addPartyToDistrict(Party*);

	void save(std::ostream& out) const;
	void load(std::istream& in);
};

}
