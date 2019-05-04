#include "encode.h"

int test_encode()
{
     uint img_size;

    // Fill with sample filenames
        // Test open_files
    if (open_files(&encInfo) == e_failure)
    {
    	printf("ERROR: %s function failed\n", "open_files" );
    }
    else
    {
    	printf("SUCCESS: %s function completed\n", "open_files" );
    }

    // Test get_image_size_for_bmp
    img_size = get_image_size_for_bmp(encInfo.fptr_src_image);
    printf("INFO: Image size = %u\n", img_size);

	rewind(encInfo.fptr_src_image);

	if(copy_bmp_header(encInfo.fptr_src_image,encInfo.fptr_stego_image) == e_success)
	{
		printf("DONE\n");
	}
	

	if(encode_magic_string(MAGIC_STRING,&encInfo)==e_success)
	{
		printf("Magic String: ENCRYPTION AND COPYING DONE\n");
	}

	if(encode_secret_file_extn_size(encInfo.secret_fname,&encInfo) == e_success)
	{
		printf("FILE EXTENSION SIZE ENCRYPTED\n");
	}


	const char *file_extn = encInfo.secret_fname;
	while(*file_extn != '.')
	{
		file_extn++;
	}
	if(encode_secret_file_extn(file_extn, &encInfo) == e_success)
	{
		printf("FILE EXTENSION ENCRYPTED\n");
	}

	printf ("SECRET FILE SIZE: %d\n", get_file_size(encInfo.fptr_secret));
	encInfo.size_secret_file = get_file_size(encInfo.fptr_secret);
	
	if (encode_secret_file_size(encInfo.size_secret_file, &encInfo) == e_success)
	{
		printf ("SECRET FILE SIZE ENCRYPTED\n");
	}

	if(encode_secret_file_data(&encInfo) == e_success)
	{
		printf("SECRET FILE CONTENT ENCRYPTED\n");
	}
	if(copy_remaining_img_data(encInfo.fptr_src_image,encInfo.fptr_stego_image) == e_success)
	{
		printf("REMAINING BYTES COPIED\n");
	}
    return e_success;
}


