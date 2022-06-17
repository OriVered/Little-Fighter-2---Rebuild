1. Little Fighters - project

=================================================
2.Written by: 
	Damian Tissembaum, id= 340888122, login= damianti
	Ori Vered,	   id = 315545400, login = orive

3.*********** General program description***********

This program is a rebuild of the game "Little Fighters 2"

The program create an interface using SFML graphics and sound
The first interface that appears in the screen is the four options that the user can pick:
3 options for playing: All vs All, Stage Mode, and Practice.
The option of help, that explains the game rules, and the keyboard controlls.

After picking an option for playing, the game goes to the Character Selection Mode, where the user picks a fighter to play with 
and other fighters to play against them or with them. The maximum ammount of players in a game are 6.

The goal of the All vs All mode is to be the only team that survives.
The goal of the Stage Mode is to kill all the enemies that appear in the game and reach the rightest part of the world.
The practice mode is a mode where the fighter does not die and the user can practice all the combos. 


The maximum ammounts of users that can play at the same time are two, one using the arrows keyboard (right side of keyboard),
and the other using the WASD to give direction to the fighter (left side of keyboard)

The game has not a timer so every game can last a lot of time of just a bit.

The goal of the game is to put the king in his throne in a period of time (shown in the window of the game).
In order to do that, the user will move the player with the arrows and will change the player that is playing by pressing 'p'

There are 4 fighters that can be used: Dennis, Firen, Firzen, Freeze. There is also the option of choosing a random fighter.
There is a small enemy called Bandit that appears in the stage mode and the player has to kill all of them to win the stage

Every Fighter has different attributes. Some of them have mor power on their hit, some of them has the abbility to throw a magic ball
All of them have the abbility to make an explosion that burns the other fighters and an iceberg that freeze the other fighters

    - Dennis: abbility to throw DennisBall, fast, regular punch
    - Firen:  abbility to throw FirzenBall, not fast, regular punch
    - Firzen: fast, hard punch
    - Freeze: fast, hard punch

Each fighter has life and manna:

If the life is 0, the fighter dies. 

The mana is used for special attacks, meaning that every special attack has a minimum ammount of mana to get actived.
The mana grows automatically for every fighter when the time pass by.

On the top part of the map, there is the information for every fighter, and it has:
    - The icon of the fighter.
    - The life remaining of the fighter represented by a red bar.
    - The mana remaining of the fighter represented by a blue bar.

In the game there also are Gifts: They will appear randomly on the board by random time as well. 
They will give to the fighter a random quantity of life

If the user press escape, the program goes back to the menu and the user can start the game from the beggining
If there is only one team remaining, the program will show the score of every fighter. The fighter gets score if it gets to take life from
another fighter. The ammount of life taken is the score given to the fighter.

4.*********** Design ***********
The design program is:

The hole program will be controlled and runned by an object of the class Controller. It starts the game and create an object of the class Menu
that polls the event created by the user. If the user picks the option Help, there is showed the rules of the game.
The other options are: All vs ALl, Stage Mode, Practice. All of them inherit from GameMode, and it inherits from State, a virtual class that has functions
to update and render events that occur on the window (the sf::RenderWindow is passed by reference when an object of this class (or that inherits from it) is
created).

When a GameMode is created, the program pass to the CharacterSelection (another class that inherits from State), where the user picks the fighters that will play
and select for everyone a team. There, the objects of the class Fighter are not created for saving memory. A function of this class CharacterSelection called choose()
(similar as run() in every class that mantains running while having a stretch contact with the user) returns a struct called playerData that has enums referring to the 
CommandType (who will be the commander: arrowUser, WASDUser or Computer), Fighter_f that referres to the fighter that will be played with, the playerNum and the team.
With this data, each GameMode creates all the fighters. 

After selecting the characters, the user will select the arena that the game will be played on. ArenaSelection also inherits from State. There are two Possible Arenas.

From here, explanation of the design of the game itself will be explained:

Inheritance:
    Fighter -> MovingObject -> GameObject -> ImageTexture -> Image
    (FireAttack, IceAttack, DennisBall, FirzenBall) -> DynamicAttack -> MovingObject -> GameObject -> ImageTexture -> Image


The object of GameMode (and the modes that inherit from it) has:
     -vector of shared_ptr of Fighters, 
     -vector of shared_ptr of DynamicAttack, 
     -vector of shared_ptr of CharacterInfo, 
     -vector of shared_ptr of LifeGift

Every Fighter has also a shared_ptr of CharacterInfo. The GameMode has all the shared_ptr of the CharacterInfo in that vector. That information is updated by the fighter,
and at the end of the game the GameMode use that same information to show the relevant data.

