#include <arch/pit.h>
#include <arch/i386/textscreen.h>
#include <kernel/debugShell.h>
#include <lib/stdio.h>
#include <lib/string.h>

static void interpretCmd (const char * cmd);

void debugShell_start () {
	printf ("ReaganOS Debug Shell\nUse help for a list of commands.\n");
	
	char cmd [50];
	while (1) {
		printf ("[debug]# ");
		readLine (cmd);
		interpretCmd (cmd);
	}
}

static void interpretCmd (const char * cmd) {
	size_t len = strlen (cmd);
	char * out [len];
	
	strsplit (cmd, ' ', out);
	
	if (strcmp (out, "echo") == 0) {
		while (strsplit (cmd, ' ', out) != NULL) {
			printf ("%s ", out);
		}
		printf ("\n");
	} else if (strcmp (out, "tty") == 0) {
		if (strsplit (cmd, ' ', out) == NULL) {
			printf ("Current tty: %d\n", textscreen_getTty ());
		} else {
			textscreen_setTty (atoi (out));
		}
	}
}
