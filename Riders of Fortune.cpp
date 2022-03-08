// Mattia Iudean
// COP 2335
// Riders of Fortune, a text based fantasy style board game.

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include <conio.h>


using namespace std;

// initializing colors
HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

// constants

const int MAPSIZE = 28;
const int numWeapons = 5;
const int numEmptySpaces = 7;

// globals

bool gameOver = false;
bool gotChoice = false;
bool isMonster = false; 
bool isWeapon = false;
bool isEmpty = false;
bool isDragon = false;
bool gameWin = false;
bool startOfGame = true;
bool alreadyDismounted = true;
bool running = true;

// initializing player's starting stats

int futurePosition = 0;
int position = 0;
int playerAttack = 2;
int playerXP = 0;
std::string weapon = "Knife";

char Map[28] = { '0', 'm', 'm', 'm', 'm', 'm', 'm',
                 'm', 'm', 'm', 'm', 'm', 'm', 'm',
                 'm', 'm', 'm', 'm', 'm', 'm', 'm',
                 'm', 'm', 'm', 'm', 'm', 'm', 'D' };

/*  0 is starting/passed space
    m is monster space
    D is dragon space
    x is empty space    */

// function prototypes
void titleScreen();
void dismount();
void startPosition();
int randomNumber(int, int);
void printMap();
void assignEmptySpaces();
void assignWeapons();
void changePosition();
int getChoice();
void dragonBattle();
void endGame();
void help();

int main()
{
    // initializing random number generator
    srand(time(NULL));
    // assigning the empty spaces
    assignEmptySpaces();
    // assigning the weapons
    assignWeapons();
    // assign starting player position
    startPosition();
    // title screen
    titleScreen();
    // print the map
    printMap();

    while (running)
    {
        while (!gotChoice && position < 27)
        {
            // when gotChoice is false AND player's position is lower than 27,
            // they are presented with the options menu. i use the gotChoice throughout
            // the program to basically serve as a return command back to the beginning
            // of the while loop that deals with the menu.

            int choice = getChoice();

            switch (choice)
            {
            case 1:
                changePosition();
                break;

            case 2:
                dismount();
                break;

            case 3:
                help();
                break;

            }

            if (choice > 3 || choice < 1)
            {
                SetConsoleTextAttribute(screen, 12);

                cout << endl << "Invalid.\n";
                gotChoice = false;

                SetConsoleTextAttribute(screen, 7);

                printMap();
            }
        }
    }

    if (gameOver || gameWin)
    {
        endGame();
    }
}

int getChoice()
{
    int choice;

    cout << setw(2) << "\nYou have ";
    
    SetConsoleTextAttribute(screen, 14);
    
    cout << playerXP << " XP.\n";

    SetConsoleTextAttribute(screen, 7);

    cout << "Your current weapon is ";
    
    SetConsoleTextAttribute(screen, 11);
    
    cout << weapon;
    
    SetConsoleTextAttribute(screen, 7);
    
    cout << ".\nYou have ";

    SetConsoleTextAttribute(screen, 10);

    cout << playerAttack;

    SetConsoleTextAttribute(screen, 7);

    cout << " damage.\n\n";

    SetConsoleTextAttribute(screen, 5);

    cout << "Enter a number to make a choice:\n"
        << setw(2) << "1.";

    SetConsoleTextAttribute(screen, 7);

    cout << "Travel to another space on the board.\n";
    
    SetConsoleTextAttribute(screen, 5);

    cout << setw(2) << "2.";
    
    SetConsoleTextAttribute(screen, 7);
    
    cout << "Dismount and explore.\n";
     
    SetConsoleTextAttribute(screen, 5);

    cout << setw(2) << "3.";

    SetConsoleTextAttribute(screen, 7);

    cout << "Help.\n\n";

    cin >> choice;

    gotChoice = true;

    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
    
    return choice;

}

