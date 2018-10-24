#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>		// for strstr

#include <physfs.h>

#define TRUE	1
#define FALSE	0

// Compile with: 
// gcc -std=c99 -m32 -o paklist paklist.c -lphysfs
int main(int argc, char **argv)
{
	// require a path/pak argument or spit out the usage
	if (argc < 2)
	{
		printf("Usage: %s <path1> [path2 ...]\n", argv[0]);
		printf("The \"maps\" directory will be searched in each path\n");
		return EXIT_SUCCESS;
	}

	PHYSFS_init(NULL);
	PHYSFS_permitSymbolicLinks(TRUE);

	// add each path from the cmdline
	for (uint8_t path = 1; path < argc; path++) 
	{
		PHYSFS_addToSearchPath(argv[path], TRUE);
	} 


	// get pointer to all files in ./maps path	
	char **maps = PHYSFS_enumerateFiles("maps");

	char *token;
	const char *delimiter = ".";

	// loop through all the files
	for (char **i = maps; *i != NULL; i++) 
	{
		// only work on .bsp* files
		if (strstr(*i, ".bsp") != NULL) 
		{
			// split the map filename by the "." and spit out the left side
			token = strtok(*i, delimiter);
			printf("%s\n", token);
		}
	}

	PHYSFS_freeList(maps);

	return EXIT_SUCCESS;
}

