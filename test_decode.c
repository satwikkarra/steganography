#include "encode.h"

int test_decode()
{
	
	
	if(open_decode_file(&decInfo) == e_success)
	{
		printf("STEGO IMAGE IS OPENED\n");
	}
	if(decode_magic_string(MAGIC_STRING,&decInfo)==e_success)
	{
		printf("MAGIC STRING ACQUIRED\n");
	}
	else
	{
		printf ("No magic string detected\n ");
			return 0;
	}
	if(decode_secret_file_extn_size(decInfo.secret_fname,&decInfo)==e_success)
	{
		printf("FILE EXTENSION SIZE ACQUIRED\n");
	}
	if(decode_secret_file_extn(decInfo.secret_fname,&decInfo)==e_success)
	{
		printf("FILE EXTENSION ACQUIRED\n");
	}

	if(decode_secret_file_data(decode_secret_file_size(&decInfo),&decInfo) == e_success)
	{
		printf("SECRET FILE DATA ACQUIRED\n");
	}
	return 0;
}

Status open_decode_file(EncodeInfo *decInfo)
{
	decInfo -> fptr_stego_image = fopen(decInfo -> stego_image_fname, "rb");

	if(decInfo -> fptr_stego_image == NULL)
	{
		perror("fopen");
		fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo ->stego_image_fname);
		return e_failure;
	}

	decInfo -> fptr_decode = fopen(decInfo -> decode_info_fname,"wb");
	
	if(decInfo -> fptr_decode == NULL)
	{
		perror("fopen");
		fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo -> decode_info_fname);
		return e_failure;
	}
	return e_success;
}


Status decode_magic_string(char *magic_string,EncodeInfo *decInfo)
{
	fseek(decInfo -> fptr_stego_image,54,SEEK_SET);
	char buff[8];
	char new = 0, s;
//	fprintf(decInfo ->fptr_decode, "Magic String:");
	for(int i = 0; i < strlen(magic_string); i++)
	{
		s = 0;
		memset(buff,0,8);
		fread(buff,1,8,decInfo -> fptr_stego_image);
		s = decode_lsb_tobyte(8, buff);
		//fprintf(decInfo->fptr_decode,"%c", s);
	}
//	fprintf(decInfo -> fptr_decode,"\n");
	if (s != '*')
	{	
		return e_failure;
	}
	return e_success;
}


/*Decode secret file extension size*/
Status decode_secret_file_extn_size(const char *secret_fname,EncodeInfo *decInfo)
{
	char *f = (char*)secret_fname;
	int count=0;
	while(*f != '.')
	{
		f++;
	}
	while(*f++)
	{
		count++;
	}
	int new=0;
	char *buff = malloc(count*8);

	fread(buff,1,count*8,decInfo -> fptr_stego_image);

//	fprintf(decInfo ->fptr_decode, "File extension Size:");

	int s=decode_lsb_tobyte(count*8, buff);

//	fprintf(decInfo->fptr_decode,"%d", s);
//	fprintf(decInfo -> fptr_decode,"\n");
	return e_success;
}

/*Decode secret file extension */
Status decode_secret_file_extn(const char *secret_fname,EncodeInfo *decInfo)
{
	char *f = (char*)secret_fname;
	int count=0;
	while(*f != '.')
	{
		f++;
	}
	while(*f++)
	{
		count++;
	}

//	fprintf(decInfo ->fptr_decode, "File extension name:");
	for(int i = 0; i < count ; i++)
	{
		char *buff = calloc(8,sizeof(char));
		fread(buff,1,8,decInfo -> fptr_stego_image);

		char s=decode_lsb_tobyte(8, buff);

//		fprintf(decInfo->fptr_decode,"%c", s);
	}
//	fprintf(decInfo -> fptr_decode,"\n");
	return e_success;
}

int decode_secret_file_size(EncodeInfo *decInfo)
{
	char buff[64];

	fread(buff,1,64,decInfo -> fptr_stego_image);

//	fprintf(decInfo -> fptr_decode, "File Extension size:");
	
	int s = decode_lsb_tobyte(64,buff);
	
//	fprintf(decInfo -> fptr_decode,"%d", s);
	
//	fprintf(decInfo -> fptr_decode, "\n");
	
	return s;
}

Status decode_secret_file_data(long file_size,EncodeInfo *decInfo)
{
//	fprintf(decInfo -> fptr_decode, "Secret file data:");
	for(int i = 0; i < file_size;i++)
	{
		char *buff = calloc(8,sizeof(char));
		fread(buff,1,8,decInfo -> fptr_stego_image);

		char s = decode_lsb_tobyte(8,buff);
	
		fprintf(decInfo -> fptr_decode,"%c", s);
	}
	
	fprintf(decInfo -> fptr_decode, "\n");
	return e_success;
}
int decode_lsb_tobyte(int size, char *image_data)
{
	int new = 0;
	for(int i = 0; i < size;i++)
	{
		if (i != (size - 1))
				new = (new | (*(image_data + i) & 1)) << 1;
			else
				new = (new | (*(image_data + i) & 1));
	}
	return new;
}
