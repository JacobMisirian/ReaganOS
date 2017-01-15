#ifndef vfs_h
#define vfs_h

typedef struct {
	char name [128];
} dirEntry_t;

typedef struct {
	char name [128];
} fileEntry_t;

typedef struct {
	char name [128];
	char root [128];
	void (* createDir) 		(const char *);
	void (* createFile) 	(const char *);
	void (* deleteDir) 		(const char *);
	void (* deleteFile) 	(const char *);
	int  (* dirExists) 		(const char *);
	int  (* fileExists) 	(const char *);
	stream_t * (* openFile) (const char *);
} fileSystem_t;

#endif
