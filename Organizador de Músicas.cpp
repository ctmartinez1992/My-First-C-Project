#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <tchar.h>
#include <iostream>

using namespace std;

typedef struct{
                 int n_seq;
                 char musica[50];
                 char banda[20];
                 int tipo;
                 } CONTACTO;
                
#define NOME_FICH  "\\dados.dat"                      

FILE *fd;

int menu()
{
    int op=0;

    do{
        system("cls");
      
        puts ("--------------------------------------MENU--------------------------------------\n");
        puts ("1-Inserir registo");
        puts ("2-Listar todos os registos");
        puts ("3-Listar registos por nome da música");
        puts ("4-Listar registos por nome da banda");
        puts ("5-Listar registos por tipo");
        puts ("6-Alterar registo");
        puts ("7-Ajuda");
        puts ("8-Sair");
        printf("\nEscolha a opção: ");
        scanf("%d", &op);
        
        fflush(stdin);
      
      }while (op < 1 || op > 8);

      return(op);
}

int abre_fich(char nome_fich[])
{
    int ERRO = 0;
    char RESP;

    fd = fopen(nome_fich,"r+b");

    if (fd == NULL)
    {
        ERRO = 1;
        printf("\n  Ficheiro não existe!\n  Deseja criá-lo? ");
        scanf("%c", &RESP);
        fflush(stdin);

    if (( RESP == 's' ) || ( RESP == 'S' ))
    {
        fd = fopen(nome_fich, "w+b");

        if (fd == NULL)
        {
            ERRO = 2;
        }
        
        else
            ERRO = 0;
    }
    }

        if (ERRO != 0)
        {
            switch(ERRO)
            {
                case 1: 
                        printf("\nErro %d - Ficheiro não existe", ERRO);
                        getch();
                        break;
                        
                case 2: 
                        printf("\nErro %d - Não consegue criar ficheiro - ver directorios", ERRO);
                        getch();
                        break;
                        
                default: 
                         printf("ERRO %d"); getch();
            }
        }

return ERRO;
}

void inserir()
{
    CONTACTO dados;
    int x, gravado;
    char resp;
    
    printf("--------------------------------------------------------------------------------");
    printf("\t\t\t  Inserir Registo de Contacto\n");
    printf("--------------------------------------------------------------------------------\n");
    
    x = fseek (fd, - sizeof(CONTACTO), SEEK_END); 
    
    if ( x == 0 )
    {
       fread( &dados, sizeof(CONTACTO), 1, fd);
       x = dados.n_seq + 1;
    }
    
    else
        x = 1;
        
    printf("Número do Registo = %d\n", x);
    printf("Nome da música: "); 
    scanf ("%s", &dados.musica);
    printf("Nome da banda: "); 
    scanf("%s", &dados.banda);
    printf("\nTipo de música:\n\n  1-Electronica\n  2-Heavy Metal\n  3-Hip Hop\n  4-Instrumental\n  5-Jazz\n  6-Pop\n  7-Punk\n  8-Rap\n  9-Rock'n'Roll\n  10-Techno\n");
    printf("\nOpção: ");
    scanf("%d", &dados.tipo);
    
    if ((dados.tipo < 1) || (dados.tipo > 10))
    {
                   system("cls");
                   printf("\a\n  Opção Inválida!!!");
                   getch();
    }
    
    else
    {
        fflush (stdin);
    
        printf ("\nConfirma os dados inseridos? [S/N]\n  Resposta: ");
        scanf ("%c", &resp);
    
        fflush (stdin);
    
        if((resp == 's') || (resp == 'S'))
        {
             dados.n_seq = x;
             
             fseek(fd, 0L, SEEK_END);
             gravado = fwrite(&dados, (long)sizeof(CONTACTO), 1, fd); 
    
             if (gravado != 1)
             {
                         printf("Falha de gravação de Registo");
                         getch();
             }
    
             else
             {
                         fflush(fd);
             }
}
}
}  

