#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char alfabeto(long long int X)
{
    if(X == 2){return 'A';}
    if(X == 3){return 'B';}
    if(X == 4){return 'C';}
    if(X == 5){return 'D';}
    if(X == 6){return 'E';}
    if(X == 7){return 'F';}
    if(X == 8){return 'G';}
    if(X == 9){return 'H';}
    if(X == 10){return 'I';}
    if(X == 11){return 'J';}
    if(X == 12){return 'K';}
    if(X == 13){return 'L';}
    if(X == 14){return 'M';}
    if(X == 15){return 'N';}
    if(X == 16){return 'O';}
    if(X == 17){return 'P';}
    if(X == 18){return 'Q';}
    if(X == 19){return 'R';}
    if(X == 20){return 'S';}
    if(X == 21){return 'T';}
    if(X == 22){return 'U';}
    if(X == 23){return 'V';}
    if(X == 24){return 'W';}
    if(X == 25){return 'X';}
    if(X == 26){return 'Y';}
    if(X == 27){return 'Z';}
    if(X == 28){return ' ';}


}
long long int inverso(long long int e, long long int z)


{
    long long int d= 1; //chave privada = d
    long long int aux;
    for(aux = 0; aux < z; aux++)
    {
        if((aux * e) % z == 1)
        {
            d = aux;
            return d;
        }
    }
}
long long int inverso_modular(long long int m, long long int expoente, long long int n)
{ //texto cifrado = (textoplano ^ E) mod N , c = m ^ e % n
//// textoplano =(textocifrado ^  D) mod N, c = m ^ d % n
    
    long long int c = 1;
    long long int i;

    if(n == 1)
    {
      return 0;
    }

    for(i= 0; i < expoente; i++)
    {
      c = (c * m) % n;
    }
    
    if(m == 26){
        c = 26;
    }

    return c;
}
long long int conversao(char letra, long long int e , long long int n)
{
    long long int texto_plano;
    if(letra == 'A'){texto_plano = 2;}
    if(letra == 'B'){texto_plano = 3;}
    if(letra == 'C'){texto_plano = 4;}
    if(letra == 'D'){texto_plano = 5;}
    if(letra == 'E'){texto_plano = 6;}
    if(letra == 'F'){texto_plano = 7;}
    if(letra == 'G'){texto_plano = 8;}
    if(letra == 'H'){texto_plano = 9;}
    if(letra == 'I'){texto_plano = 10;}
    if(letra == 'J'){texto_plano = 11;}
    if(letra == 'K'){texto_plano = 12;}
    if(letra == 'L'){texto_plano = 13;}
    if(letra == 'M'){texto_plano = 14;}
    if(letra == 'N'){texto_plano = 15;}
    if(letra == 'O'){texto_plano = 16;}
    if(letra == 'P'){texto_plano = 17;}
    if(letra == 'Q'){texto_plano = 18;}
    if(letra == 'R'){texto_plano = 19;}
    if(letra == 'S'){texto_plano = 20;}
    if(letra == 'T'){texto_plano = 21;}
    if(letra == 'U'){texto_plano = 22;}
    if(letra == 'V'){texto_plano = 23;}
    if(letra == 'W'){texto_plano = 24;}
    if(letra == 'X'){texto_plano = 25;}
    if(letra == 'Y'){texto_plano = 26;}
    if(letra == 'Z'){texto_plano = 27;}
    if(letra == ' '){texto_plano = 28;}


    

    return inverso_modular(texto_plano,e,n);
}
 
