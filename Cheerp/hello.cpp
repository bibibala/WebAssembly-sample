#include <cheerp/clientlib.h>

[[cheerp::jsexport]]
int add(int a, int b) {
    return a + b;
}