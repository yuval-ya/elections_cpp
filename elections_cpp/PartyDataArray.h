#pragma once
#include "Party.h"

namespace elections {

	class PartyDataArray
	{
		// A Dynamic Array of Party Pointers.
		// Used to store Parties by division into party id (index in the array - 1)

	private:
		struct Tuple {
			Party* party;
			int votes;
            int candidates;
		};

		Tuple** _arr;
		int _logSize;
		int _pysSize;

		bool resize(int new_size);
		bool checkValidIdx(int idx) const;
        static void bubbleSort(Tuple** arr, int size);

	public:
		PartyDataArray(int size = 0);
		PartyDataArray(const PartyDataArray&);
		~PartyDataArray();

		// return Party according to the id received
		// Notice: get(1) return Party No.1
		Tuple& get(int id);
		const Tuple& get(int id) const;
        int getPartyIdWithMaxVotes() const;

		int getLength() const { return _logSize; }

		bool set(int idx, Party* p, int votes = 0, int candidates = 0);
		bool setLength(int new_size);

		// add new Party to the array in the next empty cell
		const Tuple& add(Party* p);

        // Sort the party array by the number of candidates for each party
        void sortArrayByCandidates();
        
		// return Party according to the index received
		// Notice: arr[0] = Party No.1
		Tuple& operator[](int idx);
		const Tuple& operator[](int idx) const;
	};

}