void listar_musica()
{
    CONTACTO dados;
    int i, esp, j=0, teste=0;
    char vtipo[15], musc[90];

    printf("Indique o nome da música que quer listar: ");
    gets(musc);
    
    system("cls");
    
    rewind(fd);
    
    while ( fread (&dados, sizeof(CONTACTO), 1, fd) == 1 )
    {
        if (( strcmp (musc, dados.musica)) == 0 )
        {
           while (j == 0)
           {
                 printf("--------------------------------------------------------------------------------");
                 printf("\t\t  Todas as Músicas com o nome: %s\n", musc);
                 puts("--------------------------------------------------------------------------------\n");
                 printf("NReg Nome Banda                                                     Tipo        ");
                 printf("--------------------------------------------------------------------------------");
                 j=1;
           }
        
        printf("%d    %s", dados.n_seq, dados.banda);
        
        esp = 63 - strlen(dados.banda);
        
        for (i=1; i<=esp; i++) printf(" ");
        {
            switch(dados.tipo)
            {
                  case 1: 
                          strcpy(vtipo, "Electrónica");
                          break;
                        
                  case 2: 
                          strcpy(vtipo, "Heavy Metal");
                          break;
                        
                  case 3: 
                          strcpy(vtipo, "Hip Hop");
                          break;
                        
                  case 4: 
                          strcpy(vtipo, "Instrumental");
                          break;
                        
                  case 5: 
                          strcpy (vtipo, "Jazz");
                          break;
                        
                  case 6: 
                          strcpy (vtipo, "Pop");
                          break;
                        
                  case 7: 
                          strcpy(vtipo, "Punk");
                          break;
                        
                  case 8: 
                          strcpy(vtipo, "Rap");
                          break;
                        
                  case 9: 
                          strcpy(vtipo, "Rock'n'Roll");
                          break;
                        
                  case 10:
                          strcpy (vtipo, "Techno");
                          break;
                         
                  default: 
                           printf("\n\a  Opção Inválida!!!");
                  }
        
        printf("%s\n", vtipo);
        
        teste=1;
        
        }
        }
        }
        
if(teste != 1)
{
         printf("\a\n  Não existe nenhuma banda com esse nome!!!");
}
}
      
void listar()
{
    CONTACTO dados;
    int esp, i;
    char tipo[15];

    system("cls");
    
    printf("--------------------------------------------------------------------------------");
    printf("\t\t        Registos do Ficheiro de Músicas\n");
    printf("--------------------------------------------------------------------------------\n");
    
    rewind(fd);
    
    printf("NReg Nome Música                    Nome Banda                      Tipo \n");
    printf("--------------------------------------------------------------------------------");
    
    while ( fread(&dados, sizeof(CONTACTO), 1, fd) == 1 ) 
    {       
           printf("%d    %s", dados.n_seq, dados.musica);
           
           esp = 31 - strlen ( dados.musica );
           
           for ( i=1 ; i <= esp ; i++ ) printf(" ");
           printf("%s", dados.banda);
           
           esp = 32 - strlen(dados.banda);
           
           for (i=1; i<=esp; i++) printf(" ");
           switch(dados.tipo)
           {
                case 1: 
                        strcpy(tipo, "Electrónica");
                        break;
                        
                case 2: 
                        strcpy(tipo, "Heavy Metal");
                        break;
                        
                case 3: 
                        strcpy(tipo, "Hip Hop");
                        break;
                        
                case 4: 
                        strcpy(tipo, "Instrumental");
                        break;
                        
                case 5: 
                        strcpy (tipo, "Jazz");
                        break;
                        
                case 6: 
                        strcpy (tipo, "Pop");
                        break;
                        
                case 7: 
                        strcpy(tipo, "Punk");
                        break;
                        
                case 8: 
                        strcpy(tipo, "Rap");
                        break;
                        
                case 9: 
                        strcpy(tipo, "Rock'n'Roll");
                        break;
                        
                case 10: 
                         strcpy (tipo, "Techno");
                         break;
           }
           
           printf("%s\n", tipo);
                         
}            
}

