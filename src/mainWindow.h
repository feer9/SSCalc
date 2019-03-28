#ifndef __MAIN_WINDOW_H
#define __MAIN_WINDOW_H

#ifndef DBGPRNT
	#if 0
	#define DBGPRNT(...) {printf(__VA_ARGS__);fflush(stdout);}
	#else
	#define DBGPRNT(...)
	#endif
#endif

#include "ui.h"
#include "../libs/libcalc/src/calc.h"
#include "../libs/libvarious/src/strings.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


typedef struct {
	uiWindow *window;
	uiBox *box;
	uiGrid *funcsGrid;
	uiGrid *numsGrid;
	uiMultilineEntry *resultsTextBox;
	uiEntry *entryTextBox;
	double ans;
	int errFlag;
	int i;
	char c;
} mainWindow_t;


// Public functions

// alloc memory for the main window struct
mainWindow_t *newMainWindow_t (void);

// Interface initialization
void uiConfigure(void);

// open new window with "about" info
void uiShowWindow_about(uiMenuItem *sender, uiWindow *window, void *data);

// open the main window
void uiShowWindow_mainWindow(mainWindow_t *mainWindow);


// callback function to confirm a close operation
static inline int closeWindow(uiWindow *w, void *data) {
	return 1;
}

// callback function to a button that closes a window
// receives the window pointer in the void* data pointer
static inline void closeWindowButton(uiButton *sender, void *window) {
	uiControlDestroy(uiControl(window));
}


// g: pointer to the grid to append the item
// c: pointer to the item to append to the grid
// left: COLUMN   ;   top: ROW
// xspan: number of blocks that this item will occupy, from 'left' to the right
// yspan: number of blocks that this item will occupy, from 'top' to the bottom
// hexpand: boolean: if true, the block try to expands horizontally
// halign: typedef for the behavior of the block, it will tend to allign at (start|center|end|fill) in the horizontal direction
// vexpand: boolean: if true, the block try to expands vertically
// valign: typedef for the behavior of the block, it will tend to allign at (start|center|end|fill) in the vertical direction
_UI_EXTERN void uiGridAppend(uiGrid *g, uiControl *c, int left, int top, int xspan, int yspan, int hexpand, uiAlign halign, int vexpand, uiAlign valign);


#endif // __MAIN_WINDOW_H