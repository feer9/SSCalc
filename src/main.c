#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "ui.h"

#if 1
#define DBGPRNT(...) {printf(__VA_ARGS__);fflush(stdout);}
#else
#define DBGPRNT(...)
#endif

#define NUM_DOT 10

typedef struct {
	uiWindow *window;
	uiBox *box;
	uiGrid *grid;
	uiMultilineEntry *resultsTextBox;
	uiEntry *entryTextBox;
	int i;
	char c;
} mainWindow_t;

void onButtonClicked(uiButton *b, void *data)
{
	mainWindow_t *mainWindow = (mainWindow_t *) data;
	char c = *uiButtonText(b);
	char *prevText = uiEntryText(mainWindow->entryTextBox);
	size_t prevLen = strlen(prevText);
	char newText[128] = "";

	if(prevLen < sizeof newText - 1)
	{
		strcpy(newText, prevText);
		newText[prevLen] = c;
		newText[prevLen+1] = '\0';
	}
	uiEntrySetText(mainWindow->entryTextBox, newText);
	DBGPRNT("in onButtonClicked: %c clicked\n", c);
}

void onEqualsClicked(uiButton *b, void *data)
{
	static int st = 0;
	if(st) {
		uiButtonSetText(b, "=");
	} else {
		uiButtonSetText(b, "JAJA");
	}
	st = !st;
}


int onClosing(uiWindow *w, void *data)
{
	mainWindow_t *m = (mainWindow_t*) data;
	DBGPRNT("in onClosing()\n");
	free(m);
	uiQuit();
	return 1;
}

int onShoudQuit(void *data)
{
	mainWindow_t *m = (mainWindow_t*) data;
	uiWindow *w = m->window;
	DBGPRNT("in onShouldQuit()\n");
	free(m);
	uiControlDestroy(uiControl(w));
	return 1;
}

extern inline int closeWindow(uiWindow *w, void *data) {
	return 1;
}

extern inline void closeWindowButton(uiButton *sender, void *window) {
	uiControlDestroy(uiControl(window));
}


void uiShowWindow_about(uiMenuItem *sender, uiWindow *window, void *data)
{
#if 1
	uiMsgBox(window,"About","Created by Fernando Coda");
#else
	uiWindow *aboutWindow = uiNewWindow("About", 180, 120, 0);
	uiBox *box = uiNewVerticalBox();
	uiButton *button = uiNewButton("Ok");
	uiLabel *message = uiNewLabel("Created by Fernando Coda");
	
	uiWindowSetChild(aboutWindow, uiControl(box));
	uiWindowOnClosing(aboutWindow, closeWindow, NULL);
	uiWindowSetMargined(aboutWindow, 1);
	uiBoxSetPadded(box,1);
	uiBoxAppend(box, uiControl(message), 1);
	uiBoxAppend(box, uiControl(button), 0);
	uiControlShow(uiControl(aboutWindow));
	uiButtonOnClicked(button, closeWindowButton, (void*) aboutWindow);
#endif
}



mainWindow_t *setMainWindow(uiWindow *w,
							uiBox *box,
							uiGrid *grid,
							uiMultilineEntry *resultsTextBox,
							uiEntry *entryTextBox )
{
	mainWindow_t *m = malloc(sizeof *m);
	if(m == NULL)
	{
		perror("malloc");
		uiControlDestroy(uiControl(w));
	//	uiQuit()
		exit(1);
	}

	m->window         = w;
	m->box            = box;
	m->grid           = grid;
	m->entryTextBox   = entryTextBox;
	m->resultsTextBox = resultsTextBox;

	return m;
}

void createMenus(void)
{
	uiMenu *menuFile = uiNewMenu("File");
	uiMenuAppendQuitItem(menuFile);

	uiMenu *menuHelp = uiNewMenu("Help");
	uiMenuItem *itemAbout = uiMenuAppendAboutItem(menuHelp);
	uiMenuItemOnClicked(itemAbout, uiShowWindow_about, NULL);
}

// Interface initialization
void uiConfigure(void)
{
	uiInitOptions o;
	memset(&o, 0, sizeof o);
	const char *err = uiInit(&o);
	if(err != NULL)
	{
		fprintf(stderr, "error initializing ui: %s\n", err);
		uiFreeInitError(err);
		exit(1);
	}
	createMenus();
}

