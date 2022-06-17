#include "TwoPlayerMode.h"

TwoPlayerMode::TwoPlayerMode(sf::RenderWindow& window)
	:GameMode(window, Modes::AllVsAll)
{
	createMode();
}

void TwoPlayerMode::createMode()
{
	selection();

	setBackground(std::make_shared< CWBackground>(Modes::AllVsAll));
}
void TwoPlayerMode::selection()
{
	auto choosen = CharacterSelection(m_window, TwoPlayers, TwoCommanders).choose();
	if (choosen.empty()) m_isRunning = false;
	else createPlayers(choosen);

}

void TwoPlayerMode::handleView()
{
	sf::View view = m_window.getView();

	for (auto& player : m_characters)
		player->setInfoView(view.getCenter().x - WindowWidth / 2.f);
}