void listar_banda()
{
    CONTACTO dados;
    int i, esp, j=0, flag=0;
    char vtipo[15], band[90];

    printf("Indique o nome da banda que quer listar: ");
    gets(band);
    
    system("cls");
    
    rewind(fd);
    
    while ( fread( &dados, sizeof(CONTACTO), 1, fd ) == 1 )
    {
        if (( strcmp (band, dados.banda)) == 0 )
        {
           while (j == 0)
           {
                 printf("--------------------------------------------------------------------------------");
                 printf("\t\t    Todas as Músicas da Banda: %s\n", band);
                 puts("--------------------------------------------------------------------------------\n");
                 printf("NReg Nome Música                                             Tipo               ");
                 printf("--------------------------------------------------------------------------------");
                 j=1;
           }
        
        printf("%d    %s", dados.n_seq, dados.musica);
        
        esp = 56 - strlen(dados.musica);
        
        for (i=1; i<=esp; i++) printf(" ");
        {
            switch(dados.tipo)
            {
                  case 1: 
                          strcpy(vtipo, "Electrónica");
                          break;
                        
                  case 2: 
                          strcpy(vtipo, "Heavy Metal");
                          break;
                        
                  case 3: 
                          strcpy(vtipo, "Hip Hop");
                          break;
                        
                  case 4: 
                          strcpy(vtipo, "Instrumental");
                          break;
                        
                  case 5: 
                          strcpy (vtipo, "Jazz");
                          break;
                        
                  case 6: 
                          strcpy (vtipo, "Pop");
                          break;
                        
                  case 7: 
                          strcpy(vtipo, "Punk");
                          break;
                        
                  case 8: 
                          strcpy(vtipo, "Rap");
                          break;
                        
                  case 9: 
                          strcpy(vtipo, "Rock'n'Roll");
                          break;
                        
                  case 10: 
                           strcpy (vtipo, "Techno");
                           break;
                         
                  default: 
                           printf("\n\a  Opção Inválida!!!");

                           }
        
        printf("%s\n", vtipo);
        
        flag=1;
        
        }}}
        
    if(flag != 1)
        printf("\a\n  Não existe nenhuma banda com esse nome!!!");

}

void listar_tipo()
{
    CONTACTO dados;
    int esp, x, y=0, test=0, tipo;
    char v_tipo[15];

    printf("Tipos de Música:\n\n  1-Electrónica\n  2-Heavy Metal\n  3-Hip Hop\n  4-Instrumental\n  5-Jazz\n  6-Pop\n  7-Punk\n  8-Rap\n  9-Rock'n'Roll\n  10-Techno\n");
    printf("\nIndique o tipo de música que quer listar: ");
    scanf("%d", &tipo);
    
    system("cls");
        
    switch(tipo)
    {
                case 1: 
                        strcpy(v_tipo, "Electrónica");
                        break;
                        
                case 2: 
                        strcpy(v_tipo, "Heavy Metal");
                        break;
                        
                case 3: 
                        strcpy(v_tipo, "Hip Hop");
                        break;
                        
                case 4: 
                        strcpy(v_tipo, "Instrumental");
                        break;
                        
                case 5: 
                        strcpy (v_tipo, "Jazz");
                        break;
                        
                case 6: 
                        strcpy (v_tipo, "Pop");
                        break;
                        
                case 7: 
                        strcpy(v_tipo, "Punk");
                        break;
                        
                case 8: 
                        strcpy(v_tipo, "Rap");
                        break;
                        
                case 9: 
                        strcpy(v_tipo, "Rock'n'Roll");
                        break;
                        
                case 10: 
                         strcpy (v_tipo, "Techno");
                         break;
                        
            }
    
    rewind(fd);
    
    while (fread(&dados, sizeof(CONTACTO), 1, fd) == 1)
    {
        if (tipo == dados.tipo)
        {
                 while (y == 0)
                 {
                       printf("--------------------------------------------------------------------------------");  
                       printf("\t\t     Todas as músicas do tipo %s\n", v_tipo);
                       printf("--------------------------------------------------------------------------------\n");
                       printf("NReg Nome Música                            Nome Banda                         \n");
                       printf("--------------------------------------------------------------------------------");
                       y=1;
                 }
        
        printf("%d    %s", dados.n_seq, dados.musica);
        
        esp = 39 - strlen(dados.musica);
        
        for (x=1; x<=esp; x++) printf(" ");
        printf("%s\n", dados.banda);
        
        test=1;
        }
    }
    
    if(test != 1)
    {
            printf("\a\n  Opção Inválida!!!");
    }
}

