#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, int size, bool isAlive, StudentWorld* studentWorldPointer);
    
    virtual void doSomething() = 0;
    virtual bool isAlive();
    bool IsIntersection(int x, int y);
    
    
    StudentWorld* gettingWorld();
    
    
    
private:
    StudentWorld* studentWorldPointer;
    bool m_alive = true;
    int y; // x:startX, y:startY, direction:startDirection
    int x;
    int direction;
};

class Player: public Actor
{
public:
    Player(int imageID, int startX, int startY, int player, StudentWorld* studentWorldPointer);
    
    virtual void doSomething();
    virtual int getPlayer();
    virtual int getTicks();
    virtual void setTicks();
    virtual int getCoins() const;
    virtual int getStars() const;
    virtual void addCoins(int numberofCoins);
    virtual void addStars(int numberofStars);
    void CoinSquareHandler(int x, int y);
    virtual bool waittoRoll();
    bool getState();
    void walk();
    void teleportHandler(int x, int y);
    
private:
    int player;
    int ticks_to_move;
    int m_totalCoins;
    int m_totalStars;
    int m_moveDir;
    bool m_waittoRoll;
    bool m_walkingState;
    
};

class Baddie: public Actor
{
    public:
    Baddie(int imageID, int startX, int startY, StudentWorld* studentWorldPointer);
    virtual void doSomething() = 0;

    
};

class Bowser: public Baddie
{
    public:
    Bowser(int imageID, int startX, int startY, StudentWorld* studentWorldPointer);
    virtual void doSomething();
    
    private:
    bool m_BowserState;
    int m_BowserCount;
    int squares_to_move;
    int ticks_to_move;
    int m_moveDir;
};

class Boo: public Baddie
{
    public:
    Boo(int imageID, int startX, int startY, StudentWorld* studentWorldPointer);
    virtual void doSomething();
    
    private:
    bool m_BooState;
    int m_BooCount;
    int squares_to_move;
    int ticks_to_move;
    int m_moveDir;
};

class Peach: public Player
{
public:
    Peach(int imageID, int startX, int startY, StudentWorld* studentWorldPointer);
    
    
};

class Yoshi: public Player
{
public:
    Yoshi(int imageID, int startX, int startY, StudentWorld* studentWorldPointer);
    //virtual void doSomething();
};


class Square : public Actor{
    
public:
    Square(int imageID, int startX, int startY, int startDirection, StudentWorld* studentWorldPointer);
    
    virtual void doSomething();
};

class CoinSquare: public Square{
    
public:
    CoinSquare(int startX, int startY, bool good, int startDirection, StudentWorld* studentWorldPointer);
    
    virtual void doSomething();
    
    
private:
    bool goodgrant;
    
};

class StarSquare: public Square{
    
    public:
    StarSquare(int startX, int startY, int startDirection, StudentWorld* studentWorldPointer);
    virtual void doSomething();
};

class DirectionalSquare: public Square{
    public:
    DirectionalSquare(int startX, int startY, int m_dir, StudentWorld* studentWorldPointer);
    
    private:
        int m_dir;
};

class BankSquare: public Square{
    public:
    BankSquare(int startX, int startY, int startDirection, StudentWorld* studentWorldPointer);
    virtual void doSomething();
    
};

class EventSquare: public Square{
    public:
    EventSquare(int startX, int startY, int startDirection, StudentWorld* studentWorldPointer);
    virtual void doSomething();
};




#endif // ACTOR_H_
