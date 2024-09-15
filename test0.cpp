#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

bool fg = true;

void sig_handler(int signo)
{
	printf("Alarm handler!\n");
	fg = false;
}

int main(int argc, char *argv[])
{
	int ret;
	struct tms tm;
	struct timeval tv;
	struct itimerval delay;

	signal(SIGALRM, sig_handler);

	printf("%ld\n", time(nullptr));

	ret = alarm(5);
	if(ret < 0)
	{
		perror("alarm()");
		return 1;
	}

	while(fg);

	times(&tm);

	printf("%ld %ld\n", tm.tms_utime, tm.tms_stime);

	fg = true;

	delay.it_value.tv_sec = 5;
	delay.it_value.tv_usec = 0;
	delay.it_interval.tv_sec = 1;
	delay.it_interval.tv_sec = 0;

	ret = setitimer(ITIMER_REAL, &delay, nullptr);
	if(ret < 0)
	{
		perror("setitimer()");
		return 1;
	}

	while(fg);

	return 0;
}