void titleScreen()
{
    cout << "/_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-/\n" << "v" << setw(90) << "v\n";

    cout << "v";
    
    SetConsoleTextAttribute(screen, 14); 
    
    cout << setw(40) << "WELCOME TO " << "RIDERS OF FORTUNE!";
    
    SetConsoleTextAttribute(screen, 7);
    
    cout << setw(32) << "v\n";

    cout << "v";
        
    SetConsoleTextAttribute(screen, 14); 
    
    cout << setw(80) << "You are Yarra, an adventurer on a journey through a perilous kingdom";
    
    SetConsoleTextAttribute(screen, 7); 
    
    cout << setw(10) << "v\n"
        << "v";
    
    SetConsoleTextAttribute(screen, 14); 
    
    cout << setw(75) << "seeking to slay a dragon & claim the Chalice of Knowledge!";
    
    SetConsoleTextAttribute(screen, 7); 
    
    cout << setw(15) << "v\n"
        << "v";

    SetConsoleTextAttribute(screen, 7);

    cout << setw(90) << "v\n" << "/_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-/\n\n"
            << setw(5) << "Press ANY KEY to begin your adventure...\n\n";

    _getch();
}

int randomNumber(int low, int high)
{
    // random number generator

    return (rand() % (high - low + 1)) + low;
}

void assignEmptySpaces()
{   
    // for loop iterates 7 times (as there are 7 empty spaces), assigning an empty
    // space only on monster spaces.

    for (int count = 0; count < numEmptySpaces; count++) 
    {   // random number between 2 and 27
        int random = randomNumber(1, 26);   
        bool assigned = false;
        while (!assigned)
        {
            if (Map[random] == 'm')
            {
                assigned = true;
                Map[random] = 'x';
            }

            else
                random = randomNumber(2, 27);
        }
    }
}

void assignWeapons()
{   
    // logic to assign weapons

    bool crossBowAssigned = false;
    bool flailAssigned = false;
    bool broadSwordAssigned = false;
    bool dragonAssigned = false;
    bool spellOfGodsAssigned = false;

    /* letter assignment:
    crossbow = C
    flail = F
    broadsword = B
    dragon slayer = G
    spell of gods = S */

    for (int count = 0; count < numWeapons; count++)
    {
        // random space between 2 and 27

        int random = randomNumber(1, 26);

        bool assigned = false;
        while (!assigned)
        { 
            // we assign a weapon to a random monster space

            if (Map[random] == 'm')
            {
                assigned = true;

                if (!crossBowAssigned)
                {
                    Map[random] = 'C';
                    crossBowAssigned = true;
                }

                else if (!flailAssigned)
                {
                    Map[random] = 'F';
                    flailAssigned = true;
                }

                else if (!broadSwordAssigned)
                {
                    Map[random] = 'B';
                    broadSwordAssigned = true;
                }

                else if (!dragonAssigned)
                {
                    Map[random] = 'G';
                    dragonAssigned = true;
                }

                else if (!spellOfGodsAssigned)
                {
                    Map[random] = 'S';
                    spellOfGodsAssigned = true;
                }
            }

            else
            {
                random = randomNumber(1, 26);
            }
        }
    }
}

void startPosition()
{
    while (startOfGame)
    {
        Map[0] = 'P';
        startOfGame = false;
    }
}

