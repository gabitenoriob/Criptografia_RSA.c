#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char alfabeto[28] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
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
long long int conversao(char frase[], long long int tamanho, long long int i, long long int j, long long int e, long long int n)
{//mudar p for

    if(j > 27)
    {
        return 0;
    }
    if(frase[i] == alfabeto[j])
    {
        long long int texto_plano = j;
        return inverso_modular(texto_plano,e,n);
    }
    else
    {
        conversao(frase,tamanho,i,j + 1,e,n);
    }
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
    printf("Por favor digite os valores de 'p', 'q', e 'e'\n");
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

//ta cifrando erradooo
    while(i < tamanho)
    {
        cifrado[i] = conversao(frase,tamanho,i,0,e,n);
        //printf("ta cifrando isso:%lld\n", cifrado[i]);
        fprintf(mensagens,"%lld", cifrado[i]);
        i++;
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
    char a[100000];
    FILE *msg_aux, *msg_descrip;
    msg_aux = fopen("mensagem_criptografada.txt", "rt");

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
      printf("esse é o inverso modular %lld", mensagem[i]);
    }

    msg_descrip = fopen("mensagem_descriptografada.txt", "w");
    for(i = 0 ; i < tamanho ; i++)
    {
      a[i] = alfabeto[mensagem[i]];
      printf("conversao p letra: %c", a[i]);
      fprintf(msg_descrip, "%c", a[i]);
    }
    fclose(msg_descrip);
    printf("Mensagem descriptografada! Salva em 'mensagem_descriptografada.txt'.\n\n");
    printf("Deseja mostrar mensagem na tela?\nDigite 1 para mostrar e 0 para sair.\n");

    int w;
    scanf("%d", &w);
    if(w == 1)
    {
      for(i = 0 ; i < tamanho ; i++)
      {
        printf("%c", a[i]);
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