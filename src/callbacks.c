//
// Created by feer on 31/5/21.
//
#include "sscalc-gui.h"

static void text_insert(GtkEditable *widget, gchar *text);


void on_button_equal_clicked (struct application *app)
{
	static char i = '0';
	const gchar *in = gtk_entry_get_text(app->text_in);

	gtk_text_buffer_set_text(app->buffer_out, in, -1);
	gtk_entry_buffer_set_text(app->buffer_in, &i, 1);
	g_debug("equal clicked");
	++i;
}

void on_button_sqrt_clicked (struct application *app)
{
	text_insert(GTK_EDITABLE(app->text_in), "√(");
}

void on_button_multiply_clicked (struct application *app)
{
	text_insert(GTK_EDITABLE(app->text_in), "×");
}

void on_button_plus_clicked (struct application *app)
{
	text_insert(GTK_EDITABLE(app->text_in), "+");
}

void text_insert(GtkEditable *widget, gchar *text)
{
	gint cursor_pos = gtk_editable_get_position(widget);
	gtk_editable_insert_text(widget, text, -1, &cursor_pos);
	gtk_editable_set_position(widget, cursor_pos);
}
