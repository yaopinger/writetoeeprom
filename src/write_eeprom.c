/*******
ceil()函数的用法有问题~~~ 这是为什么？？？

***/


#include<stdio.h>
#include<math.h>
#include"utility.h"
#include"visatype.h"
#include "hardware_para.h"
#include "calibrate_data.h"
#include "analog_implement.h"
#include "addr_decode.h"
#include "ES1653.h"

#define PAGE_POINT_NUM          (4) //eeprom 每PAGE中存放的数据个数
#define PAGE_SIZE               (256)//eeprom 每PAGE包含bit数
#define CAL_DATA_FILE_NAME      "c:\\data.bin"
 //写入eeprom

void cal_init_eeprom(ES1653_Ch *phch)
{
    FILE *fp;
    ViInt32 i,point_number;
    ViUInt32 base_addr;
    ViUInt16 board_point_number;
    ViUInt8 ch_num = phch->channel-1;
    ViReal64 point[(CAL_POINT_NUM+2)*4] = {0};
    ViUInt32 page_account;
    ViUInt32 cal_point_num;
    ViUInt32 cal_point_num_div_page;
    int j;

    point_number = CAL_POINT_NUM*4;
    base_addr = EEPROM_BASE_ADDR + (1 - (phch->channel)%2)*((ViInt64)(cal_point_num/4) + 1)*PAGE_SIZE;    //一、三通道为0 二、四通道为1
    if(!( fp = fopen(CAL_DATA_FILE_NAME,"rb")))
    {
        return ;
    }

    fread(point,sizeof(ViReal64),(ViUInt32)point_number,fp); //从bin文件读取数据
#if 0
    for(i = 0; i < point_number; i++)
    {
        printf("point[%d] = %f\n",i, point[i]);
    }
#endif // 0

    cal_point_num = CAL_POINT_NUM;
    cal_point_num_div_page = (ViInt64)(cal_point_num/4) + 1;
    for(i = 0 ; i<cal_point_num_div_page; i++)   //将数据写入 eeprom
    {
        eeprom_sel_mode(phch, EEPROM_MODE_WR);
        eeprom_set_addr(phch, base_addr);
        for( j=0; j<PAGE_POINT_NUM; j++)
        {
            analog_write_eeprom(phch, base_addr, point[ch_num*CAL_POINT_NUM + i*4+j]);//第一次写入一个通道中的eeprom中的数据
#if 1
            printf("point[%d] = %f\n",i, point[ch_num*CAL_POINT_NUM + i*4+j]);
#endif // 0
        }
        base_addr += PAGE_SIZE;
    }

    fclose(fp);
}

/** \brief 向eeprom写入64位浮点数据
 *
 * \param phch 通道句柄
 * \param page_addr 页面地址
 * \param data 写入的数据
 *
 */

void analog_write_eeprom(ES1653_Ch *phch, ViUInt32 page_addr, ViReal64 data)
{

    ViUInt32 i;
    ViUInt64 val;
    ViUInt64* tmp;
    ViPReal64 tmp1;

    tmp1 = &data;
    tmp =(ViUInt64*)tmp1;
    val = *tmp;

    for(i = 0; i < CAL_DATA_BIT; ++i)
    {
        eeprom_write_data(phch, (ViUInt16)((ViUInt64)val>>(i*16)));
        eeprom_enable(phch);
        delay_us(3);
    }


}

/** \brief eepROM选择模式
 *
 * \param phch 通道句柄
 * \param mode 写/读模式
 *
 */
