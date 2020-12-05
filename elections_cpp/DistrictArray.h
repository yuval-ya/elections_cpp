#pragma once
#include "District.h"

class DistrictArray
{
private:
	District** _arr;
	int _log_size;
	int _pys_size;
	void resize(int new_size);
public:
    DistrictArray(int size = 0);
	DistrictArray(const DistrictArray&) = delete;
	~DistrictArray();

	District& get(int id); /* Notice: get(1) return District No.1 */
	void set(int idx, District* d);

	void add(const District& d);
	int get_length() const { return _log_size; }
	void set_length(int new_size);
	void print() const;

	District& operator[](int idx); /* return by index arr[0] = District No.1 */
	const District& operator[](int idx) const;

	void add_party_to_district();
};

