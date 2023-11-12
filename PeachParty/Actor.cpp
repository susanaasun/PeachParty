#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

#include <string>
#include <iostream>
using namespace std;

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"


Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, int size, bool isAlive, StudentWorld* studentWorldPointer) : GraphObject(imageID, startX, startY, startDirection, depth, size), m_alive(true) ,studentWorldPointer(studentWorldPointer){
    
}

// void Actor::doSomething() const { cout << "Actor: " << endl; return;}
bool Actor::isAlive() {
    return m_alive;
}

StudentWorld* Actor::gettingWorld(){
    return studentWorldPointer;
}



Player::Player(int imageID, int startX, int startY, int player, StudentWorld* studentWorldPointer ) : Actor(imageID, startX, startY, right, 0, 1, true, studentWorldPointer), player(player), ticks_to_move(0), m_totalCoins(0), m_totalStars(0), m_waittoRoll(true), m_walkingState(false), m_moveDir(right){
    
}

Baddie::Baddie(int imageID, int startX, int startY, StudentWorld* studentWorldPointer) : Actor(imageID, startX, startY, right, 0, 1, true, studentWorldPointer){
    
}

void Baddie::doSomething(){return;}

//curr_player = this.player // checks if player 1 or 2
//if curr_player == 1 // Peach
//else if curr_player == 2 // Yoshi

void Player::doSomething(){
    cout << "Peach's turn " << m_waittoRoll << endl;

    if(m_waittoRoll){

        switch (gettingWorld()->getAction(player)){
            case ACTION_ROLL:
                int die_roll = randInt(1, 10);
                ticks_to_move = die_roll * 8;
                //cout << ticks_to_move;
                m_walkingState = true;
                m_waittoRoll = false;
                this->walk();

                break;  
        }
    }
    
    else if(m_walkingState){
        this->walk();
        //cout << ticks_to_move << endl;
    }
    
    // cout << "Coins: " << m_totalCoins << endl;
}


void Player::CoinSquareHandler(int x, int y){
    Board::GridEntry squareType = gettingWorld()->getBoard()->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT);
     cout << "squareType: " << squareType << endl;
    if(squareType == Board::GridEntry::blue_coin_square){
        m_totalCoins += 3;
        gettingWorld()->playSound(SOUND_GIVE_COIN);
    }
    else if(squareType == Board::GridEntry::red_coin_square){
        m_totalCoins -= 3;
        gettingWorld()->playSound(SOUND_TAKE_COIN);
    }
    else if(squareType == Board::GridEntry::star_square){
        if (m_totalCoins < 20){
            return;
        }
        else{
            m_totalCoins -= 20;
            m_totalStars += 1;
            gettingWorld()->playSound(SOUND_GIVE_STAR);
        }
    }
}


bool Actor::IsIntersection(int x, int y){
    int count = 0;
    
    int xnew = x, ynew = y;
    getPositionInThisDirection(up, 16, xnew, ynew);
    if (gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) != Board::GridEntry::empty) {
        count++;
    }
    xnew = x; ynew = y;
    getPositionInThisDirection(down, 16, xnew, ynew);
    if (gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) != Board::GridEntry::empty) {
        count++;
    }
    xnew = x; ynew = y;
    getPositionInThisDirection(right, 16, xnew, ynew);
    if (gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) != Board::GridEntry::empty) {
        count++;
    }
    xnew = x; ynew = y;
    getPositionInThisDirection(left, 16, xnew, ynew);
    if (gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) != Board::GridEntry::empty) {
        count++;
    }
        
    if (count > 2){
        return true;
        
    }
    return false;
}

