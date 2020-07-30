#include "ncurses.h"
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <time.h>

int main(int argc, char *argv[]) {
        
        srand(time(NULL));

        bool shouldContinue, trail;
        int row,col,x,y,t,s,len,changeDir;
        const char* bouncingText;
        float sec;				        /* to store the number of rows and *
		                    			 * the number of colums of the screen */
        sec = 0.1;
        bouncingText = "DVD";
        shouldContinue = true;
        trail = false;

        //Parses command arguments
        for (int i = 1; i < argc; i++) {
                if (std::string(argv[i]) == "-s" || std::string(argv[i]) == "--second") {
                        i++;
                        sec = atof(argv[i]);
                }
                if (std::string(argv[i]) == "-t" || std::string(argv[i]) == "--trail") {
                        trail = true;
                }
                if (std::string(argv[i]) == "-c" || std::string(argv[i]) == "--string") {
                        i++;
                        bouncingText = argv[i];
                }
                if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
                        printf("usage: bounce [options]\n\toptions:\n\t\t-s, --second     Specifies the number of movements per second. (Supports Decimals)\n\t\t-t, --trail      Enables a trail of dots\n\t\t-c, --string     Changes the string that is bounced from the default 'DVD'\n\t\t-h, --help       Help page\n");
                        return 0;
                }
        }

        initscr();		        		/* start the curses mode */
        getmaxyx(stdscr,row,col);		/* get the number of rows and columns */


        x = col/2;
        y = row/2;
        
        len = strlen(bouncingText); 
        int reverseVelocity = rand() % 2;
        int xOrY = rand() % 2;

        int velocity[2] = {1,1};

        if (reverseVelocity == 0) {
                if (xOrY == 0) {
                        velocity[0] = -velocity[0];
                }
                else {
                        velocity[1] = -velocity[1];
                }
        }

        while (shouldContinue) {

                x += velocity[0];
                y += velocity[1];

                usleep(sec*1000*1000);
                
                mvprintw(y,x,bouncingText);
                
                for (int i = 0; i < len; i++) {
                        if (trail) {
                                mvprintw(s,t+i,".");
                        }
                        else {
                                mvprintw(s,t+i," ");
                        }
                }

                mvprintw(0,0,"");

                //checks if the text has hit the edge and if it has it reverses its velocity
                if (x == col-len) {
                        velocity[0] = -velocity[0];
                }
                else if (x == 1) {
                        velocity[0] = -velocity[0];
                }
                if (y == row-1) {
                        velocity[1] = -velocity[1];
                }
                else if (y == 0) {
                        velocity[1] = -velocity[1];
                }

                //s and t are the old x/y coordinates.
                //This is used to print over the old characters
                t = x;
                s = y;
                
                getmaxyx(stdscr,row,col);	
                if (x > col-len || y > row-1) {
                        erase();
                        x = col/2;
                        y = row/2;
                }
                refresh();
        }
}
