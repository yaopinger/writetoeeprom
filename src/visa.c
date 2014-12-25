#include <stdlib.h>
#include "visa.h"
#include "utility.h"
#include "visa.h"
#include "DeviceInit.h"

ViStatus _VI_FUNC viOpen          (ViSession sesn, ViRsrc name, ViAccessMode mode,
                                    ViUInt32 timeout, ViPSession vi)
{
    PLX_DEVICE_KEY DevKey;
	PLX_DEVICE_OBJECT *Device=malloc(sizeof(PLX_DEVICE_OBJECT));
	BOOLEAN IsInitOk;
	PLX_STATUS rc;

    IsInitOk = DeviceInit(&DevKey);
	if(IsInitOk)
	{
		rc = PlxPci_DeviceOpen(&DevKey, Device);
		if(rc != ApiSuccess)
			return VI_ERROR_ALLOC;
		else
        {
            *vi = (ViSession)Device;
            return VI_SUCCESS;
        }
	}
	else
	{
		return VI_ERROR_ALLOC;
	}
}

ViStatus _VI_FUNC  viIn16          (ViSession vi, ViUInt16 space,
                                    ViBusAddress offset, ViPUInt16 val16)
{
    if(ReadLocalBus((PLX_DEVICE_OBJECT*)vi,space,offset,val16)== ApiInvalidAddress)
        return VI_ERROR_IO;
    else
        return VI_SUCCESS;
}

ViStatus _VI_FUNC  viOut16         (ViSession vi, ViUInt16 space,
                                    ViBusAddress offset, ViUInt16  val16)
{
    if(WriteLocalBus((PLX_DEVICE_OBJECT*)vi,space,offset,val16)== ApiInvalidAddress)
        return VI_ERROR_IO;
    else
        return VI_SUCCESS;
}

