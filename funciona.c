#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char alfabeto[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
long long int conversao_letra(long long int letras[], long long int tamanho)
{
  
    for (long long int i = 0; i < tamanho; i ++)
    {
         printf("essa letra q ta vindo%lld",letras[i]);
    for(int j = 0; j <= 27; j++)
    {
        if(letras[i] == j)
        {
           printf("%s", alfabeto[j]);
        }
    }
    }
}
long long int inverso(long long int e, long long int z)
{
    long long int d= 1; //chave privada = d
    for(long long int aux = 0; aux < z; aux++)
    {
        if((aux * e) % z == 1)
        {
            d = aux  ;
            return d;
        }
    }
}
long long int inverso_modular(long long int m, long long int expoente, long long int n)
{ //texto cifrado = (textoplano ^ E) mod N , c = m ^ e % n
//// textoplano =(textocifrado ^  D) mod N, c = m ^ d % n
    
    long long int c = 1;

    if(n == 1)
    {
      return 0;
    }

    for(long long int i = 0; i < expoente; i++)
    {
      c = (c * m) % n;
    }

    return c;
}
long long int conversao(char frase[], long long int tamanho, long long int i, long long int j, long long int e, long long int n)
{
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
    int w;
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


    while(i < tamanho)
    {
        cifrado[i] = conversao(frase,tamanho,i,0,e,n);
        //printf("ta cifrando isso:%lld\n", cifrado[i]);
        fprintf(mensagens,"%lld ", cifrado[i]);
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
    long long int d, p, q, e, z;
    long long int mensagem[100000];
    printf("Digite os valores de 'p', 'q', 'e':\n");
    scanf("%lld%lld%lld", &p, &q, &e);
    z = (p - 1) * (q - 1);
    d = inverso(e, z);
    FILE * msg_descrip;
    msg_descrip = fopen("mensagem_descriptografada", "w");
    char msg_cif[100000];
    printf("Digite sua mensagem criptografada(números):\n");
    long long int i = 0;
    scanf("%s", msg_cif);
    long long int msg_cifrada = atoll(msg_cif);
    long long int msg_pura;
    msg_pura =  inverso_modular(msg_cifrada,d,p * q);//4
    //printf("MSG PURA %lld\n", msg_pura);
    char msg_letras[100000];
    sprintf(msg_letras,"%lld",msg_pura);

    long long int tamanho = strlen(msg_letras);
    //printf("TAMANHO  %lld\n", tamanho);
    for(i = 0; i < tamanho; i++)
    {
        if(msg_letras[i] == '0'){printf("A");fprintf(msg_descrip,"%c","A");}
        if(msg_letras[i] == '1'){printf("B");}
        if(msg_letras[i] == '2'){printf("C");}
        if(msg_letras[i] == '3'){printf("D");}
        if(msg_letras[i] == '4'){printf("E");}
        if(msg_letras[i] == '5'){printf("F");}
        if(msg_letras[i] == '6'){printf("G");}
        if(msg_letras[i] == '7'){printf("H");}
        if(msg_letras[i] == '8'){printf("I");}
        if(msg_letras[i] == '9'){printf("J");}
        if(msg_letras[i] == '10'){printf("K");}
        if(msg_letras[i] == '11'){printf("L");}
        if(msg_letras[i] == '12'){printf("M");}
        if(msg_letras[i] == '13'){printf("N");}
        if(msg_letras[i] == '14'){printf("O");}
        if(msg_letras[i] == '15'){printf("P");}
        if(msg_letras[i] == '16'){printf("Q");}
        if(msg_letras[i] == '17'){printf("R");}
        if(msg_letras[i] == '18'){printf("S");}
        if(msg_letras[i] == '19'){printf("T");}
        if(msg_letras[i] == '20'){printf("U");}
        if(msg_letras[i] == '21'){printf("V");}
        if(msg_letras[i] == '22'){printf("W");}
        if(msg_letras[i] == '23'){printf("X");}
        if(msg_letras[i] == '24'){printf("Y");}
        if(msg_letras[i] == '25'){printf("Z");}
        if(msg_letras[i] == '26'){printf(" ");}


    }



    /*long long int msg_letra[tamanho];
    for(i = 0; i < tamanho; i++)
    {
        msg_letra[i] = atoll(msg_letras[i]);
        printf("MSG LETRA %lld", msg_letra[i]);
    }*/

    
}
int main()
{

    printf("Bem vindos ao Projeto de Criptografia RSA das alunas Gabriela Batista,Layanne da Silva e Lais Souza\n\n");

    int escolha = 0; //num aleatorio p inicializar 

    while (escolha != 4)
    {
       printf("\nEscolha uma opção:\n\nDigite 1 para GERAR CHAVE PÚBLICA\nDigite 2 para ENCRIPTAR\nDigite 3 para DESENCRIPTAR\nDigite 4 para SAIR DO PROGRAMA\n");
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