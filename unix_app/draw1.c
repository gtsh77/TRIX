#include "lib.c"

dbyte playerIndex;

void draw1(void)
{
	start = getCycles();
	//
	// === GC INIT ===
	//
	//set graphical context mask
	gc_mask = GCCapStyle | GCJoinStyle;
	//set gc vals
	gc_val.cap_style = CapButt;
	gc_val.join_style = JoinBevel;
	//create gc
	gc = XCreateGC(session, window, gc_mask, &gc_val);
	//printf("%d\n",gc);
	//set foreground
	//XSetForeground(session, gc, WhitePixel(session,cur_screen));
	//set background
	XSetBackground(session, gc, BlackPixel(session,cur_screen));
	//set fill style
	XSetFillStyle(session, gc, FillSolid);
	//set line attrs
	XSetLineAttributes(session, gc, 1, LineSolid, CapRound, JoinRound);

	//
	// === DRAW SHAPES ===
	//

	//multi-lines
	// XPoint points[] = 
	// {
	// 	{0,130},
	// 	{15,130},
	// 	{0,160},
	// 	{0,130}
	// };

	//XDrawLines(session, window, gc, points, 4, CoordModeOrigin);
	//XFillPolygon(session, window, gc, points, 4, Complex, CoordModeOrigin);


	//draw single line
	//XDrawLine(session, window, gc, 0, 120, 100, 120);

	//draw & fill rectangle
	//XDrawRectangle(session, window, gc, 0, 0, 100, 100);
	//XFillRectangle(session, window, gc, 0, 0, 320, 320);

	//
	// === DRAW CEIL/FLOOR ===
	//

	visual = DefaultVisual(session, DefaultScreen(session));
	colormap = XCreateColormap(session, window, visual, AllocNone);

	XColor ceil_color, floor_color;

	//CEILCOLOR
	ceil_color.red = BIT16(255);
	ceil_color.green = 0;
	ceil_color.blue = 0;

	XAllocColor(session, colormap, &ceil_color);
	XSetForeground(session, gc, ceil_color.pixel);

	XFillRectangle(session, window, gc, 0, 0, FIELDW, FIELDH/2);

	//FLOORCOLOR
	floor_color.red = 0;
	floor_color.green = BIT16(255);
	floor_color.blue = 0;

	XAllocColor(session, colormap, &floor_color);
	XSetForeground(session, gc, floor_color.pixel);

	XFillRectangle(session, window, gc, 0, (FIELDH/2), FIELDW, FIELDH);

	//
	// === DRAW FENCE BEHIN PLAYER
	//

	//DrawRectangle(session, window, gc, 0, 0, FIELDW, FIELDH/2);	
	playerIndex = getPlayer(level.map,level.length);
	printf("%d\n",playerIndex);
	

	//
	// === BENCH STUFF
	//

	//get core freq
	// long_u start, end;
	// start = getCycles();
	// sleep(1);
	end = getCycles();
	//printf("%ld\n",(long_u)(end-start));
	printf("Render: %.9f\n",(double)(getCycles()-start)/3.5e9);
	return;

}






