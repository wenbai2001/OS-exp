#include <sys/syscall.h>
#include <unistd.h>

int main()
{
	syscall(333, "111.txt", "222.txt");
	return 0;
}
