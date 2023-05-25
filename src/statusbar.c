#include "sscalc-gui.h"

static gboolean timer_started = FALSE;

static gint timeout(gpointer data)
{
	struct application *app = data;
	timer_started = FALSE;
	gtk_statusbar_pop(app->statusbar, 0);
	return G_SOURCE_REMOVE;
}

void statusbar_update(struct application *app, const char *str)
{
	static guint time_id = 0;

	if (timer_started) {
		g_source_remove(time_id);
		gtk_statusbar_pop(app->statusbar, 0);
	}
	time_id = g_timeout_add_seconds (4, timeout, app);
	timer_started = TRUE;

	gtk_statusbar_push(app->statusbar, 0, str);
}