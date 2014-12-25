#ifndef _ADF4351_H_
#define _ADF4351_H_

#include <math.h>

#include <windows.h>
#include <io.h>


//#define CLK_DATA       0x200007


//#define CLK_LE    0x200004
//#define CLK_SCLK       0x200003


void wr_adf4351_reg(uint32 reg_data);
void set_adf4351(uint32 multiple, uint32 divider);
uint32 get_divide_val(float freq);
void set_sample_clk(float freq);

void wr_adf4351_reg(uint32 reg_data)
  {
    int i;


    CLK_Write(&Device,CLK_LE,1)
    CLK_Write(&Device,CLK_LE,0)


    Sleep(10);

    for(i = 0; i < 32; i ++)
      {

    CLK_Write(&Device,CLK_SCLK,0)

	     Sleep(10);

	    DATA = (0x80000000 & reg_data) >> 31;
	    reg_data = reg_data << 1;

		 Sleep(10);

    CLK_Write(&Device,CLK_SCLK,1)

	  }

      Sleep(10);
    CLK_Write(&Device,CLK_SCLK,0)

      Sleep(10);
    CLK_Write(&Device,CLK_LE,1)


  }



void set_adf4351(uint32 multiple, uint32 divider)
  {
    uint32 reg0,reg1,reg2;
  	uint32 reg3,reg4,reg5;

	reg0 = 0x00000000;
	reg1 = 0x08008011;
	reg2 = 0x0C005FC2;
	reg3 = 0x006004B3;
	reg4 = 0x008501FC;
	reg5 = 0x00580005;

	reg0 = reg0 | (multiple << 15);
	reg4 = reg4 | (divider << 20);

	wr_adf4351_reg(reg5);
	wr_adf4351_reg(reg4);
	wr_adf4351_reg(reg3);
	wr_adf4351_reg(reg2);
	wr_adf4351_reg(reg1);
	wr_adf4351_reg(reg0);

  }

uint32 get_divide_val(float freq)
  {
      uint32 divide_val;
      if((freq >= 2200e6) && (freq < 4400e6))
	  {
	    divide_val = 0;
	  }

    else if((freq >= 1100e6) && (freq < 2200e6))
	  {
	    divide_val = 1;
	  }

    else if((freq >= 550e6) && (freq < 1100e6))
	  {
	    divide_val = 2;
	  }

    else if((freq >= 275e6) && (freq < 550e6))
	  {
	    divide_val = 3;
	  }

    else if((freq >= 137.5e6) && (freq < 275e6))
	  {
	    divide_val = 4;
	  }

    else if((freq >= 68.75e6) && (freq < 137.5e6))
	  {
	    divide_val = 5;
	  }

    else if((freq >= 34.375e6) && (freq < 68.75e6))
	  {
	    divide_val = 6;
      }
	else
	  {
	    divide_val = 0;
	  }

	  return divide_val;
  }


void set_sample_clk(float freq)
  {
    uint32 divide_val,multi_val;

    divide_val = get_divide_val(freq);

//    multi_val = (uint32)(freq / 20e6 * pow(2,divide_val));
	multi_val = 100;
    set_adf4351(multi_val,divide_val);

  }


#endif /*_AD4351_H_*/

