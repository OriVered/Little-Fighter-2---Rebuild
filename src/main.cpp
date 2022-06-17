
#include <Controller.h>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() try
{
	Controller controller;

	controller.run();


	return EXIT_SUCCESS;
}
catch (std::exception& e) {
	std::cerr << "Exception: " << e.what() << '\n'; return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Exception catched " << '\n'; return EXIT_FAILURE;
}
