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
    inp[0] = '-1';
    while(inp[0] != '0'){
        
        printf("GAME TYPING\n\n"
           "[ 1 ] Entrar\n"
           "[ 2 ] Cadastrar\n\n"
           "[ 0 ] Sair\n\n> ");
        
        fgets(inp, 16, stdin);
        if(inp[0] == '0'){
            exit(0);
        }
        resp = strtoull(inp, NULL, 16);
        
        if(resp > 2 || resp < 0){
            resp = -1;
            system("clear");
            continue;
        }
        system("clear");
        switch (resp)
        {
        case 1:
            printf("Nome: ");
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
    inp[0] = '-1';
    while(inp[0] != '0'){
        system("clear");
        
        printf("MENU\n\n"
            "[ 1 ] Partida aleatoria\n"
            "[ 2 ] Adicionar texto\n"
            "[ 3 ] Estatisticas\n\n"
            "[ 0 ] Sair do programa\n\n> ");
        
        fgets(inp, 16, stdin);
        resp = strtoull(inp, NULL, 16);
        
      
       

        if(resp > 3 || resp < 0){
            resp = -1;
            system("clear");
            continue;
        }


        int quant = -2, txtrandom;
        DIR *dp;
        struct dirent *ep;
        srand(time(NULL));
        char *texto = calloc(32, sizeof(char));
        char *textoarq = calloc(5000, sizeof(char));
        char chartemp[32] = "./textos/";
        char *temp = calloc(32, sizeof(char));
        texto = &chartemp;
        int led=0;
        
        char *resp3 = calloc(5, sizeof(char));

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
                printf("\nDigite qualquer tecla para continuar\n> ");
                fgets(resp3, 5, stdin);
                


                fclose(arq);
                closedir(dp);
                    
            }
                
            else{
                printf("Erro ao abrir o diretorio!");
            }
            
            sleep(3);
            system("clear");
            break;
        

        case 2:
            system("clear");
            dp = opendir("./textos");

            if(dp != NULL){
                while(ep = readdir(dp)){
                quant = quant +1;
                }
                temp = itoa(quant+1, temp);
                strcat(texto, temp);
                strcat(texto, ".txt");
                    
                arq = fopen(texto, "w");
                printf("Para adicionar um texto voce devera inserir linha por linha.\n\n");
                int cont2 = 1;
                char *resp2 = malloc(5 * sizeof(char));
                
                *resp2 = '1';

                while(strcmp(resp2, "0") != 0){
                    char *textoarq2 = calloc(1024, sizeof(char));
                    printf("Insira aqui a %d linha: ", cont2);
                    fgets(textoarq2, 1024, stdin);
                    strncat(textoarq, textoarq2, sizeof(textoarq2)-1);
                    
                    
                    printf("\n");
                    printf("Digite qualquer tecla para continuar ou 0 para finalizar\n> ");
                    fgets(resp2, 5, stdin);
                    
                    if(strcmp(resp2, "0\n")==0 && cont2 > 1){
                        fprintf(arq, "%s", textoarq);
                        break;
                    }
                    else{
                        if(strcmp(resp2, "0\n")==0 && cont2 == 1){
                            system("clear");
                            printf("Nao eh permitido adicionar apenas uma linha.\n");
                            sleep(2);
                            led =1;
                            break;
                        }
                    }
                    cont2++;
                    *resp2 = '1';
                    printf("\n");

                    
                }
                sleep(2);
                system("clear");
                
                if(led == 0) printf("\nTexto adicionado com sucesso!\n");
                
         
            
            }
            else{
                printf("Erro ao abrir o diretorio!");
            }
            sleep(3);
            system("clear");
            fclose(arq);
            closedir(dp);
            
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
    int vidas = 3, led=0;
    while(!feof(arq)){
        system("clear");
        
        printf("VIDAS: ");
        for(int i=vidas; i>0; i--){
            printf("\U0001F499 ");
        }
        printf("\n\n");

        
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
        if(strcasecmp(textoarq, txt) != 0){
            if(vidas == 1){
                system("clear");
                printf("FIM DE JOGO!\n\nVoce ficou sem vidas\n");
                led =1;
                sleep(4);
                break;
            }
            vidas = vidas - 1;
        }
    }

    if(led == 0){
        printf("VIDAS: ");
        for(int i=vidas; i>0; i--){
            printf("\U0001F499 ");
        }
        printf("\n\n");
        time_fim = time(NULL);
        tempo = difftime(time_fim, time_ini);
        tempo = tempo/60;
        palavras += 1;
        system("clear");
        printf("%.2f minutos\n", tempo);
        printf("%d palavras\n", palavras);
        vel = palavras / tempo;
        printf("%.2f WPM (palavras por minuto)\n", vel);
    }
    

}

int main(){

    telalogin();

    telamenu();

    return 0;
}