void Player::walk(){
    int xnew, ynew;
    //round the getX and getY before getx()%16 == 0 and getY()%16 == 0
    if (getX() % 16 == 0 && getY() % 16 == 0 ){
        Board::GridEntry ge = gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT);
        if(ge == Board::GridEntry::up_dir_square || ge == Board::GridEntry::down_dir_square || ge == Board::GridEntry::left_dir_square || ge == Board::GridEntry::right_dir_square ){
            switch(ge){
                case 4:
                    if (ge == Board::GridEntry::up_dir_square) {
                        // check right
                        getPositionInThisDirection(up, 16, xnew, ynew);
                        if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                            setDirection(right);
                            m_moveDir = up;
                        }
                        // assume left is valid (if it isn't, board has a problem)
                        else{
                            setDirection(left);
                            m_moveDir = left;
                        }
                    }
                    break;
                case 5:
                    if (ge == Board::GridEntry::down_dir_square) {
                        // check right
                        getPositionInThisDirection(down, 16, xnew, ynew);
                        if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                            setDirection(right);
                            m_moveDir = down;
                        }
                        // assume left is valid (if it isn't, board has a problem)
                        else{
                            setDirection(left);
                            m_moveDir = down;
                        }
                    }
                    break;
                case 6:
                    if (ge == Board::GridEntry::left_dir_square) {
                        // check up
                        getPositionInThisDirection(left, 16, xnew, ynew);
                        if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                            setDirection(left);
                            m_moveDir = left;
                        }
                        // assume down is valid (if it isn't, board has a problem)
                        else{
                            setDirection(left);
                            m_moveDir = down;
                        }
                    }
                    break;
                case 7:
                    if (ge == Board::GridEntry::right_dir_square) {
                        // check up
                        getPositionInThisDirection(right, 16, xnew, ynew);
                        if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                            setDirection(right);
                            m_moveDir = right;
                        }
                        // assume down is valid (if it isn't, board has a problem)
                        else{
                            setDirection(left);
                            m_moveDir = down;
                        }
                    }
                    break;
            }
        }
        // Not a directional arrow, so needs to be a fork
        else if (IsIntersection(getX(), getY())){
            int action = gettingWorld()->getAction(player);
            switch (action)
            {
                case ACTION_RIGHT:
                    if (m_moveDir == left )
                        return;
                    setDirection(right);
                    m_moveDir = right;
                    break;
                case ACTION_LEFT:
                    if (m_moveDir == right || m_moveDir == down)
                        return;
                    setDirection(left);
                    m_moveDir = left;
                    break;
                case ACTION_UP:
                    if (m_moveDir == down || m_moveDir == right)
                        return;
                    
                    setDirection(right);
                    m_moveDir = up;
                    break;
                case ACTION_DOWN:
                    int xnew, ynew;
                    if (m_moveDir == up)
                        return;
                    
                    getPositionInThisDirection(down, 16, xnew, ynew);
                    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::empty){
                        return;
                    }
                    setDirection(right);
                    m_moveDir = down;
                    break;
                default:
                    return;
            }
        }
    }
    
//    int xnew, ynew;
    getPositionInThisDirection(m_moveDir, 16, xnew, ynew);
    
    if(ticks_to_move %8 != 0 || gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
        // Move valid
    }
    
    else{
        // Update direction because can't continue moving forward
        if (m_moveDir == up || m_moveDir == down) {
            // check right
            getPositionInThisDirection(right, 16, xnew, ynew);
            if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                setDirection(right); // sets the player facing direction
                m_moveDir = right; //moves the player in that direction
            }
            // assume left is valid (if it isn't, board has a problem)
            else{
                setDirection(left);
                m_moveDir = left;
            }
        }
        else if (m_moveDir == left || m_moveDir == right) {
            // check up
            getPositionInThisDirection(up, 16, xnew, ynew);
            if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                setDirection(right);
                m_moveDir = up;
            }
            // assume down is valid (if it isn't, board has a problem)
            else{
                setDirection(right);
                m_moveDir = down;
            }
        }
    }
    moveAtAngle(m_moveDir, 2);
  
    ticks_to_move--;
    if (ticks_to_move == 0){
        int x = getX();
        int y = getY();
        
        cout << "Handling coin " << endl;
        CoinSquareHandler(x, y);
        
//        int xnew, ynew;
//
//        getPositionInThisDirection(right, 16, xnew, ynew);
//        if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::blue_coin_square){
//            cout << "I am here" << endl;
//        }
        
        m_walkingState = false;
        m_waittoRoll = true;
        
    }
}

int Player::getPlayer(){
    return player;
}
void Player::setTicks(){
    ticks_to_move = 0;
}

int Player::getTicks(){
    return ticks_to_move;
}
int Player::getCoins() const{
    return m_totalCoins;
}
void Player::addCoins(int numberofCoins){
    m_totalCoins += numberofCoins;
}

void Player::addStars(int numberofStars){
    m_totalStars += numberofStars;
}

int Player::getStars() const{
    return m_totalStars;
}

bool Player::waittoRoll(){
    return true;
}

