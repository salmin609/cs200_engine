#pragma once

#include <memory>
#include <functional>

struct PlatformImpl;
enum Keyboard
{
    W, A, S, D,
    None
};

enum MouseButtons
{
    Left,
    Right
};

class Window
{
public:
    Window();
    ~Window();

    bool CreateAndShowWindow(const wchar_t* title, int w, int h);

    void PollEvents();
    void CloseWindow();
    bool ShouldQuit();

    void SetOnKeyPressed(std::function<void(Keyboard)> callback);
    void SetOnKeyReleased(std::function<void(Keyboard)> callback);
private:
    std::unique_ptr<PlatformImpl> pimpl{};
};
