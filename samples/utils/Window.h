
#if defined(ANDROID)
#include "android/Window.h"
#elif defined(SAMPLE_USE_GLX)
#include "glx/Window.h"
#else
#include "gtk/Window.h"
#endif