void alterar() 
{
     CONTACTO dados;
     int  gravado, re, test=0, x, esp, i, opcao, g, alterou; 
     char tipo[15], tipo2[15], sn;
     
     system("cls");
    
     printf("--------------------------------------------------------------------------------");
     printf("\t\t        Registos do Ficheiro de Músicas\n");
     printf("--------------------------------------------------------------------------------\n");
    
     rewind(fd);
    
     printf("NReg  Nome Musica                 Nome Banda            Tipo   \n");
     printf("-------------------------------------------------------------------------------\n");
    
     while ( fread(&dados, sizeof(CONTACTO), 1, fd) == 1 ) 
     {       
           printf("%4d  %s", dados.n_seq, dados.musica);
           
           esp = 28 - strlen ( dados.musica );
           
           for ( i=1 ; i <= esp ; i++ ) printf(" ");
           printf("%s", dados.banda);
           
           esp = 22 - strlen(dados.banda);
           
           for (i=1; i<=esp; i++) printf(" ");
           switch(dados.tipo)
           {
                case 1: 
                        strcpy(tipo, "Electrónica");
                        break;
                        
                case 2: 
                        strcpy(tipo, "Heavy Metal");
                        break;
                        
                case 3: 
                        strcpy(tipo, "Hip Hop");
                        break;
                        
                case 4: 
                        strcpy(tipo, "Instrumental");
                        break;
                        
                case 5: 
                        strcpy(tipo, "Jazz");
                        break;
                        
                case 6: 
                        strcpy(tipo, "Pop");
                        break;
                        
                case 7: 
                        strcpy(tipo, "Punk");
                        break;
                        
                case 8: 
                        strcpy(tipo, "Rap");
                        break;
                        
                case 9: 
                        strcpy(tipo, "Rock'n'Roll");
                        break;
                        
                case 10: 
                         strcpy (tipo, "Techno");
                         break;
           }
           
           printf("%s\n", tipo);
    
      }
                 
      printf ("\nIndique o número de registo a procurar: ");
      scanf ("%d", &x);
      
      fseek (fd, 0L, 2);
      
      if (( x > dados.n_seq ) || ( x < 1 ))
      {
            system("cls");
            printf("\n  \aRegisto não Existe!!!");
      }
      
      else
      {
          dados.n_seq = x;
     
          if ( x == dados.n_seq )
          {
                 test = 1;
     
                 fseek (fd,(x-1)*sizeof(CONTACTO),0);
                 fread(&dados, sizeof(CONTACTO), 1, fd);
      
                 system("cls");
      
                 printf("--------------------------------------------------------------------------------");
                 printf("                                 Registo Antigo                                 ");
                 printf("--------------------------------------------------------------------------------\n\n");
                 printf("Número de Registo: %d\n", dados.n_seq);
                 printf("Nome da Música: %s\n", dados.musica);
                 printf("Nome da Banda: %s\n", dados.banda);
                 switch(dados.tipo)
                 {
                                   case 1: 
                                           strcpy(tipo, "Electrónica");
                                           break;
                        
                                   case 2: 
                                           strcpy(tipo, "Heavy Metal");
                                           break;
                        
                        
                                   case 3: 
                                           strcpy(tipo, "Hip Hop");
                                           break;
                        
                                   case 4: 
                                           strcpy(tipo, "Instrumental");
                                           break;
                        
                                   case 5: 
                                           strcpy(tipo, "Jazz");
                                           break;
                        
                                   case 6: 
                                           strcpy(tipo, "Pop");
                                           break;
                        
                                   case 7: 
                                           strcpy(tipo, "Punk");
                                           break;
                        
                                   case 8: 
                                           strcpy(tipo, "Rap");
                                           break;
                        
                                   case 9: 
                                           strcpy(tipo, "Rock'n'Roll");
                                           break;
                        
                                   case 10:
                                           strcpy (tipo, "Techno");
                                           break;
           }
           
           printf("Tipo de Música: %s\n", tipo);
      
           fflush(stdin);
      
           printf("\nÉ este o registo que quer alterar[S/N]?\n  Opção: ");
           scanf("%c", &sn);
      
           fflush(stdin);
      
           if (( sn == 's' ) || ( sn == 'S' ))
           {
              system("cls");
    
              printf("Que deseja alterar?\n\n");
              printf("  1-O nome da música\n");
              printf("  2-O nome da banda\n");
              printf("  3-O tipo de música\n");
              printf("  4-Tudo\n\n");
              printf("Opção: ");
              scanf("%d", &opcao);
    
              switch(opcao)
              {
                 case 1:  
                          if ( x == dados.n_seq )
                          {
                             test = 1;
                             printf("Nome da música: ");
                             scanf ("%s", &dados.musica);
                             fseek(fd,-(long)sizeof(CONTACTO),1);
                             g=fwrite(&dados,(long)sizeof(CONTACTO),1,fd);
                             alterou = 1;
                          }                  
                          break;
                            
                 case 2:  
                          if ( x == dados.n_seq )
                          {
                             test = 1;
                             printf("Nome da banda: ");
                             scanf("%s", &dados.banda);
                             fseek(fd,-(long)sizeof(CONTACTO),1);
                             g=fwrite(&dados,(long)sizeof(CONTACTO),1,fd);
                             alterou = 1;
                          }
                          break;
                            
                 case 3:  
                          if ( x == dados.n_seq )
                          {
                             test = 1;
                             printf("\nTipos de Música:\n\n1-Electrónica\n2-Heavy Metal\n3-Hip Hop\n4-Instrumental\n5-Jazz\n6-Pop\n7-Punk\n8-Rap\n9-Rock'n'Roll\n10-Techno\n");
                                             
                             switch(dados.tipo)
                             {
                                               case 1: 
                                                       strcpy(tipo, "Electrónica");
                                                       break;
                                                               
                                               case 2: 
                                                       strcpy(tipo, "Heavy Metal");
                                                       break;
                                                               
                                               case 3: 
                                                       strcpy(tipo, "Hip Hop");
                                                       break;
                                                               
                                               case 4: 
                                                       strcpy(tipo, "Instrumental");
                                                       break;
                        
                                               case 5: 
                                                       strcpy (tipo, "Jazz");
                                                       break;
                        
                                               case 6: 
                                                       strcpy (tipo, "Pop");
                                                       break;
                        
                                               case 7: 
                                                       strcpy(tipo, "Punk");
                                                       break;
                        
                                               case 8: 
                                                       strcpy(tipo, "Rap");
                                                       break;
                        
                                               case 9: 
                                                       strcpy(tipo, "Rock'n'Roll");
                                                       break;
                        
                                               case 10:
                                                       strcpy (tipo, "Techno");
                                                       break;
                                               }
                         
                              printf("\nTipo de música: ");
                              scanf("%d", &dados.tipo);
                         
                              if (( dados.tipo < 1 ) || ( dados.tipo > 10 ))
                              {
                                 system("cls");
                                 printf("\n  \aOpção Inválida!!!");
                              }
                               
                              fseek(fd,-(long)sizeof(CONTACTO),1);
                              g=fwrite(&dados,(long)sizeof(CONTACTO),1,fd);
                         
                              alterou = 1;
                         }
                         break;

                  case 4: 
                          if ( x == dados.n_seq )
                          {
                              test = 1;
                              printf("\nNome da música: ");
                              scanf ("%s", &dados.musica);
                              printf("Nome da banda: ");
                              scanf("%s", &dados.banda);
                              printf("\nTipos de Música:\n\n1-Electrónica\n2-Heavy Metal\n3-Hip Hop\n4-Instrumental\n5-Jazz\n6-Pop\n7-Punk\n8-Rap\n9-Rock'n'Roll\n10-Techno\n");
                                
                              switch(dados.tipo)
                              {
                                                case 1: 
                                                        strcpy(tipo2, "Electrónica");
                                                        break;
                                                               
                                                case 2: 
                                                        strcpy(tipo2, "Heavy Metal");
                                                        break;
                                                               
                                                case 3: 
                                                        strcpy(tipo2, "Hip Hop");
                                                        break;
                                                               
                                                case 4: 
                                                        strcpy(tipo2, "Instrumental");
                                                        break;
                        
                                                case 5: 
                                                        strcpy(tipo2, "Jazz");
                                                        break;
                        
                                                case 6: 
                                                        strcpy(tipo2, "Pop");
                                                        break;
                        
                                                case 7: 
                                                        strcpy(tipo2, "Punk");
                                                        break;
                        
                                                case 8: 
                                                        strcpy(tipo2, "Rap");
                                                        break;
                        
                                                case 9: 
                                                        strcpy(tipo2, "Rock'n'Roll");
                                                        break;
                        
                                                case 10: 
                                                         strcpy(tipo2, "Techno");
                                                         break;
                                                }
                         
                                   printf("\nTipo de música: ");
                                   scanf("%d", &dados.tipo);
                                 
                                   fflush(stdin);
                                   
                                   if (( dados.tipo < 1 ) || ( dados.tipo > 10 ))
                                   {
                                      system("cls");
                                      printf("\n  \aOpção Inválida!!!");
                                   }
                                   
                                   fseek(fd,-(long)sizeof(CONTACTO),1);
                                   g=fwrite(&dados,(long)sizeof(CONTACTO),1,fd);
                                   
                                   alterou = 1;
                                   
                                   break;
                                   }
                                 
                  default: 
                           fflush(stdin);
                           system("cls");
                           
                           printf("\n\a  Opção Inválida");
                                          
                           alterou = 1;
                           
                           break;
                           }                       
                                                              
                   if (alterou == 0)
                   {
                                system("cls");
                                printf("\n  Erro na gravação!!!\a");
                                getch();
                   }
                    
                   else
                                fflush(fd); 
                  }

                  if ( test == 0 )
                  {
                     system("cls");
                     printf ("\n  Esse registo não existe!!!\a");
                     getch();     
                  }
}
}
}

