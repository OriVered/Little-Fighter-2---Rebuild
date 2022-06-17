#include "AllVsAllMode.h"



AllVsAllMode::AllVsAllMode(sf::RenderWindow& window)
	:GameMode(window, Modes::AllVsAll)
{
	createMode();
}

void AllVsAllMode::createMode()
{
	selection();
	
	setBackground(std::make_shared< CWBackground>(Modes::AllVsAll));
}
void AllVsAllMode::selection()
{	
	auto choosen = CharacterSelection(m_window, numOfPlayersAllVsAll).choose();
	if (choosen.empty()) m_isRunning = false;
	else createPlayers(choosen);
	
}

void AllVsAllMode::handleView()
{

	sf::View view = m_window.getView();

	for (auto& player : m_characters)
		player->setInfoView(view.getCenter().x - WindowWidth / 2.f);
}


