//
// Created by feer on 19/5/21.
//

#include "sscalc-gui.h"

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);

	setupGUI();

	gtk_main ();

	return (0);
}
