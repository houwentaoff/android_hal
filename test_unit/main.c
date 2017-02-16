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
#include <pthread.h>
#include <math.h>
#include <time.h>
#include "gpio.h"

static const GpsInterface* sGpsInterface = NULL;

static const GpsXtraInterface* sGpsXtraInterface = NULL;
static const AGpsInterface* sAGpsInterface = NULL;
static const GpsNiInterface* sGpsNiInterface = NULL;
static const GpsDebugInterface* sGpsDebugInterface = NULL;
static const AGpsRilInterface* sAGpsRilInterface = NULL;
static const GpsGeofencingInterface* sGpsGeofencingInterface = NULL;

static void location_callback(GpsLocation* location);
static void status_callback(GpsStatus* status);
static void sv_status_callback(GpsSvStatus* sv_status);
static void nmea_callback(GpsUtcTime timestamp, const char* nmea, int length);
static void set_capabilities_callback(uint32_t capabilities);
static void acquire_wakelock_callback();
static void release_wakelock_callback();
static pthread_t create_thread_callback(const char* name, void (*start)(void *), void* arg);
static void request_utc_time_callback();

static void xtra_download_request_callback();

GpsCallbacks sGpsCallbacks = {
    sizeof(GpsCallbacks),
    location_callback,
    status_callback,
    sv_status_callback,
    nmea_callback,
    set_capabilities_callback,
    acquire_wakelock_callback,
    release_wakelock_callback,
    create_thread_callback,
    request_utc_time_callback,
};

GpsXtraCallbacks sGpsXtraCallbacks = {
    xtra_download_request_callback,
    create_thread_callback,
};
static void do_agps_status_callback(AGpsStatus* agps_status)
{

}
AGpsCallbacks sAGpsCallbacks = {
    do_agps_status_callback,
    create_thread_callback,
};
static void do_gps_ni_notify_callback(GpsNiNotification *notification)
{

}
GpsNiCallbacks sGpsNiCallbacks = {
    do_gps_ni_notify_callback,
    create_thread_callback,
};
static void agps_request_set_id(uint32_t flags)
{

}
static void agps_request_ref_location(uint32_t flags)
{

}
AGpsRilCallbacks sAGpsRilCallbacks = {
    agps_request_set_id,
    agps_request_ref_location,
    create_thread_callback,
};
static void do_gps_geofence_transition_callback(int32_t geofence_id,  GpsLocation* location,
                int32_t transition, GpsUtcTime timestamp)
{

}
static void do_gps_geofence_status_callback(int32_t status, GpsLocation* location)
{

}
static void do_gps_geofence_add_callback(int32_t geofence_id, int32_t status)
{

}
static void do_gps_geofence_remove_callback(int32_t geofence_id, int32_t status)
{

}
static void do_gps_geofence_resume_callback(int32_t geofence_id, int32_t status)
{

}
static void do_gps_geofence_pause_callback(int32_t geofence_id, int32_t status)
{

}
GpsGeofenceCallbacks sGpsGeofenceCallbacks = {
    do_gps_geofence_transition_callback,
    do_gps_geofence_status_callback,
    do_gps_geofence_add_callback,
    do_gps_geofence_remove_callback,
    do_gps_geofence_pause_callback,
    do_gps_geofence_resume_callback,
    create_thread_callback,
};
static void location_callback(GpsLocation* location)
{
    if (!location)
        return;
    time_t time = (time_t)(location->timestamp/1000);

    printf("==>%s location: %lf %lf %lf %f %f %f\n", __FUNCTION__, location->latitude, location->longitude,
            location->altitude, location->speed, location->bearing, location->accuracy);
    printf("utctime %s\n", ctime(&time));
}
static void status_callback(GpsStatus* status)
{

}

#define LED1   GPIO_TO_PIN(1,4)
#define LED2   GPIO_TO_PIN(9,2)

