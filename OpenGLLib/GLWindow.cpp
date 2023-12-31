#include "GLWindow.h"

GLWindow::GLWindow() : _window(NULL),
                       _shader(NULL),
                       _initialized(false)
{

}

GLWindow::GLWindow(GLSize size, std::string title, unsigned int major, unsigned int minor, GLHints hints) : _window(NULL),
                                                                                                                 _shader(NULL)
{
    Create(size, title, major, minor, hints);
}

GLWindow::~GLWindow()
{
    if (_window)
    {
        glfwDestroyWindow(_window);
    }

    if (_shader)
    {
        delete _shader;
    }
}

bool GLWindow::Create(GLSize size, std::string title, unsigned int major, unsigned int minor, GLHints hints)
{
    glfwInit();

    CheckVersion(major, minor);
    CheckSize(size);

    SetMajor(major);
    SetMinor(minor);

    SetHints(hints);

    _window = glfwCreateWindow(size.first, size.second, title.c_str(), NULL, NULL);

    if (!_window)
    {
        _initialized = false;
        return false;
    }

    _title       = title;
    _initialized = true;
    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    return true;
}

bool GLWindow::IsInitialized()
{
    return _initialized;
}

GLSize GLWindow::GetSize() const
{
    if (!_window)
    {
        return GLSize();
    }

    GLSize size;

    glfwGetWindowSize(_window, &size.first, &size.second);

    return size;
}

std::string GLWindow::GetTitle() const
{
    // There is no glfw method to obtain the window title, thus we have to use a variable to keep track of it.
    return _title;
}

unsigned int GLWindow::GetGLMajor() const
{
    int test = glfwGetWindowAttrib(_window, GLFW_CONTEXT_VERSION_MAJOR);
    return test;
}

unsigned int GLWindow::GetGLMinor() const
{
    return glfwGetWindowAttrib(_window, GLFW_CONTEXT_VERSION_MINOR);
}

GLRGBA GLWindow::GetBackgroundColour() const
{
    return _backgroundColour;
}

GLShader* GLWindow::GetAttachedShader() const
{
    return _shader;
}

void GLWindow::SetCurrentContext()
{
    if (_window)
    {
        glfwMakeContextCurrent(_window);
    }
}

void GLWindow::SetSize(GLSize size)
{
    if (!_window)
    {
        return;
    }

    CheckSize(size);

    glfwSetWindowSize(_window, size.first, size.second);
}

void GLWindow::SetTitle(std::string title)
{
    if (!_window)
    {
        return;
    }

    glfwSetWindowTitle(_window, title.c_str());
    _title = title;
}

void GLWindow::SetBackgroundColour(GLRGBA backgroundColour)
{
    _backgroundColour = backgroundColour;
}

void GLWindow::AttachShader(GLShader* shader)
{
    _shader = shader;
}

void GLWindow::ClearBackground()
{
    glClearColor(_backgroundColour.GetR(), _backgroundColour.GetG(), _backgroundColour.GetB(), _backgroundColour.GetA());
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLWindow::SwapBuffers()
{
    if (_window)
    {
        glfwSwapBuffers(_window);
    }
}

bool GLWindow::IsWindowResizable()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_RESIZABLE) : false;
}

bool GLWindow::IsWindowDecorated()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_DECORATED) : false;
}

bool GLWindow::IsWindowMaximized()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_MAXIMIZED) : false;
}

bool GLWindow::IsWindowMinimized()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_ICONIFIED) : false;
}

bool GLWindow::IsWindowVisible()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_VISIBLE) : false;
}

bool GLWindow::IsWindowAutoMinimized()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_AUTO_ICONIFY) : false;
}

bool GLWindow::IsWindowFloating()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_FLOATING) : false;
}

bool GLWindow::IsWindowFocusedOnShow()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_FOCUS_ON_SHOW) : false;
}

bool GLWindow::IsWindowFocused()
{
    return _window ? glfwGetWindowAttrib(_window, GLFW_FOCUSED) : false;
}

void GLWindow::SetWindowResizable(bool resizable)
{
    _window ? glfwSetWindowAttrib(_window, GLFW_RESIZABLE, resizable) : void();
}

