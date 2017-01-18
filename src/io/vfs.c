#include <stddef.h>
#include <stdint.h>

#include <io/vfs.h>
#include <lib/stream.h>
#include <lib/string.h>
#include <mm/heap.h>

static filesystem_t * filesystemHead = NULL;

static filesystem_t * findFS (const char * path);

void vfs_add (filesystem_t * fs) {
	if (filesystemHead == NULL) {
		filesystemHead = fs;
	} else {
		filesystem_t * temp = filesystemHead;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = fs;
	}
}

void vfs_createDir (const char * path) {
	filesystem_t * fs = findFS (path);
	return fs->deleteDir (path + strlen (fs->root));
}
void vfs_createFile (const char * path) {
	filesystem_t * fs = findFS (path);
	return fs->createFile (path + strlen (fs->root));
}
void vfs_deleteDir (const char * path) {
	filesystem_t * fs = findFS (path);
	return fs->deleteDir (path + strlen (fs->root));
}
void vfs_deleteFile (const char * path) {
	filesystem_t * fs = findFS (path);
	return fs->deleteFile (path + strlen (fs->root));
}
int vfs_dirExists (const char * path) {
	filesystem_t * fs = findFS (path);
	return fs->dirExists (path + strlen (fs->root));
}
int vfs_fileExists (const char * path) {
	filesystem_t * fs = findFS (path);
	return fs->fileExists (path + strlen (fs->root));
}
dirEntry_t * vfs_getDirListing (const char * path, dirEntry_t * entry) {
	filesystem_t * fs = findFS (path);
	return fs->getDirListing (path + strlen (fs->root), entry);
}
fileEntry_t * vfs_getFileListing (const char * path, fileEntry_t * entry) {
	filesystem_t * fs = findFS (path);
	return fs->getFileListing (path + strlen (fs->root), entry);
}
stream_t * vfs_openFile (const char * path) {
	filesystem_t * fs = findFS (path);
	return fs->openFile (path + strlen (fs->root));
}

static filesystem_t * findFS (const char * path) {
	filesystem_t * temp = filesystemHead;
	while (temp != NULL) {
		if (strStarts (path, temp->root) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}
