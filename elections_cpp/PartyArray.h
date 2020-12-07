#pragma once
#include "Party.h"

class PartyArray
{
	// A Dynamic Array of Party Pointers.
	// Used to store Parties by division into party id (index in the array - 1)

private:
	Party** _arr;
	int _log_size;
	int _pys_size;
	
	void resize(int new_size);
	void check_valid_idx(int idx) const;
public:
    PartyArray(int size = 0);
	PartyArray(const PartyArray&) = delete;
	~PartyArray();

	// return Party according to the id received
	// Notice: get(1) return Party No.1
	Party& get(int id);
	int get_length() const { return _log_size; }

	void set(int idx, Party* d);
	void set_length(int new_size);
	
	// add new Party to the array in the next empty cell
	void add(const Party& d);

	// add new cell for District in each Party in the array
	void add_district_to_party();

	void print() const;

	// return Party according to the index received
	// Notice: arr[0] = Party No.1
	Party& operator[](int idx); 
	const Party& operator[](int idx) const; 
};
