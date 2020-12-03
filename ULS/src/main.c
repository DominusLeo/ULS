#include "uls.h"
#include <stdio.h>


void traverse(char *fn, int indent) {
  DIR *dir;
  struct dirent *entry;
  int count;
  char path[1025];
  struct stat info;

  for (count=0; count<indent; count++) printf("  ");
  printf("%s\n", fn);

  if ((dir = opendir(fn)) == NULL)
    perror("opendir() error");
  else {
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_name[0] != '.') {
        strcpy(path, fn);
        strcat(path, "/");
        strcat(path, entry->d_name);
        if (stat(path, &info) != 0)
          fprintf(stderr, "stat() error on %s: %s\n", path,
                  strerror(errno));
        else if (S_ISDIR(info.st_mode))
               traverse(path, indent+1);
      }
    }
    closedir(dir);
  }
}

// void traverse(char *dirname)
// {
//   DIR *dir;
//   struct dirent *ent;
// //   int count;
// //   char path[1025];
// //   struct stat info;

//    printf("First pass on '%s':\n",dirname);
//    if ((dir = opendir(dirname)) == NULL)
//    {
//      perror("Unable to open directory");
//      exit(1);
//    }
//    while ((ent = readdir(dir)) != NULL)
//      printf("%s\n",ent->d_name);

//    printf("Second pass on '%s':\n",dirname);
//    rewinddir(dir);
//    while ((ent = readdir(dir)) != NULL)
//      printf("%s\n",ent->d_name);
//    if (closedir(dir) != 0)
//      perror("Unable to close directory");
// }

int main(int argc,char *argv[])
{
  (void)argv;
  (void)argc;
  //  traverse("/", 0);
  traverse(argv[1], 0);
   exit(0);
}
