#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <time.h>

const char* text_color(int color);

int main() {
	clrscr();
	window(10, 5, 70, 15);
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 8; j++) 
		{
			textbackground(j);
			textcolor(i);
			cprintf("\n\rBackground color: %d", j);
			cprintf("    Text color: %s", text_color(i));
			delay(300);
			union REGS r;
			r.h.al = 1;
			r.h.ah = 6;
			r.h.ch = 4;
			r.h.cl = 9;
			r.h.dh = 14;
			r.h.dl = 69;
			r.h.bh = 0x07;
			int86(0x10, &r, &r);
		}
	getchar();
	return 0;
}

const char* text_color(int color)
{
	switch (color)
	{
		case BLACK: return "black";
		case BLUE: return "blue";
		case GREEN: return "green";
		case CYAN: return "cyan";
		case RED: return "red";
		case MAGENTA : return "magenta";
		case BROWN: return "brown";
		case LIGHTGRAY: return "light gray";
		case DARKGRAY: return "dark gray";
		case LIGHTBLUE: return "light blue";
		case LIGHTGREEN: return "light green";
		case LIGHTCYAN: return "light cyan";
		case LIGHTRED: return "light red";
		case LIGHTMAGENTA: return "light magenta";
		case YELLOW: return "yellow";
		case WHITE: return "white";
		default: return "error";
	}
}