#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void print_permissions(mode_t mode) {
    char perms[11] = "----------";

    if (S_ISDIR(mode)) perms[0] = 'd';
    else if (S_ISLNK(mode)) perms[0] = 'l';
    else if (S_ISCHR(mode)) perms[0] = 'c';
    else if (S_ISBLK(mode)) perms[0] = 'b';
    else if (S_ISSOCK(mode)) perms[0] = 's';
    else if (S_ISFIFO(mode)) perms[0] = 'p';

    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';

    printf("%s", perms);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char timebuf[80];

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (lstat(entry->d_name, &file_stat) == -1) {
            perror("lstat");
            continue;
        }

        // Права доступу
        print_permissions(file_stat.st_mode);

        // Кількість жорстких посилань
        printf(" %ld", (long) file_stat.st_nlink);

        // Власник
        struct passwd *pw = getpwuid(file_stat.st_uid);
        printf(" %s", pw ? pw->pw_name : "?");

        // Група
        struct group *gr = getgrgid(file_stat.st_gid);
        printf(" %s", gr ? gr->gr_name : "?");

        // Розмір
        printf(" %5ld", (long) file_stat.st_size);

        // Час останньої модифікації
        strftime(timebuf, sizeof(timebuf), " %b %d %H:%M", localtime(&file_stat.st_mtime));
        printf("%s", timebuf);

        // Ім'я файлу
        printf(" %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
