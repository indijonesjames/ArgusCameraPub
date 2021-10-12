
#ifndef PREVIEWCONSUMER_H
#define PREVIEWCONSUMER_H

#include <Argus/Argus.h>
#include "EGLGlobal.h"
#include "GLContext.h"
#include "Thread.h"
#include "Window.h"

namespace ArgusSamples
{

using namespace Argus;

/*******************************************************************************
 * Preview consumer thread:
 *   Uses an on-screen window and and OpenGL EGLStream consumer to render a live
 *   preview of an OutputStream to the display.
 ******************************************************************************/
class PreviewConsumerThread : public Thread
{
public:

    enum RenderLayout {
        /// Streams divide the window horizontally, first on the left, last on the right.
        /// Expected window size is (height, width * streams.size())
        LAYOUT_HORIZONTAL,

        /// Streams divide the window vertically, first at the top, last at the bottom.
        /// Expected window size is (height * streams.size(), width)
        LAYOUT_VERTICAL,

        /// Streams are tiled evenly (eg. 2x2, 3x3, etc.) to maintain window aspect ratio.
        LAYOUT_TILED,

        /// Streams are divided horizontally to render to a single region.
        LAYOUT_SPLIT_HORIZONTAL,

        /// Streams are divided vertically to render to a single region.
        LAYOUT_SPLIT_VERTICAL,
    };

    explicit PreviewConsumerThread(EGLDisplay display, EGLStreamKHR stream);
    explicit PreviewConsumerThread(EGLDisplay display, const std::vector<EGLStreamKHR>& streams,
                                   RenderLayout layout = LAYOUT_TILED,
                                   bool syncStreams = false);
    ~PreviewConsumerThread();

    /**
     * Sets the width of the line to render between streams.
     */
    void setLineWidth(uint32_t width);

    /**
     * Sets the line color.
     */
    void setLineColor(float r, float g, float b);

private:
    /** @name Thread methods */
    /**@{*/
    virtual bool threadInitialize();
    virtual bool threadExecute();
    virtual bool threadShutdown();
    /**@}*/

    void renderStreams();

    EGLDisplay m_display;
    GLContext m_context;
    std::vector<EGLStreamKHR> m_streams;
    std::vector<GLuint> m_textures;
    GLuint m_program;
    GLint m_textureUniform;
    Size2D<uint32_t> m_windowSize;
    RenderLayout m_layout;
    bool m_syncStreams;
    uint32_t m_lineWidth;
    float m_lineColor[3];
};

} // namespace ArgusSamples

#endif // PREVIEWCONSUMER_H