bool Player::getState(){
    return m_waittoRoll;
}

void Player::teleportHandler(int x, int y){
    moveTo(x, y);
}



Peach::Peach(int imageID, int startX, int startY, StudentWorld* studentWorldPointer) : Player(IID_PEACH, startX, startY, 1, studentWorldPointer){
    
}

Yoshi::Yoshi(int imageID, int startX, int startY, StudentWorld* studentWorldPointer) : Player(IID_YOSHI, startX, startY, 2, studentWorldPointer){
    
}

Bowser::Bowser(int imageID, int startX, int startY, StudentWorld* studentWorldPointer) : Baddie(IID_BOWSER, startX, startY, studentWorldPointer), m_BowserState(false), m_BowserCount(180), m_moveDir(right), ticks_to_move(0), squares_to_move(0){
    
}

void Bowser::doSomething(){
    cout << "Bowser's Turn " << m_BowserState << " " << m_BowserCount << endl;
    
    if (m_BowserState == false) {
        if(getX() == gettingWorld()->getPlayer(1)->getX() && getY() == gettingWorld()->getPlayer(1)->getY() && gettingWorld()->getPlayer(1)->getState()){
            int random = randInt(1, 10);
            if (random % 2 == 0){
                int numofCoins = gettingWorld()->getPlayer(1)->getCoins();
                gettingWorld()->getPlayer(1)->addCoins(numofCoins*-1);
                int numofStars = gettingWorld()->getPlayer(1)->getStars();
                gettingWorld()->getPlayer(1)->addStars(numofStars*-1);
                gettingWorld()->playSound(SOUND_BOWSER_ACTIVATE);
            }
        }
        
        if(getX() == gettingWorld()->getPlayer(2)->getX() && getY() == gettingWorld()->getPlayer(2)->getY() && gettingWorld()->getPlayer(2)->getState()){
            int random = randInt(1, 10);
            if (random % 2 == 0){
                int numofCoins = gettingWorld()->getPlayer(2)->getCoins();
                gettingWorld()->getPlayer(2)->addCoins(numofCoins*-1);
                int numofStars = gettingWorld()->getPlayer(2)->getStars();
                gettingWorld()->getPlayer(2)->addStars(numofStars*-1);
                gettingWorld()->playSound(SOUND_BOWSER_ACTIVATE);
            }
        }
        
        m_BowserCount--;
        
        if (m_BowserCount == 0) {
            squares_to_move = randInt(1, 10);
            ticks_to_move = squares_to_move * 8;
            int direction = randInt(0, 3) * 90;
            int xnew = getX();
            int ynew = getY();
            // cout << "Direction: " << direction << endl;
            getPositionInThisDirection(direction, 16, xnew, ynew);
            // cout << gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) << endl;
            while(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::empty){
                direction = randInt(0, 3) * 90;
                getPositionInThisDirection(direction, 16, xnew, ynew);
            }
            if (m_moveDir == left){
                setDirection(left);
            }
            else{
                setDirection(right);
            }
            m_BowserState = true;
        }
    }
    
    int xnew = getX(), ynew = getY();
    getPositionInThisDirection(m_moveDir, 16, xnew, ynew);
    
    // Walking state
    if (m_BowserState == true) {
        if(IsIntersection(getX(), getY())){
            int direction = randInt(0, 3) * 90;
            int xnew = getX();
            int ynew = getY();
            getPositionInThisDirection(direction, 16, xnew, ynew);
            while(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::empty){
                direction = randInt(0, 3) * 90;
                getPositionInThisDirection(direction, 16, xnew, ynew);
            }
            if (m_moveDir == left){
                setDirection(left);
            }
            else{
                setDirection(right);
            }
        }
        else if (gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::empty) {
            if (m_moveDir == up || m_moveDir == down) {
                // check right
                getPositionInThisDirection(right, 16, xnew, ynew);
                if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                    setDirection(right); // sets the player facing direction
                    m_moveDir = right; //moves the player in that direction
                }
                // assume left is valid (if it isn't, board has a problem)
                else{
                    setDirection(left);
                    m_moveDir = left;
                }
            }
            else if (m_moveDir == left || m_moveDir == right) {
                // check up
                getPositionInThisDirection(up, 16, xnew, ynew);
                if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                    setDirection(right);
                    m_moveDir = up;
                }
                // assume down is valid (if it isn't, board has a problem)
                else{
                    setDirection(right);
                    m_moveDir = down;
                }
            }
        }
        
        moveAtAngle(m_moveDir, 2);
        ticks_to_move--;
        if (ticks_to_move == 0){
            m_BowserState = false;
            m_BowserCount = 180;
            int chance = randInt(1, 4);
            if(chance == 1){
                //ask the studentworld to remove the square and add a dropping square
                gettingWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
            }
        }
    }
}

