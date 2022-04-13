#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
        while (1) {
                char input[50];
                fgets(input, 50, stdin);
                input[strlen(input) - 1] = '\0';
                if (strcmp(input, "hello\0") == 0) {
                        printf("Hello! Welcome to the extremely limited shell.\n");
                } else if (strcmp(input, "bye\0") == 0) {
                        printf("You input \"bye.\" See you around!\n");
                        break;
                } else if (strcmp(input, "assignment\0") == 0) {
                        printf("202 lab #1 (Spring 2022)\n");
                } else if (strcmp(input, "author\0") == 0) {
                        printf("Name: Ruochen Miao\nN-number: N12271287\nnetid: rm5327\n");
                } else if (strcmp(input, "section\0") == 0) {
                        printf("003\n");
                } else if (strcmp(input, "date\0") == 0 || strcmp(input, "dir\0") == 0 || strcmp(input, "echo\0") == 0) {
                        int parentOrChild;
                        int status;
                        parentOrChild = fork();
                        if (parentOrChild == 0) {
                                char* argv[] = {input,  NULL};
                                char* envp[] = {NULL};
                                char rs[] = "/bin/";
                                strcat(rs, input);
                                execve(rs, argv, envp);
                                exit(0);
                        } else {
                                wait(&status);
                        }
                } else {
                        printf("Unknown command.\n");
                }
        }
        return 0;
}
