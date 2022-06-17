#pragma once

#include "GameMode.h"

class TwoPlayerMode : public GameMode
{
public:
	TwoPlayerMode(sf::RenderWindow& window);
	void createMode();
	void selection();
	void handleView() override;
private:

};