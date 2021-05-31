//
// Created by feer on 29/5/21.
//

#ifndef SSCALC_GUI_H
#define SSCALC_GUI_H

#ifdef G_LOG_DOMAIN
	#undef G_LOG_DOMAIN
#endif
#define G_LOG_DOMAIN "sscalc"

#include <gtk/gtk.h>
#include <gio/gio.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkbuildable.h>
#include <glib.h>
#include <locale.h>

// https://stackoverflow.com/questions/17967997/gtk-pass-user-data-to-callback-using-glade
// code to

struct application {
	GtkBuilder *builder;
	GtkWidget *window;
	GtkEntryBuffer *buffer_in;
	GtkTextBuffer *buffer_out;
	GtkEntry *text_in;
	GtkTextView *text_out;
} ;

void setupGUI();

#define CLICKED_CALLBACK_PROTOTYPE(BUTTON) \
		void on_button_##BUTTON##_clicked (struct application *)

CLICKED_CALLBACK_PROTOTYPE(plus);
CLICKED_CALLBACK_PROTOTYPE(sqrt);
CLICKED_CALLBACK_PROTOTYPE(multiply);
CLICKED_CALLBACK_PROTOTYPE(equal);


#endif // SSCALC_GUI_H
