/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Jz.
 *       Filename:  main.c
 *
 *    Description:  
 *         Others:
 *
 *        Version:  1.0
 *        Created:  12/19/2016 11:54:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joy. Hou (hwt), houwentaoff@gmail.com
 *   Organization:  Jz
 *
 * =====================================================================================
 */


#include "libhardware/gps.h"
#include "libhardware/hardware.h"
#include <stdlib.h>

static const GpsInterface* sGpsInterface = NULL;

void android_location_GpsLocationProvider_class_init_native()
{
    int err;
    hw_module_t* module;

    err = hw_get_module(GPS_HARDWARE_MODULE_ID, (hw_module_t const**)&module);
    if (err == 0) {
        hw_device_t* device;
        err = module->methods->open(module, GPS_HARDWARE_MODULE_ID, &device);
        if (err == 0) {
            struct gps_device_t* gps_device = (struct gps_device_t *)device;
            sGpsInterface = gps_device->get_gps_interface(gps_device);
        }
    }
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{

    return EXIT_SUCCESS;
}