Boo::Boo(int imageID, int startX, int startY, StudentWorld* studentWorldPointer) : Baddie(IID_BOO, startX, startY, studentWorldPointer), m_BooState(false), m_BooCount(180){
    
}

void Boo::doSomething(){
    if(m_BooState == false){
        if(getX() == gettingWorld()->getPlayer(1)->getX() && getY() == gettingWorld()->getPlayer(1)->getY() && gettingWorld()->getPlayer(1)->getState()){
            int random = randInt(1, 3);
            switch (random){
                case 1:{
                    int player1Coins = gettingWorld()->getPlayer(1)->getCoins();
                    int player2Coins = gettingWorld()->getPlayer(2)->getCoins();
                    
                    player1Coins = player2Coins;
                    break;
                }
                case 2: {
                    int player1Stars = gettingWorld()->getPlayer(1)->getStars();
                    int player2Stars = gettingWorld()->getPlayer(2)->getStars();
                    player1Stars = player2Stars;
                    break;
                }
            }
            gettingWorld()->playSound(SOUND_BOO_ACTIVATE);
            m_BooCount--;
            if(m_BooCount == 0){
                squares_to_move = randInt(1, 3);
                ticks_to_move = squares_to_move * 8;
                int direction = randInt(0, 3) * 90;
                int xnew = getX();
                int ynew = getY();
                getPositionInThisDirection(direction, 16, xnew, ynew);
                while(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::empty){
                    direction = randInt(0, 3) * 90;
                    getPositionInThisDirection(direction, 16, xnew, ynew);
                }
                if (m_moveDir == left){
                    setDirection(left);
                }
                else{
                    setDirection(right);
                }
                m_BooState = true;
            }
        }
    }
    
    int xnew = getX(), ynew = getY();
    getPositionInThisDirection(m_moveDir, 16, xnew, ynew);
    if (m_BooState == true) {
        if(IsIntersection(getX(), getY())){
            int direction = randInt(0, 3) * 90;
            int xnew = getX();
            int ynew = getY();
            getPositionInThisDirection(direction, 16, xnew, ynew);
            while(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::empty){
                direction = randInt(0, 3) * 90;
                getPositionInThisDirection(direction, 16, xnew, ynew);
            }
            if (m_moveDir == left){
                setDirection(left);
            }
            else{
                setDirection(right);
            }
        }
        else if (gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::empty) {
            if (m_moveDir == up || m_moveDir == down) {
                // check right
                getPositionInThisDirection(right, 16, xnew, ynew);
                if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                    setDirection(right); // sets the player facing direction
                    m_moveDir = right; //moves the player in that direction
                }
                // assume left is valid (if it isn't, board has a problem)
                else{
                    setDirection(left);
                    m_moveDir = left;
                }
            }
            else if (m_moveDir == left || m_moveDir == right) {
                // check up
                getPositionInThisDirection(up, 16, xnew, ynew);
                if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT)){
                    setDirection(right);
                    m_moveDir = up;
                }
                // assume down is valid (if it isn't, board has a problem)
                else{
                    setDirection(right);
                    m_moveDir = down;
                }
                
            }
        }
        
        moveAtAngle(m_moveDir, 2);
        ticks_to_move--;
        if (ticks_to_move == 0){
            m_BooState = false;
            m_BooCount = 180;
        }
        
    }
}

Square::Square(int imageID, int startX, int startY, int startDirection, StudentWorld* studentWorldPointer) : Actor(imageID, startX, startY, startDirection, 1, 1, true, studentWorldPointer){
    
}

//check directions (x and y) if the player is on it
void Square::doSomething() { return; }

CoinSquare::CoinSquare(int startX, int startY, bool good, int startDirection, StudentWorld* studentWorldPointer) : Square(good ? IID_BLUE_COIN_SQUARE : IID_RED_COIN_SQUARE, startX, startY, startDirection, studentWorldPointer), goodgrant(good){
    
}

