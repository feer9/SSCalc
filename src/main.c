#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "ui.h"


int onClosing(uiWindow *w, void *data)
{
	printf("in onClosing()\n");
	uiQuit();
	return 1;
}

int main(int argc, char *argv[])
{
	uiWindow *w;
	uiGrid *g;
	uiLabel *l;

	uiInitOptions o;
	memset(&o, 0, sizeof o);
	const char *err = uiInit(&o);

	w = uiNewWindow("Main Window", 240, 320, 1);
	uiWindowSetMargined(w, 1);

	g = uiNewGrid();
	uiWindowSetChild(w, uiControl(g));

	l = uiNewLabel("YEEEEEE");
	uiGridAppend(g, uiControl(l),
		0, 20, 2, 10,
		1, uiAlignCenter, 0, uiAlignFill);
	

	uiWindowOnClosing(w, onClosing, NULL);
	printf("main window %p\n", (void *) w);

	uiControlShow(uiControl(w));
	uiMain();
	printf("after uiMain()\n");
	
	uiUninit();
	printf("after uiUninit()\n");
	
	return 0;
} 