long long int mdc(long int x,long int y)
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
long long int primos(long int n,int contador)
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
void chavepublica()
{
    long long int p, q, e;
    printf("Por favor digite os valores de 'p', 'q', e 'e'\npfv utilizar numeros maiores que 3 e ate 5 digitos :)\n\n");
    scanf("%lld%lld%lld", &p, &q, &e);

    //p e q precisam ser primos e e precisa ser um relativamente primo a (p -1) * (q - 1)

    long long int n = p * q;
    long long int z = (p-1) * (q-1); 

    int invalido = 0;

    while (!invalido)
    {
        if(primos(p,2) == 0 || primos(q,2) == 0 || mdc(z,e) != 1 )
        {
            printf("Valores inválidos, tente novamente\n");
            return;
        }
        else
        {
            printf("Valor válido, vamos começar...\n");
            printf("Salvo em 'chaves_pulblicas.txt'\n");
            FILE *chaves;
            int w;
            chaves = fopen("chaves_pulblicas.txt","w");
            fprintf(chaves, "%lld %lld", n, e); //par(n,e)
            fclose(chaves);

            printf("Se quiser ver os resultados na tela DIGITE 1, caso não DIGITE 0\n");
            scanf("%d", &w);

            if(w == 1)
            {
                printf("Essa é sua chave pública:\nn = %lld\ne = %lld\n",n, e); //par(n,e)
                printf("Encerra-se aqui a criação da sua chave pública\n\n");
            }

            invalido = 1; // p fechar essa parte do programa
            
        }
    }
    

}
void encriptografar()
{
    long long int n, e;
    int w, j;
    FILE *mensagens;
    mensagens = fopen("mensagem_criptografada.txt", "w");

    printf("Por favor digite seus valores (chave pública) de 'n' e 'e'\n");
    scanf("%lld%lld", &n, &e);


    char frase[1000000];
    printf("\nDigite a frase que deja criptografar:\nobs: utilize apenas letras MAIUSCULAS\n");
    scanf(" %[^\n]s", frase);

    //para cada letra(q ja é um numero inteiro) deve encontrar o equivalente cifrado 

    long long int tamanho = strlen(frase);
    long long int i = 0;
    long long int cifrado[10000]; 


         for(i = 0; i < tamanho; i++)
         {

        cifrado[i]= conversao(frase[i],e,n);
        fprintf(mensagens,"%lld ", cifrado[i]);

         }
        
        
        
       
    

    printf("Se quiser ver os resultados na tela DIGITE 1, caso não DIGITE 0\n");
            scanf("%d", &w);

            if(w == 1)
            {
                printf("Essa é sua mensagem criptografada: ");
                for(i = 0; i < tamanho; i ++)
                {
                printf("%lld ",cifrado[i] ); 
                }
                printf("\n");
            }
    printf("Mensagem Criptografada com sucesso e salva no arquivo txt ""mensagem_criptografada""\n\n");
    printf("Encerra-se aqui a criação da mensagem criptografada\n\n");
    fclose(mensagens);


}
void descriptografar()
{
    long long int d, i, tamanho, p, q, e, z;
    long long int mensagem[100000];
    char string[100000];
    FILE *msg_aux, *msg_descrip;
    msg_aux = fopen("mensagem_criptografada.txt", "r");

    printf("Digite os valores de 'p', 'q', 'e':\n");
    scanf("%lld%lld%lld", &p, &q, &e);
    z = (p - 1) * (q - 1);
    d = inverso(e, z);

    
    for(i = 0 ; !feof(msg_aux) ; i++)
    {
      fscanf(msg_aux,"%lld", &mensagem[i]);
    }

    tamanho = i;
    for(i = 0 ; i < tamanho ; i++)
    {
      mensagem[i] = inverso_modular(mensagem[i], d, p * q);
      
    }

    msg_descrip = fopen("mensagem_descriptografada.txt", "w");

    for(i = 0 ; i < tamanho -1  ; i++)
    {
      string[i] = alfabeto(mensagem[i]);
      fprintf(msg_descrip, "%c", string[i]);
    }
    fclose(msg_descrip);
    printf("Mensagem descriptografada! Salva em 'mensagem_descriptografada.txt'.\n\n");
    printf("Deseja mostrar mensagem na tela?\nDigite 1 para mostrar e 0 para sair.\n");

    int w;
    scanf("%d", &w);
    if(w == 1)
    {
      for(i = 0 ; i < tamanho - 1; i++)
      {
        printf("%c", string[i]);
      }
      printf("\n");
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
        chavepublica();
       }
       if(escolha == 2)
       {
        printf("CRIPTOGRAFANDO\n\n");
        encriptografar(); 
       
       }
       if(escolha == 3)
       {
        printf("DESCRIPTOGRAFANDO\n\n");
        descriptografar();
        // textoplano =(textocifrado ^  D) mod N
       }
       if(escolha == 4)
       {
        printf("VOCE ESTA DEIXANDO O PROGRAMA. ATÉ A PROXIMA ;)\n");

       }
    }

    return 0;
    
}
