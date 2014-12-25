#include<stdio.h>
#include"DeviceInit.h"
#include"utility.h"
#include"ES1653.h"

#define CAL_DATA_FILE_NAME      "c:\\data.bin"
ES1653_Ch *phch[4];

int main()
{
	PLX_DEVICE_OBJECT *Device /*=malloc(sizeof(PLX_DEVICE_OBJECT))*/;
	PLX_DEVICE_KEY DevKey;
	BOOLEAN IsInitOk;
	PLX_STATUS rc;
    ViSession io,vi;
    int i;

#if 0
    i = ceil(4.3);
    printf("i = %d \n",i);
    i = ceil(5.3);
    printf("i = %d \n",i);
    i = ceil(4.6);
    printf("i = %d \n",i);
    i = ceil(3.1);
    printf("i = %d \n",i);

#endif // 1



    for(i=0; i < 4; i++)
    {
        phch[i] = (ES1653_Ch *)calloc(1,sizeof(ES1653_Ch));
    }

    viOpen(VI_NULL, VI_NULL, VI_NO_LOCK,0,&io);

    if(io == 0)
        return;

    for(i=0;i<4;i++)
    {
        phch[i]->io = io;
        phch[i]->channel = i+1;
    }

    eeprom_reset(phch[0]);//eeprom reset

    for(i=0;i<4;i++)
    {
        cal_init_eeprom(phch[i]);
    }
    printf("请输入任意值，退出~\n");
    getchar();

	return 0;
}
