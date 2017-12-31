#include "types.h"
#include "regs.h"
#include "sprites/ship.h"  //sprite data and palette made with pcx2sprite
#include "sprites/ball.h"
#include "backgrounds/intro.h"

//makes a table that contains OAM info about all 128 sprites
OAMEntry sprites[128];
 
//function to copy all our sprite data from the table to OAM memory
void CopyOAM()
{
      u16 loop;
      u16* temp;
      temp = (u16*)sprites;
      for(loop = 0; loop < 128*4; loop++) //2 bytes at the time (2byte * 4 * 128 = 1024 bytes)
      {
            OAM[loop] = temp[loop];
      }
}

void InitializeSprites()
{
      u16 loop;
      for(loop = 0; loop < 128; loop++)
      {
            sprites[loop].attribute[0] = 160;  //y to > 159
            sprites[loop].attribute[1] = 240;  //x to > 239
            sprites[loop].attribute[2] = 0;
      }
}

void SetMode(uint16 mode) 
{
      *(uint16 *)0x4000000 = mode;
}

void WaitForStart()
{
      while (1) { // loops infinitely till they press start
            if (! (*INPUT & KEY_START) ) {
                  return;
            }
      }
}
 
inline void vsync()
{
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}

void PlotPixel(int x,int y, unsigned short int c)     
{ 
      FrontBuffer[(y) * 120 + (x)] = (c); 
}

void WaitForVblank()    // waits for the drawer to get to end before flip
{
      while(*(volatile u16*)0x4000006 < 160) {  // do nothing
      }//now we are in the vblank period
}

void EraseScreen(void)
{
      int x,y;
      for(y = 0; y < 160; y++)
      {
            for(x = 0; x < 120; x++)

            {
                  PlotPixel(x,y,0xFFFF);//logoData contains the color values of your pict
                  
            }
      }
      WaitForVblank();
}

int main()
{
      u16 loop;      
      u16 x = 10;    
      u16 y = 50;
      u16 frame = 0, waveSwell = 1;

      SetMode(MODE_4 | BG2_ENABLE);

      for (loop = 0; loop < 256; ++loop)
      {
            BG_PaletteMem[loop] = intro_palette[loop];
      }

      for (loop = 0; loop < 160*120; ++loop)
      {
            FrontBuffer[loop] = intro[loop];
      }

      vsync();
      WaitForStart();
      EraseScreen();

      SetMode(MODE_0 | BG0_ENABLE | OBJ_ENABLE | OBJ_MAP_1D);

      InitializeSprites();   //set all sprites outside the screen (removes unwanted sprites)

      sprites[0].attribute[0] = COLOR_256 | SQUARE | y;  //set 256 colors, shape and y-coordinate
      sprites[0].attribute[1] = SIZE_32 | x;  //set shape and x-coordinate

      for (loop = 0; loop < 256; ++loop)
      {
            OBJ_PaletteMem[loop] = shipPalette[loop];
      }

      for (loop = 0; loop < 32*16; ++loop)
      {
            OAM_Data[loop] = shipData[loop];
      }
           
      while(1)  //main loop
      {
            if(!(*INPUT & KEY_RIGHT)) {
                  ++x;
                  sprites[0].attribute[1] &= ~HORIZONTAL_FLIP; 
                  if (x <= 0)
                  {
                        x = 0;
                  }
            }
            if(!(*INPUT & KEY_LEFT)) {
                  --x;
                  sprites[0].attribute[1] |= HORIZONTAL_FLIP;
                  if (x >= SCREEN_W - 32)
                  {
                        x = SCREEN_W - 32;
                  }
            }
            if(!(*INPUT & KEY_UP)) {
                  --y;
                  if (y > SCREEN_H -32)
                  {
                        y = SCREEN_H-32;
                  }  
            }
            if(!(*INPUT & KEY_DOWN)) {
                  ++y;
                  if (y <= 0)
                  {
                        y = 0;
                  }
            }
            if (!(*INPUT & KEY_A))
            {
            	
            }

            uint16 reg0 = sprites[0].attribute[0] & 0XFF00, reg1 = sprites[0].attribute[1] & 0XFE00;

            sprites[0].attribute[0] = (y + waveSwell) | reg0;
            sprites[0].attribute[1] = x | reg1;


            if((frame = (frame+1) % 40) == 0) waveSwell *= -1;

            vsync();  //wait for screen to finish drawing.
            CopyOAM();  //copy sprite info (OAM) into OAM memory
      }
}