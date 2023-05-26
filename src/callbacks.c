//
// Created by feer on 31/5/21.
//

#include "sscalc-gui.h"
#include "libcalc/src/calc.h"


#define BUTTON_CLICKED_CALLBACK(BUTTON, TEXT)                       \
		void on_button_##BUTTON##_clicked (struct application *app) \
		{                                                           \
            text_insert(GTK_EDITABLE(app->text_in), TEXT);          \
		}

BUTTON_CLICKED_CALLBACK(sine,    "sin(")
BUTTON_CLICKED_CALLBACK(cosine,  "cos(")
BUTTON_CLICKED_CALLBACK(tangent, "tan(")
BUTTON_CLICKED_CALLBACK(log_10,  "log(")
BUTTON_CLICKED_CALLBACK(log_e,   "ln(")
BUTTON_CLICKED_CALLBACK(abs,     "|")
BUTTON_CLICKED_CALLBACK(pi,      "π")
BUTTON_CLICKED_CALLBACK(euler,   "e")

BUTTON_CLICKED_CALLBACK(num_0,   "0")
BUTTON_CLICKED_CALLBACK(num_1,   "1")
BUTTON_CLICKED_CALLBACK(num_2,   "2")
BUTTON_CLICKED_CALLBACK(num_3,   "3")
BUTTON_CLICKED_CALLBACK(num_4,   "4")
BUTTON_CLICKED_CALLBACK(num_5,   "5")
BUTTON_CLICKED_CALLBACK(num_6,   "6")
BUTTON_CLICKED_CALLBACK(num_7,   "7")
BUTTON_CLICKED_CALLBACK(num_8,   "8")
BUTTON_CLICKED_CALLBACK(num_9,   "9")
BUTTON_CLICKED_CALLBACK(dot,     ".")
BUTTON_CLICKED_CALLBACK(exp,     "E")

BUTTON_CLICKED_CALLBACK(open_bracket, "(")
BUTTON_CLICKED_CALLBACK(close_bracket,")")
BUTTON_CLICKED_CALLBACK(plus,         "+")
BUTTON_CLICKED_CALLBACK(minus,        "-")
BUTTON_CLICKED_CALLBACK(multiply,     "×")
BUTTON_CLICKED_CALLBACK(divided,      "/")
BUTTON_CLICKED_CALLBACK(sqrt,         "√(")
BUTTON_CLICKED_CALLBACK(ans,          "ANS")


void on_button_equal_clicked (struct application *app)
{
	// This string points to internally allocated storage in the
	// widget and must not be freed, modified or stored.
	const gchar *input = gtk_entry_get_text(app->text_in);
	gchar str_out[MAX_EXPR_LEN] = "";

	if(strlen(input) > 0)
	{
		process_input(input, &app->calc_data, str_out, sizeof str_out);
	}

	GtkTextIter iter;
	gtk_text_buffer_get_start_iter(app->buffer_out, &iter);
	gtk_text_buffer_insert(app->buffer_out, &iter, str_out, -1);

	if(app->calc_data.errFlag == E_NONE)
		gtk_entry_buffer_set_text(app->buffer_in, "", 0);
}

void on_menu_clear_activate (struct application *app)
{
	(void)app;
	clear_input();
}

void on_menu_clear_all_activate (struct application *app)
{
	(void)app;
	clear_all();
}

void on_text_in_changed (struct application *app)
{
//	const gchar *in = gtk_entry_get_text(app->text_in);
//	(void) in;
}

void on_copy_clipboard(struct application *app)
{
	int selection_bound, cursor_position;
	g_object_get(G_OBJECT(app->text_in),
				 "selection-bound", &selection_bound,
				 "cursor-position", &cursor_position, NULL);
	gboolean text_in_selected = abs(selection_bound - cursor_position);

	if (text_in_selected) {
		statusbar_update(app, "Selection copied to the clipboard");
		g_signal_emit_by_name(G_OBJECT(app->text_in), "copy-clipboard", NULL);
	}
	else {
		gboolean text_out_selected = gtk_text_buffer_get_has_selection(GTK_TEXT_BUFFER(app->buffer_out));

		if (text_out_selected) {
			statusbar_update(app, "Selection copied to the clipboard");
			g_signal_emit_by_name(G_OBJECT(app->text_out), "copy-clipboard", NULL);
		}
		else {
			// Copy the value of ANS to the clipboard
			if (gtk_text_buffer_get_char_count(GTK_TEXT_BUFFER(app->buffer_out)) > 0 &&
					app->calc_data.errFlag == E_NONE)
			{
				statusbar_update(app, "ANS value copied to the clipboard");
				GtkClipboard *clip = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
				gchar ans_str[128];
				snprintf(ans_str, 128, "%.*g", DECIMAL_DIGITS, app->calc_data.ans);
				gtk_clipboard_set_text(clip, ans_str, (gint) strlen(ans_str));
			}
		}
	}
}

void on_cut_clipboard(struct application *app)
{
	g_signal_emit_by_name(G_OBJECT(app->text_in), "cut-clipboard", NULL);
	gtk_statusbar_pop(app->statusbar,0);
	statusbar_update(app, "Cut");
}

void on_paste_clipboard(struct application *app)
{
	g_signal_emit_by_name(G_OBJECT(app->text_in), "paste-clipboard", NULL);
	statusbar_update(app, "Pasted");
}

void show_about_dialog(struct application *app)
{
	static gboolean init = FALSE;
	if (!init) {
		GdkPixbuf *app_logo = gdk_pixbuf_new_from_resource("/org/gtk/SSCalc/sscalc.png", NULL);
		gchar *auth[] = {"Fernando Coda", "fcoda@pm.me", "github.com/feer9",NULL};
		gtk_show_about_dialog (/*GTK_WINDOW(app->window),*/NULL,
		                       "program-name", "Simple Scientific Calc",
		                       "logo", app_logo,
		                       "title", ("About SSCalc"),
							   "authors", auth,
							   "comments", "Just another simple but functional (kinda) calculator.",
		                       NULL);
		g_object_unref(G_OBJECT(app_logo));
		init = TRUE;
	}
	else {
		gtk_show_about_dialog(NULL, NULL, NULL);
	}
}