Every Fighter has a shared_ptr to the commander that controlls it. Strategy design pattern is used here:
The control of every action is done by a std::pair <ActionType, Direction>, called Action.
The fighter will setNextAction by RTTI. Meaning that if the Commander is a ComputerCommander, the computer will decide which is the next action
and if the Commander is a UserCommander, the user will decide which is the next action to be done.

Explanation of how the next action will be decided:


If the commander is a user (arrows or WASD):
The commander constantly controlls the fighter by sf::keyboard::isKeyPressed, 
passing by the two std::unoreded_map that have all the keys - sf::Keyboard::Key with their value - ActionType (for the first std::unorered_map)
                                                                                                 - Direction (for the second std::unorered_map)

These actions will be pushed back into a vector of ActionType and Direction and these will determine the Action. Most of the ActionTypes are done with the
direction of Standing, excepting Walking, Running, Jumping. 

There are another ActionTypes that are Combos (ComboA, ComboB, ComboC) and they are setted by sf::Event::KeyReleased. When a key is released and this key is
contained in the possible keys that can get a combo, the key is pushed back into a vector that contains the possibleCombo. The program checks if that vector
of keys is equal to the vector that means a combo. if it is, that combo is setted. If no combo was found, the m_combo (also an ActionType will be ActionType::Standing)
and the final Action won't be influenced by the combo. If a combo is found, the final ActionType will be determined by that combo.


If the commander is the computer:

Every Fighter has a std::shared_ptr called m_target. The computer will guide the fighter to be close enough to the
target. The target will always be the closest fighter that is not passivelyDelayed (will be explained later),
and it will always be from a different team. 
If the Fighter is close enough to the target, it will hit him and after that will go for a small period of time in order 
to get a better performance of the game.

Also, the computer from time to time (randomly) will activate a combo if it is close enough to its target (in the x axis because the combo runs by x axis)
The final Action will be determined by the combo if its not ActionType::Standing.


If the m_combo is a real combo, a DynamicAttack will be created afterwards. Every DynamicAttack has a pointer to the playerData representing the owner. The fighter
has a std::shared_ptr <DynamicAttack> where the DynamicAttack is putted after its creation.
After creating the DynamicAttack, the GameMode will check on every Fighter and if the shared_ptr <DynamicAttack> doesnt point to nullptr, it will take if from him
(in order to check all the collisions after)


After setting the next action, the characters are updated: Also their Animation (each ActionType has it own vector of sf::IntRect), and most of the ActionTypes have
a delayOfAction (sitted in an unoreded_map), while the Fighter is in delay (active or passive), it cannot set its next action. And there are some procedures that 
wont give the Fighter control of its next action again (for example dying). If the fighter is passivelyDelayed, it means that it has been attacked, so it cannot be
attacked again in that period (excepting the DynamicAttack, where it can attacked by it all the time). 
If the Fighter is activelyDelayed, it means that it is doing an ActionType from itself so it can be attacked

There are different of applications of view, depending on what GameMode is played:
If All vs All: the screen is not moved, the view is the same all the time
If StageMode: the screen is moved depending on the main Character (the arrow user)

In StageMode, enemies will be dropped in the game and the character will must kill them all in order to win the game.



5.***********  Files ***********


AllVsAllMode.cpp - The file that has the functions definition of the class AllVsAllMode (inherits from GameMode). 
        The main difference from the application of this class is that it has enemies, the characterSelection is different,
        and the view is different
AllVsAllMode.h - Signature of AllVsAllMode class and functions related to it


Animation.cpp - The file that has the function definitions of the class Animation, in charge of move the MovingObject
         with animations using a vector of sf::IntRect
Animation.h - Signature of Animation class and functions related to it


AnimationData.h - contains the struct AnimationData that has an only member of std::unordered_map of ActionType and 
        std::vector < sf::IntRect>


ArenaSelection.cpp - The file that has the functions definition of the class ArenaSelection (inherits from State).
         Class used by the user to choose the Arena that the game will be played on 
ArenaSelection.h - Signature of ArenaSelection class and functions related to it


Background.cpp -  The file that has the functions definition of the class Background - a base virtual class for the
        different background of the whole program 
Background.h -  Signature of Background class and functions related to it


CharacterInfo.cpp - The file that has the functions definition of the class CharacterInfo, a base class that contains the 
        basic information of the character
CharacterInfo.h -  Signature of CharacterInfo class and functions related to it        


CharacterSelection.cpp - The file that has the functions definition of the class CharacterSelection (inherits from State). This class 
        selects the characters that will play the game
CharacterSelection.h -  Signature of CharacterSelection class and functions related to it        


