#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define Bullet_No 6 // Maximum no of alive bullet

char string[128]; // String used by txtIt & SDL_ttf
// Conver Variable Argument into a string
inline void txtIt(char *pStr , ...) {
    va_list valist; // Type to hold information about variable arguments
    va_start(valist, pStr); // Initialize a variable argument list
    vsprintf( string , pStr , valist ); // Print formatted variable argument list to string
    va_end(valist); // This macro should be executed before the function
	return;
 	}

int FPS = 50;    // Assign a FPS
int NextTick , interval ; // Used by FPS_Fn
// Initialize FPS_Fn( )
void FPS_Initialize(void) {
NextTick = 0 ;
interval = 1 * 1000 / FPS ; 
return;
}
// Frame Per Second Function  , put this in a loop
void FPS_Fn(void) {
if ( NextTick > SDL_GetTicks( ) ) SDL_Delay( NextTick - SDL_GetTicks( ) );
NextTick = SDL_GetTicks( ) + interval ;
return;
}

// This function load a image file to a surface
// Set bCKey with colorkey (R,G,B) to clear a color on the image
// Set alpha value for transparency 0(No transparent) ~ 255(Ivisible)
inline SDL_Surface *ImgLoader(char *file,bool bCKey, int r , int g , int b , int alpha)
{
	SDL_Surface *pic;
	pic = IMG_Load(file); // From SDL_image.h , load the image to pic
	if(pic==NULL) fprintf(stderr,"Missing image %s : %s\n",file,IMG_GetError());
	if( bCKey ) {
		SDL_SetColorKey(pic,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(pic->format,r,g,b));
 		}
	if(alpha) SDL_SetAlpha(pic, SDL_SRCALPHA|SDL_RLEACCEL , 255 - alpha);
	pic = SDL_DisplayFormat(pic);
	return (pic);
}

// Load a normal picture into a surface
inline SDL_Surface *ImgLoader(char *file)       
				{ return ImgLoader(file,1,0,0,0,0) ; }
// Load a pic & set the transparent color to (255,255,255) , no alpha
inline SDL_Surface *ImgLoader(char *file,bool bCKey)
				{ return ImgLoader(file,1,255,255,255,0) ; }


