//
// Created by feer on 31/5/21.
//
#include "sscalc-gui.h"

static void text_insert(GtkEditable *widget, gchar *text);

#define BUTTON_CLICKED_CALLBACK(BUTTON, TEXT)                       \
		void on_button_##BUTTON##_clicked (struct application *app) \
		{                                                           \
            text_insert(GTK_EDITABLE(app->text_in), TEXT);          \
		}

BUTTON_CLICKED_CALLBACK(sine,    "sin(");
BUTTON_CLICKED_CALLBACK(cosine,  "cos(");
BUTTON_CLICKED_CALLBACK(tangent, "tan(");
BUTTON_CLICKED_CALLBACK(log_10,  "log(");
BUTTON_CLICKED_CALLBACK(log_e,   "ln");
BUTTON_CLICKED_CALLBACK(abs,     "|");
BUTTON_CLICKED_CALLBACK(pi,      "π");
BUTTON_CLICKED_CALLBACK(euler,   "e");

BUTTON_CLICKED_CALLBACK(num_0,   "0");
BUTTON_CLICKED_CALLBACK(num_1,   "1");
BUTTON_CLICKED_CALLBACK(num_2,   "2");
BUTTON_CLICKED_CALLBACK(num_3,   "3");
BUTTON_CLICKED_CALLBACK(num_4,   "4");
BUTTON_CLICKED_CALLBACK(num_5,   "5");
BUTTON_CLICKED_CALLBACK(num_6,   "6");
BUTTON_CLICKED_CALLBACK(num_7,   "7");
BUTTON_CLICKED_CALLBACK(num_8,   "8");
BUTTON_CLICKED_CALLBACK(num_9,   "9");
BUTTON_CLICKED_CALLBACK(dot,     ".");
BUTTON_CLICKED_CALLBACK(exp,     "E");


BUTTON_CLICKED_CALLBACK(open_bracket, "(");
BUTTON_CLICKED_CALLBACK(close_bracket,")");
BUTTON_CLICKED_CALLBACK(plus,         "+");
BUTTON_CLICKED_CALLBACK(minus,        "-");
BUTTON_CLICKED_CALLBACK(multiply,     "×");
BUTTON_CLICKED_CALLBACK(divided,      "/");
BUTTON_CLICKED_CALLBACK(sqrt,         "√(");
BUTTON_CLICKED_CALLBACK(ans,          "ANS");


void on_button_equal_clicked (struct application *app)
{
	static char i = '0';
	const gchar *in = gtk_entry_get_text(app->text_in);

	gtk_text_buffer_set_text(app->buffer_out, in, -1);
	gtk_entry_buffer_set_text(app->buffer_in, &i, 1);
	g_debug("equal clicked");
	++i;
}


void text_insert(GtkEditable *widget, gchar *text)
{
	gint cursor_pos = gtk_editable_get_position(widget);
	gtk_editable_insert_text(widget, text, -1, &cursor_pos);
	gtk_editable_set_position(widget, cursor_pos);
}
