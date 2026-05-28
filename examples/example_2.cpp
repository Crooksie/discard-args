#include <discard_args.h>
#include <cstdio>
#include <string>

// For this example, we are imagining we are using a GUI library that has a handler for when a button is clicked.
// This library always sends the mouse coordinates and the name of the button when the button is pressed.
typedef void (*button_handler_t)(int x, int y, std::string name);
void buttonClicker(button_handler_t handler) { handler(1, 2, "MyButton"); }

// Our button handler only uses the x, y coordinates of the mouse, but doesn't want the
void myButtonHandler(int x, int y) {
    printf("button pressed x: %d, y: %d\n", x, y);
}


int main() {
    using namespace discard_args;
    // Here we use the discard_args library to wrap our handler with the parameters (int, int, string) and then,
    // map the two first parameters of the wrapper to the first two parameters of our callback
    auto withParams = adapt<myButtonHandler>().to<int, int, std::string>().map<0, 1>();

    // Now the adapted version of the function can be called by the library.
    buttonClicker(withParams);


    return 0;

}