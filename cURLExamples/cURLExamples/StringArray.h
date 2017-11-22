#pragma once

class StringArray
{
public:
	StringArray();
	~StringArray();

	void Add(char *str);
	void Remove(int elem);
	int Size();
	void Clear();
	void Sort();

	char *operator[] (int elem);

private:
	void add2matrix(char ***matrix, char *str, int *current_size);
	void free_matrix(char ***matrix, int size_y);

	char **array = NULL;
	int nr_items = 0;
};

