#include <stdio.h>

Status check_capacity(EncodeInfo *encInfo)
{
	printf ("HI\n");
//	fseek(encInfo->fptr_src_image,0,SEEK_END);
//	long s1 = ftell(encInfo->fptr_src_image);
//	rewind(encInfo->fptr_src_image);
	fseek(encInfo->fptr_secret,0,SEEK_END);
	int s2 = ftell(encInfo->fptr_secret);
	rewind(encInfo->fptr_secret);
	printf("size of secret: %d\n", s2);

	if(s2 > s1)
	{
		return e_failure;
	}
	return e_success;
}
