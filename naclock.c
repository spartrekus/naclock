


//////////////////////////
// ncurses
//////////////////////////
#if defined(__linux__)
#define MYOS 1
#include <ncurses.h>
#elif defined(_WIN32)
#define MYOS 2
#include <curses.h>
#elif defined(_WIN64)
#define MYOS 3
#include <curses.h>
#elif defined(__unix__)
#define MYOS 4
#include <ncurses.h>
#else
#define MYOS 0
#include <ncurses.h>
#endif




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
void tinyclock()
{
   initscr();	
   curs_set( 0 );
   int rows, cols;  
   getmaxyx( stdscr, rows, cols);
   refresh();

   curs_set( 0 );
   attroff( A_REVERSE);
   attron( A_BOLD);
   color_set( 0,NULL);
   nodelay( stdscr, TRUE);

	long t;
	struct tm *ltime;
        erase();
        while ( 1 )
	{
	    time(&t);
            ltime=localtime(&t);
            nodelay( stdscr, TRUE);
	    mvprintw( 1,0, "TIME");
	    mvprintw( 2,0, "[TIME :%02d:%02d:%02d]", ltime->tm_hour, ltime->tm_min, ltime->tm_sec);
	    mvprintw( 3,0, "[DATE :%02d/%02d/%02d]", 1900 + ltime->tm_year, ltime->tm_mon +1 , ltime->tm_mday);
	    refresh();
          usleep( 1e6 /2 /5 ); 
	}

}


int ch ; 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define FontWH_Ratio 2
nrclock_drw_cir(hand_max, sycen, sxcen)
int hand_max; int sycen; int sxcen;
{
	int x,y,r;
	char c;

	for(r=0;r<60;r++){
		x=cos(r*M_PI/180*6)*hand_max*FontWH_Ratio+sxcen;
		y=sin(r*M_PI/180*6)*hand_max+sycen;
		switch (r) {
			case 0:
			case 5:
			case 10:
			case 15:
			case 20:
			case 25:
			case 30:
			case 35:
			case 40:
			case 45:
			case 50:
			case 55:
				c='o';
				break;
			default:
				c='.';
				break;
		}
		mvaddch(y,x,c);
	}
}

nrclock_draw_hand(minute, hlenght, c, sxcen, sycen)
int minute; int hlenght; char c; int sxcen; int sycen;
{
	int x,y,n;
	float r=(minute-15)*(M_PI/180)*6;

	for(n=1; n<hlenght; n++){
		x=cos(r)*n*FontWH_Ratio+sxcen;
		y=sin(r)*n+sycen;
		mvaddch(y,x,c);
	}
}





/////
void nrclock(){
	char digital_time[15];
	int sXmax, sYmax, smax, hand_max, sXcen, sYcen;
	long t;
	struct tm *ltime;

   int nrclock_gameover =  0;
   curs_set( 0 );
   attroff( A_REVERSE);
   attron( A_BOLD);
   color_set( 2,NULL);
   nodelay( stdscr, TRUE);

        int rows, cols;  
        getmaxyx( stdscr, rows, cols);
        char hostnet[250];
        strncpy( hostnet, "", 250 );


        nrclock_gameover =  0;
        while( nrclock_gameover == 0 ){

		time(&t);
		ltime=localtime(&t);
		sXmax = COLS;
		sYmax = LINES;

		if(sXmax/2<=sYmax)
			smax=sXmax/2;
		else
			smax=sYmax;

		hand_max = (smax/2)-1;

		sXcen = sXmax/2;
		sYcen = sYmax/2;

		erase();
		nrclock_drw_cir(hand_max, sYcen, sXcen);

		nrclock_draw_hand((ltime->tm_hour*5)+(ltime->tm_min/10), 2*hand_max/3, 'h', sXcen, sYcen);
		nrclock_draw_hand(ltime->tm_min, hand_max-2, 'm', sXcen, sYcen);
		nrclock_draw_hand(ltime->tm_sec, hand_max-1, '.', sXcen, sYcen);

   
   mvprintw(sYcen-(3*hand_max/5) +2 , sXcen-5, "[%02d:%02d:%02d]", ltime->tm_hour, ltime->tm_min, ltime->tm_sec); 


	mvprintw( 0,0, "[%02d:%02d:%02d]", ltime->tm_hour, ltime->tm_min, ltime->tm_sec);

	mvprintw( rows-1,0, "[%02d:%02d:%02d]", ltime->tm_hour, ltime->tm_min, ltime->tm_sec);

     mvaddstr(rows-1 , cols -12 -1 , ".:NACLOCK:.");

     refresh();

     nodelay( stdscr, TRUE);
                ch = getch(); 
		switch( ch ){

		   case KEY_F(10):
		   case 'i':
		   case 'q':
		    nrclock_gameover = 1;
		    break;

		}



               usleep( 1e6 /2 /5 ); 
	}

   curs_set( 1 );
   attroff( A_REVERSE);
   color_set(0,NULL);
   nodelay( stdscr, FALSE);
}










void drawit(){
        int rows, cols;  
        getmaxyx( stdscr, rows, cols);
        mvprintw(5 , 5, "Hello World !!!");	
        mvprintw(rows-1 , 0, "<Press Key to Continue>");
}




////////////////////////////////////////////////
int main( int argc, char *argv[])
{


    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( strcmp( argv[1] , "--simple" ) ==  0 ) 
      {
         printf( " NACLOCK SIMPLE \n" );
         tinyclock();
         return 0;
      }



        printf( " NACLOCK CLASSIC \n" );
        initscr();	
        curs_set( 0 );
        drawit();
        nrclock();

	refresh();			
        curs_set( 1 );
	endwin();		
	return 0;
}





