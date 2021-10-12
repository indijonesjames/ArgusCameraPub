
#include "CommonOptions.h"
#include "ArgusHelpers.h"

namespace ArgusSamples
{

static const uint32_t DEFAULT_CAMERA_DEVICE = 0;
static const uint32_t DEFAULT_SENSOR_MODE   = 0;
static const uint32_t DEFAULT_CAPTURE_TIME  = 5;
static const uint32_t DEFAULT_FRAME_COUNT   = 60;
static const Argus::Rectangle<uint32_t> DEFAULT_WINDOW_RECT(0, 0, 1024, 768);

CommonOptions::CommonOptions(const char *programName, uint32_t optionEnables)
    : Options(programName)
    , m_optionEnables(optionEnables)
    , m_cameraDeviceIndex(DEFAULT_CAMERA_DEVICE)
    , m_sensorModeIndex(DEFAULT_SENSOR_MODE)
    , m_captureTime(DEFAULT_CAPTURE_TIME)
    , m_frameCount(DEFAULT_FRAME_COUNT)
    , m_windowRect(DEFAULT_WINDOW_RECT)
{
    printf("Executing Argus Sample: %s\n", programName);

    addOption(Option("listdevices", 'l', "",
            Option::TYPE_ACTION,
            "List all available CameraDevices, then exit", listCameraDevices, this));

    if (m_optionEnables & Option_D_CameraDevice)
    {
        addOption(createValueOption
            ("device", 'd', "INDEX", "Camera Device index.", m_cameraDeviceIndex));
    }
    if (m_optionEnables & Option_M_SensorMode)
    {
        addOption(createValueOption
            ("mode", 'm', "INDEX", "Sensor Mode index.", m_sensorModeIndex));
    }
    if (m_optionEnables & Option_R_WindowRect)
    {
        addOption(createValueOption
            ("rect", 'r', "WINDOW", "Window rectangle.", m_windowRect));
    }
    if (m_optionEnables & Option_T_CaptureTime)
    {
        addOption(createValueOption
            ("duration", 't', "SECONDS", "Capture duration.", m_captureTime));
    }
    if (m_optionEnables & Option_F_FrameCount)
    {
        addOption(createValueOption
            ("frames", 'f', "COUNT", "Frame count.", m_frameCount));
    }
}

CommonOptions::~CommonOptions()
{
}

bool CommonOptions::parse(const int argc, char * const *argv)
{
    bool results = Options::parse(argc, argv);

    if ((m_optionEnables & Option_R_WindowRect) && (windowRect().width() % 2))
    {
        printf("WARNING: Window rect has an odd width. If the Argus OutputStream is sized\n"
               "         according to the window rect, using an odd size may fail.\n");
    }

    return results;
}

/* static */
bool CommonOptions::listCameraDevices(void *userPtr, const char *optArg)
{
    CommonOptions *options = reinterpret_cast<CommonOptions*>(userPtr);

    Argus::UniqueObj<Argus::CameraProvider> cameraProvider(Argus::CameraProvider::create());
    Argus::ICameraProvider *iCameraProvider =
        Argus::interface_cast<Argus::ICameraProvider>(cameraProvider);
    if (iCameraProvider)
    {
        std::vector<Argus::CameraDevice*> cameraDevices;
        iCameraProvider->getCameraDevices(&cameraDevices);
        printf("%lu Available CameraDevices:\n\n",
               static_cast<unsigned long>(cameraDevices.size()));
        for (uint32_t i = 0; i < cameraDevices.size(); i++)
        {
            printf("  ==== CameraDevice %u: =========================================\n", i);
            ArgusHelpers::printCameraDeviceInfo(cameraDevices[i], "    ");
            printf("\n");
        }
    }

    options->requestExit();

    return true;
}

}; // namespace ArgusSamples
