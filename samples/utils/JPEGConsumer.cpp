
#include "JPEGConsumer.h"
#include "Error.h"

#include <Argus/Argus.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>


namespace ArgusSamples
{

#define JPEG_CONSUMER_PRINT(...)    printf("JPEG CONSUMER: " __VA_ARGS__)

#ifdef ANDROID
#define JPEG_PREFIX "/sdcard/DCIM/Argus_"
#else
#define JPEG_PREFIX "Argus_"
#endif

bool JPEGConsumerThread::threadInitialize()
{
    // Create the FrameConsumer.
    m_consumer = UniqueObj<FrameConsumer>(FrameConsumer::create(m_stream));
    if (!m_consumer)
        ORIGINATE_ERROR("Failed to create FrameConsumer");

    return true;
}

bool JPEGConsumerThread::threadExecute()
{
    IEGLOutputStream *iEGLOutputStream = interface_cast<IEGLOutputStream>(m_stream);
    IFrameConsumer *iFrameConsumer = interface_cast<IFrameConsumer>(m_consumer);

    // Wait until the producer has connected to the stream.
    JPEG_CONSUMER_PRINT("Waiting until producer is connected...\n");
    if (iEGLOutputStream->waitUntilConnected() != STATUS_OK)
        ORIGINATE_ERROR("Stream failed to connect.");
    JPEG_CONSUMER_PRINT("Producer has connected; continuing.\n");;

    int frameCount = 0;
    while (true)
    {
        // Acquire a Frame.
        UniqueObj<Frame> frame(iFrameConsumer->acquireFrame());
        IFrame *iFrame = interface_cast<IFrame>(frame);
        if (!iFrame)
            break;

        // Get the Frame's Image.
        Image *image = iFrame->getImage();
        IImageJPEG *iJPEG = interface_cast<IImageJPEG>(image);
        if (!iJPEG)
            ORIGINATE_ERROR("Failed to get IImageJPEG interface.");

        // Write the Image to disk as JPEG.
        std::ostringstream fileName;
        fileName << JPEG_PREFIX << std::setfill('0') << std::setw(4) << frameCount++ << ".jpg";
        if (iJPEG->writeJPEG(fileName.str().c_str()) == STATUS_OK)
            JPEG_CONSUMER_PRINT("Captured a still image to '%s'\n", fileName.str().c_str());
        else
            ORIGINATE_ERROR("Failed to write JPEG to '%s'\n", fileName.str().c_str());
    }

    JPEG_CONSUMER_PRINT("No more frames. Cleaning up.\n");

    PROPAGATE_ERROR(requestShutdown());

    return true;
}

bool JPEGConsumerThread::threadShutdown()
{
    JPEG_CONSUMER_PRINT("Done.\n");

    return true;
}

} // namespace ArgusSamples
