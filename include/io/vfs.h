#ifndef vfs_h
#define vfs_h

#include <lib/stream.h>

typedef struct dirEntry {
	char name [128];
	int pos;
} dirEntry_t;

typedef struct fileEntry {
	char name [128];
	int pos;
} fileEntry_t;

typedef struct filesystem {
	char name [128];
	char root [128];
	void (* createDir) 		(const char *);
	void (* createFile) 	(const char *);
	void (* deleteDir) 		(const char *);
	void (* deleteFile) 	(const char *);
	int  (* dirExists) 		(const char *);
	int  (* fileExists) 	(const char *);
	dirEntry_t * (* getDirListing) 	 (const char *, dirEntry_t * entry);
	fileEntry_t * (* getFileListing) (const char *, fileEntry_t * entry);
	stream_t * (* openFile) (const char *);
	struct filesystem * next;
} filesystem_t;

void vfs_createDir 		(const char * path);
void vfs_createFile 	(const char * path);
void vfs_deleteDir 		(const char * path);
void vfs_deleteFile 	(const char * path);
int  vfs_dirExists 		(const char * path);
int  vfs_fileExists 	(const char * path);
dirEntry_t * vfs_getDirListing 	 (const char * path, dirEntry_t * entry);
fileEntry_t * vfs_getFileListing (const char * path, fileEntry_t * entry);
stream_t * vfs_openFile 		 (const char * path);

#endif 
