#include <arch/pit.h>
#include <arch/i386/textscreen.h>
#include <io/vfs.h>
#include <kernel/debugShell.h>
#include <lib/stdio.h>
#include <lib/stream.h>
#include <lib/string.h>

static char * curDir = "/initrd/";

static void interpretCmd (const char * cmd);
static vgaColor_t strToVga (char * str);
static char * vgaToStr (vgaColor_t color, char * out);

void debugShell_start () {
	printf ("ReaganOS Debug Shell\nUse help for a list of commands.\n");
	
	char cmd [50];
	while (1) {
		printf ("[debug:%s]# ", curDir);
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
	}
	else if (strcmp (out, "cls") == 0) {
		textscreen_termCls ();
	}
	else if (strcmp (out, "tty") == 0) {
		if (strsplit (cmd, ' ', out) == NULL) {
			printf ("Current tty: %d\n", textscreen_getTty ());
		}
		else {
			textscreen_setTty (atoi (out));
		}
	}
	else if (strcmp (out, "bcol") == 0) {
		if (strsplit (cmd, ' ', out) == NULL) {
			char temp [10];
			printf ("Current bcol: %s\n", vgaToStr (textscreen_termGetBColor (), temp));
		}
		else {
			vgaColor_t col = strToVga (out);
			if (col == -1) {
				printf ("Error! Enter a valid color string!\n");
			}
			else {
				textscreen_termSetBColor (col);
			}
		}
	}
	else if (strcmp (out, "fcol") == 0) {
		if (strsplit (cmd, ' ', out) == NULL) {
			char temp [10];
			printf ("Current fcol: %s\n", vgaToStr (textscreen_termGetFColor (), temp));
		}
		else {
			vgaColor_t col = strToVga (out);
			if (col == -1) {
				printf ("Error! Enter a valid color string!\n");
			}
			else {
				textscreen_termSetFColor (strToVga (out));
			}
		}
	}
	else if (strcmp (out, "ls") == 0) {
		fileEntry_t * file = heap_alloc (sizeof (fileEntry_t));
		file->pos = 0;
		
		while (file->pos != -1) {
			printf ("%s ", vfs_getFileListing (curDir, file));
		}
		heap_free (file);
		printf ("\n");
	}
	else if (strcmp (out, "cat") == 0) {
		if (strsplit (cmd, ' ', out) == NULL) {
			printf ("Error! Enter a file name!");
		}
		else {
			char path [0xFF];
			stream_t * stream = vfs_openFile (strcat (curDir, out, path));
			if (stream == -1) {
				printf ("Error! File does not exist!\n");
			}
			else {
				while (stream_peek (stream) != -1) {
					printf ("%c", stream_read (stream));
				}
			}
		}
	}
}

static vgaColor_t strToVga (char * str) {
	strlow (str);
	if (strcmp (str, "black") == 0) {
		return VGA_COLOR_BLACK;
	}
	else if (strcmp (str, "blue") == 0) {
		return VGA_COLOR_BLUE;
	}
	else if (strcmp (str, "brown") == 0) {
		return VGA_COLOR_BROWN;
	}
	else if (strcmp (str, "cyan") == 0) {
		return VGA_COLOR_CYAN;
	}
	else if (strcmp (str, "green") == 0) {
		return VGA_COLOR_GREEN;
	}
	else {
		return -1;
	}
}

static char * vgaToStr (vgaColor_t color, char * out) {
	if (color == VGA_COLOR_BLACK) {
		out = "black";
	}
	else if (color == VGA_COLOR_BLUE) {
		out = "blue";
	}
	else if (color == VGA_COLOR_BROWN) {
		out = "brown";
	}
	else if (color == VGA_COLOR_CYAN) {
		out = "cyan";
	}
	else if (color == VGA_COLOR_GREEN) {
		out = "green";
	}
	else {
		return -1;
	}
	return out;
}
