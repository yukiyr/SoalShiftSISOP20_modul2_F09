#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

int main() {
  pid_t pid, sid;

  pid = fork();
  int inc = 0;

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
	pid_t child_id;
	int status;
	child_id = fork();
        time_t raw;
        struct tm *timeinfo;
        char tanggal[40];
        time(&raw);
        timeinfo = localtime(&raw);
        strftime(tanggal, sizeof(tanggal), "%Y-%m-%d_%H:%M:%S", timeinfo); 
	if (child_id < 0) {
		exit(EXIT_FAILURE);
	}
	if (child_id == 0) {
		char *argv[4] = {"mkdir", "-p", tanggal, NULL};
		execv("/bin/mkdir", argv); 
	} else {
		while ((wait(&status)) > 0);
		pid_t child_id_2;
		int status2, i=0;
		child_id_2 = fork();
		if (child_id_2 == 0)
		{
			while (i<20)
			{
        			time_t raw2;
        			struct tm *timeinfo2;
        			char tanggal2[40];
        			time(&raw2);
        			timeinfo2 = localtime(&raw2);
        			strftime(tanggal2, sizeof(tanggal2), "%Y-%m-%d_%H:%M:%S", timeinfo2); 
				char alamat[50];
				sprintf(alamat, "https://picsum.photos/%ld", ((raw2%1000)+100));
				pid_t child_id_3;
				child_id_3 = fork();
				if (child_id_3 == 0) {
					chdir(tanggal);
					execl("/usr/bin/wget", "wget", "-O", tanggal2, alamat, NULL);
				}
				i++;
				sleep(5);
			}

			char namazip[50];
			sprintf(namazip, "%s.zip", tanggal);
                        char *argv2[5] = {"zip", "-rm", namazip, tanggal, NULL};
                        execv("/usr/bin/zip", argv2);
		}
	}
	//berjalan setiap 30 detik
	sleep(30);
  }
}
