//
// Created by feer on 29/5/21.
//

#include "sscalc-gui.h"


static void set_signals(GtkBuilder *builder);
static void set_pointers(GtkBuilder *builder);
static gboolean keys_handler(GtkWidget *widget, GdkEventKey *event, gpointer data);


static struct application app = {0};



void setupGUI()
{
	setlocale (LC_ALL, "");

	GtkBuilder  *builder = gtk_builder_new_from_resource ("/org/gtk/SSCalc/sscalc.ui");

	set_pointers(builder);
	set_signals(builder);

//	g_object_unref (G_OBJECT (builder));

	gtk_widget_show (app.window);
}

static void set_signals(GtkBuilder *builder)
{
	g_signal_connect(app.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(app.window, "key_press_event", G_CALLBACK(keys_handler), NULL);

#define CONNECT_CALLBACK(BUTTON) \
		g_signal_connect_swapped(gtk_builder_get_object(builder, "button_"#BUTTON), \
		                 "clicked", G_CALLBACK(on_button_##BUTTON##_clicked), &app)

	CONNECT_CALLBACK(multiply);
	CONNECT_CALLBACK(equal);
	CONNECT_CALLBACK(plus);
	CONNECT_CALLBACK(sqrt);


	// Load each callback defined in the .glade file into the gtk API
	gtk_builder_connect_signals(builder, NULL);
}

static void set_pointers(GtkBuilder *builder)
{
	app.builder    = builder;
	app.window     = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	app.text_in    = GTK_ENTRY(gtk_builder_get_object(builder, "text_in"));
	app.text_out   = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_out"));
	app.buffer_in  = GTK_ENTRY_BUFFER(gtk_builder_get_object(builder, "buffer_in"));
	app.buffer_out = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "buffer_out"));
}


static void clear_input(void)
{
	gtk_entry_buffer_delete_text(app.buffer_in, 0, -1);
}

static void clear_output(void)
{
	gtk_text_buffer_set_text(app.buffer_out, "", -1);
}

static void clear_all(void)
{
	clear_input();
	clear_output();
}

void on_menu_discard_activate ()
{
	clear_all();
}

void on_text_in_changed (GtkEditable *text_in)
{
//	const gchar *in = gtk_entry_get_text(app.text_in);
	g_debug("text in changed");
}


static gboolean keys_handler(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	gboolean handled = FALSE;
	guint val = event->keyval;

	if(event->is_modifier) return handled;

	switch (val)
	{
		case GDK_KEY_Escape:
			clear_all();
			handled = TRUE;
			break;
		case GDK_KEY_Return:
		case GDK_KEY_KP_Enter:
			g_debug("enter key pressed");
			break;
		case GDK_KEY_KP_Add:
		case GDK_KEY_plus:
			g_debug("+ key pressed");
			break;
		case GDK_KEY_KP_Subtract:
		case GDK_KEY_minus:
			g_debug("- key pressed");
			break;
		case GDK_KEY_KP_Multiply:
		case GDK_KEY_asterisk:
			g_debug("* key pressed");
			on_button_multiply_clicked(&app);
			handled = TRUE;
			break;
		default:
			g_debug("Other key pressed");
			break;
	}
	return handled;
}
