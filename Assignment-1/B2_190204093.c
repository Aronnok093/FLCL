#include<stdio.h>

int main(){

    FILE*fp,*fw,*fr;
    char pre_ch='\0',ch;
    int isComment=0;

    fp=fopen("input.c","r");
    fw=fopen("output.c","w");
    fr=fopen("output.c","r");

    if(fp==NULL){
        printf("Something went wrong!!\n");
        return 1;
    }

    while((ch=fgetc(fp))!=EOF){

        if(isComment){
            if(ch=='/'&& pre_ch=='*'){
                isComment=0;
            }
        }
        else if(ch=='*'&& pre_ch=='/'){
            isComment=1;
        }
        else if(ch=='/' && pre_ch== '/'){
            while((ch=fgetc(fp))!=EOF && ch!='\n'); // Trap if single line comment
        }
        else if(ch==' ' && pre_ch== ' '){

            // empty
        }
        else if(ch=='\n'|| ch=='/'){

            //Ignore new line
        }
        else{
            fputc(ch,fw); // save filtered code in output.c
        }

        pre_ch=ch;
    }
    fclose(fp);
    fclose(fw);

    //read output.c file
    while((ch=fgetc(fr))!=EOF){
        printf("%c",ch);
    }
    printf("\n");
    fclose(fw);

    return 0;
}
