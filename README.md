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

**Screenshot**
![Screenshot from 2020-03-13 14-06-44.png](Screenshot from 2020-03-13 14-06-44.png)

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

**Kendala Yang Dialami**

**Screenshot**

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

**Kendala Yang Dialami**

**Screenshot**
