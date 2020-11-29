#pragma once
#include "Party.h"

class PartyArray
{
private:
	Party** _arr;
	int _log_size;
	int _pys_size;
	void resize(int new_size);

public:
	explicit PartyArray(int size = 0);
	PartyArray(const PartyArray&) = delete;
	~PartyArray();

	Party& get(int id); /* Notice: get(1) return party No.1 */
	void set(int idx, Party* d);

	void add(const Party& d);
	int get_length() { return _log_size; }
	void set_length(int new_size);

	Party& operator[](int idx); /* return by index arr[0] = Party No.1 */
	const Party& operator[](int idx) const; 
};
