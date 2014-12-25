/** \file addr_decode.h
 * \brief  UESTC ES FGEN SERIES
 *
 * \sa FPGA基地址和地址获取宏，关于多通道的地址，参见 hardware_para.h 中的通道偏移宏
 * \author UESTC
 * \date 2001 - 2013
 * \copyright (c) 2001-2013, UESTC.  All Rights Reserved.
 *
 */
#ifndef _ADDR_DECODE_H
#define _ADDR_DECODE_H

#define EN_RAMH         0x018000             /**< 高速ram基地址 */
#define EN_RAML         0x020000             /**< 低速ram基地址 */
#define EN_DDSH         0x008000             /**< 高速DDS基地址 */
#define EN_MODU	        0x010000             /**< 调制模块基地址 */
#define EN_IO           0x080000             /**<  IO模块基地址*/
#define EN_DAC8560      0x0A4000             /**< DAC8560模块 */
#define EN_EXTEND       0x028000             /**< RAM页面地址 */
#define EN_CLK          0x0A0000             /**< 时钟模块基地址 */
#define EN_SEQ          0xC0000              /**< SEQ模块基地址 */
#define EN_ANALOG       0x200100             /**< 信号调理模块地址 */
#define EN_EEPROM       0x200110             /**< EEPROM模块地址 */

#define	  getramh_addr(off_addr)    (volatile ViUInt32)(EN_RAMH+(off_addr))   /**< 获取高速ram模块中偏移为off_addr的地址 */
#define	  getraml_addr(off_addr)    (volatile ViUInt32)(EN_RAML+(off_addr))   /**< 获取低速ram模块中偏移为off_addr的地址 */
#define   geteeprom_addr(off_addr)  (volatile ViUInt32)(EN_EEPROM +(off_addr)) /**< 获取eepROM模块中偏移为off_addr的地址 */
#define   getddsh_addr(off_addr)    (volatile ViUInt32)(EN_DDSH+(off_addr) )  /**< 获取高速DDS模块中偏移为off_addr的地址 */
#define   getio_addr(off_addr)      (volatile ViUInt32)(EN_IO+(off_addr) )      /**< 获取IO模块中偏移为off_addr的地址 */
#define   getmodu_addr(off_addr)    (volatile ViUInt32)(EN_MODU+(off_addr) )  /**< 获取调制模块中偏移为off_addr的地址 */
#define   getclk_addr(off_addr)     (volatile ViUInt32)(EN_CLK+(off_addr) )    /**< 获取时钟模块中偏移为off_addr的地址 */
#define   getanalog_addr(off_addr)  (volatile ViUInt32)(EN_ANALOG+(off_addr) )  /**< 获取模拟通道模块中偏移为off_addr的地址 */
#define   getextend_addr(off_addr)  (volatile ViUInt32)(EN_EXTEND+(off_addr) ) /**< 获取外部扩展模块中偏移为off_addr的地址 */
#define   getdac8560_addr(off_addr) (volatile ViUInt32)(EN_DAC8560 + (off_addr))   /**< 获取DAC8560模块中偏移为off_addr的地址 */
//#define   gettpci6595_addr(off_addr)  (volatile ViUInt32)(EN_TPCI6595 + (off_addr)) /**< 获取TPCI6595模块中偏移为off_addr的地址 */
#define   getseq_addr(off_addr)     (volatile ViUInt32)(EN_SEQ + (off_addr))    /**< 获取SEQ模块中偏移为off_addr的地址 */
#endif
