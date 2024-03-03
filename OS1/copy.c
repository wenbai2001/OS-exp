#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// #include <time.h>
#include <sys/time.h>

#define BUFF_SIZE 1024

int main(int argc, char *argv[])
{
  int copy_fd, to_fd, Readsum, WriteRes;
  char buf[BUFF_SIZE]; 

  
  if (argc != 3)
  {
    printf("输入参数不正确！\n");
    printf("请输入两个参数，前一个参数为目标文件名，后一个参数为被复制的文件名 ！\n");
    return -1;
  }

  struct timeval start, end;
  
  gettimeofday(&start, NULL);


  copy_fd = open(argv[2], O_RDONLY);
  if (copy_fd == -1)
  {
    printf("open %s error\n", argv[2]);
    return -1;
  }

 
  to_fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if (to_fd == -1)
  {
    printf("create %s error\n", argv[1]);
    return -1;
  }

  while (1)
  {

    Readsum = read(copy_fd, buf, sizeof(buf));
    if (Readsum == -1)
    {
      printf("read %s error\n", argv[2]);
      return -1;
    }
    else if (Readsum > 0)
    {
  
      WriteRes = write(to_fd, buf, Readsum);
      if (WriteRes != Readsum)
      {
        printf("write %s error\n", argv[1]);
        return -1;
      }
    }
  
    else if (Readsum == 0)
    {
      printf("copy %s complete\n", argv[2]);
 
      gettimeofday(&end,NULL);
      suseconds_t msec = end.tv_usec-start.tv_usec;
      time_t sec = end.tv_sec-start.tv_sec;
      printf("time used : %lu.%lus\n",sec,msec);

      break;
    }
  }

  return 0;
}
