#include <stdio.h>
#include<windows.h>
#define V 21 //dimensiones de nuestro campo
#define H 75 //h=x y v=y

void inicio (char campo[V][H], int pelX, int PelY, int inijug, int finjug, int iniia, int finia);
void borde(char campo[V][H]);
void raqjug(char campo[V][H], int inijug,int finjug);
void raqia(char campo[V][H], int iniia, int finia);
void pel(char campo[V][H],int pelX, int pelY);
void leercamp(char campo[V][H]);
void gameloop(char campo[V][H],int pelX, int pelY, int inijug, int finjug, int iniia, int finia, int modX, int modY, int modia);
void draw (char campo[V][H]);
void input(char campo[V][H], int *pelX, int *pelY, int *inijug, int *finjug, int *iniia, int *finia, int *modX, int *modY, int *modia, int *gol);
void update(char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia);
void gotoxy(int x, int y);

int main(){

    int pelX, pelY, inijug, finjug, iniia, finia; //posicion
//las variables pelX y pelY nos indican la posicion en la que se moveran los elementos de nuestro juego, en este caso las raquetas y la pelota
//las variables inijug y finjug indica donde comienza la raqueta y donde termina
//las variables iniia y finia indican el comienzo de la raqueta de la ia y el fin de la raqueta del jugador
    int modX, modY, modia; //movimiento (modificar la trayectoria de la pelota, modia modifica el movimiento de la raqueta de la ia)
    char campo [V][H];

    //Posicion
    pelX = 37;
    pelY = 10;

    inijug = 8;
    finjug = 12;

    iniia = 8;
    finia = 12;

    //Modificacion
    modX = -1;
    modY = -1;
    modia = -1;

//llamamos a la funcion inicio
    inicio(campo,pelX,pelY,inijug,finjug,iniia,finia);
    gameloop(campo, pelX, pelY, inijug, finjug, iniia, finia, modX, modY, modia);





system("pause");
return 0;
}

//Declaramos la funcion Inicio
void inicio (char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia){
//llamamos a la funcion borde
    borde(campo);
    raqjug(campo,inijug,finjug);
    raqia(campo,iniia,finia);
    pel(campo,pelX,pelY);
}

//Declaramos la funcion borde
void borde(char campo[V][H]){ //pinta el rectangulo que sera nuestro campo de juego
  int i, j;

    for(i = 0; i < V; i++){
        for(j = 0; j < H; j++){
            if(i == 0 || i == V-1){
                campo[i][j] = '-';
            }
            else if(j == 0 || j == H-1){
                campo[i][j] = '|';
            }
            else{
                campo[i][j] = ' ';
            }
        }
    }
}

//Declaramos la funcion raqjug (construye la raqueta del jugador)
void raqjug(char campo[V][H], int inijug,int finjug){
 int i, j;

  for(i = inijug; i <= finjug; i++){
    for(j = 2; j <= 3; j++){
        campo[i][j] = '*';
    }
  }
}

//Declaramos la funcion raqia (construye la raqueta de la ia)
void raqia(char campo[V][H], int iniia, int finia){
 int i,j;

   for(i = iniia; i <= finia; i++){
       for(j = H-4; j <= H-3; j++){
        campo[i][j] = '*';
       }
   }
}

//Declaramos la funcion pel (construye la pelota)
void pel(char campo[V][H],int pelX, int pelY){
     campo[pelY][pelX] = 'O';
}

//Declaramos la funcion leercamp(nos mostrara la matriz (area del juego) en pantalla
void leercamp(char campo[V][H]){
     int i,j;

     for(i = 0; i < V; i++){
        for(j = 0; j < H; j++){
            printf("%c",campo[i][j]);
        }
            printf("\n");
     }


}

//Declaramos la función gameloop
void gameloop(char campo[V][H],int pelX, int pelY, int inijug, int finjug, int iniia, int finia, int modX, int modY, int modia){
   int gol;
    gol = 0;

    do{
      draw(campo); //Dibujar en pantalla
      input(campo, &pelX, &pelY, &inijug,&finjug, &iniia, &finia, &modX, &modY, &modia, &gol); //Verificar y modificar las posiciones
      update(campo,pelX,pelY,inijug,finjug,iniia,finia); //Actualizar la matriz campo
      Sleep(10);
    }
      while(gol == 0);

}

//Declaramos la funcion draw
void draw (char campo[V][H]){
    gotoxy(0,0);
    leercamp(campo);
}

//Declaramos la funcion input
void input(char campo[V][H], int *pelX, int *pelY, int *inijug, int *finjug, int *iniia, int *finia, int *modX, int *modY, int *modia, int *gol){
  int i;
  char key, key2;

  //Verificacion
    if(*pelY == 1 || *pelY == V-2){
        *modY *= -1;
    }

    if(*pelX == 1 || *pelX == H-2){
        *gol = 1;
    }

    if(*pelX == 4){
        for(i = (*inijug); i <= (*finjug); i++){
            if(i == (*pelY)){
                *modX *= -1;
            }
        }
    }

    if(*pelX == H-5){
        for(i = (*iniia); i <= (*finia); i++){
            if(i == (*pelY)){
                *modX *= -1;
            }
        }
    }

    if(*iniia == 1 || *finia == V-1){
        *modia *= -1;
    }


  //Modificacion


     if(*gol == 0){
     //pelota: (movimiento)

     *pelX += (*modX);
     *pelY += (*modY);

     //Raqueta de la IA



    // Raqueta jugador:

    if(kbhit() == 1){
       key = getch(); //lo mismo que scanf solo que no hay que pulsar intro
       key2 = getch();

        if(key == '8'){
            if(*inijug != 1){
                *inijug -= 1;
                *finjug -= 1;
            }
        }

        if(key == '2'){
            if(*finjug != V-2){
                *inijug += 1;
                *finjug += 1;
            }
        }

        if(key2 == 'q'){
            if(*iniia != 1){
                *iniia -= 1;
                *finia -= 1;
            }
        }

        if(key2 == 'z'){
            if(*finia != V-2){
                *iniia += 1;
                *finia += 1;
            }
        }

    }

 }


}

//Declaramos la funcion update
void update(char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia){

    borde(campo);
    raqjug(campo,inijug,finjug);
    raqia(campo,iniia,finia);
    pel(campo,pelX,pelY);
}

//Declaramos la funcion gotoxy
void gotoxy(int x, int y){
COORD coord;
coord.X=x;
coord.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


