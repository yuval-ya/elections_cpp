#pragma once

class DynamicArray
{
private:
	int* _arr;
	int _log_size;
	int _pys_size;
	void resize(int new_size);

public:
	DynamicArray(int size = 0);
	DynamicArray(const DynamicArray&) = delete;
	~DynamicArray();

	int get(int party_id) const { return _arr[party_id - 1]; }
	int get_max() const; // return the idx of the max number
	void set(int idx, int val) { _arr[idx] = val; }
	void add(int val = 0);

	int get_length() const { return _log_size; }
	void set_length(int new_size);

	int& operator[](int idx); /* return by index arr[0] = Party No.1 */
	const int& operator[](int idx) const;

};

