#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include "utils.h"

char* file_read(const char *path)
{
	FILE* file = fopen(path, "r");
	int len, end;
	char* buf;

	fseek(file, 0, SEEK_END);

	len = ftell(file);
	buf = malloc(len + 1);

	fseek(file, 0, SEEK_SET);
	end = fread(buf, sizeof(char), len, file);

	buf[end] = '\0';

	fclose(file);

	return buf;
}
