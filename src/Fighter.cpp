#include "Fighter.h"



Fighter::Fighter(const playerData& playerData, const sf::Vector2f& pos)
    : m_playerData(playerData),
    MovingObject(pos, playerData.m_fighter , fighterFactorData.find(playerData.m_fighter)->second),
    m_isDead(false), m_combo(ActionType::DelayWalk),
    m_fighterSpeed(fighterSpeedData.find(playerData.m_fighter)->second)
{
    startCommander(playerData);
    startInfo(playerData);

}

void Fighter::startInfo(const playerData& playerData)
{
    if (playerData.m_fighter == Fighter_f::bandit_f)
        m_info = std::make_shared< CharacterInfo>(playerData);
    else
        m_info = std::make_shared< MainCharacterInfo>(playerData);//still has to put the team
}

void Fighter::startCommander(const playerData& playerData)
{
    if (playerData.m_commander == CommandType::Computer)
        m_commander = std::make_shared <ComputerCommander>(playerData);
    else
        m_commander = std::make_shared<UserCommander>(playerData);
}

void Fighter::setNextAction()
{
    Direction dir;
    ActionType actionType;

    //ComputerCommander
    if (auto commander = dynamic_cast<ComputerCommander*>(m_commander.get()))
        setComputerAction(actionType, dir);
     

    //UserCommander
    else 
        setUserAction(actionType, dir);


    setActionByCombo(actionType, dir);
    

    MovingObject::setAction({ actionType, dir });
    setActiveDelay(true);
    setSpeed();
}


void Fighter::setComputerAction(ActionType& actionType, Direction& dir)
{
    Action action;
    if (m_target)
    {
        action = m_commander->getActionFromAlgo(this->getPosition(), m_target->getPosition());
        m_commander->setComputerCombo(this->getPosition(), m_target->getPosition());
    }

    else
        action = m_commander->setRandomAction();

    actionType = action.first;
    dir = action.second;
}


void Fighter::setUserAction(ActionType& actionType, Direction& dir)
{
    auto actions = m_commander->getAction();
    dir = setDir(actions.second);
    actionType = setActionTypeFromKeyboard(actions.first, dir);
}

void Fighter::setActionByCombo(ActionType& actionType, Direction& dir)
{
    m_combo = m_commander->getCombo();

    if (m_combo != ActionType::Standing && m_info->getMana() >= minimumManaMap.find(m_combo)->second)
    {
        actionType = nextActionComboMap.find(m_combo)->second;
        dir = Direction::Stay;
    }
    else
        m_combo = ActionType::Standing;

}


playerData Fighter::getPlayerData() const
{
    return m_playerData;
}

std::shared_ptr <CharacterInfo> Fighter::getInfo() const
{
    return m_info;
}

bool Fighter::isActiveDelayed() const
{
    return m_isActiveDelayed;
}

bool Fighter::isPasiveDelayed() const
{
    return m_isPasiveDelayed;
}



Direction Fighter::setDir(const std::vector <Direction>& directionsPressed) const
{
    auto dir = std::find_if (finalDirection.begin(), finalDirection.end(),
        [&](auto pair){return pair.first == directionsPressed;});


    if (dir != finalDirection.end())
        return dir->second;

    else return Direction::Stay;
    
}


ActionType Fighter::setActionTypeFromKeyboard(std::vector <ActionType>& actionsPressed, Direction& dir) const
{
    ActionType returnValue;
    if (!actionsPressed.empty())
        returnValue = actionsPressed.front();
    
    else
    {
        if (dir != Direction::Stay)
            returnValue = ActionType::Walking;
        
        else
            returnValue = ActionType::Standing;
    }

    if (returnValue == ActionType::Sprinting && dir == Direction::Stay)
            returnValue = ActionType::Standing;

    if (!canReapeatActionType.contains(returnValue))
    {
        dir = Direction::Stay;
        
        if (m_action.first == returnValue) //not good for game that last action is the same as next one
            returnValue = ActionType::Wait;
    }



    return returnValue;
}


void Fighter::setSpeed()
{
    m_speed = speedOfAction.find(m_action.first)->second * m_fighterSpeed;
}

void Fighter::setCombo(const ActionType combo)
{
    m_combo = combo;
}


void Fighter::draw(sf::RenderWindow& window) const
{
    m_info->draw(window);
    MovingObject::draw(window);
}


