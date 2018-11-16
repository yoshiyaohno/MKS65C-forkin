#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

unsigned int oof_random(void);
int young_boye(void);

unsigned int oof_random()
{
    int *p = malloc(4);
    int devrand;
    if( (devrand = open("/dev/urandom", O_RDONLY)) == -1 ) {
        printf("#### ERROR ACCESSING /dev/urandom ####\n\t%s\n",
                strerror(errno));
        return 0;
    }
    read( devrand, p, 4);
    if( close(devrand) ) {
        printf("#### ERROR CLOSING /dev/urandom ####\n\t%s\n",
                strerror(errno));
        return 0;
    }
    int out = *p;
    free(p);
    return out;
}

int young_boye()
{
    unsigned int wtime = oof_random()%16 + 5;
    printf("%i:\ttime 2 sleep\n\t(for %i seconds)\n", getpid(), wtime);
    sleep(wtime);
    printf("%i:\tI'm done, g'bye\n", getpid());
    exit(wtime);
}

int main()
{
    int st;
    printf("%i:\thmm today i will forke some processes\n", getpid());
    if(!fork()) young_boye();
    if(!fork()) young_boye();
    int winner = wait(&st);
    printf("%i:\tour winner is %i\n\t...completed in %i seconds.\n",
            getpid(), winner, WEXITSTATUS(st));
    return 0;
}
