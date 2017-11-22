#include "stdafx.h"
#include "StringArray.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


StringArray::StringArray() {
}


StringArray::~StringArray() {
	Clear();
}

void StringArray::Add(char *str) {
	add2matrix(&array, str, &nr_items);
}

void StringArray::Remove(int elem) {
	assert(elem >= 0);
	assert(nr_items >= 0);
	assert(elem < nr_items);
	assert(array != NULL);

	free(array[elem]);

	for (int i = elem; i < nr_items - 1; i++) {
		array[i] = array[i + 1];
	}

	nr_items--;
}

int StringArray::Size() {
	return nr_items;
}

void StringArray::Clear() {
	free_matrix(&array, nr_items);
	nr_items = 0;
}

int default_cmp_function(const void *a, const void *b) {
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;

	const char * s1 = *ia;
	const char * s2 = *ib;

	return strcmp(s1, s2);
}

void StringArray::Sort() {
	Sort(&default_cmp_function);
}

void StringArray::Sort(int cmpfunction(const void *a, const void *b)) {
	if (!array)
		return;

	qsort(array, nr_items, sizeof(char *), cmpfunction);
}

char * StringArray::operator[] (int elem) {
	assert(elem >= 0);
	assert(nr_items >= 0);
	assert(array != NULL);

	return array[elem];
}

void StringArray::add2matrix(char ***matrix, char *str, int *current_size)
{
	assert(*current_size >= 0);

	if (capacity <= *current_size)
		(*matrix) = (char**)realloc((*matrix), (*current_size + 1) * sizeof(char*));

	(*matrix)[*current_size] = str;
	(*current_size)++;
}

void StringArray::free_matrix(char ***matrix, int size_y)
{
	if (matrix && (*matrix))
	{
		for (int i = 0; i < size_y; i++)
		{
			if ((*matrix)[i])
			{
				free((*matrix)[i]);
				(*matrix)[i] = NULL;
			}
		}

		free((*matrix));

		(*matrix) = NULL;
	}
}

