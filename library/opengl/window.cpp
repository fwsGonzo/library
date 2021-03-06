#include <library/opengl/window.hpp>

#include <library/log.hpp>
#include <library/opengl/opengl.hpp>
#include <library/sleep.hpp>

namespace library
{
bool WindowClass::init = false;

WindowConfig::WindowConfig()
{
    // set default window settings
    this->title = "Untitled window";
    this->fullscreen = false;
    this->vsync = true;
    this->refreshrate = 0;
    this->SW = 640;
    this->SH = 480;
    this->multisample = 0;
    this->depthbits = 24;
    this->stencbits = 8;

    this->core_context = false;
    this->ver_major = 3;
    this->ver_minor = 3;
}
WindowConfig::WindowConfig(std::string title, int width, int height) : WindowConfig()
{
    // set default window settings
    this->title = title;
    this->SW = width;
    this->SH = height;
    this->fullscreen = false;
}

void WindowClass::open(const WindowConfig& wndconf)
{
    if (this->init == false) { glfwInit(); }
    this->closing = false;

    // fullscreen enables setting refresh rate
    this->fullscreen = wndconf.fullscreen;

    // set primary monitor if we are to run in fullscreen
    GLFWmonitor* monitor = (fullscreen) ? glfwGetPrimaryMonitor() : nullptr;
    if (fullscreen) { glfwWindowHint(GLFW_REFRESH_RATE, wndconf.refreshrate); }
    glfwWindowHint(GLFW_RESIZABLE, 1);

    // clamp multisample to at least 0
    int multisample = wndconf.multisample;
    if (multisample < 0) multisample = 0;
    // set multisampling level for main framebuffer
    glfwWindowHint(GLFW_SAMPLES, multisample);
    // common stencil & depth settings
    glfwWindowHint(GLFW_DEPTH_BITS, wndconf.depthbits);
    glfwWindowHint(GLFW_STENCIL_BITS, wndconf.stencbits);

    // OpenGL API version request
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, wndconf.ver_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, wndconf.ver_minor);
    // profile type request
    this->is_core_context = false;
    if (wndconf.ver_major < 3 || (wndconf.ver_major == 3 && wndconf.ver_minor < 2))
    {
        // older API versions
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    }
    else if (wndconf.core_context)
    {
        // forward-only core profile
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        this->is_core_context = true;
    }
    else
    {
        // compatibility mode
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    }

    // create new glfw3 window
    this->wndHandle =
        glfwCreateWindow(wndconf.SW, wndconf.SH, wndconf.title.c_str(), monitor, nullptr);
    if (this->wndHandle == nullptr)
    {
        logger << Log::ERR << "Could not open 32bit / 24d8s window of size: " << wndconf.SW << ", "
               << wndconf.SH << Log::ENDL;
        glfwTerminate();
        throw std::string(
            "Window::init(): Could not open OpenGL context window, check your drivers!");
    }

    // get actual size, since it may not be supported
    int width;
    int height;
    glfwGetFramebufferSize(this->wndHandle, &width, &height);

    // make this window the current OpenGL context
    setCurrent();

    // vertical sync
    glfwSwapInterval((wndconf.vsync) ? 1 : 0);

    // set default viewport
    glViewport(0, 0, width, height);

    // initialize OpenGL automatically
    if (this->init == false)
    {
        this->init = true;
        // init OpenGL entries & defaults
        OpenGL ogl(this->is_core_context);
    }
}

int WindowClass::getWidth() const noexcept
{
    int width;
    int height;
    glfwGetFramebufferSize(this->wndHandle, &width, &height);
    return width;
}
int WindowClass::getHeight() const noexcept
{
    int width;
    int height;
    glfwGetFramebufferSize(this->wndHandle, &width, &height);
    return height;
}
glm::vec2 WindowClass::getSize() const noexcept
{
    int width;
    int height;
    glfwGetFramebufferSize(this->wndHandle, &width, &height);
    return glm::vec2(width, height);
}
float WindowClass::getAspect() const noexcept
{
    int width;
    int height;
    glfwGetFramebufferSize(this->wndHandle, &width, &height);
    return width / (float) height;
}

void WindowClass::close()
{
    if (wndHandle)
    {
        setCurrent();
        glfwDestroyWindow(wndHandle);
        wndHandle = nullptr;
    }
}

void WindowClass::waitClose()
{
    while (this->closing == false) relinquishCPU();
    close();
}

GLFWwindow* WindowClass::window() { return this->wndHandle; }

void WindowClass::setTitle(std::string const& title)
{
    glfwSetWindowTitle(wndHandle, title.c_str());
}

void WindowClass::setPosition(int x, int y) { glfwSetWindowPos(wndHandle, x, y); }

// makes this window the current opengl context
void WindowClass::setCurrent() { glfwMakeContextCurrent(this->wndHandle); }

void WindowClass::startRenderingLoop(RenderClass& rclass)
{
    setCurrent();
    double t0 = glfwGetTime();
    double t1 = t0;

    glfwSetWindowShouldClose(wndHandle, 0);
    while (!glfwWindowShouldClose(wndHandle))
    {
        setCurrent();

        double t_last = t1;
        t1 = glfwGetTime();

        // render function returns false if we should stop rendering
        if (rclass.render(*this, t1 - t_last, t1 - t0) == false) break;

        // check for events (which might set window to be flagged as closing)
        glfwPollEvents();
    }
    this->closing = true;
}

} // namespace library
