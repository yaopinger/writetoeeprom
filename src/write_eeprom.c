#include<stdio.h>
#include<math.h>
#include"utility.h"
#include"visatype.h"
#include "hardware_para.h"
#include "calibrate_data.h"
#include "analog_implement.h"
#include "addr_decode.h"
#include "ES1653.h"

#define PAGE_POINT_NUM          (4) //eeprom ÿPAGE�д�ŵ����ݸ���
#define PAGE_SIZE               (256)//eeprom ÿPAGE����bit��
#define CAL_DATA_FILE_NAME      "c:\\data.bin"
 //д��eeprom

void cal_init_eeprom(ES1653_Ch *phch)
{
    FILE *fp;
    ViInt32 i,point_number;
    ViUInt32 base_addr;
    ViUInt16 board_point_number;
    ViUInt8 ch_num = phch->channel-1;
    ViReal64 point[CAL_POINT_NUM*4];
    ViUInt32 page_account;
    ViUInt32 cal_point_num;
    ViUInt32 cal_point_num_div_page;
    int j;

    point_number = CAL_POINT_NUM*4;
    base_addr = EEPROM_BASE_ADDR + (1 - (phch->channel)%2)*ceil((ViReal64)CAL_POINT_NUM/PAGE_POINT_NUM)*PAGE_SIZE;    //һ����ͨ��Ϊ0 ������ͨ��Ϊ1
    if(!( fp = fopen(CAL_DATA_FILE_NAME,"rb")))
    {
        return ;
    }

    fread(point,sizeof(ViReal64),(ViUInt32)point_number,fp); //��bin�ļ���ȡ����
#if 1
    for(i = 0; i < point_number; i++)
    {
        printf("point[%d] = %f\n",i, point[i]);
    }
#endif // 0

    cal_point_num = CAL_POINT_NUM;
    cal_point_num_div_page = (ViReal64)cal_point_num/4+1;
    for(i = 0 ; i<cal_point_num_div_page; i++)   //������д�� eeprom
    {
        eeprom_sel_mode(phch, EEPROM_MODE_WR);
        eeprom_set_addr(phch, base_addr);
        for( j=0; j<PAGE_POINT_NUM; j++)
        {
            analog_write_eeprom(phch, base_addr, point[ch_num*CAL_POINT_NUM + i*4+j]);//��һ��д��һ��ͨ���е�eeprom�е�����
        }
        base_addr += PAGE_SIZE;
    }

    fclose(fp);
}

/** \brief ��eepromд��64λ��������
 *
 * \param phch ͨ�����
 * \param page_addr ҳ���ַ
 * \param data д�������
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

/** \brief eepROMѡ��ģʽ
 *
 * \param phch ͨ�����
 * \param mode д/��ģʽ
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
        viOut16(io, 0, dest_addr, 0x01);//д������ֵ
        delay_us(1000);
        return;
    }
    else
        goto check;
}

/** \brief eepROMҳ���ַ����
 *
 * \param phch ͨ�����
 * \param page_addr ҳ���ַ
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
/** \brief eepROMʹ���ź�
 *
 * \param phch ͨ�����
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

/** \brief eepROM��ȡ����
 *
 * \param phch ͨ�����
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
    dest_addr = geteeprom_addr(EEPROM_READ_DATA) + offset;     //�����ߵ�ַ
    viIn16(io, 0, dest_addr, &data);

    return data;
}

/** \brief eepROMд����
 *
 * д��16bit����
 * \param phch ͨ�����
 * \param data д�������
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

/** \brief eepROM����
 *
 * \param phch ͨ�����
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
