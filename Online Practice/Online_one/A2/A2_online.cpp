#include<stdio.h>
#include <string.h>
int main(){

    FILE*fs = fopen("input.c","r");
    char ch,pre_ch='\0';
    int cnt=1;

    if(fs==NULL){
        printf("Something went wrong!!");
        return 1;
    }

    printf("Line No. of double numbers declared in: ");
    while((ch=fgetc(fs))!=EOF){

        if(ch=='\n'||ch==';'){
        cnt++;
        }
        if(ch=='d'){
            int i=0;
            char tmp[100]="";
            tmp[i++]='d';
            while((ch=fgetc(fs))!=EOF&&ch!=' '){
                tmp[i++]=ch;
            }
            if(!strcmp("double",tmp)){
                printf("%d ",cnt);
            }
        }
    }
    return 0;
}
