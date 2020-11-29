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
	explicit DistrictArray(int size = 0);
	DistrictArray(const DistrictArray&) = delete;
	~DistrictArray();

	District& get(int id); /* Notice: get(1) return District No.1 */
	void set(int idx, District* d);

	void add(const District& d);
	int get_length() { return _log_size; }
	void set_length(int new_size);

	District& operator[](int idx); /* return by index arr[0] = District No.1 */
	const District& operator[](int idx) const;
};

