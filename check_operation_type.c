
OperationType check_operation_type(char *argv[])
{
	if (strcmp(argv[1], "-e") == 0)
	{
		return e_encode;
	}
	else if (strcmp(argv[1],"-d") == 0)
	{
		return e_decode;
	}
	else
	{
		return e_unsupported;
	}
}
