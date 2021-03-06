/**
  FILE auguri_natale_2019.c 
  Copyright (C) 2019  Francesco Sisini (francescomichelesisini@gmail.com)
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <math.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define STREEP_W 99
#define BKG_W 55
#define BKG_H 7
#define TF 6 //time frame
#define V_R //rate di tempo per la velocità
#define BG 12

char * add(char *str,char reset);
double bkg_velocity(int bkg_n,int x_old, int x,double d[]);
char * color(char *str, int bg_cielo);
void print_centered(int rc,int cc, char *str);
char * scroll(char *str[], double v, double t,int x_0);
int trm_dimensioni_finestra(int *rows, int *cols);
void * suona_gingle(void *);
void pausa(float s);




char * b0[BKG_H]={"                                                                                                  ",
                  "                                                                                                  ",
                  "              _                                                                                   ",
                  "            _/_\\_                             _                                                     ",
                  "            ('A')                            (_)                                                  ",
                  "           *(A:A)*                          (A:A)                                                 ",
                  "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"};


char  *b1[BKG_H]={"  #                                             #                                                 ",
                  " ###                    #               #      ###      #                  #                #     ",
                  "#####       #          ###             ###    #####    ###                ###              ###    ",
                  "#####      ###        #####           #####   #####   #####              #####            #####   ",
                  "  @       #####         @               @    ###@###    @               ###@###             @     ",
                  "  @         @           @               @       @       @                  @                @     ",
                  "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"};

char  *b2[BKG_H*TF]={"     .    .          .  .      .                          .                .         .     .     ",
                     "          .   .              .                  .  .               .        .     .              ",
                     " .    .           .                  .                    .                        .         .   ",
                     "  .          .          .         .            .                           .                .    ",
                     "                 .           .                                  .                  .   .         ",
                     "     .      .      .                   .                           .                      .      ",
                     "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO",
                     

                     "           .         .                   .              .       .              .             .   ", 
                     "     .    .    .     .   .    .                           .                 .        .     .     ",
                     "           .   .              .                 .  .              .         .    .               ",
                     "  .    .          .                 .                      .                        .        .   ",
                     "  .          .          .         .            .                           .                .    ",
                     "                 .           .                                  .                  .   .         ",
                     "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO",
                     

                     "   .  .           .              . .            .  .                   .                         ",
                     "          .          .                    .             .      .               .                 ", 
                     "     .   .    .     .     .   .                           .                .         .    .      ",
                     "          .     .              .                .   .              .        .     .              ",
                     "   .    .           .                 .                    .                        .        .   ",
                     "  .          .          .         .            .                           .                .    ",
                     "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO",
                     

                     " .         .           .      .           .                  .              .           .        ",
                     "  .   .           .             .   .             ..                   .                         ",
                     "           .         .                     .            .      .              .                  ", 
                     "                          .   .                            .               .         .    .      ",
                     "         .        .            .                .   .              .        .     .              ",
                     "                          .   .                            .               .         .    .      ",
                     "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO",
                     

                     "          .   .              .                  .  .               .        .     .              ",
                     " .         .           .      .           .                  .              .           .        ",
                     "  .   .           .             .   .             ..                   .                         ",
                     "           .         .                     .            .      .              .                  ", 
                     "                          .   .                            .               .         .    .      ",
                     "         .        .            .                .   .              .        .     .              ",
                     "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO",
                     
                     

                     "     .               .                .                    .                              .      ",
                     "          .   .              .                  .  .               .        .     .              ",
                     " .         .           .      .           .                  .              .           .        ",
                     "  .   .           .             .   .             ..                   .                         ",
                     "           .         .                     .            .      .              .                  ",
                     "                          .   .                            .               .         .    .      ",
                     "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"
                     


};



int main()
{


  /*____________________________________________________
   *
   * PERSONALIZZA IL TUO MESSAGGIO DI AUGURI
   * NON SUPERARE LE 50 LETTERE PER RIGA
   */
  
   /* SCRIVI QUI I TUOI AUGURI */
  char *str1="AUGURI DI BUON NATALE";
  char *str2="E FELICE 2021";
  char *str3="https://www.pumar.it/";
  char *str4="Da Scuola_Sisini";
  
  char buff[200];

  
  printf("\x1b[2J");

  int rn,cn;
  trm_dimensioni_finestra(&rn, &cn);

  if(cn<BKG_W+5)
    {
      printf("\nRidimensiona il terminale con almeno %d colonne",BKG_W+5);
      exit(1);
    }

  int cielo[]={16,17,18,19,20,21,57,93,129,165,201,201,201,201,165,129,93,57,21,20,19,18,17,16};
   
  int left_corner=(cn-BKG_W)/2;
  
