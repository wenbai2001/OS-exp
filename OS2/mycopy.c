asmlinkage long sys_mycopy(const char* file1, const char* file2)
{
	char buf[128]; 

	mm_segment_t old_fs = get_fs(); 
	set_fs(KERNEL_DS); 

	int f_read, f_write;

	f_read = sys_open(file1,O_RDONLY,0);
	if(f_read == -1)
		return -1;

	f_write = sys_open(file2, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR); 
	if(f_write == -1)
		return -1;

	int num;
	while((num = sys_read(f_read, buf, 128)) > 0)
	{
		sys_write(f_write, buf, num);
	}

	set_fs(old_fs); 
	return 0;
}
