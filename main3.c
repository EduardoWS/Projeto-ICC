#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void telalogin(){
    int resp = -1, led = 0;
    char inp[16];
    FILE *arq;
    char *nome = calloc(128, sizeof(char));
    char *nome1 = calloc(128, sizeof(char));
    //char *senha = calloc(30, sizeof(char));
    //char *senha1 = calloc(30, sizeof(char));
    system("clear");
    while(resp){
        
        printf("GAME TYPING\n\n"
           "[ 1 ] Entrar\n"
           "[ 2 ] Cadastrar\n\n"
           "[ 0 ] Sair\n\n> ");
        
        fgets(inp, 16, stdin);
        resp = strtoull(inp, NULL, 16);
        
        if(resp > 2 || resp < 0){
            resp = -1;
            system("clear");
            continue;
        }

        switch (resp)
        {
        case 1:
            printf("\nNome: ");
            fgets(nome, 127, stdin);
            //printf("\nSenha: ");
            //fgets(senha, 29, stdin);
            arq = fopen("login.txt", "r");

            while(!feof(arq)){
                fgets(nome1, 127, arq);
                if(strcmp(nome1, nome) == 0){
                    led = 1;
                    system("clear");
                    printf("LOGANDO...\n");
                    break;
                }
            }
            if(led == 0) printf("\nVoce ainda nao tem uma conta criada.\n");
            sleep(3);
            system("clear");
            
            
            fclose(arq);
            
            break;
        
        case 2:
            printf("\nNome Completo: ");
            fgets(nome, 127, stdin);
            arq = fopen("login.txt", "a+");
            while(!feof(arq)){
                fgets(nome1, 127, arq);
                if(strcmp(nome1, nome) == 0){
                    printf("\nJa existe uma conta com este nome.\n");
                    led = 1;
                    break;
                }
                
            }
            if(led == 0){
                fprintf(arq, "%s\n", nome);
                printf("\nConta criada com sucesso!!\n");
                

            }
            else led = 0;

            fclose(arq);
            sleep(3);
            system("clear");
            break;
        
        }
        if(led == 1) break;
    }


}

int main(){

    telalogin();


    return 0;
}