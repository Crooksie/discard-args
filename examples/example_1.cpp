#include <discard_args.h>
#include <cstdio>

// For this example, we are imagining we are using a GUI library that has a handler for when a button is clicked.
// This library always sends the mouse coordinates along with the button press.
typedef void (*button_handler_t)(int x, int y);
void buttonClicker(button_handler_t handler) {
    handler(1, 2);
}

// Our button handler doesn't use the x, y coordinates of the mouse for anything, so it doesn't include them as
// parameters
void myButtonHandler() {
    printf("button pressed\n");
}


int main() {
    using namespace discard_args;
    // Here we use the discard_args library to add two integer parameters to our button handler so that the interfaces
    // match.  We tell it to discard the inputs we've added to the function.
    auto withParams = adapt<myButtonHandler>().to<int, int>().discard_inputs();

    // Now the adapted version of the function can be called by the library.
    buttonClicker(withParams);

    return 0;

}