Collision.cpp - The file that has the functions definition of the class Collision. This class is used for the collission from all 
        the GameObjects of the game.
Collision.h -  Signature of Collision class and functions related to it        


Commander.cpp - The file that has the functions definition of the class Commander, a base virtual class that represents the
        commander of the Fighter
Commander.h -  Signature of Commander class and functions related to it        


ComputerCommander.cpp - The file that has the functions definition of the class ComputerCommander (inherits from Commander), its in charge 
        of commanding the Fighter using special algorithms to set the next action or the next combo of the Fighter
ComputerCommander.h -  Signature of ComputerCommander class and functions related to it        


Controller.cpp - The file that creates the Menu class that controls the game
Controller.h - Signature of Controller class and functions related to it


CWBackground.cpp -  The file that has the functions definition of the class CWBackground (meaning China Wall) (inherits from GameBackground).
        Is in charge of setting the background of the game with a ChinaWall beautiful picture
CWBackground.h - Signature of CWBackground class and functions related to it


DennisBall.cpp - The file that has the functions definition of the class DennisBall (inherits from DynamicAttack),
        it creates a ball that hurts every Fighter that collisions with it and it moves in x axis 
DennisBall.h - Signature of DennisBall class and functions related to it


DynamicAttack.cpp - The file that has the functions definition of the class DynamicAttack, a base virtual class that
        represents an object that a Fighter creates during the game.
DynamicAttack.h - Signature of DynamicAttack class and functions related to it


Fighter.cpp - The file that has the function definition of the class Fighter (the main GameObject of the program), (inherits from movingObject).
            It has a member from these classes or structs (or std::shared_ptr of it): PlayerData, Commander,  CharacterInfo, DynamicAttack
Fighter.h - Signature of Fighter class and functions related to it


FireAttack.cpp - The file that has the functions definition of the class FireAttack (inherits from DynamicAttack), it creates an
        explosion that burns every Fighter that collisions with it. It doesn't move.
FireAttack.h - Signature of FireAttack class and functions related to it


FirzenBall.cpp - The file that has the functions definition of the class FirzenBall (inherits from DynamicAttack),
        it creates a ball that hurts every Fighter that collisions with it and it moves in x axis 
FirzenBall.h - Signature of FirzenBall class and functions related to it

GameBackground.cpp -  The file that has the functions definition of the class GameBackground - a base virtual class (inherits from Background) for the
        different background of the game 
GameBackground.h -  Signature of GameBackground class and functions related to it


GameMode.cpp - The file that has the functions definition of the base class GameMode (inherits from State). 
        It controlls the game itself, has a vector of Fighters, DynamicAttacks and LifeGifts
GameMode.h - Signature of GameMode class and functions related to it


GameObject.cpp - The file that has the functions definition of the base class GameObject. This class represent the base class for every object that appears
        in the game. It inherits from ImageTexture                
GameObject.h - Signature of GameObject class and functions related to it


Help.cpp - The file that has the functions definition of the class Help(inherits from State). This class 
        shows the keys that the User can play with
Help.h -  Signature of Help class and functions related to it


IceAttack.cpp - The file that has the functions definition of the class IceAttack (inherits from DynamicAttack), it creates an
        iceberg that freeze every Fighter that collisions with it. It doesn't move.
IceAttack.h - Signature of IceAttack class and functions related to it


Image.h - Contains signature of base class Image and signature of functions related in it. This class only has the 
        functions that an ImageText and ImageTexture needs to work with the sf::Text, sf::Sprite (corresponding)
Image.cpp - nothing.


ImageText.cpp - The file that has the functions definition of the class ImageText (inherits from Image). Basicly it creates an sf::Text from an std::string
        and has functions to change it, locate it and else.
ImageText.h - Signature of ImageText class and functions related to it


ImageTexture.cpp - The file that has the functions definition of the base class ImageTexture (inherits from Image). Basicly it creates an sf::Sprite from an
        enum given, with a factor, and a position. It has functions to change it, locate it, draw it and else.
ImageText.h - Signature of ImageTexture class and functions related to it


LifeGift.cpp - The file that has the functions definition of the class LifeGift (inherits from GameObject). It gives
        life to every fighter that collides with it
LifeGift.h - Signature of LifeGift class and functions related to it

macros.h - has all the global and consts values that all the files use 


main.cpp - the main program Controller class is run


MainCharacterInfo.cpp - The file that has the functions definition of the class MainCharacterInfo (inherits from CharacterInfo) class that contains the 
        basic information of the mainCharacter
MainCharacterInfo.h -  Signature of MainCharacterInfo class and functions related to it


