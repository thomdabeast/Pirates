#ifndef types_h
#define types_h

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;

// comply with pcx2gba conversion
typedef uint8 u8;
typedef uint16 u16;
typedef uint32 u32;

typedef	volatile uint8		vu8;	/**< volatile Unsigned 8 bit value	*/
typedef	volatile uint16	vu16;	/**< volatile Unigned 16 bit value	*/
typedef	volatile uint32	vu32;	/**< volatile Unsigned 32 bit value	*/
typedef	volatile char	vs8;	/**< volatile Signed 8 bit value	*/
typedef	volatile short	vs16;	/**< volatile Signed 8 bit value	*/
typedef	volatile int	vs32;	/**< volatile Signed 8 bit value	*/
typedef char boolean;

//Atribute0 stuff
#define ROTATION_FLAG           0x100
#define SIZE_DOUBLE             0x200
#define MODE_NORMAL             0x0
#define MODE_TRANSPERANT        0x400
#define MODE_WINDOWED           0x800
#define MOSAIC                  0x1000
#define COLOR_16                0x0000
#define COLOR_256               0x2000
#define SQUARE                  0x0
#define TALL                    0x4000
#define WIDE                    0x8000

//Atribute1 stuff
#define ROTDATA(n)              ((n) << 9)
#define HORIZONTAL_FLIP         0x1000
#define VERTICAL_FLIP           0x2000
#define SIZE_8                  0x0
#define SIZE_16                 0x4000
#define SIZE_32                 0x8000
#define SIZE_64                 0xC000

/***** REG_DISPCNT defines	*/

#define MODE_0 0x0
#define MODE_1 0x1
#define MODE_2 0x2
#define MODE_3 0x3
#define MODE_4 0x4
#define MODE_5 0x5

#define BACKBUFFER 0x10
#define H_BLANK_OAM 0x20 

#define OBJ_MAP_2D 0x0
#define OBJ_MAP_1D 0x40

#define FORCE_BLANK 0x80

#define BG0_ENABLE 0x100
#define BG1_ENABLE 0x200 
#define BG2_ENABLE 0x400
#define BG3_ENABLE 0x800
#define OBJ_ENABLE 0x1000 

#define WIN1_ENABLE 0x2000 
#define WIN2_ENABLE 0x4000
#define WINOBJ_ENABLE 0x8000

#define REG_VCOUNT              (*(volatile uint16*) 0x04000006)
#define REG_DISPLAYCONTROL      (*(volatile uint16*) 0x04000000)

#define CHR_BASE		      0x06010000

#define SCREEN_W      240
#define SCREEN_H      160

#define REG_DISPCNT    *(u32*)0x4000000

#define true (boolean)1
#define false (boolean)0


typedef enum KEYPAD_BITS {
      KEY_A       =     (1<<0),     /*!< keypad A button */
      KEY_B       =     (1<<1),     /*!< keypad B button */
      KEY_SELECT  =     (1<<2),     /*!< keypad SELECT button */
      KEY_START   =     (1<<3),     /*!< keypad START button */
      KEY_RIGHT   =     (1<<4),     /*!< dpad RIGHT */
      KEY_LEFT    =     (1<<5),     /*!< dpad LEFT */
      KEY_UP            =     (1<<6),     /*!< dpad UP */
      KEY_DOWN    =     (1<<7),     /*!< dpad DOWN */
      KEY_R       =     (1<<8),     /*!< Right shoulder button */
      KEY_L       =     (1<<9),     /*!< Left shoulder button */

      KEYIRQ_ENABLE     =     (1<<14),    /*!< Enable keypad interrupt */
      KEYIRQ_OR         =     (0<<15),    /*!< interrupt logical OR mode */
      KEYIRQ_AND        =     (1<<15),    /*!< interrupt logical AND mode */
      DPAD        =     (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT) /*!< mask all dpad buttons */
} KEYPAD_BITS;

typedef struct OAMEntry {
      uint16 attribute[4];
} OAMEntry;

#endif