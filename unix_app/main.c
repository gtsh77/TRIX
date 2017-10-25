#include "main.h"
#include "draw3d.c"

//base vars
Display *session;
Window window;
XEvent cur_event;
byte cur_screen;
GC gc;
int_u gc_mask;
XGCValues gc_val;
long_u start, end, totals, totale;
Visual *visual;
Colormap colormap;

int main(void)
{   
    //start bench
    totals = getCycles();
    
    //load level from tct's binary output into memory
    loadTileMap("../maps/unix1.json.bin");
    //load and map textures into memory
    loadAssets();
    //seekAssets();

    //connect to xserv
    session = XOpenDisplay(NULL);   
    if (session == NULL)
    {
        fprintf(stderr, "Cannot open server\n");
        exit(1);
    }
 
    //get screen id from xserv
    cur_screen = (byte)DefaultScreen(session);
 
    //create window
    window = XCreateSimpleWindow(session, RootWindow(session, cur_screen), 0, 0, FIELDW, FIELDH, 0,
                           BlackPixel(session, cur_screen), WhitePixel(session, cur_screen));
 
    //select events??
    XSelectInput(session, window, ExposureMask | KeyPressMask);
 
    //map => show the window
    XMapWindow(session, window);
    XFlush(session);
 
    //event loop
    while(1)
    {
        XNextEvent(session, &cur_event); 
        //draw
        if (cur_event.type == Expose)
        {
            draw3d();   
            finishBench();
            //matrix algo test (affine tang 10)
            double points[] = {320,0,320,320,0,320,0,0,320-56*2,56,320-56*2,320-56,0,320,0,0}, factors[8];
            solveMatrix(factors,points);
            

        }
        //exit point
        else if (cur_event.type == KeyPress)
            break;
        else;
    }

    //XSync(session,False);

    //sleep(5);
 
    //bb to xserv
    XCloseDisplay(session);
    return 0;
 }