#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int p0[2], p1[2];
	char buf[8];
	pipe(p0);
	pipe(p1);
	if(fork() == 0)
	{
		close(p0[1]);
		close(p1[0]);
		if(read(p0[0], buf, 8)!=8)
		{
			printf("read error");
			exit(0);
		}
		printf("%d: received ping\n", getpid());
		if(write(p1[1], buf, 8)!=8)
		{
			printf("write error");
			exit(0);
		}
	}
	else
	{
		close(p0[0]);
		close(p1[1]);
		if(write(p0[1], buf, 8)!=8)
		{
			printf("write error");
			exit(0);
		}
		if(read(p1[0], buf, 8)!=8)
		{
			printf("read error");
			exit(0);
		}
		printf("%d: received pong\n", getpid());
		wait(0);
		exit(0);
	}
	exit(0);
}
