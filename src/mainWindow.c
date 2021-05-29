//
// Created by feer on 29/5/21.
//

#include "sscalc-gui.h"

static void set_signals(GtkBuilder *builder);
static void set_pointers(GtkBuilder *builder);
static gboolean keys_handler(GtkWidget *widget, GdkEventKey *event, gpointer data);

static struct window win = {0};

void setupGUI()
{
	GtkBuilder  *builder = gtk_builder_new_from_resource ("/org/gtk/SSCalc/sscalc.ui");

	set_pointers(builder);
	set_signals(builder);

	g_object_unref (G_OBJECT (builder));

	gtk_widget_show (win.window);
}

static void set_signals(GtkBuilder *builder)
{
	g_signal_connect(win.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(win.window, "key_press_event", G_CALLBACK(keys_handler), NULL);

	// Load each callback defined in the .glade file into the gtk API
	gtk_builder_connect_signals(builder, NULL);
}

static void set_pointers(GtkBuilder *builder)
{
	win.window     = GTK_WIDGET(   gtk_builder_get_object(builder, "window"));
	win.text_in    = GTK_ENTRY(       gtk_builder_get_object(builder, "text_in"));
	win.text_out   = GTK_TEXT_VIEW(   gtk_builder_get_object(builder, "text_out"));
	win.buffer_in  = GTK_ENTRY_BUFFER(gtk_builder_get_object(builder, "buffer_in"));
	win.buffer_out = GTK_TEXT_BUFFER( gtk_builder_get_object(builder, "buffer_out"));
}


void on_button_equal_clicked ()
{
	static char i = '0';
	const gchar *in = gtk_entry_get_text(win.text_in);

	gtk_text_buffer_set_text(win.buffer_out, in, -1);
	gtk_entry_buffer_set_text(win.buffer_in, &i, 1);
	g_print("equal clicked\n");
	++i;
}


void on_menu_discard_activate ()
{
	gtk_text_buffer_set_text(win.buffer_out, "", -1);
	gtk_entry_buffer_delete_text(win.buffer_in, 0, -1);
}

void on_text_in_changed (GtkEditable *text_in)
{
//	const gchar *in = gtk_entry_get_text(win.text_in);
	g_print("text in changed\n");
}

static gboolean keys_handler(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if (event->keyval == GDK_KEY_Escape) {
		on_menu_discard_activate();
		return TRUE;
	}
	g_print("key pressed\n");
	return FALSE; // do not handle this, and let other handler do the job
}
