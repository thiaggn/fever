#include <ctx/context.h>

int main() {
    struct ctx_context c = ctx_create(500, 300, "fever");

    while (c.available()) {
        c.render();
    }

    c.terminate();
    return 0;
}