void changePosition()
{
    // roll a d6 to find spaces to move, then create variable futurePosition to hold the data before the move.
    // based on what character is in the spot player will move to, initiate interactions.

    int spacesToMove = randomNumber(1, 6);
    int futurePlayerAttack = 0;
    alreadyDismounted = false;

    Map[0] = '0';

    SetConsoleTextAttribute(screen, 9);

    cout << "\n" << "Rolled a " << spacesToMove << "\n\n";

    SetConsoleTextAttribute(screen, 7);

    futurePosition = spacesToMove + position;

    if (Map[futurePosition] == 'm')
    {
        SetConsoleTextAttribute(screen, 12);

        cout << "You've encountered a monster! Dismount to fight.\n\n";

        SetConsoleTextAttribute(screen, 7);

        isMonster = true;
        gotChoice = false;
    }

    else if (Map[futurePosition] == 'x')
    {
        isEmpty = true;
        gotChoice = false;
    }

    // following is the code to assign the player's weapon. i chose to go with the simple route of just 
    // tweaking the attack and the string that holds the name of the weapon. the playerAttack will be used in combat
    // to be added to the player's roll. added in interactions for when the weapon is not better than what the player
    // already has.

    else if (Map[futurePosition] == 'C')
    {
        futurePlayerAttack = 3;

        if (futurePlayerAttack > playerAttack)
        {
            weapon = "Crossbow";

            SetConsoleTextAttribute(screen, 11);

            cout << "You equip the Crossbow.\n\n";

            SetConsoleTextAttribute(screen, 7);

            playerAttack = 3;

            alreadyDismounted = true;
        }

        else
        {

            SetConsoleTextAttribute(screen, 11);

            cout << "You see a discarded Crossbow on the side of the road, but it is no match for your " << weapon << ".\n\n";

            SetConsoleTextAttribute(screen, 7);

            alreadyDismounted = true;
        }


    }

    else if (Map[futurePosition] == 'F')
    {
        futurePlayerAttack = 4;

        if (futurePlayerAttack > playerAttack)
        {
            weapon = "Flail";

            SetConsoleTextAttribute(screen, 11);

            cout << "You equip the Flail.\n\n";

            SetConsoleTextAttribute(screen, 7);

            playerAttack = 4;

            alreadyDismounted = true;
        }

        else
        {
            SetConsoleTextAttribute(screen, 11);

            cout << "You see a discarded Flail on the side of the road, but it is no match for your " << weapon << ".\n\n";

            SetConsoleTextAttribute(screen, 7);

            alreadyDismounted = true;
        }
    }

    else if (Map[futurePosition] == 'B')
    {
        futurePlayerAttack = 5;

        if (futurePlayerAttack > playerAttack)
        {
            weapon = "Broadsword";

            SetConsoleTextAttribute(screen, 11);

            cout << "You equip the Broadsword.\n\n";

            SetConsoleTextAttribute(screen, 11);

            playerAttack = 5;

            alreadyDismounted = true;
        }

        else
        {
            SetConsoleTextAttribute(screen, 11);

            cout << "You see a discarded Broadsword on the side of the road, but it is no match for your " << weapon << ".\n\n";

            SetConsoleTextAttribute(screen, 7);

            alreadyDismounted = true;
        }

    }

    else if (Map[futurePosition] == 'G')
    {
        futurePlayerAttack = 6;

        if (futurePlayerAttack > playerAttack)
        {
            weapon = "Dragon Slayer";

            SetConsoleTextAttribute(screen, 11);

            cout << "You equip the Dragon Slayer.\n\n";

            SetConsoleTextAttribute(screen, 7);

            playerAttack = 6;

            alreadyDismounted = true;
        }

        else
        {
            SetConsoleTextAttribute(screen, 11);

            cout << "You see a discarded Dragon Slayer on the side of the road, but it is no match for your " << weapon << ".\n\n";

            SetConsoleTextAttribute(screen, 7);

            alreadyDismounted = true;
        }

    }

    else if (Map[futurePosition] == 'S')
    {
        futurePlayerAttack = 7;

        if (futurePlayerAttack > playerAttack)
        {
            weapon = "Spell of the Gods";

            SetConsoleTextAttribute(screen, 11);

            cout << "You equip the Spell of the Gods.\n\n";

            SetConsoleTextAttribute(screen, 7);

            playerAttack = 7;

            alreadyDismounted = true;
        }

        else
        {
            SetConsoleTextAttribute(screen, 11);

            cout << "You see a discarded Spell of the Gods on the side of the road, but it is no match for your " << weapon << ".\n\n";

            SetConsoleTextAttribute(screen, 7);

            alreadyDismounted = true;
        }

    }

    SetConsoleTextAttribute(screen, 7);

    if (futurePosition < 27)
    {
        // player's old position is displayed as 0 on the map.
        // the player's new position is calculated and assigned 'P,' then map is printed.

        Map[position] = '0';

        position += spacesToMove;

        Map[position] = 'P';

        printMap();

        gotChoice = false;
    }

    else if (futurePosition >= 27)
    {
        // prevents player from going out of bounds.

        Map[position] = '0';

        position = 27;

        Map[position] = 'P';

        dragonBattle();
    }
}
void printMap()
{
    for (int count = 0; count < MAPSIZE; count++)
    {
        if (Map[count] == 'm')
        {
            SetConsoleTextAttribute(screen, 12);
        }

        else if (Map[count] == 'x')
        {
            SetConsoleTextAttribute(screen, 8);
        }

        else if (Map[count] == 'P')
        {
            SetConsoleTextAttribute(screen, 10);
        }

        else if (Map[count] == 'D')
        {
            SetConsoleTextAttribute(screen, 4);
        }

        else if (Map[count] == 'C' || Map[count] == 'F' || Map[count] == 'B' || Map[count] == 'G' || Map[count] == 'S')
        {
            SetConsoleTextAttribute(screen, 11);
        }

        cout << setw(2) << Map[count];

        SetConsoleTextAttribute(screen, 7);
    }

    cout << endl;
}

