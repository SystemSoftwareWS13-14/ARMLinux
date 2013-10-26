#include <sys/sysinfo.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define MB 1000000

void printHelloWorld();
int printSysInfo();
void printErrno(char* p_str);

int main( int argc, const char* argv[])
{
        printHelloWorld();
        if(printSysInfo() != 0)
        {
                return -1;
        }

        sleep(999999999);

        return 0;
}

void printHelloWorld()
{
        printf("Hello User world\n");
}

int printSysInfo()
{
        struct sysinfo l_sysinfo;
        if(sysinfo(&l_sysinfo) != 0)
        {
                printErrno( "Could not get sysInfo");
                return -1;
        }

        printf("Uptime: %lu\n", l_sysinfo.uptime);
        printf("Total RAM: %lu MB\n", l_sysinfo.totalram / MB);
        printf("Free RAM: %lu MB\n", l_sysinfo.freeram / MB);
        printf("Process Count: %hi\n", l_sysinfo.procs);
        printf("Page size: %d\n", l_sysinfo.mem_unit);
        return 0;
}

void printErrno(char* p_str)
{
        fprintf(stderr, "%s: %d;%s\n", p_str, errno, strerror(errno));
}