void Fighter::update(const sf::Time& delta)
{
    if (m_action.first == ActionType::Jump)
    {
        if (m_activeDelayClock.getElapsedTime().asSeconds() < m_activeDelayTime / 2)
        {
            m_action.second = firstStageJumpMap.find(m_action.second)->second;
        }
        else m_action.second = secondStageJumpMap.find(m_action.second)->second;
    }


    if (m_activeDelayClock.getElapsedTime().asSeconds() > m_activeDelayTime &&
        m_pasiveDelayClock.getElapsedTime().asSeconds() > m_pasiveDelayTime )
    {
        if (isGoingToDie())
            deathProcess();

        else if (nextActionComboMap.find(m_action.first) != nextActionComboMap.end())
        {
            m_action.first = nextActionComboMap.find(m_action.first)->second;
            setActiveDelay(true);
        }

        else
        {
            setActiveDelay(false);
            setPasiveDelay(false);
        }
        
        activateCombo();
    }     
  
    if (!isActiveDelayed() && !isPasiveDelayed())
    {
        if (auto commander = dynamic_cast<ComputerCommander*>(m_commander.get()))
        {
            if (m_target)
                if (m_target->isPasiveDelayed())
                    m_target.reset();

        }

        else
            m_commander->update();  //clear combo collector

    }


    m_info->update(delta);

    MovingObject::update(delta);

}

void Fighter::activateCombo()
{


    switch (m_combo)
    {
    case ActionType::ComboA:
        switch (m_playerData.m_fighter)
        {
        case Fighter_f::dennis_f:
        {
                m_dynamicAttack = std::make_shared<DennisBall>(TextureFacing(m_sprite), 
                                                    sf::Vector2f{ getPosition().x + sgn(m_sprite.getScale().x)* xOffsetDennisBall,
                                                                 getPosition().y + yOffsetDennisBall }, m_playerData, m_info->getScore());
                m_info->addMana(ballRemoveMana);
                m_commander->setCombo(ActionType::Standing);
                m_combo = ActionType::Standing;
         
        }
        break;
        case Fighter_f::firzen_f:
        {
            m_dynamicAttack = std::make_shared<FirzenBall>(TextureFacing(m_sprite), 
                                            sf::Vector2f{ getPosition().x + sgn(m_sprite.getScale().x)* xOffsetFirzenBall,
                                                            getPosition().y + yOffsetFirzenBall }, m_playerData, m_info->getScore());
            m_info->addMana(ballRemoveMana);
            m_commander->setCombo(ActionType::Standing);
            m_combo = ActionType::Standing;
            
        }
        break;
        default:  break;
        }

        break;
    
    case ActionType::ComboB:
        {
            m_dynamicAttack = std::make_shared<FireAttack>(getPosition(), m_playerData, m_info->getScore());
            m_info->addMana(explosionRemoveMana);
            m_commander->setCombo(ActionType::Standing);
            m_combo = ActionType::Standing;
        }
        break;

    case ActionType::ComboC:
    {
        m_dynamicAttack = std::make_shared<IceAttack>(sf::Vector2f {getPosition().x +xOffsetIceAttack, getPosition().y-yOffsetIceAttack}, m_playerData, m_info->getScore());
        m_info->addMana(explosionRemoveMana);
        m_commander->setCombo(ActionType::Standing);
        m_combo = ActionType::Standing;
    }
    break;
    default:  break;
    }
}


void Fighter::deathProcess()
{
    if (m_action.first == ActionType::DieBack)
        m_isDead = true;

    auto axion = m_action.first;
    m_action.first = nextActionMap.find(axion)->second;
    m_action.second = Direction::Stay;

    setPasiveDelay(true);
}


bool Fighter::isGoingToDie() const
{
    return m_info->getHealth() == noLife;
}



void Fighter::setInfoView(const float  xPosition)
{
    if (auto info = dynamic_cast<MainCharacterInfo*>(m_info.get()))
        return info->moveInfo(xPosition, 0);
    if (auto info = dynamic_cast<CharacterInfo*>(m_info.get()))
        return info->moveInfo(getPosition().x, getPosition().y);
}

void Fighter::addHealth(const float health)
{
    m_info->addHealth(health);
}

void Fighter::decHealth(const float health)
{
    addHealth(-health);
}


bool Fighter::isDead() const
{
    return m_isDead;
}

void Fighter::getActionFromKeyReleased(const sf::Keyboard::Key& keyReleased)
{
    if (auto commander = dynamic_cast<UserCommander*>(m_commander.get()))
    {
        commander->getActionFromKeyReleased(keyReleased);
    }
}

std::shared_ptr<DynamicAttack> Fighter::getDynamicAttacks()
{
    std::shared_ptr<DynamicAttack> temp = m_dynamicAttack;
    m_dynamicAttack.reset();
    return temp;
}


void Fighter::setTarget(const std::shared_ptr <Fighter> fighter)
{
    m_target = fighter;
}

void Fighter::addScore(const float score)
{
    m_info->addScore(score);
}