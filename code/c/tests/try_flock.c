#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  int fd = open("cheers", O_WRONLY|O_CREAT|O_TRUNC, 
    S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  if(fd != -1) {
    fprintf(stderr, "File opened.\n");
  } else {
    perror("Error occurred: ");
    exit(2);
  }
  sleep(4);
  if((flock(fd, LOCK_EX)) == -1) {
    perror("Error occurred: ");
    exit(2);
  } else {
    fprintf(stderr, "Successfully locked file.\n");
  }

  if((write(fd, "YAY", 3)) == -1) {
    perror("Error occurred: ");
    exit(2);
  }
  sleep(4);
  if((write(fd, "YAY", 3)) == -1) {
    perror("Error occurred: ");
    exit(2);
  }

  if((flock(fd, LOCK_UN)) == -1) {
    perror("Error occurred: ");
    exit(2);
  } else {
    fprintf(stderr, "Successfully unlocked file.\n");
  }

  close(fd);
  return 0;
}
