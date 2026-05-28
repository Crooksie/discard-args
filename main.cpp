#include <cstdio>
#include <tuple>




void myButtonHandler() { printf("button pressed\n"); }

typedef void (*button_handler_t)(int x, int y);

void buttonClicker(button_handler_t handler) { handler(1, 2); }




int main() {

    // auto fn = [](int a){ printf("hello world\n"); };
    // auto af = adapt(fn).to<int, int>().map<0>();
    // af(1, 2);
    //
    // auto fn2 = [](int a, int b){ printf("hello world %d %d\n", a, b); };
    // auto af2 = adapt(fn2).to<int, int>().map<1, 0>();
    // af2(1, 2);
    //
    // auto no_arg = adapt([](int a) { printf("%d\n", a); }).no_args();

    auto withParams = adapt<myButtonHandler>().to<int, int>().discard_inputs();

    buttonClicker(withParams);


    return 0;

}