void CoinSquare::doSomething(){
    
    /*if (!isAlive()){
        return;
    }
    
    int peachX = gettingWorld()->getPlayer(1)->getX();
    int peachY = gettingWorld()->getPlayer(1)->getY();
    int peachTicks = gettingWorld()->getPlayer(1)->getTicks();
    int yoshiX = gettingWorld()->getPlayer(2)->getX();
    int yoshiY = gettingWorld()->getPlayer(2)->getY();
    int yoshiTicks = gettingWorld()->getPlayer(2)->getTicks();
    
    if (peachTicks == 0)
        cout << peachX << " " << peachY << " " << peachTicks << endl;
    
    if (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::blue_coin_square &&
        getX() == peachX && getY() == peachY && peachTicks == 0){
        
        cout << "\nBlue Coin Square\n";
        cout << peachX << " " << peachY << " " << peachTicks << endl;
        cout << "CoinX: " << getX() << " Coin Y: " << getY() << endl;
        
        gettingWorld()->getPlayer(1)->addCoins(3);
        gettingWorld()->playSound(SOUND_GIVE_COIN);
    }
    else if (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::red_coin_square &&
             getX() == peachX && getY() == peachY && peachTicks == 0){
        
        cout << peachX << " " << peachY << " " << peachTicks << endl;
        cout << "CoinX: " << getX() % 16 << " Coin Y: " << getY() % 16 << endl;
        
        gettingWorld()->getPlayer(1)->addCoins(-3);
        gettingWorld()->playSound(SOUND_TAKE_COIN);
    }
    
    if (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::blue_coin_square &&
        getX() == yoshiX && getY() == yoshiY && yoshiTicks == 0){
        cout << peachX << " " << peachY << " " << peachTicks << endl;
        cout << "CoinX: " << getX() % 16 << " Coin Y: " << getY() % 16 << endl;
        
        gettingWorld()->getPlayer(2)->addCoins(3);
        gettingWorld()->playSound(SOUND_GIVE_COIN);
    }
    else if (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::red_coin_square &&
             getX() == yoshiX && getY() == yoshiY && yoshiTicks == 0){
        
        cout << peachX << " " << peachY << " " << peachTicks << endl;
        cout << "CoinX: " << getX() % 16 << " Coin Y: " << getY() % 16 << endl;
        
        gettingWorld()->getPlayer(2)->addCoins(-3);
        gettingWorld()->playSound(SOUND_TAKE_COIN);
    }
    */
}

StarSquare::StarSquare(int startX, int startY, int startDirection, StudentWorld* studentWorldPointer) : Square(IID_STAR_SQUARE, startX, startY, right, studentWorldPointer){
    
}

void StarSquare::doSomething(){
    //int xnew, ynew;
    if (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::star_square && gettingWorld()->getPlayer(1)->getTicks() == 0){
        if(gettingWorld()->getPlayer(1)->getCoins() < 20){
            return;
        }
        else{
            gettingWorld()->getPlayer(1)->addCoins(-20);
            gettingWorld()->getPlayer(1)->addStars(1);
            gettingWorld()->playSound(SOUND_GIVE_STAR);
            cout << gettingWorld()->getPlayer(1)->getStars();
            
        }
    }
    
    else if (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::star_square && gettingWorld()->getPlayer(2)->getTicks() == 0){
        if(gettingWorld()->getPlayer(2)->getCoins() < 20){
            return;
        }
        else{
            gettingWorld()->getPlayer(2)->addCoins(-20);
            gettingWorld()->getPlayer(2)->addStars(1);
            gettingWorld()->playSound(SOUND_GIVE_STAR);
            cout << gettingWorld()->getPlayer(2)->getStars();
            
        }
    }
}

DirectionalSquare::DirectionalSquare(int startX, int startY, int m_dir, StudentWorld* studentWorldPointer) : Square(IID_DIR_SQUARE, startX, startY, m_dir, studentWorldPointer), m_dir(m_dir){
    
}

BankSquare::BankSquare(int startX, int startY, int startDirection, StudentWorld* studentWorldPointer) : Square(IID_BANK_SQUARE, startX, startY, right, studentWorldPointer){
    
}

