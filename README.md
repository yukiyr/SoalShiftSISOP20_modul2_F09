LAPORAN RESMI
SISTEM OPERASI



KELOMPOK : F9

**Oleh:**

Yuki Yanuar Ratna

05111740000023

Rafif Ridho

05111840000058

**Asisten Pembimbing:**

Ibrahim Tamtama Adi

5111640000018

Departemen Teknik Infomatika

Fakultas Teknologi Elektro dan Informatika Cerdas

Institut Teknologi Sepuluh Nopember (ITS)

Surabaya

2020

**Soal**

1. Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:

a. Program menerima 4 argumen berupa:

i. Detik: 0-59 atau * (any value)

ii. Menit: 0-59 atau * (any value)

iii. Jam: 0-23 atau * (any value)

iv. Path file .sh

b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai

c. Program hanya menerima 1 config cron

d. Program berjalan di background (daemon)

e. Tidak boleh menggunakan fungsi system()

Contoh: ./program \* 34 7 /home/somi/test.sh

Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.

**Jawaban :**
**Cara Pengerjaan**

*Program soal1.c*
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>


int isApa(char isi[]){
    if(strlen(isi) == 1)
        if(isi[0] == '*')
            return 1;
    else{
        for(int i = 0; i < strlen(isi); i+=1){
            if(isi[i] > '0' || isi[i] < '9')
                return 2;
            
            
        }
    } 
}

int main(int argc, char** argv){
    if(argc == 5){
        
        int argumen[4];
        
        if (argumen[1] > 59 && argumen[2] > 59 && argumen[3] > 23){
            printf("argumen tidak valid\n");
            exit(EXIT_FAILURE);
        }
        else{
            for (int i = 1; i < 4; i++)
            {
                if(isApa(argv[i]) == 2){
                    argumen[i] = atoi(argv[i]);
                    if(argumen[i] < 0){
                    printf("argumen %d tidak valid\n", i); 
                    }
                }
                else if(isApa(argv[i]) == 1){
                    argumen[i] = -1;       
                }
                else
                {
                    printf("argumen %d tidak valid\n", i);
                    exit(EXIT_FAILURE);
                }
            }
        }


        pid_t pid, sid;
        pid = fork();

        if(pid > 0)
            exit(EXIT_SUCCESS);
        if(pid < 0)
            exit(EXIT_FAILURE);

        umask(0);

        sid = setsid();
        if(sid < 0)
            exit(EXIT_FAILURE);
        
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while(1){
            time_t waktu;
            struct tm* skrg;
            waktu = time(NULL);
            skrg = localtime(&waktu);
        
            if((skrg->tm_sec == argumen[1] || argumen[1] == -1) && (skrg->tm_min == argumen[2] || argumen[2] == -1) && (skrg->tm_hour == argumen[3] || argumen[3] == -1))
                {
                    pid_t child_id;
                    child_id = fork();
                    int status;
                    if(child_id == 0){
                        char *argumenexec[] = {"bash", argv[4],NULL};
                        execv("/bin/bash", argumenexec);
                    }
                }
            
            sleep(1);
        }
    }
    else
    {
        printf("argumen tidak valid\n");
        exit(EXIT_FAILURE);
    }
    
}
```
*program test.sh*
```
#!/bin/bash
mkdir "$(date)"
```

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshoot](img/ss.png)

**Soal**

2. Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program.

a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].

b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.

e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi. Buatlah program dalam mimpi Kiwa jadi nyata!

Catatan:

- Tidak boleh memakai system().

- Program utama harus ter-detach dari terminal

Hint:

- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran tertentu

- Epoch Unix bisa didapatkan dari time()

**Jawaban :**

**Cara Pengerjaan**

```
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

```

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshoot](img/modul22a.png)

**Soal**

3. Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).

a. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”.

b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.

c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.

d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”). Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat program tersebut.

Catatan :

- Tidak boleh memakai system().

- Tidak boleh memakai function C mkdir() ataupun rename().

- Gunakan exec dan fork

- Direktori “.” dan “..” tidak termasuk

**Jawaban :**

**Cara Pengerjaan**

```

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

```

**Kendala Yang Dialami**

-

**Screenshot**

![Screenshoot](img/modul23a.png)

![Screenshoot](img/modul23b.png)

![Screenshoot](img/modul23c.png)

![Screenshoot](img/modul23d.png)

