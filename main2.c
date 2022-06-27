#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  FILE *arq;
  int resp = 3;
  char inp[16];
  char *name = calloc(128, sizeof(char));

  //arq = fopen("login.txt", "r");
  

  while (resp) {
    //system("clear");

    printf("Bem-vindo(a) %s\n\n"
           " 1. Entrar\n"
           " 2. Cadastrar\n\n"
           " 0. Exit\n\n> ", name);

    fgets(inp, 16, stdin);
    resp = strtoull(inp, NULL, 16);

    if (resp > 2) {
      resp = 3;
      continue;
    }
    char *nome = calloc(128, sizeof(char));

    switch (resp) {
      case 1: {
        printf("\nNome: ");
        
        arq = fopen("login.txt", "r");
        
        fgets(name, 128, stdin);
        

        while(!feof(arq)){
          fscanf(arq, "%s", &nome);
          printf("%c\n", nome);
          if(nome == name){
            printf("opa, seja bem vindo %s", name);
            
            break;
          }
          
        }
        
        
        //fprintf(arq, "%s", name);
        fclose(arq);
        break;
      }
      case 2: {
        // Sign-in code here
        break;
      }
    }
  }

  return 0;
}