void BankSquare::doSomething(){
    int xnew, ynew;
    if (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::bank_square){
        int bankBalance = gettingWorld()->returnBankBalance();
        gettingWorld()->getPlayer(1)->addCoins(bankBalance);
        gettingWorld()->setBankBalance(0);
        gettingWorld()->playSound(SOUND_WITHDRAW_BANK);
    }
    getPositionInThisDirection(up, 16, xnew, ynew);
    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::bank_square && gettingWorld()->getPlayer(1)){
        if (gettingWorld()->getPlayer(1)->getCoins() < 5){
            return;
        }
        gettingWorld()->getPlayer(1)->addCoins(-5);
        gettingWorld()->addBankBalance(5);
        gettingWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::bank_square && gettingWorld()->getPlayer(2)){
        if (gettingWorld()->getPlayer(2)->getCoins() < 5){
            return;
        }
        gettingWorld()->getPlayer(2)->addCoins(-5);
        gettingWorld()->addBankBalance(5);
        gettingWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    
    getPositionInThisDirection(down, 16, xnew, ynew);
    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::bank_square && gettingWorld()->getPlayer(1)){
        if (gettingWorld()->getPlayer(1)->getCoins() < 5){
            return;
        }
        gettingWorld()->getPlayer(1)->addCoins(-5);
        gettingWorld()->addBankBalance(5);
        gettingWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::bank_square && gettingWorld()->getPlayer(2)){
        if (gettingWorld()->getPlayer(2)->getCoins() < 5){
            return;
        }
        gettingWorld()->getPlayer(2)->addCoins(-5);
        gettingWorld()->addBankBalance(5);
        gettingWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    getPositionInThisDirection(right, 16, xnew, ynew);
    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::bank_square && gettingWorld()->getPlayer(1)){
        if (gettingWorld()->getPlayer(1)->getCoins() < 5){
            return;
        }
        gettingWorld()->getPlayer(1)->addCoins(-5);
        gettingWorld()->addBankBalance(5);
        gettingWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::bank_square && gettingWorld()->getPlayer(2)){
        if (gettingWorld()->getPlayer(2)->getCoins() < 5){
            return;
        }
        gettingWorld()->getPlayer(2)->addCoins(-5);
        gettingWorld()->addBankBalance(5);
        gettingWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    
    getPositionInThisDirection(left, 16, xnew, ynew);
    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::bank_square && gettingWorld()->getPlayer(1)){
        if (gettingWorld()->getPlayer(1)->getCoins() < 5){
            return;
        }
        gettingWorld()->getPlayer(1)->addCoins(-5);
        gettingWorld()->addBankBalance(5);
        gettingWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    if(gettingWorld()->getBoard()->getContentsOf(xnew/SPRITE_WIDTH, ynew/SPRITE_HEIGHT) == Board::GridEntry::bank_square && gettingWorld()->getPlayer(2)){
        if (gettingWorld()->getPlayer(2)->getCoins() < 5){
            return;
        }
        gettingWorld()->getPlayer(2)->addCoins(-5);
        gettingWorld()->addBankBalance(5);
        gettingWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    
    
}

EventSquare::EventSquare(int startX, int startY, int startDirection, StudentWorld* studentWorldPointer) : Square(IID_EVENT_SQUARE, startX, startY, right, studentWorldPointer){
    
}

void EventSquare::doSomething(){
    if (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::event_square){
        int randomEvent = randInt(1, 3);
        
        switch(randomEvent){
            case 1: {
                int randXCoord = randInt(0,15) * 16;
                int randYCoord = randInt(0,15) * 16;
                
                while (gettingWorld()->getBoard()->getContentsOf(getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT) == Board::GridEntry::empty)
                {
                    randXCoord = randInt(0,15) * 16;
                    randYCoord = randInt(0,15) * 16;
                }
                //gettingWorld()->getPlayer(0)->teleportHandler(<#int x#>, <#int y#>);
                //gettingWorld()->getPlayer(1)->moveTo(randYCoord, randYCoord);
                //moveTo(randXCoord, randYCoord);
            }
                // here, random coordinates should point to a valid square
                gettingWorld()->playSound(SOUND_PLAYER_TELEPORT);
                break;
            case 2: {
                gettingWorld()->playSound(SOUND_PLAYER_TELEPORT);
                break;
            }
            case 3: {
                gettingWorld()->playSound(SOUND_GIVE_VORTEX);
                break;
            }
        }
    }
}










