#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int is_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main() {
        pid_t child_id;
        int status, status2, status3, status4, status5, status6, status7, status8;

        child_id = fork();
  
        if (child_id < 0) {
                exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }

        if (child_id == 0) {
        // this is child
    
        char *argv[4] = {"mkdir", "-p", "/home/test/modul2", NULL};
                execv("/bin/mkdir", argv);
        } else {
                // this is parent
                while ((wait(&status)) > 0);
                pid_t child_id_2;
                child_id_2 = fork();
                if (child_id_2 == 0) {
                        char *argv[3] = {"mkdir", "/home/test/modul2/indomie", NULL};
                        execv("/bin/mkdir", argv);
                } else {
                        while ((wait(&status2)) > 0);
                        sleep(5);
                        pid_t child_id_3;
                        child_id_3 = fork();
                        if (child_id_3 == 0) {
                                char *argv[3] = {"mkdir", "/home/test/modul2/sedaap", NULL};
                                execv("/bin/mkdir", argv);
                        } else {
                                while ((wait(&status3)) > 0);
                                pid_t child_id_4;
				child_id_4 = fork();
                                if (child_id_4 == 0) {
                                        char *argv[4] = {"cp", "/home/test/Downloads/jpg.zip", "/home/test/modul2", NULL};
                                        execv("/bin/cp", argv);
                                } else {
                                        while ((wait(&status4)) > 0);
                                        pid_t child_id_5;
                                        child_id_5 = fork();
                                        if (child_id_5 == 0) {
                                                char *argv[3] = {"unzip", "/home/test/modul2/jpg.zip", NULL};
                                                execv("/usr/bin/unzip", argv);
                                        } else {
                                                while ((wait(&status5)) > 0);
                                                pid_t child_id_6;
                                                child_id_6 = fork();
                                                if (child_id_6 == 0)
                                                {
                                                        char *argv[5] = {"cp", "-r", "/home/test/SISOP2/DUA/SHIFT/jpg", "/home/test/modul2", NULL};
                                                        execv("/bin/cp", argv);
                                                } else {
                                                while ((wait(&status6)) > 0);
                                                DIR *direktori;
                                                struct dirent *dir;
                                                direktori = opendir("/home/test/modul2/jpg");
                                                while ((dir = readdir(direktori)) != NULL)
                                                {
	               					if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name, "..") == 0 )
        	        				{
                					        continue;
                					}
                                                        pid_t child_id_7;
                                                        child_id_7 = fork();
                                                        if (child_id_7 == 0) {
                                                                char satu[100];
                                                                char dua[100];
                                                                char tiga[100];
                                                                strcpy(satu, "/home/test/modul2/jpg/");
                                                                strcpy(tiga, dir->d_name);
                                                                strcpy(dua, strcat(satu,tiga));
                                                                if (is_file(dua))
                                                                {
                                                                        char *argv[4] = {"mv", dua, "/home/test/modul2/sedaap", NULL};
                                                                        execv("/bin/mv", argv);
                                                                } else {
                                                                        char *argv[4] = {"mv", dua, "/home/test/modul2/indomie", NULL};
                                                                        execv("/bin/mv", argv);
                                                                }
							}
                                                }
                                                closedir(direktori);
                                                while ((wait(&status6)) > 0);
                                                DIR *direktori2;
                                                struct dirent *dir2;
                                                direktori2 = opendir("/home/test/modul2/indomie");
                                                while ((dir2 = readdir(direktori2)) != NULL)
                                                {
                					if (strcmp(dir2->d_name,".") == 0 || strcmp(dir2->d_name, "..") == 0 )
                					{
                        					continue;
                					}
                                                	pid_t child_id_8;
                                                        child_id_8 = fork();
                                                        char empat[50];
                                                        char lima[50];
                                                        char enam[50];
                                                        strcpy(empat, "/home/test/modul2/indomie/");
                                                        strcpy(lima, strcat(empat,dir2->d_name));
                                                        strcpy(enam, strcat(lima,"/coba1.txt"));
                                                        if (child_id_8 == 0) {
                                                        	char *argv[3] = {"touch", enam, NULL};
                                                                execv("/usr/bin/touch", argv);
                                                        } else {
                                                                while ((wait(&status7)) > 0);
                                                                sleep(3);
                                                                pid_t child_id_9;
                                                                child_id_9 = fork();
                                                                char tujuh[50];
                                                                char delapan[50];
                                                                char sembilan[50];
                                                                strcpy(tujuh, "/home/test/modul2/indomie/");
                                                                strcpy(delapan, strcat(tujuh,dir2->d_name));
                                                                strcpy(sembilan, strcat(delapan,"/coba2.txt"));
                                                                if (child_id_9 == 0) {
                                                                	char *argv[3] = {"touch", sembilan, NULL};
                                                                        execv("/usr/bin/touch", argv);
                                                                }
							}

							}
						}
					}
				}
			}
		}
	}
}
