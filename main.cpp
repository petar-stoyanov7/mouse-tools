#include <X11/Xlib.h>
#include <iostream>
#include <typeinfo>

void print_debug(std::string_view message);

bool debugMode = true; //todo: implement parameters and debugging

int main() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Cannot open display\n";
        return 1;
    }

    Window root = DefaultRootWindow(display);

    // Grab the pointer — intercepts ALL mouse events system-wide
    // int result = XGrabPointer(
    //     display,
    //     root,
    //     False,
    //     ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
    //     GrabModeAsync,
    //     GrabModeAsync,
    //     None,
    //     None,
    //     CurrentTime
    // );
    int result = XGrabPointer(
        display, root,
        True,                                           // owner_events
        ButtonPressMask | ButtonReleaseMask,
        GrabModeSync, GrabModeAsync,                    // Sync is critical
        None, None, CurrentTime
    );

    if (result != GrabSuccess) {
        std::cerr << "XGrabPointer failed: " << result << std::endl;
        XCloseDisplay(display);
        return 1;
    }

    print_debug("Myshkin initialized...");

    XEvent event;
    while (true) {
        XNextEvent(display, &event);

        if (event.type == ButtonPress || event.type == ButtonRelease) {
            int button = event.xbutton.button;

            if (event.xbutton.button == Button1 || event.xbutton.button == Button2 || event.xbutton.button == Button3) {
                print_debug("click");
                // Swallow it — do NOT call XAllowEvents
                // But you must still unfreeze the grab or no more events arrive!
                XAllowEvents(display, AsyncPointer, event.xbutton.time);
            } else {
                // Pass it through to whatever is under the cursor
                XAllowEvents(display, ReplayPointer, event.xbutton.time);
            }
            XFlush(display);
        }

        // if (event.type == ButtonPress) {
        //     std::cout << "Click intercepted at ("
        //         << event.xbutton.x_root << ", "
        //         << event.xbutton.y_root << ") "
        //         << "Button: " << event.xbutton.button << std::endl;
        //
        //     // Do NOT call XAllowEvents — this prevents propagation
        //     // To allow specific clicks through:
        //     // XAllowEvents(display, ReplayPointer, CurrentTime);
        // }
        //
        // Press middle button to release grab and exit
        if (event.type == ButtonPress && event.xbutton.button == Button2) {
            break;
        }
    }

    XUngrabPointer(display, CurrentTime);
    XCloseDisplay(display);
    return 0;
}

void print_debug(const std::string_view message) {
    if (debugMode) {
        std::cout << message << std::endl;
    }
}