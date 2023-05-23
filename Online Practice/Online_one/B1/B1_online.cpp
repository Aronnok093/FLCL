#include<stdio.h>

int main(){
    FILE *fs = fopen("input.c","r");

    char ch,pre_ch,pm[100]="",rtn;
    int i=0;
    if(fs==NULL){
        printf("Something Went Wrong!!");
        return 1;
    }

    while((ch=fgetc(fs))!=EOF){
        if(pre_ch=='('&&ch!='"'){
            pm[i++]=ch;
            while((ch=fgetc(fs))!=EOF&&ch!=')'){
            pm[i++]=ch;
           }
        }
        else if(pre_ch=='r'&&ch=='e'){
            while((ch=fgetc(fs))!=EOF&&ch!=';'){
            rtn=ch;
           }
        }

        pre_ch=ch;

    }

    printf("Parameter(s): %s\n",pm);
    printf("Return Value: %c\n",rtn);

    return 0;

}
