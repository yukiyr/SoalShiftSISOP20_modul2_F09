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
