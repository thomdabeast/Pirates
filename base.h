#ifndef base_h
#define base_h
//---------------------------------------------------------------------------------

#include "types.h"

/*! \def VRAM

    \brief Base address of gba video ram.

*/
#define	VRAM		0x06000000
/*! \def IWRAM

    \brief Base address of gba internal work ram.

*/
#define	IWRAM		0x03000000
/*! \def EWRAM

    \brief Base address of gba external work ram.

*/
#define	EWRAM		0x02000000
#define	EWRAM_END	0x02040000
/*! \def SRAM

    \brief Base address of gba cart save ram.

*/
#define	SRAM		0x0E000000
/*! \def REG_BASE

    \brief Base address of gba hardware registers.

*/
#define	REG_BASE	0x04000000

#ifndef	NULL
#define	NULL	0
#endif

//---------------------------------------------------------------------------------
/*! \def SystemCall(Number)

    \brief helper macro to insert a bios call.
		\param Number swi number to call
		
		Inserts a swi of the correct format for arm or thumb code.

*/
#if	defined	( __thumb__ )
#define	SystemCall(Number)	 __asm ("SWI	  "#Number"\n" :::  "r0", "r1", "r2", "r3")
#else
#define	SystemCall(Number)	 __asm ("SWI	  "#Number"	<< 16\n" :::"r0", "r1", "r2", "r3")
#endif

/*! \def BIT(number)

    \brief Macro for bit settings.

	\param number bit number to set
*/
#define BIT(number) (1<<(number))

#define IWRAM_CODE	__attribute__((section(".iwram"), long_call))
#define EWRAM_CODE	__attribute__((section(".ewram"), long_call))

#define IWRAM_DATA	__attribute__((section(".iwram")))
#define EWRAM_DATA	__attribute__((section(".ewram")))
#define EWRAM_BSS	__attribute__((section(".sbss")))
#define ALIGN(m)	__attribute__((aligned (m)))

//---------------------------------------------------------------------------------
// modes for DMA and CPU(Fast)Set
//---------------------------------------------------------------------------------
enum DMA_MODES {
	FILL	= (1<<24),
	COPY16	= (0<<26),
	COPY32	= (1<<26)
};

//---------------------------------------------------------------------------------
#endif 