#pragma once

class DynamicArray
{
	// A Dynamic Array of Integers.
	
private:
	int* _arr;
	int _log_size;
	int _pys_size;
	
	void resize(int new_size);
	void check_valid_idx(int idx) const;
public:
	DynamicArray(int size = 0);
	DynamicArray(const DynamicArray&) = delete;
	~DynamicArray();

	int get(int id) const; // return value by id (arr[id-1])
	int get_max() const; // return the idx of the max number
	void set(int idx, int val) { _arr[idx] = val; }
	void add(int val = 0);

	int get_length() const { return _log_size; }
	void set_length(int new_size);

	int& operator[](int idx); //return value by index (arr[idx])
	const int& operator[](int idx) const;

};

