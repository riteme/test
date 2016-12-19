#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/Sdl2Application.h>

using namespace Magnum;

class MyApplication : public Platform::Application {
 public:
    MyApplication(const Arguments& arguments);

 private:
    void drawEvent() override;
    void viewportEvent(const Vector2i& size) override;
};

MyApplication::MyApplication(const Arguments& arguments)
        : Platform::Application(arguments) {
    // Set clear color to dark blue
    Renderer::setClearColor({ 0.0f, 0.0f, 0.4f });
}

void MyApplication::drawEvent() {
    // Clear the window
    defaultFramebuffer.clear(FramebufferClear::Color);
    // The context is double-buffered, swap buffers
    swapBuffers();
}

void MyApplication::viewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({ {}, size });
}

// main() function implementation
MAGNUM_APPLICATION_MAIN(MyApplication)
