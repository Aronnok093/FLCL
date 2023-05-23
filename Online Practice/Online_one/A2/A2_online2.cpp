#include<stdio.h>
#include <string.h>
int main(){

    FILE*fs = fopen("input.c","r");
    char ch,pre_ch='\0';
    int cntsf=0;
    int cntpf=0;

    if(fs==NULL){
        printf("Something went wrong!!");
        return 1;
    }

    while((ch=fgetc(fs))!=EOF){
        if(ch=='s'){
            int i=0;
            char tmp[100]="";
            tmp[i++]='s';
            while((ch=fgetc(fs))!=EOF&&ch!='('){
                tmp[i++]=ch;
            }
            if(!strcmp("scanf",tmp)){
               cntsf++;
            }
        }
        if(ch=='p'){
            int i=0;
            char tmp[100]="";
            tmp[i++]='p';
            while((ch=fgetc(fs))!=EOF&&ch!='('){
                tmp[i++]=ch;
            }
            if(!strcmp("printf",tmp)){
               cntpf++;
            }
        }
    }
    printf("No. of input functions: %d\nNo. of output functions: %d",cntsf,cntpf);
    return 0;
}

