#include "types.h"

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
	char *temp1 = argv[2];
	char *temp2 = argv[3];
	char *temp3 = argv[4];
	while (*temp1++ != '.');
	temp1--;
	if(strcmp(temp1,".bmp") == 0)
	{
		printf ("argv[2] validated successfully\n");
	}

	while (*temp2++ != '.');
	temp2--;
	if (strcmp(temp2,".txt") == 0)
	{
		printf ("argv[3] validated successfully\n");
	}
	
	while (*temp3++ != '.');
	temp3--;
	if(strcmp(temp3,".bmp") == 0)
	{
		printf ("argv[4] validated successfully\n");
	}
	
	return e_success;
}

Status read_and_validate_decode_args(char *argv[], EncodeInfo *encInfo)
{
	char *temp1 = argv[2];
	while (*temp1++ != '.');
	temp1--;
	if(strcmp(temp1,".bmp") == 0)
	{
		printf ("argv[2] validated successfully\n");
	}
	return e_success;
}

