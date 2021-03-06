// Exports2Def.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
	const int BUFFER_LENGTH = 4096;
	char line[BUFFER_LENGTH];
	const char delim[2] = " ";
	char *defFile = "";

	if (argc < 2 || strlen(argv[1]) == 0) {
		printf("Usage Exports2Def <exports_file>.\n");
		return 1;
	}

	FILE *f = fopen(argv[1], "rt");

	if (!f)	{
		printf("Couldn't open \"%s\" in read mode.\n", argv[1]);
		return 1;
	}

	char *pos = strrchr(argv[1], '.');
	if (pos) {
		defFile = (char *)malloc((pos - argv[1] + 1) * sizeof(char*));
		strncpy(defFile, argv[1], pos - argv[1]);
		defFile[pos - argv[1]] = '\0';
		strcat(defFile, ".def");
	}
	else {
		defFile = (char *)malloc((strlen(argv[1]) + 5) * sizeof(char*));
		strcpy(defFile, argv[1]);
		strcat(defFile, ".def");
	}

	FILE *fout = fopen(defFile, "wt");

	if (!fout) {
		fclose(f);

		printf("Couldn't open \"%s\" in write mode.\n", defFile);
		return 1;
	}

	fprintf(fout, "EXPORTS\n");

	bool found = false;

	while (!feof(f)) {
		if (!fgets(line, BUFFER_LENGTH, f))
			break;

		size_t len = strlen(line);

		if (len > 1 && line[len - 2] == '\r') {
			line[len - 2] = '\0';
			len -= 2;
		}
		else if (len > 0) {
			if (line[len - 1] == '\n' || line[len - 1] == '\r') {
				line[len - 1] = '\0';
				len -= 1;
			}
		}

		// we read all the functions, we're done
		if (found && len == 0)
			break;

		if (len == 0)
			continue;

		if (!found) {
			if (!strstr(line, "ordinal hint RVA"))
				continue;
			else
				found = true;

			// start of functions found,
			// read the next line (should be empty)
			if (!fgets(line, BUFFER_LENGTH, f))
				break;
		}
		else {
			char *token;
			int i = 0;

			for (token = strtok(line, delim); token; token = strtok(NULL, delim)) {
				if (i == 3)
					fprintf(fout, "%s", token);
				else if (i > 3)
					fprintf(fout, " %s", token);
				i++;
			}

			fprintf(fout, "\n");
		}
	}

	free(defFile);

	fclose(f);
	fclose(fout);

    return 0;
}
