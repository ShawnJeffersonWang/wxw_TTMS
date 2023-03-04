#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/io.h>
#include "./View/Main_Menu.h"

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Main_Menu();
	return EXIT_SUCCESS;
}
