#include "..\Core\Core.h"


int main(){
	Core engine = Core(800, 600, "test");
	engine.start();

	std::cout << "here\n";
	return 0;
}