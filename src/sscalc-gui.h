//
// Created by feer on 29/5/21.
//

#ifndef SSCALC_GUI_H
#define SSCALC_GUI_H

#include <gtk/gtk.h>
#include <gio/gio.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkbuildable.h>
#include <glib.h>


struct window {
	GtkWidget *window;
	GtkEntryBuffer *buffer_in;
	GtkTextBuffer *buffer_out;
	GtkEntry *text_in;
	GtkTextView *text_out;
} ;

void setupGUI();

#endif // SSCALC_GUI_H
