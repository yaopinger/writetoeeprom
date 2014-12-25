#ifndef _AD9954_H_
#define _AD9954_H_

#include <windows.h>
#include <io.h>


//#define CLK_UPDATE   0x200001
//#define CLK_CS       0x200002
//#define CLK_SCLK          0x200003

//#define CLK_DATA          0x200007



void wr_instruction(uchar i)  //写指令字节
  {
    uchar j;

    for(j=1;j<=8;j++)
      {

    CLK_Write(&Device,CLK_SCLK,0)

//      DATA=0x01&&(0x80&i);
		DATA=(i & 0x80)>>7;
       Sleep(10);
        i=i<<1;

    CLK_Write(&Device,CLK_SCLK,1)

       Sleep(10);
      }
  }

void wr_4byte(uint32 i)   //写4byte数据
  {
     uchar j;
     for(j=1; j<=32; j++)
       {

    CLK_Write(&Device,CLK_SCLK,0)

//       DATA=0x01&&(0x80000000&i);
		 DATA=(i & 0x80000000)>>31;
        Sleep(10);
         i=i<<1;

    CLK_Write(&Device,CLK_SCLK,1)
        Sleep(10);
       }
  }

void wr_3byte(uint32 i)    //写3byte数据
  {
     uchar j;

	 for(j=1;j<=24;j++)
	  {

    CLK_Write(&Device,CLK_SCLK,0)

//       DATA=0x01&&(0x800000&i);
		 DATA=(i & 0x800000)>>23;
	    Sleep(10);
	     i=i<<1;

    CLK_Write(&Device,CLK_SCLK,1)
	    Sleep(10);
	  }
  }

void  send_to_9954(float freq)
  {
	uint32 freq_tunning_word;

	freq_tunning_word = (uint32)(freq * 26.8435456);  //42.94967296\53.6870912 \21.47483648


  CLK_Write(&Device,CLK_CS,1)
  CLK_Write(&Device,CLK_CS,0)

	wr_instruction(0x00);
	wr_4byte(0x00003000);

  CLK_Write(&Device,CLK_CS,1)


//	UPDATA_9954=0;
//	delay_us(10);
// 	UPDATA_9954=1;
// 	delay_us(10);


  CLK_Write(&Device,CLK_CS,1)
  CLK_Write(&Device,CLK_CS,0)

	wr_instruction(0x01);
	wr_3byte(0x00000287);	 // system clock is 200MHz

  CLK_Write(&Device,CLK_CS,1)

//	UPDATA_9954=0;
//	delay_us(10);
// 	UPDATA_9954=1;
// 	delay_us(10);


  CLK_Write(&Device,CLK_CS,1)
  CLK_Write(&Device,CLK_CS,0)

	wr_instruction(0x04);
 	wr_4byte(freq_tunning_word);

  CLK_Write(&Device,CLK_CS,1)
  CLK_Write(&Device,CLK_UPDATE,0)


     Sleep(10);
  CLK_Write(&Device,CLK_UPDATE,1)

     Sleep(10);
  }



#endif /*_AD9954_H_*/
