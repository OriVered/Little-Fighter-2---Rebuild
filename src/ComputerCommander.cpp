#include "ComputerCommander.h"

ComputerCommander::ComputerCommander(const playerData& playerData)
    :Commander(playerData), m_lastAction(Action{ActionType::Walking, Direction::Right}),
    m_timeFromComboToCombo(firstTime)
{}



Action ComputerCommander::getActionFromAlgo(const sf::Vector2f& myPos, const sf::Vector2f& targetPos)
{

    if (abs(myPos.x - targetPos.x) < smallXDistance && abs(myPos.y - targetPos.y) < smallYDistance )
    {
        if (m_lastAction.first == ActionType::Walking)
            return {Action {ActionType::Punching, Direction::Stay}};

        else
            return  Action {ActionType::Walking, randomMapDirection.find(rand() % numOfDirections)->second};
    }

    else
        return Action {ActionType::Walking, toDirection(sf::Vector2f {(float) sgn (targetPos.x - myPos.x), 
                                                        (float)  sgn (targetPos.y - myPos.y)})};
}

Action ComputerCommander::setRandomAction()
{
    if (m_commanderClock.getElapsedTime().asSeconds() > determinedTime)
    {
        m_commanderClock.restart();
        m_lastAction = Action {ActionType::Walking, randomMapDirection.find(rand() % numOfDirections)->second};
    }

    return m_lastAction;

}

void ComputerCommander::setComputerCombo(const sf::Vector2f& myPos, const sf::Vector2f& targetPos)
{
    if (m_commanderComboClock.getElapsedTime().asSeconds() > m_timeFromComboToCombo && abs(myPos.y - targetPos.y) < enoughDistanceToCombo)
    {
        m_timeFromComboToCombo = float(rand () % comboTimeRange + minimumWaitForCombo);
        m_commanderComboClock.restart() ;
        m_combo = getRandomCombo();
    }
        
     else 
         m_combo =  ActionType::Standing;

}

void ComputerCommander::update()
{}

ActionType ComputerCommander::getRandomCombo() const
{
    return ActionType (rand() % numOfCombos + firstComboNum);
     
}
