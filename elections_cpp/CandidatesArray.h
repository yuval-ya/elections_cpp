#pragma once
#include "PersonList.h"

class CandidatesArray
{
private:
	PersonList** _arr;
	int _log_size;
	int _pys_size;
	void resize(int new_size);

public:
	explicit CandidatesArray(int size = 0);
	CandidatesArray(const CandidatesArray&) = delete;
	~CandidatesArray();

	PersonList& get(int district_id); /* Notice: get(1) return PersonList No.1 */

	void add();
	int get_length() { return _log_size; }
	void set_length(int new_size);

	PersonList& operator[](int idx); /* return by index arr[0] = PersonList No.1 */
	const PersonList& operator[](int idx) const;
};
