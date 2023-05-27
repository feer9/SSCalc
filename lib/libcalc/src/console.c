#include "calc.h"
#include "../../libvarious/src/strings.h"
#include <stdlib.h>

static void printHelp()
{
    puts("Simple Scientific Calc " CONSOLE_CALC_VERSION);
    puts("Use 'q' or 'quit' to close the program");
}

static int oneShot(int argc, char *argv[])
{
    char buf[256] = "";
    int i, len=0, curr_len;
    const int sz = sizeof buf;

    for(i=1; i<argc; i++)
    {
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            printHelp();
            exit(0);
        }
        else
        {
			curr_len = (int)strlen(argv[i]);
	        if(len + curr_len > sz) {
	        	fprintf(stderr, "Buffer overflow.\n");
	            exit(1);
	        }
	        strcat(&buf[len], argv[i]);
	        len += curr_len;
        }
    }
    buf[len] = '\0';

	calculator_data_t cdata = {0};
	calculate(buf, &cdata);

    return cdata.errFlag;
}

int main(int argc, char *argv[])
{
    if(argc != 1) {
        return oneShot(argc, argv);
    }

	consoleCalc();
    return 0;
}
