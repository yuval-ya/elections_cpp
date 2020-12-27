#pragma once
#include "Party.h"
#include <ostream>

namespace elections {

class PartyArray
{
	// A Dynamic Array of Party Pointers.

private:
	Party** _arr;
	int _logSize;
	int _pysSize;
	
	bool resize(int new_size);
	bool checkValidIdx(int idx) const;
public:
    PartyArray(int size = 0);
	PartyArray(const PartyArray&) = delete;
	~PartyArray();

	// return Party according to the id received
	Party& get(int id);
	const Party& get(int id) const;
  
	void makeEmpty();

	int getLength() const { return _logSize; }

	bool set(int idx, Party* p);
	bool setLength(int new_size);
	
	// add new Party to the array in the next empty cell
	Party& add(Party* party);
  
	// add new cell for District in each Party in the array
	bool addDistrictToParty(const District* district);

	void save(std::ostream& out) const;

	void print() const;
    
    // Sorting a pointer to Party array according to the total number of candidates
    // the party received in the election (implementaion of mergeSort)
    static void mergeSort(Party** arr,int l,int r);
    static void merge(Party** arr, int l, int m, int r);

	// return Party according to the index received
	Party& operator[](int idx); 
	const Party& operator[](int idx) const; 
};

}