void eeprom_sel_mode(ES1653_Ch *phch, ViInt16 mode)
{
    ViSession io;
    ViInt32 dest_addr;
    ViUInt16 status;

    ViInt8 channel = phch->channel;
    ViUInt16 fpga = get_fpga(phch);
    ViUInt32 offset = analog_select_eeprom_channel(channel);

    io = (ViSession)phch->io;
check:
    dest_addr = geteeprom_addr(EEPROM_SEL_MODE) + offset;
    viOut16(io, 0, dest_addr, mode);
    delay_us(1000);
    eeprom_enable(phch);

    dest_addr = geteeprom_addr(EEPROM_STATUS) + offset;
    viIn16(io,0,dest_addr, &status);
    delay_us(1000);
    viIn16(io,0,dest_addr, &status);//need to read twice
    if(((status&0xff)==0x02&&mode==EEPROM_MODE_WR)||((status&0xff)==0x00&&mode == EEPROM_MODE_RD))
    {
        dest_addr = geteeprom_addr(EEPROM_COMFIR_MODE) + offset;
        viOut16(io, 0, dest_addr, 0x01);//写入任意值
        delay_us(1000);
        return;
    }
    else
        goto check;
}

/** \brief eepROM页面地址设置
 *
 * \param phch 通道句柄
 * \param page_addr 页面地址
 *
 */

void eeprom_set_addr(ES1653_Ch *phch, ViInt32 page_addr)
{
    ViSession io;
    ViInt32 dest_addr;

    ViInt8 channel = phch->channel;
    ViUInt16 fpga = get_fpga(phch);
    ViUInt32 offset = analog_select_eeprom_channel(channel);

    io = (ViSession)phch->io;

    dest_addr = geteeprom_addr(EEPROM_ADDR_15_0) + offset;
    viOut16(io, 0, dest_addr, page_addr);
    delay_us(10);
    dest_addr = geteeprom_addr(EEPROM_ADDR_31_16) + offset;
    viOut16(io, 0, dest_addr, (page_addr>>16));
    delay_us(10);
   //
}
/** \brief eepROM使能信号
 *
 * \param phch 通道句柄
 *
 */
void eeprom_enable(ES1653_Ch *phch)
{
    ViSession io;
    ViInt32 dest_addr;

    ViInt8 channel = phch->channel;
    ViUInt16 fpga = get_fpga(phch);
    ViUInt32 offset = analog_select_eeprom_channel(channel);

    io = (ViSession)phch->io;

    dest_addr = geteeprom_addr(EEPROM_ENABLE) + offset;
    viOut16(io, 0, dest_addr, 0x00);
    delay_us(1000);
}

/** \brief eepROM读取数据
 *
 * \param phch 通道句柄
 *
 */

ViUInt16 eeprom_read_data(ES1653_Ch *phch)
{
    ViSession io;
    ViInt32 dest_addr;
    ViUInt16 data ;

    ViInt8 channel = phch->channel;
    ViUInt16 fpga = get_fpga(phch);
    ViUInt32 offset = analog_select_eeprom_channel(channel);

    io = (ViSession)phch->io;
    dest_addr = geteeprom_addr(EEPROM_READ_DATA) + offset;     //数据线地址
    viIn16(io, 0, dest_addr, &data);

    return data;
}

/** \brief eepROM写数据
 *
 * 写入16bit数据
 * \param phch 通道句柄
 * \param data 写入的数据
 *
 */
void eeprom_write_data(ES1653_Ch *phch, ViUInt16 data)
{
    ViSession io;
    ViInt32 dest_addr;

    ViInt8 channel = phch->channel;
    ViUInt16 fpga = get_fpga(phch);
    ViUInt32 offset = analog_select_eeprom_channel(channel);

    io = (ViSession)phch->io;

    dest_addr = geteeprom_addr(EEPROM_WRITE_DATA) + offset;
    viOut16(io, 0, dest_addr, data);
}

/** \brief eepROM重置
 *
 * \param phch 通道句柄
 *
 */
void eeprom_reset(ES1653_Ch *phch)
{
    ViSession io;
    ViInt32 dest_addr;

    ViInt8 channel = phch->channel;
    ViUInt16 fpga = get_fpga(phch);
    ViUInt32 offset = analog_select_eeprom_channel(channel);

    io = (ViSession)phch->io;

    dest_addr = geteeprom_addr(EEPROM_RESET) + offset;
    viOut16(io, 0, dest_addr, 1);
    delay_us(1000);
    viOut16(io,0,dest_addr,0);
}
