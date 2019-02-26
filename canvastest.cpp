#include <iostream>
#include <vector>
#include "../pockets/canvas.h"

using namespace std;

int func(int x) {
	return x;
}

int (*f) (int);

int main() {
	Canvas c = Canvas(7, 7);
	c.print(cout);
	f = &func;
	c.plotaxes(3, 3);
	c.plotfunction(f);
	c.print(cout);
	return 0;
}