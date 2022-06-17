#include "Collision.h"

namespace
{
    void playerVsEnemy(GameObject& obj1, GameObject& boj2)
    {
        auto& player = static_cast<Fighter&>(obj1);
        auto& enemy = static_cast<Fighter&>(boj2);

        punchCollision(player, enemy);
        punchCollision(enemy, player);
    }
    void dynamicAttackFighter(GameObject& dynamicAttack, GameObject& enemy)
    {
        auto& attack = static_cast<DynamicAttack&>(dynamicAttack);
        auto& obj = static_cast<Fighter&>(enemy);

        //if dead/ or itself
        if (obj.isDead() || attack.isDone() || 
            (obj.getPlayerData().team == attack.getOwner().team && obj.getPlayerData().team != Team::Independent) ||
            obj.getPlayerData().playerNum == attack.getOwner().playerNum ||
            obj.isPasiveDelayed())
            return;

        obj.setActionType(ActionType::Beated);
        attack.setActionType(ActionType::Explosion);
        obj.setPasiveDelay(true);
        //check delay
        obj.decHealth(attack.getDmg());
        attack.addScore(attack.getDmg());
        ResourceManager::instance().playSFX(Type_s::firenBallExplosion);
        //pasive actoin to enemy actiontype::shoted
    }
    void fighterDynamicAttack(GameObject& fighter, GameObject& dynamicAttack)
    {
        dynamicAttackFighter(dynamicAttack, fighter);
    }

    void fireAttackFighter(GameObject& fireAttack, GameObject& enemy)
    {
        auto& attack = static_cast<FireAttack&>(fireAttack);
        auto& obj = static_cast<Fighter&>(enemy);

        //if dead/ or itself
        if (obj.isDead() || attack.isDone() || 
            (obj.getPlayerData().team == attack.getOwner().team &&  obj.getPlayerData().team != Team::Independent)||
            obj.getPlayerData().playerNum == attack.getOwner().playerNum ||
            obj.isPasiveDelayed())
            return;

        obj.setActionType(ActionType::OnFire);
        Direction dir;
        if (obj.getPosition().x - attack.getPosition().x < 0)
            dir = Direction::Right;

        else dir = Direction::Left;

        obj.setDirection(dir);
        obj.setPasiveDelay(true);
        //check delay
        obj.decHealth(attack.getDmg());
        attack.addScore(attack.getDmg());
        ResourceManager::instance().playSFX(Type_s::burningMan);
        //pasive actoin to enemy actiontype::shoted
    }
    
    void fighterFireAttack(GameObject& fighter, GameObject& fireAttack)
    {
        fireAttackFighter(fireAttack, fighter);
    }

    void iceAttackFighter(GameObject& iceAttack, GameObject& enemy)
    {
        auto& attack = static_cast<IceAttack&>(iceAttack);
        auto& obj = static_cast<Fighter&>(enemy);

        //if dead/ or itself
        if (obj.isDead() || attack.isDone() || 
            (obj.getPlayerData().team == attack.getOwner().team &&  obj.getPlayerData().team != Team::Independent) ||
            obj.getPlayerData().playerNum == attack.getOwner().playerNum ||
            obj.isPasiveDelayed())
            return;

        obj.setActionType(ActionType::OnFire);
        Direction dir;
        if (obj.getPosition().x - attack.getPosition().x < 0)
            dir = Direction::Right;

        else dir = Direction::Left;
        obj.setPasiveDelay(true);
        obj.decHealth(attack.getDmg());
        attack.addScore(attack.getDmg());

        
    }
    void fighterIceAttack(GameObject& fighter, GameObject& iceAttack)
    {
        fireAttackFighter(iceAttack, fighter);
    }

     void giftAndFighter(GameObject& gift, GameObject& fighter)
    {
        auto& theGift = static_cast<LifeGift&>(gift);
        auto& player = static_cast<Fighter&>(fighter);

        //if dead/ or itself
        if (player.isDead() || theGift.isDone())
            return;

        player.addHealth(float (theGift.getLife()));
        theGift.setDone();
        ResourceManager::instance().playSFX(Type_s::giftDeleteSound);
    }
    


    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(Fighter), typeid(Fighter))] = &playerVsEnemy;
        phm[Key(typeid(DennisBall), typeid(Fighter))] = &dynamicAttackFighter;
        phm[Key(typeid(Fighter), typeid(DennisBall))] = &fighterDynamicAttack;

        phm[Key(typeid(FireAttack), typeid(Fighter))] = &fireAttackFighter;
        phm[Key(typeid(Fighter), typeid(FireAttack))] = &fighterFireAttack;

        phm[Key(typeid(IceAttack), typeid(Fighter))] = &iceAttackFighter;
        phm[Key(typeid(Fighter), typeid(IceAttack))] = &fighterIceAttack;

        phm[Key(typeid(FirzenBall), typeid(Fighter))] = &dynamicAttackFighter;
        phm[Key(typeid(Fighter), typeid(FirzenBall))] = &fighterDynamicAttack;

        phm[Key(typeid(LifeGift), typeid(Fighter))] = &giftAndFighter;
        


        return phm;
    }
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }
}
void processCollision(GameObject& obj1, GameObject& obj2)
{
    auto phf = lookup(typeid(obj1), typeid(obj2));
    if (!phf)   // collision is irrelevent between two objects 
    {
        return;
    }
    phf(obj1, obj2);
}

void punchCollision(Fighter& fighter, Fighter& enemy)
{
    if (fighter.isDead() && &fighter == &enemy ||
    (fighter.getPlayerData().team == enemy.getPlayerData().team &&  fighter.getPlayerData().team != Team::Independent)||
    fighter.getPlayerData().playerNum == enemy.getPlayerData().playerNum ||
    enemy.isPasiveDelayed())
        return;

    if (fighter.getAction() == ActionType::Punching && !enemy.isPasiveDelayed() && enemy.getAction() != ActionType::Defend) // add delay time to 
    {
        auto damage = punchPower.find(fighter.getPlayerData().m_fighter)->second;
        enemy.setActionType(ActionType::Beated);
        enemy.setPasiveDelay(true);
        enemy.decHealth(damage);
        fighter.addScore(damage);
        ResourceManager::instance().playSFX(Type_s::punchHitSound);
    }
}