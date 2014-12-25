#ifndef UTILITY_H
#define UTILITY_H
#include "PlxApi.h"
#include "Plx.h"
#include "PlxTypes.h"
#include "visatype.h"

#ifdef build_visa
#define visa_dll __declspec(dllexport)
#else
#define visa_dll __declspec(dllimport)
#endif

#define LOCAL_BUS1_BASE 	0x00000000
#define LOCAL_BUS2_BASE	0x00100000
#define CLK_BOARD_BASE		0x00200000
#define BUFFER1_BASE		0x00200100
#define BUFFER2_BASE		0x00200200

#define CLK_SCLK 	(CLK_BOARD_BASE + 0)
#define CLK_S0 		(CLK_BOARD_BASE + 1)
#define CLK_SEL		(CLK_BOARD_BASE + 2)
#define CLK_LE 		(CLK_BOARD_BASE + 3)
#define CLK_CS 		(CLK_BOARD_BASE + 4)
#define CLK_UPDATE 	(CLK_BOARD_BASE + 5)
#define CLK_DATA 	(CLK_BOARD_BASE + 6)
#define CLK_LD 		(CLK_BOARD_BASE + 7)

extern PLX_STATUS _VI_FUNC ReadLocalBus(
		PLX_DEVICE_OBJECT *pDevice,
		char Channel,
		U32 Address,
		U16 *Buffer
		);

extern PLX_STATUS _VI_FUNC WriteLocalBus(
		PLX_DEVICE_OBJECT *pDevice,
		char Channel,
		U32 Address,
		U16 Value
		);

extern visa_dll PLX_STATUS _VI_FUNC CLK_Write(
		PLX_DEVICE_OBJECT *pDevice,
		U32 Address,
		U16 Value
	);

extern visa_dll PLX_STATUS _VI_FUNC CLK_Read_LD(
		PLX_DEVICE_OBJECT *pDevice,
		U16 *Buffer

	);


#endif //UTILITY_H
