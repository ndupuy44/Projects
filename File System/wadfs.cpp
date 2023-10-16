/*#include <iostream>
#include <fuse.h>
#include <string.h>
#include <string>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include "Wad.h"
using namespace std;

Wad* wadFile;
struct fuse_operations fuseOperations;

static int getattr_callback(const char *path, struct stat *st) {
    memset(st, 0, sizeof(struct stat));
    string pathCopy = string(path);

    if (fileWad->isDirectory(pathCopy)) {
        st->st_mode = S_IFDIR | 0555;
        st->st_nlink = 2;
        return 0;
    }

    if (fileWad->isContent(pathCopy)) {
        st->st_mode = S_IFREG | 0444;
        st->st_nlink = 1;
        st->st_size = fileWad->getSize(pathCopy);
        return 0;
    }
    return -ENOENT;
}

static int open_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

static int opendir_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    if (fileWad->isContent(path)) {
        return fileWad->getContents(path, buf, size, offset);
    }

    return -ENOENT;
}

static int readdir_callback(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    vector<string> entries;
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    string pathCopy = path;
    if (pathCopy.length() >= 1 && pathCopy.substr(pathCopy.length() - 1) != "/") {
        pathCopy = pathCopy + "/";
    }
    if (pathCopy.size() == 0) {
        pathCopy = "/";
    }
    fileWad->getDirectory(pathCopy, &entries);
    for (string entry : entries) {
        filler(buf, entry.c_str(), NULL, 0);
    }

    return 0;
}

static int release_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

static int releasedir_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

int main(int argc, char *argv[]) {
    fuseOperations.getattr = getattr_callback;
    fuseOperations.open = open_callback;
    fuseOperations.read = read_callback;
    fuseOperations.readdir = readdir_callback;
    fuseOperations.opendir = opendir_callback;
    fuseOperations.release = release_callback;
    fuseOperations.releasedir = releasedir_callback;

    wadFile = Wad::loadWad(argv[1]);
    int arg = argc - 1;
    argv[1] = argv[2];
    argv[2] = NULL;

    fuse_main(arg, argv, &fuseOperations, NULL);
    delete(wadFile);
}*/