/* apertura anngolare della camera */
  double alp=60.0;
  
  /* posizione del T sul bg0    */
  int x0=strlen(b0[0])/2.;
  
  /* velocità T in passi/iterazione rispetto al piano 0 */
  double vb[BKG_W];
  vb[0]=1;
  
  /* segmento visibile del piano  */
  double lb[BKG_W];
  
  /* distanza del piano (background) dalla camera */
  double db[BKG_W]={5,20,35};

  /* Calcolo il segmento visibile per ogni piano */
  for(int i=0;i<BKG_W;i++)
    {
      lb[i]=2*db[i]*sin(alp/2);
    }


  /* suona la canzone in un thread separato */
  pthread_t musica;

  if(pthread_create(&musica,0,&suona_gingle,0) != 0)
    {
      //senza musica...
      ;
    }




  /* Cornice */
  for(int i=left_corner-2;i<left_corner+BKG_W;i++)
    {
      printf("\x1b[5;%dH%s\n",i,"X");
      pausa(0.05);
    }
  for(int i=5;i<5+BKG_H*2+3;i++)
    {
      printf("\x1b[%d;%dH%s\n",i,left_corner+BKG_W,"X");
      pausa(0.05);
    }
  for(int i=left_corner+BKG_W;i>=left_corner-1;i--)
    {
      printf("\x1b[%d;%dH%s\n",5+BKG_H*2+3,i,"X");
      pausa(0.05);
    }
  for(int i=5+BKG_H*2+3;i>5;i--)
    {
      printf("\x1b[%d;%dH%s\n",i,left_corner-2,"X");
      pausa(0.05);
    }

  
  /* Auguri */
  for(int i=1;i<=strlen(str1);i++)
    {
      strncpy(buff,str1,i);
      buff[i]=0;
      print_centered(7,cn,buff);
      pausa(0.08);
    }

  for(int i=1;i<=strlen(str2);i++)
    {
      strncpy(buff,str2,i);
      buff[i]=0;
      print_centered(8,cn,buff);
      pausa(0.08);
    }

  for(int i=1;i<=strlen(str3);i++)
    {
      strncpy(buff,str3,i);
      buff[i]=0;
      print_centered(9,cn,buff);
      pausa(0.08);
    }
  
   for(int i=1;i<=strlen(str4);i++)
    {
      strncpy(buff,str4,i);
      buff[i]=0;
      print_centered(20,cn,buff);
      pausa(0.1);
    }


  int ts = 0;//indice tempo neve
  int tg = 0;//indice ora del giorno
  
  /* Animazione */  
  for(int i=1;i<1000;i++)
    {
      /* calcola il frame relativo al background*/
      if(i%5 == 0) ts++;
      int tf_i=0;
      tf_i=(ts+5)%TF;

      /* calcola l'ora del giorno */
      tg = (i/15)%24;
      int bgc = cielo[tg];
      
      char *mp;
     
      double v=bkg_velocity(2,i-1,i,db);
      char *p=scroll(b2+tf_i*BKG_H,0,i,1);
      mp=add(p,1);
      
      v=bkg_velocity(1,i-1,i,db);
      p=scroll(b1,v,i,1);
      add(p,0);
      
      v=bkg_velocity(0,i-1,i,db);
      p=scroll(b0,v,i,1);
      mp=add(p,0);
      
      
      /*stampa il merge*/
      
      printf("\x1b[11;%dH%s\n",left_corner,color(mp,bgc));
      printf("\x1b[12;%dH%s\n",left_corner,color(mp+BKG_W,bgc));
      printf("\x1b[13;%dH%s\n",left_corner,color(mp+2*BKG_W,bgc));
      printf("\x1b[14;%dH%s\n",left_corner,color(mp+3*BKG_W,bgc));
      printf("\x1b[15;%dH%s\n",left_corner,color(mp+4*BKG_W,bgc));
      printf("\x1b[16;%dH%s\n",left_corner,color(mp+5*BKG_W,bgc));
      printf("\x1b[17;%dH%s\n",left_corner,color(mp+6*BKG_W,bgc));
      
      pausa(0.1);
    }
      

  
}

/* calcola la velocità di scorrimento del piano numero: bkg_n  */
double bkg_velocity(int bkg_n,int x_old, int x,double d[])
{
  return (x-x_old)*d[0]/d[bkg_n]; 
}

/* sovrappone in trasparenza un piano immagine all'immagine di background.
   L'immagine ottenuta è il nuovo background.
   Il char 32 (spazio) è il carattere di trasparenza.
   Se reset==1 imposta tutta l'immagine a char 32 (spazio)  */
