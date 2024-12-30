#include <cheerp/clientlib.h>
#include "Test_2.cpp"
class  [[cheerp::jsexport]] Test_1 {
private:
    Test_2 test2;

public:
    [[cheerp::jsexport]]
    int performAddition(int a, int b) {
        return test2.add(a, b);
    }
};