void GLWindow::SetWindowDecorated(bool decorate)
{
    _window ? glfwSetWindowAttrib(_window, GLFW_DECORATED, decorate) : void();
}

void GLWindow::SetWindowAutoMinimize(bool autoIconify)
{
    _window ? glfwSetWindowAttrib(_window, GLFW_AUTO_ICONIFY, autoIconify) : void();
}

void GLWindow::SetFocusOnShow(bool focus)
{
    _window ? glfwSetWindowAttrib(_window, GLFW_FOCUS_ON_SHOW, focus) : void();
}

void GLWindow::Show()
{
    _window ? glfwShowWindow(_window) : void();
}

void GLWindow::Hide()
{
    _window ? glfwHideWindow(_window) : void();
}

void GLWindow::Focus()
{
    _window ? glfwFocusWindow(_window) : void();
}

void GLWindow::Maximize(bool maximize)
{
    _window ? (maximize ? glfwMaximizeWindow(_window) : glfwRestoreWindow(_window)) : void();
}

void GLWindow::Minimize(bool minimize)
{
    _window ? (minimize ? glfwIconifyWindow(_window) : glfwRestoreWindow(_window)) : void();
}

void GLWindow::Float(bool windowFloat)
{
    _window ? glfwSetWindowAttrib(_window, GLFW_FLOATING, windowFloat) : void();
}

/* \brief Sets a keyboard input callback
 */
GLFWkeyfun GLWindow::SetKeyCallback(GLFWkeyfun callback)
{
    return _window ? glfwSetKeyCallback(_window, callback) : NULL;
}

/* \brief Sets a unicode character input callback
 */
GLFWcharfun GLWindow::SetCharCallback(GLFWcharfun callback)
{
    return _window ? glfwSetCharCallback(_window, callback) : NULL;
}

/* \brief Sets a custom unicode character input callback
 */
GLFWcharmodsfun GLWindow::SetCharModsCallback(GLFWcharmodsfun callback)
{
    return _window ? glfwSetCharModsCallback(_window, callback) : NULL;
}

/* \brief Sets a callback for mouse movement in the window
 */
GLFWcursorposfun GLWindow::SetCursorPosCallback(GLFWcursorposfun callback)
{
    return _window ? glfwSetCursorPosCallback(_window, callback) : NULL;
}

/* \brief Sets a callback for the mouse entering/exiting the window
 */
GLFWcursorenterfun GLWindow::SetCursorEnterCallback(GLFWcursorenterfun callback)
{
    return _window ? glfwSetCursorEnterCallback(_window, callback) : NULL;
}

/* \brief Sets a callback for mouse button input in the window
 */
GLFWmousebuttonfun GLWindow::SetMouseButtonCallback(GLFWmousebuttonfun callback)
{
    return _window ? glfwSetMouseButtonCallback(_window, callback) : NULL;
}

/* \brief Sets a callback for scrolling in the window
 */
