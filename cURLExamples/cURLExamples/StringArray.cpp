#include "stdafx.h"
#include "StringArray.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


StringArray::StringArray() {
}


StringArray::~StringArray() {
	clear();
}

void StringArray::add(char *str) {
	add2matrix(&array, str, &nr_items);
}

void StringArray::remove(int elem) {
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

int StringArray::size() {
	return nr_items;
}

void StringArray::clear() {
	free_matrix(&array, nr_items);
}

int default_cmp_function(const void *a, const void *b) {
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;

	const char * s1 = *ia;
	const char * s2 = *ib;

	return strcmp(s1, s2);
}

void StringArray::sort() {
	sort(&default_cmp_function);
}

void StringArray::sort(int cmpfunction(const void *a, const void *b)) {
	if (!array)
		return;

	qsort(array, nr_items, sizeof(char *), cmpfunction);
}

bool StringArray::contains(char *elem) {
	assert(elem != NULL);
	assert(nr_items >= 0);

	if (!array)
		return false;

	for (int i = 0; i < nr_items; i++)
	{
		if (array[i] && strcmp(array[i], elem) == 0)
			return true;
	}

	return false;
}

char * StringArray::concat(char delim, bool add_delim_after_last) {
	int size = 0;
	char *temp = NULL;

	temp = (char *)malloc(1 * sizeof(char));
	temp[0] = 0;

	for (int i = 0; i < nr_items; i++) {
		char *elem = array[i];
		int len = strlen(elem);

		temp = (char *)realloc(temp, size + len + 2);

		memcpy(&(temp[size]), elem, len);
		size += len + 1;
		temp[size - 1] = delim;
		temp[size] = 0;
	}

	if (!add_delim_after_last && temp && size > 0)
		temp[size - 1] = 0;

	return temp;
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

	if (capacity <= *current_size) {
		(*matrix) = (char**)realloc((*matrix), (*current_size + 1) * sizeof(char*));
		capacity++;
	}

	(*matrix)[*current_size] = str;
	(*current_size)++;
}

void StringArray::free_matrix(char ***matrix, int size_y)
{
	if (matrix && (*matrix)) {
		for (int i = 0; i < size_y; i++) {
			if ((*matrix)[i]) {
				free((*matrix)[i]);
				(*matrix)[i] = NULL;
			}
		}

		free((*matrix));

		(*matrix) = NULL;
	}

	nr_items = 0;
	capacity = 0;
}

