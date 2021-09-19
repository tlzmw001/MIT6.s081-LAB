#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
	int fd=open(argv[1], 0);
	printf("%d\n", fd);
	struct dirent de;
	if(read(fd, &de, sizeof(de))== sizeof(de))
	printf("%d, %s\n", de.inum, de.name);
	if(read(fd, &de, sizeof(de))== sizeof(de))
	printf("%d, %s\n", de.inum, de.name);
	if(read(fd, &de, sizeof(de))== sizeof(de))
	printf("%d, %s\n", de.inum, de.name);
	if(read(fd, &de, sizeof(de))== sizeof(de))
	printf("%d, %s\n", de.inum, de.name);
	if(read(fd, &de, sizeof(de))== sizeof(de))
	printf("%d, %s\n", de.inum, de.name);
	exit(0);
}
