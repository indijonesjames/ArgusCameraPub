
#ifndef CAMERA_MODULES_XML_CONFIG_H
#define CAMERA_MODULES_XML_CONFIG_H

namespace ArgusSamples
{

/**
 * Load configuration from XMl file.
 *
 * @param configFile [in]
 */
bool loadConfig(const char *configFile);

/**
 * Save configuration to a XMl file.
 *
 * @param configFile [in]
 */
bool saveConfig(const char *configFile);

}; // namespace ArgusSamples

#endif // CAMERA_MODULES_XML_CONFIG_H
