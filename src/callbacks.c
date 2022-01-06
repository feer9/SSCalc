//
// Created by feer on 31/5/21.
//

#include "sscalc-gui.h"

#include "libcalc/src/calc.h"
#include "libvarious/src/strings.h"

static void text_insert(GtkEditable *widget, gchar *text);
void process_input(const gchar *input, struct calculator_data *data, gchar *str_out);

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
BUTTON_CLICKED_CALLBACK(num_7,   "7")
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
	const gchar *input = gtk_entry_get_text(app->text_in);
	gchar str_out[128] = "";

	if(strlen(input) > 0)
	{
		process_input(input, &app->calc_data, str_out);
	}

	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_line (app->buffer_out, &iter, 0);
	gtk_text_buffer_insert(app->buffer_out, &iter, str_out, -1);

	if(app->calc_data.errFlag == E_NONE)
		gtk_entry_buffer_set_text(app->buffer_in, "", 0);
}

void process_input(const gchar *input, struct calculator_data *data, gchar *str_out)
{
	double result = 0.0;
	int *err = &data->errFlag;
	double *ans = &data->ans;

	result = solveExpression(input, *ans, err);

	if(*err == E_NONE)
	{
		snprintf(str_out, 128, "%s = %.*g\n",
						input, DECIMAL_DIGITS, result);
	}
	else if(*err == E_SYNTAX)
	{
		strcpy(str_out, "SYNTAX ERROR\n");
	}
	else if(*err == E_MATH)
	{
		strcpy(str_out,  "MATH ERROR\n");
	}

	*ans = result;

	g_debug("equal clicked:\n"
			"\tinput: %s\n"
			"\tresult: %lf\n"
			"\tsResult: %s",
			input, result, str_out);
}

void text_insert(GtkEditable *widget, gchar *text)
{
	gint cursor_pos = gtk_editable_get_position(widget);
	gtk_editable_insert_text(widget, text, -1, &cursor_pos);
	gtk_editable_set_position(widget, cursor_pos);
}
