#ifdef __WIN32__
  #include <windows.h>
  #include <string.h>
  #include <limits.h>

  char * ResourceLocator_getFullPath(const char * file) {
    char buff[MAX_PATH];
    GetModuleFileName(NULL, buff, MAX_PATH);
    char path[MAX_PATH]; 
    for(int i = strlen(buff); i > 0; i--) {
      char curr = buff[i];
      if(curr == '\\') {
        strncpy(path, buff, i+1);
        break;
      }
    }
    char * fullPath = malloc(strlen(path) + strlen(file) + 1);
    strcat(fullPath,path);
    strcat(fullPath,file);
    return fullPath;
  }
#elif __linux__
  #include <stdio.h>
  #include <stdlib.h>
  #include <linux/limits.h>
  #include <unistd.h>
  #include <string.h>

  char * ResourceLocator_getFullPath(const char * file) {
    char buff[PATH_MAX];
    int len = readlink("/proc/self/exe", buff, PATH_MAX);
    char path[PATH_MAX];
    for(int i = strlen(buff); i > 0; i--) {
      char curr = buff[i];
      if(curr == '/') {
        strncpy(path, buff, i+1);
        break;
      }
    }
    char * fullPath = malloc(strlen(path) + strlen(file) + 1);
    fullPath[0] = '\0';
    strcat(fullPath,path);
    strcat(fullPath,file);
    fullPath[strlen(fullPath)] = '\0';
    return fullPath; 
  }
#endif
