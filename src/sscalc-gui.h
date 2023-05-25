//
// Created by feer on 29/5/21.
//

#ifndef SSCALC_GUI_H
#define SSCALC_GUI_H

#ifdef G_LOG_DOMAIN
	#undef G_LOG_DOMAIN
#endif
#define G_LOG_DOMAIN "sscalc"
// execute with env G_MESSAGES_DEBUG=sscalc to enable debug messages

#include <gtk/gtk.h>
#include <gio/gio.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkbuildable.h>
#include <glib.h>
#include <locale.h>
#include <memory.h>

// https://stackoverflow.com/questions/17967997/gtk-pass-user-data-to-callback-using-glade

struct calculator_data {
	double ans;
	int errFlag;
	int i;
	char c;
} ;

struct application {
//	GtkBuilder *builder;
	GtkWidget *window;
	GtkEntryBuffer *buffer_in;
	GtkTextBuffer *buffer_out;
	GtkEntry *text_in;
	GtkTextView *text_out;
	GtkStatusbar *statusbar;
	struct calculator_data calc_data ;
} ;


#define BUTTON_CLICKED_CALLBACK_PROTOTYPE(BUTTON) \
		void on_button_##BUTTON##_clicked (struct application *)

BUTTON_CLICKED_CALLBACK_PROTOTYPE(sine);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(cosine);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(tangent);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(log_10);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(log_e);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(abs);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(pi);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(euler);

BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_0);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_1);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_2);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_3);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_4);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_5);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_6);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_7);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_8);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(num_9);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(dot);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(exp);

BUTTON_CLICKED_CALLBACK_PROTOTYPE(open_bracket);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(close_bracket);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(plus);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(minus);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(multiply);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(divided);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(sqrt);
BUTTON_CLICKED_CALLBACK_PROTOTYPE(ans);
extern BUTTON_CLICKED_CALLBACK_PROTOTYPE(equal);

void setupGUI();
void text_insert(GtkEditable *widget, gchar *text);
void process_input(const gchar *input, struct calculator_data *data, gchar *str_out);

void clear_all                  (void);
void clear_input                (void);
void on_text_in_changed         (struct application *);
void on_copy_clipboard          (struct application *);
void on_cut_clipboard           (struct application *);
void on_paste_clipboard         (struct application *);
void on_menu_clear_activate     (struct application *);
void on_menu_clear_all_activate (struct application *);

void statusbar_update(struct application *, const char *);


#endif // SSCALC_GUI_H
