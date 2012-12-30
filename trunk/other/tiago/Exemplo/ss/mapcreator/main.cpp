//This example program is created by thecplusplusuy for demonstration purposes (no video about this, I think, it's too simple, and not show nothing new, but I put the source up, to make a complete program with the simple sidescroller (there is video about that)). It's a map-creator for the simple sidescroller game.
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, if you would not delete the link
//so other people can see the tutorial
//this file is main.cpp the entry point of the program
#include "mapcreator.h"	//we include the header, so we can start the mapcreator program

int main(int argc,char** argv)
{
	mapcreator mc;	//we create a new instance of the mapcreator
	mc.start();			//then we start the program
	return 0;
}
