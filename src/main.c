#include "mainWindow.h"

int main(int argc, char *argv[])
{
	mainWindow_t mainWindow;
	uiConfigure();
	uiShowWindow_mainWindow(&mainWindow);
	uiMain();
	DBGPRNT("after uiMain()\n");
	
	uiUninit();
	DBGPRNT("after uiUninit()\n");
	
	return 0;
} 
