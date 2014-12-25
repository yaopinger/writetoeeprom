#include <stdio.h>
#include "utility.h"

PLX_STATUS _VI_FUNC ReadLocalBus(
    PLX_DEVICE_OBJECT *pDevice,
    char Channel,
    U32 Address,
    U16 *Buffer)
{
   /* if (Address < 0 || Address > 0x100000)
    {
        printf("Invalid address.\n");
        return ApiInvalidAddress;
    }*/
    Address <<= 2;
    switch (Channel)
    {
    case 0:
        return PlxPci_PciBarSpaceRead(
                   pDevice,
                   2,
                   Address,
                   Buffer,
                   2,
                   BitSize16,
                   FALSE);
        break;
    case 1:
        return PlxPci_PciBarSpaceRead(
                   pDevice,
                   2,
                   Address | 0x0400000,
                   Buffer,
                   2,
                   BitSize16,
                   FALSE);
        break;
    default:
        printf("Invalid Channel.\n");
        return ApiInvalidAddress;
    }
}


PLX_STATUS _VI_FUNC WriteLocalBus(
    PLX_DEVICE_OBJECT *pDevice,
    char Channel,
    U32 Address,
    U16 Value)
{
   /* if (Address < 0 || Address > 0x100000)
    {
        printf("Invalid address.\n");
        return ApiInvalidAddress;
    }*/
    Address = Address << 2;
    switch (Channel)
    {
    case 0:
        return PlxPci_PciBarSpaceWrite(
                   pDevice,
                   2,
                   Address,
                   &Value,
                   2,
                   BitSize16,
                   FALSE);
        break;
    case 1:

        Address = Address | 0x0400000;
        return PlxPci_PciBarSpaceWrite(
                   pDevice,
                   2,
                   Address,
                   &Value,
                   2,
                   BitSize16,
                   FALSE);
        break;
    default:
        printf("Invalid Channel.\n");
        return ApiInvalidAddress;

    }
}

PLX_STATUS _VI_FUNC visa_dll CLK_Write(
    PLX_DEVICE_OBJECT *pDevice,
    U32 Address,
    U16 Value
)
{
	return PlxPci_PciBarSpaceWrite(
               pDevice,
               2,
               Address  <<2,
               &Value,
               2,
               BitSize16,
               FALSE);
}

PLX_STATUS  _VI_FUNC visa_dll CLK_Read_LD(
    PLX_DEVICE_OBJECT *pDevice,
    U16 *Buffer
)
{
    PLX_STATUS status;
    status = PlxPci_PciBarSpaceRead(
                 pDevice,
                 2,
                 CLK_LD <<2,
                 Buffer,
                 2,
                 BitSize16,
                 FALSE);
    *Buffer &= 0x0001;
	return status;
}

