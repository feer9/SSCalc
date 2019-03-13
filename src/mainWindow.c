#include "mainWindow.h"


static void createButtons(mainWindow_t *m);
static void onButtonClicked(uiButton *b, void *data);
static void onEqualsClicked(uiButton *b, void *data);
static int onClosing(uiWindow *w, void *data);
static int onShoudQuit(void *data);
static void clearResults(uiMenuItem *sender, uiWindow *window, void *data);
static mainWindow_t *setMainWindow(mainWindow_t *m,
							uiWindow *w,
							uiBox *box,
							uiGrid *grid,
							uiMultilineEntry *resultsTextBox,
							uiEntry *entryTextBox );
static void createMenus(mainWindow_t *m);
static void createButtons(mainWindow_t *m);



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
	mainWindow_t *m = (mainWindow_t *) data;
	double result;
	char sResult[64];
	char *input = uiEntryText(m->entryTextBox);
	if(strlen(input) > 0)
	{
		result = resolverExpresion(input, m->ans, &m->errFlag);
		if(m->errFlag == E_NO)
		{
			uiMultilineEntryAppend(m->resultsTextBox, input);
			uiMultilineEntryAppend(m->resultsTextBox, " = ");
			snprintf(sResult, sizeof sResult, "%.*g\n",
							DECIMAL_DIGITS, result);
			uiMultilineEntryAppend(m->resultsTextBox, sResult);
		}
		else if(m->errFlag == E_SINTAXIS)
		{
			uiMultilineEntryAppend(m->resultsTextBox, "SYNTAX ERROR\n");
		}
		else if(m->errFlag == E_MATH)
		{
			uiMultilineEntryAppend(m->resultsTextBox, "MATH ERROR\n");
		}
	}
	uiEntrySetText( m->entryTextBox , "" );
	m->ans = result;
	DBGPRNT("in OnEqualsClicked():\n"
								"\tinput = %s\n"
								"\tresult = %lf\n"
								"\tsResult = %s",
								input, result, sResult);
}


int onClosing(uiWindow *w, void *data)
{
	DBGPRNT("in onClosing()\n");
	uiQuit();
	return 1;
}

int onShoudQuit(void *data)
{
	uiWindow *w = data;
	DBGPRNT("in onShouldQuit()\n");
	uiControlDestroy(uiControl(w));
	return 1;
}

void uiShowWindow_about(uiMenuItem *sender, uiWindow *window, void *data)
{
#if 1
	uiMsgBox(window,"About","Created by Fernando Coda");
#else
	// don't delete this since it's a good example of a new window
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

void clearResults(uiMenuItem *sender, uiWindow *window, void *data)
{
	mainWindow_t *m = (mainWindow_t*) data;
	uiMultilineEntrySetText(m->resultsTextBox, "");
}

mainWindow_t *newMainWindow_t (void)
{
	mainWindow_t *m = malloc(sizeof *m);
	if(m == NULL)
	{
		perror("malloc");
		uiQuit();
		exit(1);
	}
	return m;
}

mainWindow_t *setMainWindow(mainWindow_t *m,
							uiWindow *w,
							uiBox *box,
							uiGrid *grid,
							uiMultilineEntry *resultsTextBox,
							uiEntry *entryTextBox )
{
	m->window         = w;
	m->box            = box;
	m->grid           = grid;
	m->resultsTextBox = resultsTextBox;
	m->entryTextBox   = entryTextBox;
	m->ans            = 0.0;
	m->errFlag        = E_NO;
	m->i              = 0;
	m->c              = '\0';

	return m;
}

void createMenus(mainWindow_t *m)
{
	uiMenu *menuFile = uiNewMenu("File");
	uiMenuAppendQuitItem(menuFile);

	uiMenu *menuEdit = uiNewMenu("Edit");
	uiMenuItem *itemClearLog = uiMenuAppendItem(menuEdit, "Clear log");
	uiMenuItemOnClicked(itemClearLog, clearResults, m);

	uiMenu *menuHelp = uiNewMenu("Help");
	uiMenuItem *itemAbout = uiMenuAppendAboutItem(menuHelp);
	uiMenuItemOnClicked(itemAbout, uiShowWindow_about, NULL);
}

void uiConfigure()
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
}


void uiShowWindow_mainWindow(mainWindow_t *mainWindow)
{
	createMenus(mainWindow);
	uiWindow *w = uiNewWindow("Calculator", 240, 400, 1);
	uiBox *box = uiNewVerticalBox();
	uiGrid *grid = uiNewGrid();
	uiMultilineEntry *resultsTextBox = 
			uiNewNonWrappingMultilineEntry();
	uiEntry *entryTextBox = uiNewEntry();

	DBGPRNT("Main Window %p\n", (void *) w);


	setMainWindow(mainWindow, w, box, grid,
				resultsTextBox, entryTextBox);


	// Main Window parameters
	uiWindowSetMargined(w, 1);
	uiWindowSetBorderless(w, 0);
	uiControlShow(uiControl(w));
	
	uiWindowOnClosing(w, onClosing, NULL);
	uiOnShouldQuit(onShoudQuit, w);

	// Set Box on main window
	uiWindowSetChild(w, uiControl(box));

	// Fill Box with text fields and grid
	uiBoxAppend(box, uiControl(resultsTextBox), 1);
	uiBoxAppend(box, uiControl(entryTextBox), 0);
	uiBoxAppend(box, uiControl(grid), 0);

	// Box parameters
	uiBoxSetPadded(box, 1);

	// Grid parameters
	uiGridSetPadded(grid, 1);

	// Output text box parameters
	uiMultilineEntrySetReadOnly(resultsTextBox, 1);

	// Input text box parameters
//	uiEntryOnChanged(entryTextBox, NULL, NULL);

	// Add numerical buttons on grid
	createButtons(mainWindow);
}

// "macro" function to create a button and put it on a grid
extern inline void newButton(const char *s, void (*cb)(uiButton *b, void *data), 
		mainWindow_t *w, uiGrid *grid, int left, int top, int xspan, int yspan, 
		int hexpand, uiAlign halign, int vexpand, uiAlign valign)
{
	uiButton *b = uiNewButton(s);
	uiButtonOnClicked(b, cb, w);
	uiGridAppend(grid, uiControl(b),
		left, top, xspan, yspan,
		hexpand, halign, vexpand, valign);
}

void createButtons(mainWindow_t *m)
{
	uiGrid *grid = m->grid;
	int buttonNum = 1;
	char buttonText[] = "";
	int i,j, row=5, column;

	for(j=0; j<3; j++)
	{
		column=0;
		for(i=0; i<3; i++)
		{
			buttonText[0] = buttonNum + '0';

			newButton(buttonText, onButtonClicked, m, grid,
				column, row, 1, 1, 1, uiAlignFill, 1, uiAlignFill);

			buttonNum++;
			column++;
		}
		row--;
	}

	column = 0;
	row = 6;

	newButton("0", onButtonClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	column++;
	newButton(".", onButtonClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	column++;
	newButton("=", onEqualsClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	column++; row--;
	newButton("+", onButtonClicked, m, grid, column, row,
				1, 2, 1, uiAlignFill, 1, uiAlignFill);

	row--;
	newButton("-", onButtonClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	row--;
	newButton("*", onButtonClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	row--;
	newButton("/", onButtonClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	column--;
	newButton("^", onButtonClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	column--;
	newButton(")", onButtonClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	column--;
	newButton("(", onButtonClicked, m, grid, column, row,
				1, 1, 1, uiAlignFill, 1, uiAlignFill);

	return;
}