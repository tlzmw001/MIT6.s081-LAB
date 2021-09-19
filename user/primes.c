#include "kernel/types.h"
#include "user/user.h"

void process(int p[])
{
	close(p[1]);
	int prime;
	if(read(p[0], &prime ,4))
	{
		printf("prime %d\n", prime);
		int pp[2];
		pipe(pp);
		if(fork()==0)
		{
			process(pp);
		}
		else
		{
			close(pp[0]);
			int i;
			while(read(p[0], &i, 4))
			{
				if(i%prime != 0)
					write(pp[1], &i, 4);
			}
			close(pp[1]);
			wait(0);
		}
	}
}
int main(int argc, char *argv[])
{
	int p[2];
	pipe(p);
	if(fork()==0)
	{
		process(p);
	}
	else
	{
		close(p[0]);
		for(int i=2; i<36; ++i)
		{
			write(p[1], &i, 4);
		}
		close(p[1]);
		wait(0);
	}
	exit(0);
}