GLFWscrollfun GLWindow::SetScrollCallback(GLFWscrollfun callback)
{
    return _window ? glfwSetScrollCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when a joystick is connected/disconnected from the system.
 */
GLFWjoystickfun GLWindow::SetJoystickCallback(GLFWjoystickfun callback)
{
    return glfwSetJoystickCallback(callback);
}

/* \brief Sets a callback that activates when a path(s) are dropped into the window
 */
GLFWdropfun GLWindow::SetDropCallback(GLFWdropfun callback)
{
    return _window ? glfwSetDropCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the window moves
 */
GLFWwindowposfun GLWindow::SetWindowPosCallback(GLFWwindowposfun callback)
{
    return _window ? glfwSetWindowPosCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the window size changes
 */
GLFWwindowsizefun GLWindow::SetWindowSizeCallback(GLFWwindowsizefun callback)
{
    return _window ? glfwSetWindowSizeCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the window closes. Callback activates right after the close flag is set.
 */
GLFWwindowclosefun GLWindow::SetWindowCloseCallback(GLFWwindowclosefun callback)
{
    return _window ? glfwSetWindowCloseCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the window needs to be refreshed
 */
GLFWwindowrefreshfun GLWindow::SetWindowRefreshCallback(GLFWwindowrefreshfun callback)
{
    return _window ? glfwSetWindowRefreshCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the window gains/loses focus
 */
GLFWwindowfocusfun GLWindow::SetWindowFocusCallback(GLFWwindowfocusfun callback)
{
    return _window ? glfwSetWindowFocusCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the window is iconified (minimized?)
 */
GLFWwindowiconifyfun GLWindow::SetWindowIconifyCallback(GLFWwindowiconifyfun callback)
{
    return _window ? glfwSetWindowIconifyCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the window is maximized
 */
GLFWwindowmaximizefun GLWindow::SetWindowMaximizeCallback(GLFWwindowmaximizefun callback)
{
    return _window ? glfwSetWindowMaximizeCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the framebuffer size changes
 */
GLFWframebuffersizefun GLWindow::SetFramebufferSizeCallback(GLFWframebuffersizefun callback)
{
    return _window ? glfwSetFramebufferSizeCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when the content scale (ratio of current DPI to the platform's default DPI) changes
 */
GLFWwindowcontentscalefun GLWindow::SetWindowContentScaleCallback(GLFWwindowcontentscalefun callback)
{
    return _window ? glfwSetWindowContentScaleCallback(_window, callback) : NULL;
}

/* \brief Sets a callback that activates when a monitor is connected/disconnected
 */
GLFWmonitorfun GLWindow::SetMonitorCallback(GLFWmonitorfun callback)
{
    return glfwSetMonitorCallback(callback);
}

void GLWindow::SetMajor(unsigned int major)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
}

void GLWindow::SetMinor(unsigned int minor)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void GLWindow::CheckVersion(unsigned int & major, unsigned int & minor)
{
    switch(major)
    {
        case(1):
        {
            if (minor > 5)
            {
                major = 1;
                minor = 0;
            }
            break;
        }
        case(2):
        {
            if (minor > 1)
            {
                major = 1;
                minor = 0;
            }
            break;
        }
        case(3):
        {
            if (minor > 3)
            {
                major = 1;
                minor = 0;
            }
            break;
        }
        case(4):
        {
            if (minor > 6)
            {
                major = 1;
                minor = 0;
            }
            break;
        }
        default:
        {
            major = 1;
            minor = 0;
        }
    }
}

void GLWindow::CheckSize(GLSize size)
{
    if (size.first < 1)
    {
        size.first = 1;
    }

    if (size.second < 1)
    {
        size.second = 1;
    }
}

void GLWindow::SetHints(GLHints hints)
{
    hints & GL_RESIZABLE     ? glfwWindowHint(GLFW_RESIZABLE,     GLFW_TRUE) : glfwWindowHint(GLFW_RESIZABLE,     GLFW_FALSE);
    hints & GL_VISIBLE       ? glfwWindowHint(GLFW_VISIBLE,       GLFW_TRUE) : glfwWindowHint(GLFW_VISIBLE,       GLFW_FALSE);
    hints & GL_DECORATED     ? glfwWindowHint(GLFW_DECORATED,     GLFW_TRUE) : glfwWindowHint(GLFW_DECORATED,     GLFW_FALSE);
    hints & GL_FOCUSED       ? glfwWindowHint(GLFW_FOCUSED,       GLFW_TRUE) : glfwWindowHint(GLFW_FOCUSED,       GLFW_FALSE);
    hints & GL_AUTO_MINIMIZE ? glfwWindowHint(GLFW_AUTO_ICONIFY,  GLFW_TRUE) : glfwWindowHint(GLFW_AUTO_ICONIFY,  GLFW_FALSE);
    hints & GL_FLOATING      ? glfwWindowHint(GLFW_FLOATING,      GLFW_TRUE) : glfwWindowHint(GLFW_FLOATING,      GLFW_FALSE);
    hints & GL_MAXIMIZED     ? glfwWindowHint(GLFW_MAXIMIZED,     GLFW_TRUE) : glfwWindowHint(GLFW_MAXIMIZED,     GLFW_FALSE);
    hints & GL_FOCUS_ON_SHOW ? glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE) : glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
}