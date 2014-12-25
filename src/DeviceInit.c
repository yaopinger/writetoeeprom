#include<string.h>
#include<stdio.h>
#include "DeviceInit.h"
#include "PexApi.h"

BOOLEAN DeviceInit(PLX_DEVICE_KEY *pKey)
{
	PLX_DEVICE_KEY DevKey;
	PLX_STATUS rc;
	S16 i = 0;

	do
	{
		memset(&DevKey, PCI_FIELD_IGNORE, sizeof(PLX_DEVICE_KEY));
		rc = PlxPci_DeviceFind(&DevKey, (U8)i);
		if(rc == ApiSuccess)
		{
			if(DevKey.DeviceId == 0X9054)
			{
				*pKey = DevKey;
				printf("Bingo, Find 9054 device.\n");
				return TRUE;
			}
		}
		i++;
	}
	while ((rc == ApiSuccess) && (i < MAX_DEVICES_TO_LIST));
	return FALSE;
}
