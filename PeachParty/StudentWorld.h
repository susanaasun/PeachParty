#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  virtual int returnBankBalance();
  virtual int setBankBalance(int changeBalance);
  virtual int addBankBalance(int amount);
  Board* getBoard();
  Player* getPlayer(int player);
    ~StudentWorld();
    

private:
    bool peachWon();
    Player *m_Peach;
    Player *m_Yoshi;
    Board *m_Board;
    int m_bankBalance;
    std::vector<Actor*> tracker;
    

};

#endif // STUDENTWORLD_H_