//	uiLabel *l = uiNewLabel("this will be");

void uiShowWindow_mainWindow(void)
{
	uiWindow *w = uiNewWindow("Main Window", 240, 320, 1);
	uiBox *box = uiNewVerticalBox();
	uiGrid *grid = uiNewGrid();
	uiMultilineEntry *resultsTextBox = 
						uiNewNonWrappingMultilineEntry();
	uiEntry *entryTextBox = uiNewEntry();
	uiButton *b;

	mainWindow_t *mainWindow = setMainWindow(w, box, grid,
								resultsTextBox, entryTextBox);

	DBGPRNT("Main Window %p\n", (void *) w);


	// Main Window parameters
	uiWindowSetMargined(w, 1);
	uiWindowSetBorderless(w, 0);
	uiControlShow(uiControl(w));
	
	uiWindowOnClosing(w, onClosing, mainWindow);
	uiOnShouldQuit(onShoudQuit, mainWindow);

	// Set Box on main window
	uiWindowSetChild(w, uiControl(box));

	// Fill Box with text fields and grid
	uiBoxAppend(box, uiControl(resultsTextBox), 1);
	uiBoxAppend(box, uiControl(entryTextBox), 0);
	uiBoxAppend(box, uiControl(grid), 1);

	// Box parameters
	uiBoxSetPadded(box, 1);

	// Grid parameters
	uiGridSetPadded(grid, 1);

	// Output text box parameters
	uiMultilineEntrySetReadOnly(resultsTextBox, 1);
	uiMultilineEntryAppend(resultsTextBox, "RESULTS TEXT BOX");

	// Input text box parameters
//	uiEntryOnChanged(entryTextBox, NULL, NULL);

/*
	uiGridAppend(g, uiControl(l),
		0, 0, 1, 1,
		1, uiAlignCenter, 0, uiAlignStart);
*/
/*
void uiGridAppend(uiGrid *g, uiControl *c, 
int left, int top, int xspan, int yspan, 
int hexpand, uiAlign halign, int vexpand, uiAlign valign)
*/

	// TODO: crear los botones en una funcion
	// Add numerical buttons on grid
	int buttonNum = 7;
	char buttonText[] = "";
	int i,j, row=3;
	for(j=0; j<3; j++)
	{
		for(i=0; i<3; i++)
		{
			buttonText[0] = buttonNum + '0';
			b = uiNewButton(buttonText);
			uiButtonOnClicked(b, onButtonClicked, mainWindow);
	//						(void*) (uintptr_t) buttonNum);
			uiGridAppend(grid, uiControl(b),
				i, row, 1, 1,
				1, uiAlignFill, 1, uiAlignFill);

			buttonNum++;
		}
		row++;   buttonNum -= 6;
	}
	b = uiNewButton("0");
	uiButtonOnClicked(b, onButtonClicked, mainWindow);
	uiGridAppend(grid, uiControl(b),
		1, row, 1, 1,
		1, uiAlignFill, 1, uiAlignFill);

	b = uiNewButton(".");
	uiButtonOnClicked(b, onButtonClicked, mainWindow);
	uiGridAppend(grid, uiControl(b),
		2, row, 1, 1,
		1, uiAlignFill, 1, uiAlignFill);

	b = uiNewButton("=");
	uiButtonOnClicked(b, onEqualsClicked, mainWindow);
	uiGridAppend(grid, uiControl(b),
		3, row, 1, 1,
		1, uiAlignFill, 1, uiAlignFill);

	b = uiNewButton("+");
	uiButtonOnClicked(b, onButtonClicked, mainWindow);
	uiGridAppend(grid, uiControl(b),
		3, row-1, 1, 1,
		1, uiAlignFill, 1, uiAlignFill);

	b = uiNewButton("-");
	uiButtonOnClicked(b, onButtonClicked, mainWindow);
	uiGridAppend(grid, uiControl(b),
		3, row-2, 1, 1,
		1, uiAlignFill, 1, uiAlignFill);

}


int main(int argc, char *argv[])
{
	uiConfigure();
	uiShowWindow_mainWindow();
	uiMain();
	DBGPRNT("after uiMain()\n");
	
	uiUninit();
	DBGPRNT("after uiUninit()\n");
	
	return 0;
} 