void dismount()
{
    // here we see the use of the isMonster, isWeapon, etc boolean. i use it to determine
    // which of the if statements executes, and encapsulate it all in the dismount() function.

    if (alreadyDismounted)
    {
        // this prevents the program from getting stuck when the player has already dismounted
        // or is on a weapon space/just began the game

        cout << "\nYou've already dismounted!\n\n";

        gotChoice = false;
    }

    else
    {
        if (isMonster)
        {
            // this is the combat mechanic. displays weapon, monster HP (which is decided by rolling a d6),
            // the amount the player rolled, the attack from their weapon, and their total damage. through the use of an if loop,
            // the program decides whether the player has won or not.

            int damage;
            int damageRoll = randomNumber(1, 6);
            int monsterHP = randomNumber(2, 7);

            cout << endl << "You dismount your horse and ready your ";
            
            SetConsoleTextAttribute(screen, 11);
            
            cout << weapon << ".\n";
            
            SetConsoleTextAttribute(screen, 7);

            cout << "Monster has ";
            
            SetConsoleTextAttribute(screen, 12);
            
            cout << monsterHP;
            
            SetConsoleTextAttribute(screen, 7);
                
            cout << " HP.\n" << "You rolled ";
            
            SetConsoleTextAttribute(screen, 9);
            
            cout << damageRoll;
            
            SetConsoleTextAttribute(screen, 7);

            cout << ", and your weapon grants you ";
            
            SetConsoleTextAttribute(screen, 2);

            cout << playerAttack;

            SetConsoleTextAttribute(screen, 7);

            cout << " damage.\n\n";

            damage = damageRoll + playerAttack;

            cout << setw(4) << "You attack for a total of ";

            SetConsoleTextAttribute(screen, 2);

            cout << damage;

            SetConsoleTextAttribute(screen, 7);

            cout << " damage.\n\n";
            
            SetConsoleTextAttribute(screen, 7); 

            if (damage >= monsterHP)
            {
                playerXP += 2;

                SetConsoleTextAttribute(screen, 10);

                cout << "You have slain your foe!\n";
                
                SetConsoleTextAttribute(screen, 7);
                
                cout << "You gained";

                SetConsoleTextAttribute(screen, 14);

                cout << " 2 XP.\n";

                SetConsoleTextAttribute(screen, 7);
                
                cout << "You now have ";
                
                SetConsoleTextAttribute(screen, 14);
                    
                cout << playerXP << " XP.\n";
                
                SetConsoleTextAttribute(screen, 7);

                cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";

                printMap();
                gotChoice = false;
                isMonster = false;
                alreadyDismounted = true;
            }

            else
            {
                cout << "\n" << "Despite your best efforts, you are unable to best your opponent.\n\n";

                gameOver = true;   

                endGame();
            }
        }

        else if (isEmpty)
        {
            cout << "\n" << "There is nothing for you to do,\nso you reflect upon your adventures thus far.\n"
                << "You take the time to train and enhance your reflexes.\n";

            SetConsoleTextAttribute(screen, 14);

            cout << "+1 EXP.\n";

            SetConsoleTextAttribute(screen, 7);

            cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";

            playerXP += 1;

            printMap();
            gotChoice = false;
            alreadyDismounted = true;
        }
    }
}

