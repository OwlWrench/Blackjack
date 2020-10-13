#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

int getRandomNumber(int max);

int cardDraw(int max);
const int max = 13;

int houseDraw(int);
int house = 0; 

bool whoWins(bool bust);

int points;
bool houseturn;

int dosh = 100;
int housedosh = 100;

int victory = 0;

int main()
{
    srand(time(nullptr));

    bool gameover = 0;

    

    do
    {
        bool menu = 1;

        bool bettable = 0;
        int bet = 0;
        do
        {
            system("CLS");

            std::cout << "Your money: " << dosh << "$" << std::endl;
            std::cout << "The house money: " << housedosh << "$" << std::endl;

            
            std::cout << "How much money do you want to bet? (min 10$)" << std::endl;
            std::cin >> bet;

            if (bet > dosh)
            {
                std::cout << "You dont have enough to bet that much...";
                system("PAUSE");
            }
            else if (bet > housedosh)
            {
                std::cout << "The house can't bet as much as you. Bet lower.";
                system("PAUSE");
            }
            else if (bet < 10)
            {
                std::cout << "The house can't bet as much as you. Bet lower.";
                system("PAUSE");
            }
            else if (bet > 9)
            {
                bettable = 1;
            }

        } while (bettable == 0);

        system("CLS");
        std::cout << "You bet " << bet << "$. Good luck!" << std::endl;

        // round loop -----------------------------------------------
        do
        {
            char option = ' ';
            if (points != 0)
            {
                std::cout << "You currently have " << points << " points.\n" << std::endl;
            }
            std::cout << "What do you choose?" << std::endl;
            std::cout << "d: Draw a card" << std::endl;
            std::cout << "s: Stop drawing cards" << std::endl;
            std::cin >> option;

            system("CLS");

            switch (option)
            {
            case 'd':
                int card;
                card = cardDraw(max);

                points = points + card;

                break;
            case 's':
                std::cout << "You have " << points << " points." << std::endl;
                houseDraw(0);
                menu = 0;
                break;
            }

            if (points > 21)
            {
                std::cout << "Oh no\n" << points << " points.\n I'ts a bust..." << std::endl;
                system("Pause");
                system("CLS");
                points = -1;
                menu = 0;
                whoWins(0);

            }

            

        } while (menu == 1);
        // round loop over ------------------------------------------------------
        system("CLS");
        
        switch (victory)
        {
        case 0:
            std::cout << "the result was a draw. The money is returned." << std::endl;
            break;
        case 1:
            dosh = dosh + bet;
            housedosh = housedosh -bet;

            std::cout << "You won! You get the money!" << std::endl;
            break;
        case 2:
            dosh = dosh - bet;
            housedosh = housedosh + bet;

            std::cout << "You lost.. The house gets the money..." << std::endl;
            break;
        }

        if (dosh <= 10)
        {
            std::cout << "You dont have enough money... you lost." << std::endl;
            gameover = 1;
        }
        else if (housedosh <= 10)
        {
            std::cout << "The house can't bet anymore, wich means you won!" << std::endl;
            gameover = 1;
        }

        system("PAUSE");
        system("CLS");

    } while (gameover == 0);

}


int cardDraw(int max)
{
    int card = getRandomNumber(max);

    bool valid = 0;
    //add idividual cards
    switch (card)
    {
    case 1:
        //ace -----------

        do
        {
            if (houseturn == 1)
            {
                std::cout << "The house got an ace!" << std::endl;
                if (house < 12)
                {
                    std::cout << "The house wanted it to be a 10" << std::endl;
                    card = 10;
                    valid = 1;
                }
                else if (house > 11)
                {
                    std::cout << "The house wanted it to be a 1" << std::endl;
                    card = 1;
                    valid = 1;
                }
            }
            else
            {
                std::cout << "You got an Ace!\nYou want it to be a 1 or a 10?" << std::endl;
                int ace = 0;
                std::cin >> ace;
                if (ace == 1)
                {
                    std::cout << "The ace is now a 1" << std::endl;
                    card = 1;
                    valid = 1;
                }
                else if (ace == 10)
                {
                    std::cout << "The ace is now a 10" << std::endl;
                    card = 10;
                    valid = 1;
                }
                else
                {
                    system("CLS");
                    std::cout << "I said a 1 or a 10" << std::endl;
                }
            }

        } while (valid == 0);

        break;

    case 11:
        //knight ----------
        card = 10;
        if (houseturn == 1)
        {
            std::cout << "The house got a knight!" << std::endl;
        }
        else
        {
            std::cout << "You got a knight!" << std::endl;
        }
        
        break;
    case 12:
        //queen -----------
        card = 10;
        if (houseturn == 1)
        {
            std::cout << "The house got a queen!" << std::endl;
        }
        else
        {
            std::cout << "You got a queen!" << std::endl;
        }
        break;
    case 13:
        //King -----------
        card = 10;
        if (houseturn == 1)
        {
            std::cout << "The house got a king!" << std::endl;
        }
        else
        {
            std::cout << "You got a king!" << std::endl;
        }
        break;

    default:
        //any other card -----

        if (houseturn == 1)
        {
            std::cout << "The house picked " << card << std::endl;
        }
        else
        {
            std::cout << "You picked " << card << std::endl;
        }
        break;
    }


    return card;
}

int houseDraw(int)
{
    houseturn = 1;
    house = 0;
    std::cout << "Now the house will draw cards: " << std::endl;

    bool finished = 0;
    bool bustH = 0;
    do
    {
        if (house < points)
        {
            int card;
            card = cardDraw(max);
            house = house + card;
            
        }
        else if (house >= points && house <= 21)
        {

            finished = 1;
        }
        else if (house > 21)
        {
            bustH = 1;
            finished = 1;
        }
    } while (finished == 0);

    std::cout << "House has " << house << " total." << std::endl;

    whoWins(bustH);

    return 0;
}

bool whoWins(bool bust)
{
    // who wins ------------------------------
    if (points < house && bust == 0)
    {
        std::cout << "The house wins." << std::endl;
        victory = 2;
    }
    else if (points == house)
    {  
        std::cout << "It's a draw." << std::endl;
        victory = 0;
    }
    else if (house > 21)
    {
        std::cout << "The house bust! You win!" << std::endl;
        victory = 1;
    }

    system("PAUSE");

    house = 0;
    points = 0;
    houseturn = 0;

    return 0;
}

int getRandomNumber(int max)
{
    int randomNumber = rand() % max + 1;
    return randomNumber;
}
