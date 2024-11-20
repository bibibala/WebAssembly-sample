#include <cheerp/clientlib.h>

[[cheerp::genericjs]] // Required when using browser APIs like console.log
void webMain() {
  client::console.log("Hello, world!");
}