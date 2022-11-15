#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int entradaPadrao(int n, int e)
{
    //tornar entrada padrao, quando receber a frase, transformar todas as letras maiusculas.
    char caractere; 
    caractere = ('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ');
    numeros = (2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28);
    
}

int inverso()
{
    
}

long int mdc(long int x,long int y)
{
    if( y == 0) 
    {
        return x;
    }
    else 
    {
        return mdc(y, (x % y));
    }
}
long int primos(long int n,int contador)
{
    if(n == contador) 
    {
        return 1;
    }
    else if(n % contador == 0 || n < 2) 
    {
        return 0;
    }
    else 
    {
        primos(n,contador + 1);
    }
}
void chavesp()
{
    long int p, q, e;
    printf("Por favor digite os valores de 'p', 'q', e 'e'\n");
    scanf("%ld%ld%ld", &p, &q, &e);

    //p e q precisam ser primos e e precisa ser um relativamente primo a (p -1) * (q - 1)

    long int coprimos = (p-1) * (q-1); //mdc = 1

    int invalido = 0;

    while (!invalido)
    {
        if(primos(p,2) == 0 || primos(q,2) == 0 || mdc(coprimos,e) != 1 )
        {
            printf("Valores inválidos, tente novamente\n");
            return;
        }
        else
        {
            printf("Valor válido, vamos começar...\n");
            printf("Salvo em 'chaves_pulblicas.txt'\n");
            FILE *chaves;
            int abrirfechar;
            chaves = fopen("chaves_pulblicas.txt","abrirfechar");
            fprintf(chaves, "%ld%ld", p * q, e); //par(n,e)
            fclose(chaves);

            printf("Se quiser ver os resultados na tela DIGITE 1, caso não DIGITE 0\n");
            scanf("%d", &abrirfechar);

            if(abrirfechar == 1)
            {
                printf("Essa é sua chave pública:\n n = %ld\ne = %ld\n", p * q, e); //par(n,e)
                printf("Encerra-se aqui a criação da sua chave pública\n\n");
            }

            invalido = 1; // p fechar essa parte do programa
            
        }
    }
    

}
int main()
{

    printf("Bem vindos ao Projeto de Criptografia RSA das alunas Gabriela Batista,Layanne da Silva e Lais Souza\n\n");

    int escolha = 0; //num aleatorio p inicializar 

    while (escolha != 4)
    {
       printf("Escolha uma opção:\n\nDigite 1 para GERAR CHAVE PÚBLICA\nDigite 2 para ENCRIPTAR\nDigite 3 para DESENCRIPTAR\nDigite 4 para SAIR DO PROGRAMA\n");
       scanf("%d", &escolha);

       if(escolha == 1)
       {
        printf("GERANDO CHAVES PUBLICAS\n\n");
        chavesp();
       }
       if(escolha == 2)
       {
        printf("CRIPTOGRAFANDO\n\n");
        //criptografar();
       }
       if(escolha == 3)
       {
        printf("DESCRIPTOGRAFANDO\n\n");
        //descriptografar();
       }
       if(escolha == 4)
       {
        printf("VOCE ESTA DEIXANDO O PROGRAMA. ATÉ A PROXIMA ;)\n");

       }
    }

    return 0;
    
}
