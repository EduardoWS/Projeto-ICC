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

void saindo(int led){
    system("clear");
    char *u = calloc(7, sizeof(char));
    char *name = calloc(30, sizeof(char));
    if(led==0) name = "SAINDO";
    else name = "LOGANDO";

    for(int i=0; i<3; i++){
        if(i==0) u = ".";
        if(i==1) u="..";
        if(i==2) u="...";
        //if(i==3) u="....";
        //if(i==4) u=".....";
        printf("\033[1;32m%s%s\033[m\n", name, u);
        
        sleep(1);
        system("clear");
    }
}

char *cores(int n){
    char *cor = calloc(20, sizeof(char));
    char *azul = calloc(20, sizeof(char));
    char *semcor = calloc(20, sizeof(char));
    char *branco = calloc(20, sizeof(char));
    char *vermelho = calloc(20, sizeof(char));
    semcor = "\033[m";
    azul = "\033[1;36m";
    branco = "\033[1;30m";
    vermelho = "\033[1;31m";
    if(n == 0) cor = semcor;
    if(n == 1) cor = azul;
    if(n == 2) cor = branco;
    if(n == 3) cor = vermelho;

    return cor;
}

void telalogin(){
    
    
    //char *cor = calloc(20, sizeof(char));
    
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
        
        printf(
            "%s===========================\n\n"
            "  ----- TYPING GAME -----   \n\n"
            "===========================%s\n\n"
            "%s[ 1 ] Entrar\n"
            "[ 2 ] Cadastrar\n\n"
            "[ 0 ] Sair%s\n\n%s> %s", cores(1), cores(0), cores(2), cores(0), cores(3), cores(0));
        
        fgets(inp, 16, stdin);
        if(inp[0] == '0'){
            saindo(0);
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
            printf("%sNome: %s", cores(1), cores(0));
            fgets(nome, 127, stdin);
            //printf("\nSenha: ");
            //fgets(senha, 29, stdin);
            arq = fopen("./logins/login.txt", "r");

            while(!feof(arq)){
                fgets(nome1, 127, arq);
                if(strcmp(nome1, nome) == 0){
                    led = 1;
                    
                    saindo(1);
                    break;
                }
            }
            if(led == 0) printf("\nVoce ainda nao tem uma conta criada.\n");

            sleep(3);
            system("clear");
            
            
            fclose(arq);
            
            break;
        
        case 2:
            printf("CADASTRO\n\nNome Completo: ");
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
                fprintf(arq, "%s", nome);
                sleep(2);
                system("clear");
                printf("Conta criada com sucesso!!\n");
                

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
    
    inp[0] = '-1';
    while(inp[0] != '0'){
        system("clear");
        
        printf(
            "%s===========================\n\n"
            "  ----- TYPING GAME ----- \n\n"
            "===========================%s\n\n"
            "%s[ 1 ] Partida aleatoria\n"
            "[ 2 ] Adicionar texto\n"
            "[ 3 ] Ranking\n\n"
            "[ 0 ] Sair%s\n\n%s> %s", cores(1), cores(0), cores(2), cores(0), cores(3), cores(0));
        
        fgets(inp, 16, stdin);
        resp = strtoull(inp, NULL, 16);
        
        if(inp[0] == '0'){
            saindo(0);
            exit(0);
        }
      
       

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
                printf("\n%sDigite qualquer tecla para continuar%s\n\n%s> %s", cores(1), cores(0), cores(3), cores(0));
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
                    
                //arq = fopen(texto, "w");
                printf("%s===========================================================\n"
                    "Para adicionar um texto voce devera inserir linha por linha%s\n\n", cores(1), cores(0));
                int cont2 = 1;
                char *resp2 = malloc(5 * sizeof(char));
                
                *resp2 = '1';

                while(strcmp(resp2, "0") != 0){
                    char *textoarq2 = calloc(1024, sizeof(char));
                    printf("Insira aqui a %d linha: ", cont2
                    );
                    fgets(textoarq2, 1024, stdin);
                    strcat(textoarq, textoarq2);
                    
                    
                    printf("\n");
                    printf("Digite qualquer tecla para continuar ou 0 para finalizar\n> ");
                    fgets(resp2, 5, stdin);
                    
                    if(strcmp(resp2, "0\n")==0 && cont2 >= 3){
                        arq = fopen(texto, "w");
                        fprintf(arq, "%s", textoarq);
                        break;
                    }
                    else{
                        if(strcmp(resp2, "0\n")==0 && cont2 < 3){
                            system("clear");
                            printf("%sNecessita-se ter ao menos 3 linhas%s\n", cores(3), cores(0));
                            sleep(2);
                            led =1;
                            break;
                        }
                    }
                    cont2++;
                    *resp2 = '1';
                    printf("\n");

                    
                }
                
                system("clear");
                
                if(led == 0){
                    printf("%sTexto adicionado com sucesso!%s\n", cores(1), cores(0));
                    fclose(arq);
                    free(textoarq);
                }

                
                
                
         
            
            }
            else{
                printf("Erro ao abrir o diretorio!");
            }
            sleep(3);
            system("clear");
            
            closedir(dp);
            
            break;

        
        }

        

        
    }

}

void partida(FILE *arq, char *textoarq){
    time_t time_ini, time_fim;
    float tempo, vel;
    char *txt = calloc(1024, sizeof(char));
    char *repetida = calloc(1024, sizeof(char));
    int cont, palavras=0;
    time_ini = time(NULL);
    int vidas = 3, led=0;
    int score;
    while(!feof(arq)){
        system("clear");
        fgets(textoarq, 1024, arq);
        if(strcmp(textoarq, repetida)==0){
            break;
        }
        printf("%sVIDAS: %s", cores(1), cores(0));
        for(int i=vidas; i>0; i--){
            printf("\U0001F499 ");
        }
        printf("\n\n");

        
        cont = 0;
        

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
                printf("%sFIM DE JOGO!\n\nVoce ficou sem vidas%s\n", cores(3), cores(0));
                led =1;
                sleep(4);
                break;
            }
            vidas = vidas - 1;
        }
        strcpy(repetida, textoarq);
    }
    time_fim = time(NULL);

    if(led == 0){
        system("clear");
        printf("%sVIDAS: %s", cores(1), cores(0));
        for(int i=vidas; i>0; i--){
            printf("\U0001F499 ");
        }
        printf("\n\n");
        printf("================================\n");
        tempo = difftime(time_fim, time_ini);
        tempo = tempo/60;
        //palavras += 1;
        
        vel = palavras / tempo;
        if(vidas == 3) score = (((vel*vidas)*3 + palavras*3)+2)/(2);
        if(vidas==2) score = (((vel*vidas)*2 + palavras)+2)/(2);
        if(vidas==1) score = (((vel*vidas)/2 + palavras/2)+4)/(4);
        printf("\033[1;32m           SCORE: %d\033[m\n", (int)score);
        printf(
            "\n%s%.2f minutos\n"
            "%d palavras\n"
            "%.2f WPM (palavras por minuto)%s\n", cores(2), tempo, palavras, vel, cores(0)
        );
        
        printf("\n================================\n");
    }
    

}

int main(){

    telalogin();

    telamenu();

    return 0;
}
