//
// Created by dev on 11/14/21.
//

#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "util.h"

#define BUFFER_SIZE 1024

int main()
{
	int ec = 0;
	char command[BUFFER_SIZE];
	printf("in>\n");
	fgets(command, BUFFER_SIZE, stdin);
	command[strcspn(command, "\n")] = 0;
	if (strcmp(command, "val") == 0)
		val(&ec);
	else if (strcmp(command, "ddx") == 0)
		ddx(&ec);
	else if (strcmp(command, "sum") == 0)
		sum(&ec);
	else if (strcmp(command, "dvd") == 0)
		dvd(&ec);
	else
		ec = bad_command_err;
	return ec;
}