void ajudar ()
{
     int resp;
     
     printf ("\tEsta opção serve para esclarecer qualquer dúvida, que você possa ter.\n");
     printf ("\tEste programa tem como objectivo organizar músicas, de forma a facilitar a sua procura.\n");
     printf ("\tSe nao tiver nenhum ficheiro onde armazenar a informação, será lhe perguntado se quer criar um, se sim, ele cria o ficheiro em C:\\trabalho\\dados.dat, se nao, ele sai do programa.\n");
     printf ("\tApós criar o programa, será apresentado um menu com várias opções\n");
     printf ("\tSe não tiver qualquer informação guardada, deverá comecar pela opção inserir, para poder testar as outras opções\n");
     printf ("\tNa opção Inserir, use o underscore em vez de espaços, para não criar erros, o mesmo se aplica à função Alterar\n");
     printf ("\tDepois de inseridos os dados, então aí, já os pode listar, por nome da banda, tipo de musica ou até todos registos.\nEm caso de engano, poderá usar a opção Alterar, para corrijir o erro, esteja à vontade para explorar estas opções.\n");
     printf ("\n\tFEITO POR CARLOS E DIOGO, 11I1, COLÉGIO DE GAIA\n\n\n1-Voltar ao MENU (Pressione 2 vezes ENTER)\n2-Sair\n\nOpção: ");
     scanf("%d", &resp);
     
     switch (resp)
     {
            case 1:
                    break;
                    
            case 2: 
                    exit(1);
                    break;
                    
            default: 
                     system("cls");
                     printf("\n  \aOpção Inválida!");
                     getch();
     }    
}

