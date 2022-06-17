#pragma once

#include "GameMode.h"

class AllVsAllMode : public GameMode
{
public:
	AllVsAllMode(sf::RenderWindow& window);
	void createMode();
	void selection();
	void handleView() override;
protected:

};