#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

char *  itoa( int value, char * str )
{
    char temp;
    
    int i =0;
    while (value > 0) {
        int digito = value % 10;

        str[i] = digito + '0';
        value /= 10;
        i++;

    }

    i = 0;
    int j = strlen(str) -1;
    

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
    return str;
}

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
            arq = fopen("./logins/login.txt", "r");

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
            arq = fopen("./logins/login.txt", "a+");
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

void telamenu(){

    int resp = -1;
    char inp[16];
    FILE *arq;
    system("clear");
    while(resp){
        printf("MENU\n\n"
            "[ 1 ] Partida aleatoria\n"
            "[ 2 ] Escolher texto\n"
            "[ 3 ] Estatisticas\n\n"
            "[ 0 ] Sair do programa\n\n> ");
        
        fgets(inp, 16, stdin);
        resp = strtoull(inp, NULL, 16);
        if(resp > 2 || resp < 0){
            resp = -1;
            system("clear");
            continue;
        }
        int quant = -2, txtrandom;
        DIR *dp;
        struct dirent *ep;
        srand(time(NULL));
        char *texto = calloc(32, sizeof(char));
        char *textoarq = calloc(1024, sizeof(char));
        char chartemp[32] = "./textos/";
        char *temp = calloc(32, sizeof(char));
        texto = &chartemp;
        switch (resp)
        {
        case 1:
            
            dp = opendir("./textos");

            if(dp != NULL){
                while(ep = readdir(dp)){
                    quant = quant +1;

                }
                txtrandom = (rand() % quant)+1;
                temp = itoa(txtrandom, temp);
                strcat(texto, temp);
                strcat(texto, ".txt");
                
                arq = fopen(texto, "r");
                
                partida(arq, textoarq);

                /*
                while(!feof(arq)){
                    fgets(textoarq, 1024, arq);
                    printf("%s\n", textoarq);

                } */

                closedir(dp);
                fclose(arq);
            }
            else{
                printf("Erro ao abrir o diretorio!");
            }
            sleep(3);
            system("clear");
            break;
        
        
        }
        
    }

}

void partida(FILE *arq, char *textoarq){
    time_t time_ini, time_fim;
    float tempo, vel;
    char *txt = calloc(1024, sizeof(char));
    int cont, palavras=0;
    time_ini = time(NULL);
    while(!feof(arq)){
        system("clear");
        cont = 0;
        fgets(textoarq, 1024, arq);
        for(int i=0; textoarq[i]!='\0'; i++){
            if(isspace(textoarq[i]) != 0){
                cont++;
            }
        }
        palavras = palavras + cont;
        printf("%s\n\n> ", textoarq);
        fgets(txt, 1024, stdin);
    }
    time_fim = time(NULL);
    tempo = difftime(time_fim, time_ini);
    tempo = tempo/60;
    palavras += 1;
    printf("%.2f minutos\n", tempo);
    printf("%d palavras\n", palavras);
    vel = palavras / tempo;
    printf("%.2f WPM\n", vel);
    sleep(10);

}

int main(){

    telalogin();

    telamenu();

    return 0;
}


