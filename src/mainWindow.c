//
// Created by feer on 29/5/21.
//

#include "sscalc-gui.h"

#include "libvarious/src/strings.h"


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

	GdkPixbuf *app_logo = gdk_pixbuf_new_from_resource("/org/gtk/SSCalc/sscalc.png", NULL);
	gtk_window_set_icon (GTK_WINDOW (app.window), app_logo);
	g_object_unref(G_OBJECT(app_logo));

	gtk_widget_show (app.window);
}

static void set_signals(GtkBuilder *builder)
{
	g_signal_connect(app.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(app.window, "key_press_event", G_CALLBACK(keys_handler), &app);

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
							 "activate", G_CALLBACK(CALLBACK), &app)

	CONNECT_MENU_CALLBACK(menu_cut,       on_cut_clipboard);
	CONNECT_MENU_CALLBACK(menu_copy,      on_copy_clipboard);
	CONNECT_MENU_CALLBACK(menu_paste,     on_paste_clipboard);
	CONNECT_MENU_CALLBACK(menu_clear,     on_menu_clear_activate);
	CONNECT_MENU_CALLBACK(menu_clear_all, on_menu_clear_all_activate);
	CONNECT_MENU_CALLBACK(menu_about,     show_about_dialog);

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
	app.calc_data.index=1;
}

void set_input(const gchar *str)
{
	gtk_entry_buffer_set_text(app.buffer_in, str, -1);
}

void input_scroll(int n) {
	const char *buf;
	int listIndex = calc_getLastIndex(app.calc_data.list);
	int displayIndex = app.calc_data.index;

	if (n > 0 && app.calc_data.list && app.calc_data.list->prev == NULL) {
		buf = "";
		displayIndex += n;
	}
	else if(displayIndex > listIndex) {
		buf = calc_getLastExpr(app.calc_data.list);
		displayIndex += n;
	}
	else {
		buf = calc_scroll(&app.calc_data.list, n);
		displayIndex += n;
	}

	if (displayIndex < 1 )
		displayIndex = 1;
	else if(displayIndex > listIndex+1)
		displayIndex = listIndex+1;

	app.calc_data.index = displayIndex;

	set_input(buf);
	gtk_editable_set_position(GTK_EDITABLE(app.text_in), -1);
}

/*static gboolean cb_char_equal(gunichar ch, gpointer user_data)
{
	(void) user_data;
	return (ch == '=');
}

void set_input_last_expression(struct application *p_app)
{
	GtkTextIter start_iter, end_iter;
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(p_app->buffer_out), &start_iter);
	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(p_app->buffer_out), &end_iter);

	if (gtk_text_iter_forward_find_char(&end_iter, cb_char_equal, NULL, NULL))
	{
		gchar buf[MAX_EXPR_LEN];
		gchar *expr = gtk_text_iter_get_text(&start_iter, &end_iter);
		size_t len = strnlen(expr, sizeof buf) - 1;

		strncpy(&buf[1], expr, sizeof buf - 3);
		buf[0] = '(';
		buf[len + 1] = ')';
		buf[len + 2] = '\0';

		set_input(buf);
		gtk_editable_set_position(GTK_EDITABLE(p_app->text_in) , -1);

		free(expr);
	}
}*/

void clear_input(void)
{
	gtk_entry_buffer_delete_text(app.buffer_in, 0, -1);
}

static void clear_output(void)
{
	gtk_text_buffer_set_text(app.buffer_out, "", -1);
	calc_clearData(&app.calc_data);
}

void clear_all(void)
{
	clear_input();
	clear_output();
}

static gboolean keys_handler(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	(void) widget;
	guint val = event->keyval;
	struct application *p_app = data;
	gboolean handled = FALSE;

	if(event->is_modifier) return handled;

	switch (val)
	{
		case GDK_KEY_Escape:
			if(gtk_entry_get_text_length(p_app->text_in) > 0)
				clear_input();
			else
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
		case GDK_KEY_Up:
			input_scroll(-1);
			break;
		case GDK_KEY_Down:
			input_scroll( 1);
			break;
		default:
		//	g_debug("Other key pressed");
			break;
	}
	return handled;
}

void process_input(const gchar *input, struct calculator_data *data, gchar *str_out, size_t len)
{
	int *err = &data->errFlag;

	calc_solveExpression(input, data);

	if(*err == E_NONE)
	{
		snprintf(str_out, len, "%s = %.*g\n",
						input, DECIMAL_DIGITS, data->ans);
	}
	else if(*err == E_SYNTAX)
	{
		strcpy(str_out, "SYNTAX ERROR\n");
	}
	else if(*err == E_MATH)
	{
		strcpy(str_out,  "MATH ERROR\n");
	}

	g_debug("equal clicked:\n\n"
			"\tinput: %s\n"
			"\tresult: %lf\n"
			"\tsResult: %s",
			input, data->ans, str_out);
}

void text_insert(GtkEditable *widget, gchar *text)
{
	gint cursor_pos = gtk_editable_get_position(widget);
	gtk_editable_insert_text(widget, text, -1, &cursor_pos);
	gtk_editable_set_position(widget, cursor_pos);
}
