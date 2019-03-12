#include "calc.h"
#include "../../libvarious/src/strings.h"
#include <stdlib.h>

static void printHelp()
{
    puts("Scientific Calc v0.9");
    puts("Use 'q' or 'quit' to close the program");
}

static void analyze(int argc, char *argv[])
{
    int i;
    for(i=1; i<argc; i++)
    {
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            printHelp();
        }
        else
        {
            printf("Invalid argument '%s'\n", argv[i]);
            exit(1);
        }
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    if(argc != 1) {
        analyze(argc,argv);
    }

	consoleCalc();
    return 0;
}
