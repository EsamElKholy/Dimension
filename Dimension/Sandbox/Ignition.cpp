#include "..\Core\Core.h"


int main(){
	Core engine = Core(1366, 768, "Dimension" ,60 ,TestGame());
	engine.start();

	return 0;
}