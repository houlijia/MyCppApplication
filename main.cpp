#include <iostream>
#include <thread>
#include "thread/threading.h"
#include "stl/stlvariables.h"
#include "stackandhap/stackandhap.h"
#include "testclass/testclass.h"
#include "testlink/testlink.h"
#include "testpointer/testpointer.h"
#include "testvariables/testvariables.h"

using namespace std;
#include <iostream>
void logg(const char* message);

int main() {
    funthreading();
    //teststlvar();
    //testpointer();
    //testclass();
    //stackandhap();
    //testlink();
    testvariables();

    return 0;
}
