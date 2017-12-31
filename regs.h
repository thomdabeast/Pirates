#ifndef regs_h
#define regs_h

#include "base.h"

#define REG_DMA0SAD	*(vu32*)(REG_BASE + 0x0b0)
#define REG_DMA0DAD	*(vu32*)(REG_BASE + 0x0b4)
#define REG_DMA0CNT	*(vu32*)(REG_BASE + 0x0b8)

#define REG_DMA1SAD	*(vu32*)(REG_BASE + 0x0bc)
#define REG_DMA1DAD	*(vu32*)(REG_BASE + 0x0c0)
#define REG_DMA1CNT	*(vu32*)(REG_BASE + 0x0c4)

#define REG_DMA2SAD	*(vu32*)(REG_BASE + 0x0c8)
#define REG_DMA2DAD	*(vu32*)(REG_BASE + 0x0cc)
#define REG_DMA2CNT	*(vu32*)(REG_BASE + 0x0d0)

#define REG_DMA3SAD	*(vu32*)(REG_BASE + 0x0d4)
#define REG_DMA3DAD	*(vu32*)(REG_BASE + 0x0d8)
#define REG_DMA3CNT	*(vu32*)(REG_BASE + 0x0dc)


#define DMA_DST_INC		(0<<21)
#define DMA_DST_DEC		(1<<21)
#define DMA_DST_FIXED	(2<<21)
#define DMA_DST_RELOAD	(3<<21)

#define DMA_SRC_INC		(0<<23)
#define DMA_SRC_DEC		(1<<23)
#define DMA_SRC_FIXED	(2<<23)

#define DMA_REPEAT		(1<<25)

#define DMA16			(0<<26)
#define DMA32			(1<<26)

#define	GAMEPAK_DRQ		(1<<27)

#define DMA_IMMEDIATE	(0<<28)
#define DMA_VBLANK		(1<<28)
#define DMA_HBLANK		(2<<28)
#define DMA_SPECIAL		(3<<28)

#define DMA_IRQ			(1<<30)
#define DMA_ENABLE		(1<<31)

#define DMA_Copy(channel, source, dest, mode) {\
	REG_DMA##channel##SAD = (uint32)(source);\
	REG_DMA##channel##DAD = (uint32)(dest);\
	REG_DMA##channel##CNT = DMA_ENABLE | (mode); \
}

static inline void dmaCopy(const void * source, void * dest, uint32 size) {
	DMA_Copy(3, source, dest, DMA16 | size>>1);
}

#define	DMA0COPY( source, dest, mode) DMA_Copy(0,(source),(dest),(mode))
#define	DMA1COPY( source, dest, mode) DMA_Copy(1,(source),(dest),(mode))
#define	DMA2COPY( source, dest, mode) DMA_Copy(2,(source),(dest),(mode))
#define	DMA3COPY( source, dest, mode) DMA_Copy(3,(source),(dest),(mode))

uint16* OAM = 			(uint16*)	0x07000000;
vu16* OBJ_PaletteMem = 	(vu16*)		0x5000200;
vu16* BG_PaletteMem = 	(vu16*)		0x05000000;
vu16* OAM_Data = 		(vu16 *)	0x6010000;
vu16* FrontBuffer = 	(vu16 *)	0x06000000;
vu16* BackBuffer = 		(vu16 *)	0x0600A000;
vu32* INPUT = 			(vu32*)		0x04000130;
 
#endif