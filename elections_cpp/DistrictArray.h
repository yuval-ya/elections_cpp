#pragma once
#include "District.h"

namespace elections {
	class DistrictArray
	{
		// A Dynamic Array of District Pointers.
		// Used to store Districts by division into district id (index in the array - 1)

	private:
		District** _arr;
		int _log_size;
		int _pys_size;

		void resize(int new_size);
		void check_valid_idx(int idx) const;
	public:
		DistrictArray(int size = 0);
		DistrictArray(const DistrictArray&) = delete;
		~DistrictArray();

		// return District according to the id received
		// Notice: get(1) return District No.1
		District& get(int id);
		const District& get(int id) const;
		void set(int idx, District* d);

		// add new District to the array in the next empty cell
		void add(const District& d);

		int get_length() const { return _log_size; }
		void set_length(int new_size);
		void print() const;

		// return District according to the index received
		// Notice: arr[0] = District No.1
		District& operator[](int idx);
		const District& operator[](int idx) const;

		// add new cell for Party in each District in the array
		void add_party_to_district();
	};

}