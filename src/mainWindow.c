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
	setlocale (LC_ALL, "en_US.UTF-8");

	GtkBuilder  *builder = gtk_builder_new_from_resource ("/org/gtk/SSCalc/sscalc.ui");

	set_pointers(builder);
	set_signals(builder);

	g_object_unref (G_OBJECT (builder));

	gtk_window_set_icon_name (GTK_WINDOW (app.window), "sscalc.png"); // fixme: nope, not working
	gtk_widget_show (app.window);
}

static void set_signals(GtkBuilder *builder)
{
	g_signal_connect(app.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(app.window, "key_press_event", G_CALLBACK(keys_handler), NULL);

#define CONNECT_CALLBACK(BUTTON) \
		g_signal_connect_swapped(gtk_builder_get_object(builder, "button_"#BUTTON), \
		                 "clicked", G_CALLBACK(on_button_##BUTTON##_clicked), &app)

	CONNECT_CALLBACK(sine);
	CONNECT_CALLBACK(cosine);
	CONNECT_CALLBACK(tangent);
	CONNECT_CALLBACK(log_10);
	CONNECT_CALLBACK(log_e);
	CONNECT_CALLBACK(abs);
	CONNECT_CALLBACK(pi);
	CONNECT_CALLBACK(euler);

	CONNECT_CALLBACK(num_0);
	CONNECT_CALLBACK(num_1);
	CONNECT_CALLBACK(num_2);
	CONNECT_CALLBACK(num_3);
	CONNECT_CALLBACK(num_4);
	CONNECT_CALLBACK(num_5);
	CONNECT_CALLBACK(num_6);
	CONNECT_CALLBACK(num_7);
	CONNECT_CALLBACK(num_8);
	CONNECT_CALLBACK(num_9);
	CONNECT_CALLBACK(dot);
	CONNECT_CALLBACK(exp);

	CONNECT_CALLBACK(open_bracket);
	CONNECT_CALLBACK(close_bracket);
	CONNECT_CALLBACK(plus);
	CONNECT_CALLBACK(minus);
	CONNECT_CALLBACK(multiply);
	CONNECT_CALLBACK(divided);
	CONNECT_CALLBACK(sqrt);
	CONNECT_CALLBACK(ans);
	CONNECT_CALLBACK(equal);


#define CONNECT_MENU_CALLBACK(MENU,CALLBACK) \
	g_signal_connect_swapped(gtk_builder_get_object(builder, #MENU), \
							 "activate", G_CALLBACK(CALLBACK), &app);

	CONNECT_MENU_CALLBACK(menu_cut,       on_cut_clipboard);
	CONNECT_MENU_CALLBACK(menu_copy,      on_copy_clipboard);
	CONNECT_MENU_CALLBACK(menu_paste,     on_paste_clipboard);
	CONNECT_MENU_CALLBACK(menu_clear,     on_menu_clear_activate);
	CONNECT_MENU_CALLBACK(menu_clear_all, on_menu_clear_all_activate);

	// Load each callback defined in the .ui file into the gtk API
	gtk_builder_connect_signals(builder, &app);
}

static void set_pointers(GtkBuilder *builder)
{
//	app.builder    = builder;
	app.window     = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	app.text_in    = GTK_ENTRY(gtk_builder_get_object(builder, "text_in"));
	app.text_out   = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_out"));
	app.buffer_in  = GTK_ENTRY_BUFFER(gtk_builder_get_object(builder, "buffer_in"));
	app.buffer_out = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "buffer_out"));
	app.statusbar  = GTK_STATUSBAR(gtk_builder_get_object(builder, "statusbar"));
	memset(&app.calc_data, 0, sizeof(struct calculator_data));
}


void clear_input(void)
{
	gtk_entry_buffer_delete_text(app.buffer_in, 0, -1);
}

static void clear_output(void)
{
	gtk_text_buffer_set_text(app.buffer_out, "", -1);
}

void clear_all(void)
{
	clear_input();
	clear_output();
}


static gboolean keys_handler(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	(void) widget; (void) data;
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
/*			g_signal_emit_by_name(GTK_BUTTON(gtk_builder_get_object(app.builder, "button_multiply")),
						 "clicked", 0);*/
			on_button_multiply_clicked(&app);
			handled = TRUE;
			break;
		default:
		//	g_debug("Other key pressed");
			break;
	}
	return handled;
}
