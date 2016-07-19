#include "mylib.h"
#include "galagaalpha1.h"
#include "stars.h"
#include "closingscreen.h"

u16* videoBuffer = (u16*) 0x6000000;
extern const unsigned char fontdata_6x8[12288];


void setPixel(int x, int y, u16 color)
{
    videoBuffer[y * 240 + x] = color;
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

//Draws an image (specified by *image) at x, y
void drawImage3(int x, int y, int width, int height, const unsigned short *image)
{
	int pixelsDrawn = 0;
	for (int i = 0; i < height; i++) {
		DMA[3].src = image + pixelsDrawn;
		DMA[3].dst = videoBuffer + (240 * (y + i)) + x;
		DMA[3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_ON;
		pixelsDrawn += width;
	}


}

void drawChar(int row, int col, char ch, u16 color)
{
	for(int r=0; r<8; r++)
	{
		for(int c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6) + ch*48])
			{
				setPixel(col+c, row+r, color); //row is y, col is x
			}
		}
	}
}

void drawString(int row, int col, char *str, u16 color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col += 6;
	}

	
}

void drawTitleScreen()
{
	drawImage3(0, 0, GALAGAALPHA1_WIDTH, GALAGAALPHA1_HEIGHT, galagaalpha1_data);
	drawString(110, 0, "WITH AN ASTEROIDS TWIST!", YELLOW);
	drawString(130, 55, "Press Start to Play!", WHITE);
}

void clearScreenBlack()
{
	volatile u16 color = BLACK;
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
}

void drawGameOverScreen() {
	drawString(70, 90, "GAME OVER", GREEN);
	//drawString(120, 60, "PLAY AGAIN? [START]", BLUE);
}

void wait(int x) {
	volatile int i = 0;
	while (i < x) {
		i += 1;
	}
}

void drawRectangle(int x, int y, int width, int height, u16 color) {
	color = (volatile u16) color;
	for (int i = 0; i < height; i++) {
		//waitForVblank();
		DMA[3].src = &color;
		DMA[3].dst = videoBuffer + (240 * (i + y)) + x;
		DMA[3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
	}
}

void drawClosingScreen() {
	drawImage3(0, 0, CLOSINGSCREEN_WIDTH, CLOSINGSCREEN_HEIGHT, closingscreen_data);
	drawString(20, 60, "THANKS FOR PLAYING!", BLUE);
	drawString(140, 60, "PLAY AGAIN? [START]", BLUE);

}