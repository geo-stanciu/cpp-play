#pragma once

class StringArray
{
public:
	StringArray();
	~StringArray();

	void add(char *str);
	void remove(int elem);
	int size();
	void clear();
	void sort();
	void sort(int cmpfunction(const void *a, const void *b));
	bool contains(char *elem);
	char * concat(char delim, bool add_delim_after_last = false);

	char *operator[] (int elem);

private:
	void add2matrix(char ***matrix, char *str, int *current_size);
	void free_matrix(char ***matrix, int size_y);

	char **array = NULL;
	int nr_items = 0;
	int capacity = 0;
};

