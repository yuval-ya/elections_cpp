#pragma once
#include "Party.h"
#include <ostream>

namespace elections {

	class PartyDataArray
	{
		// A Dynamic Array of Party Pointers.
		// Used to store Parties by division into party id (index in the array - 1)

	private:
		struct Tuple {
			Party* party;
			int data;
		};

		Tuple* _arr;
		int _logSize;
		int _pysSize;

		bool resize(int new_size);
		bool checkValidIdx(int idx) const;

	public:
		PartyDataArray(int size = 0);
		PartyDataArray(const PartyDataArray&) = delete;
		~PartyDataArray();

		// return Party according to the id received
		// Notice: get(1) return Party No.1
		Party& get(int id);
		const Party& get(int id) const;

		int getLength() const { return _logSize; }

		bool set(int idx, Party* d);
		bool setLength(int new_size);

		// add new Party to the array in the next empty cell
		const PartyDataArray& add(const Party& d);

		void print() const;

		// Sorting a pointer to Party array according to the total number of candidates
		// the party received in the election (implementaion of mergeSort)
		static void mergeSort(Party** arr, int l, int r);
		static void merge(Party** arr, int l, int m, int r);

		// return Party according to the index received
		// Notice: arr[0] = Party No.1
		PartyDataArray& operator[](int idx);
		const PartyDataArray& operator[](int idx) const;
	};

}