char * add(char *img,char reset)
{
  static char mal=0;
  static char * buffer=0;
  if(!mal)
    {
      buffer=malloc(BKG_H*BKG_W*sizeof(char));
      mal=1;
    }
  if(reset) memset(buffer,32,BKG_H*BKG_W*sizeof(char));
  for(int i=0;i<BKG_H*BKG_W;i++)
    {
      if(*(img+i)!=32)*(buffer+i)=*(img+i);
    }
  return buffer;
}


/* Accetta una stringa aggiunge gli escape per colorarli
   secondo una codifica ASCII->colore stabilita in questa 
   stessa funzione
*/
char * color(char * str, int bg_cielo){
static char mal=0;
  static char * buffer=0;
  int buffer_p=0;
  if(!mal)
    {
      buffer=malloc(BKG_H*BKG_W*sizeof(char)*3);
      mal=1;
    }
  static char ansi_code[80];
  /* Hash table colori con codifca a 8-bit ESC[48;5;#m */
  /*
    
    da 0 a 7 colori ANSI normali
    da 8 a 15 colori ANSI brillanti
    da 16 a 231 scala RGB: B+G*6+R*36
    da 232 a 255 scala di grigi da bianco a nero

    hash table (modificabile a piacere):
    #-> verde / 34
    @-> marrone / 94 
    O-> rosso / 9
   */
  int c=255;
  int b;
  for(int i=0;i<strlen(str);i++){

     if(*(str+i)=='A')
      {
        c=bg_cielo;
        b=bg_cielo;
      }
    if(*(str+i)=='#')
      {
        c=34;
        b=bg_cielo;
      }
     if(*(str+i)=='O')
      {
        c=15;
        b=15;
      }
     if(*(str+i)=='*')
      {
        c=15;
        b=bg_cielo;
      }
    if(*(str+i)=='@')
      {
        c=94;
        b=bg_cielo;
      }
    
    if(*(str+i)=='.')
      {
        c=15;
         b=bg_cielo;
      }
    if(*(str+i)=='v') 
    {
      c = 2;
      b=bg_cielo;
    }
    if(*(str+i)=='(' || *(str+i)==')' || *(str+i)==':' || *(str+i)=='\\' || *(str+i)=='/' || *(str+i)=='_'|| *(str+i)=='\'' ) 
    {
      c=15;
      b=bg_cielo;
    }
     if(*(str+i)==' ') 
    {
       b=bg_cielo;
    }
    
     
     sprintf(ansi_code,"\x1b[38;5;%dm\x1b[48;5;%dm%c\x1b[38;5;0m\x1b[48;5;0m",c,b,*(str+i));
     strcpy(buffer+buffer_p,ansi_code);
     buffer_p=buffer_p+strlen(ansi_code)-1;
     
     buffer_p++;
  }
  *(buffer+buffer_p)=0;
  return buffer;
}



/* scorre l'immagine str in base alla posizione e alla velocità  */
char * scroll(char *str[], double v, double t,int x_0)
{
  static char mal=0;
  static char * buffer=0;
  if(!mal)
    {
      buffer=malloc(BKG_H*BKG_W*sizeof(char));
      mal=1;
    }

    
  int l=strlen(str[0]);
  int n=x_0+v*t;
  
  
  if((n%l)+BKG_W<l)
    {
      for(int i=0;i<BKG_H;i++)
        {
          memcpy(buffer+i*BKG_W,str[i]+(n%l),BKG_W);
          *(buffer+(i+1)*BKG_W-1)=0;
        }
    }
  else
    {
      int w=l-n%l;
      for(int i=0;i<BKG_H;i++){
        memcpy(buffer+i*BKG_W,str[i]+(n%l),w);
        memcpy(buffer+i*BKG_W+w,str[i],BKG_W-w);
        *(buffer+(i+1)*BKG_W-1)=0;
      }
    }
  
  return buffer;
  
}

void print_centered(int rc,int cc, char *str){

  int ln = strlen(str);
  if(ln>BKG_W-5)
    {
      printf("\nInserire messaggio di auguri per righe minori di %d\n",BKG_W-5);
      exit(1);
    }
  
  int l=(cc-ln)/2;
  printf("\x1b[%d;%dH%s\n",rc,l,str);
}

int trm_dimensioni_finestra(int *rows, int *cols) 
{
  struct winsize ws;  
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
    {
      return -1;
    } else
    {
      *cols = ws.ws_col;
      *rows = ws.ws_row;
      return 0;
    }
}

void * suona_gingle(void * ptr)
{
  //for(int i=0;i<5;i++)
  system("./gb");
  
}

void pausa(float s)
{
  struct timespec tc;
  tc.tv_sec = s;
  tc.tv_nsec = s*1000000000;
  nanosleep(&tc, 0);
}
