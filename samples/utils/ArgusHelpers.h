
#ifndef ARGUS_HELPERS_H
#define ARGUS_HELPERS_H

#include <Argus/Argus.h>

namespace ArgusSamples
{

namespace ArgusHelpers
{


/**
 * Returns the CameraDevice of a given index from a CameraProvider.
 *
 * @param[in] cameraProvider The CameraProvider to get the device from.
 * @param[in] cameraDeviceIndex The index of the device to get.
 */
Argus::CameraDevice* getCameraDevice(Argus::CameraProvider* cameraProvider,
                                     uint32_t cameraDeviceIndex);

/**
 * Returns the SensorMode of a given index from a CameraProvider.
 *
 * @param[in] cameraDevice The CameraDevice to get the sensor mode from.
 * @param[in] sensorModendex The index of the sensor mode to get.
 */
Argus::SensorMode* getSensorMode(Argus::CameraDevice* cameraDevice,
                                 uint32_t sensorModeIndex);

/**
 * Return the first available WDR (DOL or PWL) sensor mode from a CameraDevice.
 *
 * @param[in] cameraDevice The CameraDevice to get the WDR sensor mode from.
 */
Argus::SensorMode* getWdrSensorMode(Argus::CameraDevice* cameraDevice);

/**
 * Prints out information about a CameraDevice.
 *
 * @param[in] cameraDevice The device to print the info for.
 * @param[in] indent the indent to prepend to each line of output.
 */
void printCameraDeviceInfo(Argus::CameraDevice* cameraDevice, const char* indent);

/**
 * Prints out information about a SensorMode.
 *
 * @param[in] sensorMode The mode to print the info for.
 * @param[in] indent the indent to prepend to each line of output.
 */
void printSensorModeInfo(Argus::SensorMode* sensorMode, const char* indent);

/**
 * Prints out a UUID.
 */
void printUUID(const Argus::UUID& uuid);

}; // namespace ArgusHelpers

}; // namespace ArgusSamples

#endif // ARGUS_HELPERS_H