Menu.cpp - The file that has the functions definition of the class Menu. It has the buttons that the user can press
        at the beggining to choose which mode he wants to play.
Menu.h - Signature of Menu class and functions related to it


MenuBackground.cpp -  The file that has the functions definition of the class MenuBackground (inherits from Background).
        Is in charge of setting the background of the Menu
MenuBackground.h - Signature of MenuBackground class and functions related to it


MovingObject.cpp - The file has the functions definition of the class MovingObject (inherits from GameObject). This is an 
                intermediate class that has the functions related to the direction of the moving of the character
MovingObject.h - Signature of MovingObject class and functions related to it


ResourceManager.cpp - singatue for ResourcesManager and the functions of the Singleton DP
ResourceManager.h - The file that has the functions definition of the Singleton DP resourceManager


Score.cpp - The file that has the functions definition of the class Score. It Shows for every Player its final score
        depending on how many damage it has done to the other Fighters
Score.h -  Signature of Score class and functions related to it
        

SPBackground.cpp -  The file that has the functions definition of the class SPBackground (meaning Stanley Prison) (inherits from GameBackground).
        Is in charge of setting the background of the game with an old styled Prison with animations 
SPBackground.h - Signature of SPBackground class and functions related to it


StageMode.cpp - The file that has the functions definition of the class StageMode (inherits from GameMode). 
        The main difference from the application of this class is that it does not have enemies, the characterSelection is different,
        and the view is different (it moves depending on the position of the main character of the game)
StageMode.h - Signature of StageMode class and functions related to it


State.cpp - the file that contains the class State that is base class for every State of the game. It gets the sd::RenderWindow by reference and can update and
        render all the events that happen in that state
State.h -  Signature of State class and functions related to it

UserCommander.cpp - The file that has the functions definition of the class UserCommander (inherits from Commander), its in charge 
        of commanding the Fighter with the keyBoard
UserCommander.h -  Signature of UserCommander class and functions related to it        


Utilities.cpp -  The file that has the  implementation of general functions that are used by most of the other files.
Utilities.h -  The file that has the  definition of general functions that are used by most of the other files.



7. **********data structures***********

Using a lot of std::unordered_map in order to make searching efficient (O(1))

ComboData:  is a vector with 2 elements (one for every Keyboard). Every element is a vector of pairs. 
            The pair.left is a vector of the keys that has to be pressed one after the other
            and the pair.right is the combo that it gets


Using Singleton the program load all the textures/sounds/fonts into a vector or unordered_map of textures/sounds/fonts
so the loading is been done only once in the hole program



8. **********remarkable algorithms***********

Using Singleton (ResourceManager) we have been made the program an easier one to run because the
files are loaded to the program only once

Using Strategy design pattern on the Commander of the Fighter: Every fighter can have a different type of commander, so Strategy
enables selecting an algorithm at runtime. Instead of implementing a single algorithm directly, code receives run-time instructions 
as to which in a family of algorithms to use. In this case, two different algorithms - User or Computer

Using State design pattern on the different States that the program does.

Using Command design pattern in Menu: object is used to encapsulate all information needed to perform an action or trigger an event at a later time. 
This information includes the method name, the object that owns the method and values for the method parameters.


The difficulty of the game getting a good war, a playable. So the computer must not be too easy and not too difficult.
So every Fighter has a std::shared_ptr called m_target. The computer will guide the fighter to be close enough to the
target. The target will always be the closest fighter that is not passivelyDelayed (will be explained later),
and it will always be from a different team. 
If the Fighter is close enough to the target, it will hit him and after that will go for a small period of time in order 
to get a better performance of the game.
Also, the computer from time to time (randomly) will activate a combo if it is close enough to its target (in the x axis because the combo runs by x axis)
The final Action will be determined by the combo if its not ActionType::Standing.
computer algoritm for searching the target

Delay: There is active and passive delay. If a fighter is in active or passive delay, it cannot change the action that is doing right now. 
If it is in passive delay and another fighter hits him, it does not get hurt.

Combo: There are another ActionTypes that are Combos (ComboA, ComboB, ComboC) and they are setted by sf::Event::KeyReleased. 
When a key is released and this key is contained in the possible keys that can get a combo, the key is pushed back into a vector
that contains the possibleCombo. The program checks if that vector of keys is equal to the vector that means a combo. 
If it is, that combo is setted. If no combo was found, the m_combo (also an ActionType will be ActionType::Standing)
and the final Action won't be influenced by the combo. If a combo is found, the final ActionType will be determined by that combo.

multimethods: Handling collision with multimethods

most of searching has been done in unordered_map means O(1) on average

   
8. ******bugs******
The game starts with a really high animations speed.

9.*****comments*****
no comments
