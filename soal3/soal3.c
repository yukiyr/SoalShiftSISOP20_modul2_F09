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
	int status, status2, status3, status4, status5, status6, status7;

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
						char *argv2[5] = {"cp", "-r", "/home/test/SISOP2/DUA/SHIFT/jpg", "/home/test/modul2", NULL};
	                                        execv("/bin/cp", argv2);
                                                pid_t child_id_6;
                                                child_id_6 = fork();
                                                if (child_id_6 == 0) {
							DIR *direktori;
							struct dirent *dir;
							direktori = opendir("/home/test/modul7/jpg");
							while ((dir = readdir(direktori)) != NULL)
							{
								if (is_file(dir->d_name))
								{
	                                                		char *argv[4] = {"mv", dir->d_name, "/home/test/modul2/sedaap", NULL};
                                                			execv("/bin/mv", argv);
								} else {
                                                                        char *argv[4] = {"mv", dir->d_name, "/home/test/modul2/indomie", NULL};
                                                                        execv("/bin/mv", argv);
								}
							}
							closedir(direktori);
						} else {
							while ((wait(&status6)) > 0);
							DIR *direktori2;
							struct dirent *dir2;
							direktori2 = opendir("/home/test/modul2/indomie");
							while ((dir2 = readdir(direktori2)) != NULL)
							{
								pid_t child_id_7;
								child_id_7 = fork();
								char satu[50];
								char dua[50];
								char tiga[50];
								strcpy(satu, "/home/test/modul2/indomie/");
								strcpy(dua, strcat(satu,dir2->d_name));
								strcpy(tiga, strcat(dua,"/coba1.txt"));
								if (child_id_7 == 0) {
                                                                        char *argv[3] = {"touch", tiga, NULL};
                                                                        execv("/usr/bin/touch", argv);
								} else {
									while ((wait(&status7)) > 0);
									sleep(3);
                                                                	pid_t child_id_8;
                                                                	child_id_8 = fork();
                                                                	char empat[50];
                                                                	strcpy(empat, strcat(dua,"/coba2.txt"));
                                                                	if (child_id_8 == 0) {
                                                                        	char *argv[3] = {"touch", empat, NULL};
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
