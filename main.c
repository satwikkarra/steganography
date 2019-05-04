#include <stdio.h>
#include "encode.h"
#include "encode.c"
#include "common.h"
#include "types.h"
#include <string.h>
#include <stdlib.h>
#include "test_encode.c"
#include "test_decode.c"
#include "read_and_validate_encode_args.c"
#include "check_operation_type.c"
#include "open_files.c"
#include "get_image_size_for_bmp.c"

int main(int argc, char *argv[])
{
	if (strcmp(argv[1],"-e") == 0)
	{
		if (read_and_validate_encode_args(argv,&encInfo) == e_success)
		{
			printf ("VALIDATION SUCCESSFUL\n");
		}
	}
	else if (strcmp(argv[1],"-d") == 0)
	{
		if (read_and_validate_decode_args(argv,&encInfo) == e_success)
		{
			printf ("VALIDATION SUCCESSFUL\n");
		}

	}
	else
	{
		printf ("UNSUPPORTED\n");
	}

	if (check_operation_type(argv) == e_encode)
	{		
        encInfo.src_image_fname = argv[2];
        encInfo.secret_fname = argv[3];
        encInfo.stego_image_fname = argv[4];
        if (open_files(&encInfo) == e_success)
		{
			printf ("Files opened\n");
		}
        if (get_image_size_for_bmp(encInfo.fptr_src_image) > get_file_size(encInfo.fptr_secret))
		{
			printf ("CAPACITY CHECKED\n");
		}
		else
		{
			printf ("FATAL ERROR\n");
		}
		test_encode();

	}
	else if (check_operation_type(argv) == e_decode)
	{
       decInfo.stego_image_fname = argv[2];
       if (argv[3] == NULL)
	   {
			decInfo.decode_info_fname = "default.txt";
	   }
	   else
	   	{
	   		decInfo.decode_info_fname = argv[3];
		}
       decInfo.src_image_fname = "beautiful.bmp";
       decInfo.secret_fname = "secret.txt";
	   test_decode();
	}
	else
	{
		printf ("unsupported\n`");
	}
}