main()
{
    CONTACTO dados;
    int ERRO, op=0;

    _tsetlocale(LC_ALL, _T("portuguese_portugal"));

    ERRO = abre_fich(NOME_FICH);

    if(ERRO == 0)
    {

            do
            {
                 system("cls");
                 op=menu();
                 fflush(stdin);
                 system("cls");
                 switch(op)
                 {
                            
                            case 1: 
                                    inserir(); 
                                    getch();
                                    system("cls");
                                    fflush(stdin);
                                    break;
                            
                            case 2:
                                    listar();
                                    getch();
                                    system("cls");
                                    fflush(stdin);
                                    break;
                                    
                            case 3: 
                                    listar_musica();
                                    getch();
                                    system("cls");
                                    fflush(stdin);        
                                    break;
                                    
                            case 4: 
                                    listar_banda();
                                    getch();
                                    system("cls");
                                    fflush(stdin);
                                    break;
                                    
                            case 5:
                                    listar_tipo();
                                    getch();
                                    system("cls");
                                    fflush(stdin);
                                    break;
                            
                            case 6:
                                    alterar();
                                    getch();
                                    system("cls");
                                    fflush(stdin);
                                    break;
                                       
                            case 7:
                                    ajudar();
                                    getch();
                                    system("cls");
                                    fflush(stdin);
                                    break;
                                                                              
                            case 8:
                                    fflush(stdin);
                                    fclose(fd);
                                    exit(1);
                                    break;
                                    
                            default:
                                    printf("\a\n  Opção inválida!");
                                    getch();
                    }  
   
   }while(op != 9);

}  

fclose(fd);

}