static void sv_status_callback(GpsSvStatus* sv_status)
{
    printf ("==>%s joy: satellite num [%d]\n", __FUNCTION__, sv_status->num_svs);
    if (sv_status->num_svs > 1)
    {
        if (sv_status->num_svs <= 3)
        {
            int value = gpio_get_value(LED1);
            sleep(1);
            gpio_set_value(LED1, value == GPIO_HIGH ? GPIO_LOW : GPIO_HIGH);
        }
        else
        {
            int value = gpio_get_value(LED2);
            sleep(1);            
            gpio_set_value(LED2, value == GPIO_HIGH ? GPIO_LOW : GPIO_HIGH);
        }
    }
}
static void nmea_callback(GpsUtcTime timestamp, const char* nmea, int length)
{
    printf("==>%s joy : nmea callback: %s \n", __FUNCTION__, nmea);
}
static void set_capabilities_callback(uint32_t capabilities)
{
}
static void acquire_wakelock_callback()
{

}
static void release_wakelock_callback()
{

}
static pthread_t create_thread_callback(const char* name, void (*start)(void *), void* arg)
{
    pthread_t tid;
    printf("==>%s name[%s]\n", __FUNCTION__, name);
    pthread_create(&tid, NULL, (void *)start, arg);
    return (pthread_t)tid;
}
static void request_utc_time_callback()
{
}
static void xtra_download_request_callback()
{

}
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
    if (sGpsInterface) {
        sGpsXtraInterface =
            (const GpsXtraInterface*)sGpsInterface->get_extension(GPS_XTRA_INTERFACE);
        sAGpsInterface =
            (const AGpsInterface*)sGpsInterface->get_extension(AGPS_INTERFACE);
        sGpsNiInterface =
            (const GpsNiInterface*)sGpsInterface->get_extension(GPS_NI_INTERFACE);
        sGpsDebugInterface =
            (const GpsDebugInterface*)sGpsInterface->get_extension(GPS_DEBUG_INTERFACE);
        sAGpsRilInterface =
            (const AGpsRilInterface*)sGpsInterface->get_extension(AGPS_RIL_INTERFACE);
        sGpsGeofencingInterface =
            (const GpsGeofencingInterface*)sGpsInterface->get_extension(GPS_GEOFENCING_INTERFACE);
    }
}
static bool android_location_GpsLocationProvider_is_supported() {
    return (sGpsInterface != NULL);
}
static bool android_location_GpsLocationProvider_init()
{
    // fail if the main interface fails to initialize
    if (!sGpsInterface || sGpsInterface->init(&sGpsCallbacks) != 0)
        return false;

    // if XTRA initialization fails we will disable it by sGpsXtraInterface to NULL,
    // but continue to allow the rest of the GPS interface to work.
    if (sGpsXtraInterface && sGpsXtraInterface->init(&sGpsXtraCallbacks) != 0)
        sGpsXtraInterface = NULL;
    if (sAGpsInterface)
        sAGpsInterface->init(&sAGpsCallbacks);
    if (sGpsNiInterface)
        sGpsNiInterface->init(&sGpsNiCallbacks);
    if (sAGpsRilInterface)
        sAGpsRilInterface->init(&sAGpsRilCallbacks);
    if (sGpsGeofencingInterface)
        sGpsGeofencingInterface->init(&sGpsGeofenceCallbacks);

    return true;
}
static void android_location_GpsLocationProvider_cleanup()
{
    if (sGpsInterface)
        sGpsInterface->cleanup();
}
static bool android_location_GpsLocationProvider_start()
{
    if (sGpsInterface)
        return (sGpsInterface->start() == 0);
    else
        return false;
}
static bool  android_location_GpsLocationProvider_stop()
{
    if (sGpsInterface)
        return (sGpsInterface->stop() == 0);
    else
        return false;
}
static bool  android_location_GpsLocationProvider_set_position_mode(
        int mode, int recurrence, int min_interval, int preferred_accuracy, int preferred_time)
{
    if (sGpsInterface)
        return (sGpsInterface->set_position_mode(mode, recurrence, min_interval, preferred_accuracy,
                    preferred_time) == 0);
    else
        return false;
}

//void test_dll()
//{
//    pthread_t tid;
//    pthread_create(&tid, NULL, NULL, NULL);
//    floor(1.1);
//    floorl(2.2);
//}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    android_location_GpsLocationProvider_class_init_native();
    if (!android_location_GpsLocationProvider_is_supported())
    {
        printf("not support gps\n");
        return -1;
    }
    android_location_GpsLocationProvider_init();
    android_location_GpsLocationProvider_set_position_mode(GPS_POSITION_MODE_STANDALONE, 0, 3000, 0, 0);
    android_location_GpsLocationProvider_start();
    if (gpio_export(LED1) < 0)
    {
        
    }
    if (gpio_export(LED2) < 0)
    {
        
    }
    gpio_direction_output(LED1, 1);
    gpio_direction_output(LED2, 1);
    while (1)
    {
        sleep(30); 
        system("echo \"at^wpdgp\" >/dev/ttyUSB4");
    }
    return EXIT_SUCCESS;
}
