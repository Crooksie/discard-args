#include <discard_args.h>
#include <cstdio>
#include <string>

// For this example, we are imagining we are using a GUI library that has a handler for when a button is clicked.
// This library doesn't pass any arguments to the callback.
typedef void (*button_handler_t)();
void buttonClicker(button_handler_t handler) { handler(); }

// Our button handler takes 2 integer parameters, our handler doesn't take any.  For this example, we don't want to
// change our callback, maybe because it's used elsewhere in the codebase, but we are happy passing in default/null values.
void myButtonHandler(int x, int y) {
    printf("button pressed x: %d, y: %d\n", x, y);
}


int main() {
    using namespace discard_args;
    // Here we use the discard_args library to wrap our handler with the parameters (int, int, string) and then,
    // map the two first parameters of the wrapper to the first two parameters of our callback
    auto withParams = adapt<myButtonHandler>().no_args();

    // Now the adapted version of the function can be called by the library.
    buttonClicker(withParams);


    return 0;

}