int main(int argc, char *argv[])
{
TTF_Font *font; // Declare a SDL_ttf font : font
TTF_Init(); // Initilize SDL_ttf
font = TTF_OpenFont("./font/cour.ttf",16); // Open a font & set the font size
SDL_Surface *imgTxt ; // Store image of the text for blit
SDL_Rect txtRect ; // Store (x,y) of text for blit
txtRect.x = 10;
txtRect.y = 250;
SDL_Color fColor , fColorW , fColorR , fColorG ; // Font color (R,G,B)
txtRect.x = 10;
txtRect.y = 250;
fColor.r = 250;
fColor.g = 250;
fColor.b = 250;
fColorW = fColor;
fColorR.r = 250;
fColorR.g = 25;
fColorR.b = 25;
fColorG.r = 25;
fColorG.g = 250;
fColorG.b = 25;

SDL_Event event; // For keyboard event
bool bRun = 1; // The switch of while loop
// bKeyXXX Present the state of keyboard
bool bKeyUP = 0 , bKeyDOWN = 0 , bKeyLEFT = 0 , bKeyRIGHT = 0 , bKeyA = 0; 
int pidx = 0 , aTick = 0 , bKeyATick = 0;
short dx = 2; // The movement value when moving the object anim[ ]
SDL_Surface *screen ;
enum { pic1 , pic2 , pic3 , pic4 , pic5 , pic6 , pic_No  };
SDL_Surface *anim[pic_No];
SDL_Rect animRect ; // The coordinate of anim[ ]
animRect.x = 160 ;
animRect.y = 160 ;

atexit(SDL_Quit);

if( SDL_Init(SDL_INIT_VIDEO) < 0 ) exit(1);

SDL_WM_SetCaption("SDL Window - Prototype", NULL);

screen = SDL_SetVideoMode( 400 , 300 , 32 , SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);

anim[0] = ImgLoader("./anim/justice1.gif",1,255,255,255,0);
anim[1] = ImgLoader("./anim/justice2.gif",1);
anim[2] = ImgLoader("./anim/justice3.gif",1);
anim[3] = ImgLoader("./anim/justice4.gif",1);
anim[4] = ImgLoader("./anim/justice5.gif",1);
anim[5] = ImgLoader("./anim/justice6.gif",1);

FPS_Initialize( );

// Create a class for object bullet
class _Bullet {
	public:
	bool alive; // For bullet alive checking
	SDL_Rect b ; // For SDL fill rectangle
	char w,h ; // The width & height of a bullet
	} bullet[Bullet_No];
// Initialize the bullet
for(int i=0;i<Bullet_No;i++) {
	bullet[i].alive = 0;
	bullet[i].w = bullet[i].h = 5 ; // Bullet Size Configuration
	}

while(bRun) {
	aTick++;
	SDL_FillRect(screen , NULL , 0x221122);
	SDL_BlitSurface( anim[pidx] , NULL , screen , &animRect );
	// Show status of bullet slots
	for(int i=0;i<Bullet_No;i++) {
		txtRect.x = 0 ;
		txtRect.y = 50 + i * 15 ;
		txtIt("%1d" , bullet[i].alive );
		imgTxt = TTF_RenderText_Solid( font , string , fColor );
		SDL_BlitSurface( imgTxt , NULL , screen , &txtRect );
		}
	txtIt("%1d %1d %1d %1d - %1d", bKeyUP , bKeyDOWN , bKeyLEFT , bKeyRIGHT , bKeyA);
	imgTxt = TTF_RenderText_Solid( font , string , fColor );
	SDL_BlitSurface( imgTxt , NULL , screen , NULL );
	
	// Check if exist any empty slot for Initialize a bullet
	if(bKeyA == 1 && bKeyATick%10 == 1) {
		for(int i=0;i<Bullet_No;i++) if(!bullet[i].alive) {
			bullet[i].alive = 1;
			bullet[i].b.x = animRect.x + 60 ;
			bullet[i].b.y = animRect.y + 30 ;
			break; // break this for( ) loop
			}
		} // if(bKeyA == 1 && bKeyATick%10 == 1) { END
	for(int i=0;i<Bullet_No;i++) if(bullet[i].alive) {
		bullet[i].b.x += 5;
		bullet[i].b.w = bullet[i].w;
		bullet[i].b.h = bullet[i].h;
		SDL_FillRect(screen , &bullet[i].b , 0xFFFF66);
		// Bullet Destroy condition
		if(bullet[i].b.x > 380) bullet[i].alive = 0;
		}
	
	
	SDL_Flip(screen);
    FPS_Fn();
	if( aTick%10 == 0 ) pidx++;
	if(pidx >= pic_No) pidx = 0;
	while( SDL_PollEvent( &event ) ){
		switch( event.type ){
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ){
					case SDLK_UP:
						bKeyUP = 1;
						break;
					case SDLK_DOWN:
						bKeyDOWN = 1;
						break;
					case SDLK_LEFT:
						bKeyLEFT = 1;
						break;
					case SDLK_RIGHT:
						bKeyRIGHT = 1;
						break;
					case SDLK_f:
						bKeyA = 1;
						break;
					case SDLK_ESCAPE:
						bRun = 0 ;
						break;
					default:
						break;
					} // switch( event.key.keysym.sym ){ END
				break; // case SDL_KEYDOWN: END
			case SDL_KEYUP:
				switch( event.key.keysym.sym ){
					case SDLK_UP:
						bKeyUP = 0;
						break;
					case SDLK_DOWN:
						bKeyDOWN = 0;
						break;
					case SDLK_LEFT:
						bKeyLEFT = 0;
						break;
					case SDLK_RIGHT:
						bKeyRIGHT = 0;
						break;
					case SDLK_f:
						bKeyA = 0;
						break;
					default:
						break;
					} // switch( event.key.keysym.sym ){ END
				break; // case SDL_KEYUP: END
			case SDL_QUIT:
				bRun = 0;
				break;
			default:
				break;
			} // switch( event.type ){ END
		} // while( SDLK_PollEvent( &event ) ){ END
	// Deal with key states
	if(bKeyUP) animRect.y = animRect.y - dx;
	if(bKeyDOWN) animRect.y = animRect.y + dx;
	if(bKeyLEFT) animRect.x = animRect.x - dx;
	if(bKeyRIGHT) animRect.x = animRect.x + dx;
	if(bKeyA) bKeyATick++; // Press KeyA counter + 1
	if(!bKeyA) bKeyATick=0; // Release KeyA counter = 0

	}; // while(bRun) { END
	

return 0;
}