void dragonBattle()
{
    if (playerXP >= 5)
    {
        // the dragon battle is not too different from the monster battle except the HP is already
        // decided, and it only triggers if the player has at least 5 XP. otherwise, it results in game over.

        int dragonHP = 10;
        int damageRoll = randomNumber(1, 6);
        int damage = damageRoll + playerAttack;

        printMap();

        cout << "\nYou enter through the mouth of the cave leading to the dragon's den.\n"
            << "Something stirs from deep within the darkness, and suddenly--\n";

        gotChoice = false;

        cout << endl << "The DRAGON approaches you and ready your ";

        SetConsoleTextAttribute(screen, 14);

        cout << weapon << ".\n";

        SetConsoleTextAttribute(screen, 7);

        cout << "DRAGON has ";

        SetConsoleTextAttribute(screen, 12);

        cout << dragonHP;

        SetConsoleTextAttribute(screen, 7);

        cout << " HP.\n" << "You rolled ";

        SetConsoleTextAttribute(screen, 9);

        cout << damageRoll;

        SetConsoleTextAttribute(screen, 7);

        cout << ", and your weapon grants you ";

        SetConsoleTextAttribute(screen, 2);

        cout << playerAttack;

        SetConsoleTextAttribute(screen, 7);

        cout << " damage.\n\n";

        damage = damageRoll + playerAttack;

        cout << setw(4) << "You attack for a total of ";

        SetConsoleTextAttribute(screen, 12);

        cout << damage;

        SetConsoleTextAttribute(screen, 7);

        cout << " damage.\n\n";

        if (damage >= dragonHP)
        {
            SetConsoleTextAttribute(screen, 10);

            cout << "Due to your cunning and experience, you have defeated the deadly DRAGON.\n" << "Your quest has ended, good sir. "
                << "You've obtained the Chalice of Knowledge and all of Earth's mysteries are revealed.";

            SetConsoleTextAttribute(screen, 7);

            gameWin = true;
            endGame();
        }

        else
        {
            // failed to kill the dragon first try

            SetConsoleTextAttribute(screen, 12);

            cout << "You've come a long way, and yet it is still not enough to defeat the dragon.\n"
                << "Flames wash over you, and everything goes black.";

            SetConsoleTextAttribute(screen, 7);

            gameOver = true;
            endGame();
        }
    }

    else
    {
        // didn't have enough XP

        printMap();

        cout << "\nAlas, the dragon's eyes stare at you and places you under his spell.\n" <<
            "You try to move but fail to do so and find yourself torched by the dragon's fire.\n\n"
            << "If only you had more experience, you could have seen it coming.";

        gameOver = true;
        endGame();
    }
}

void endGame()
{
    // just a simple endgame menu to be shown either after the player dies or beats the dragon

    if (gameWin)
    {
        cout << setw(4) << "\n\nCongratulations, Yarra! You have defeated the dragon and won the game!\n\n"
            << "Restart game to try again...\n\n";
    }

    else
    {
        cout << setw(4) << "\n\nYou've fought valiantly, Yarra, yet you have been overcome by your enemies.\n\n"
            << "Restart game to try again...\n\n";
    }
}

void help()
{
    cout << "\nThe various letters represent different things:\n"
        << setw(4) << "P = player\n"
        << setw(4) << "D = dragon\n"
        << setw(4) << "x = empty space\n"
        << "You choose your action every turn, and roll a die for movement. You roll a die when fighting enemies.\n"
        << "Your weapon's damage is added to your roll as a modifier. If your damage is not higher than the monster's health,\nyou die.\n\n"
        << "Reach the dragon and beat him to win the game, but beware: if you have less than 5 XP, you automatically lose.\n"
        << "Earn XP by fighting monsters and dismounting on empty spaces.\nEvery time you pass by a weapon with higher attack than yours,\n"
        << "it is automatically equipped. If not, you leave it there.\n\n"
        << "Good luck!\n"
        << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";

    gotChoice = false;

}
