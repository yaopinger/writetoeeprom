#ifndef DEVICEINIT_H
#define DEVICEINIT_H
#include<stdio.h>
#include "PlxApi.h"
#include "Plx.h"
#include "PlxTypes.h"

#define MAX_DEVICES_TO_LIST 100
extern BOOLEAN DeviceInit(PLX_DEVICE_KEY *pKey);

#endif
