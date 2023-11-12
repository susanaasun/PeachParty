#include "StudentWorld.h"
#include "GameConstants.h"
#include "Board.h"
#include <string>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::returnBankBalance(){
    return m_bankBalance;
}

int StudentWorld::setBankBalance(int changeBalance){
   return m_bankBalance = changeBalance;
}

int StudentWorld::addBankBalance(int amount){
    return m_bankBalance += amount;
}

Board* StudentWorld::getBoard(){
    return m_Board;
}

Player* StudentWorld::getPlayer(int player){
    if(player == 1){
        return m_Peach;
    }
    
    return m_Yoshi;
}

//Actor* StudentWorld::randomSquare(){
//    int num = randInt(0, Actor.size());
//    return actor[num];
//}


int StudentWorld::init()
{
    //string filename = "";
     //change x and y variable
    
	startCountdownTimer(99);  // this placeholder causes timeout after 5 seconds
    
    m_Board = new Board();
//    m_Board->loadBoard(filename);
    
    
    int board_num = getBoardNumber();
    string board_file;
    
    switch (board_num) {
        case 1:
            board_file = assetPath() + "board01.txt";
            break;
        case 2:
            board_file = assetPath() + "board02.txt";
            break;
        case 3:
            board_file = assetPath() + "board03.txt";
            break;
        case 4:
            board_file = assetPath() + "board04.txt";
            break;
        case 5:
            board_file = assetPath() + "board05.txt";
            break;
        case 6:
            board_file = assetPath() + "board06.txt";
            break;
        case 7:
            board_file = assetPath() + "board07.txt";
            break;
        case 8:
            board_file = assetPath() + "board08.txt";
            break;
        case 9:
            board_file = assetPath() + "board09.txt";
            break;
            
    }
//    string board_file = assetPath() + "board01.txt";
    
     Board::LoadResult result = m_Board->loadBoard(board_file);
     if (result == Board::load_fail_file_not_found)
     cerr << "Could not find board01.txt data file\n";
     else if (result == Board::load_fail_bad_format)
     cerr << "Your board was improperly formatted\n";
     else if (result == Board::load_success) {
         cerr << "Successfully loaded board\n";
         
         for (int i = 0; i<BOARD_WIDTH ; i++){
             for (int j = 0; j<BOARD_HEIGHT; j++){

                 Board::GridEntry ge = m_Board->getContentsOf(i, j);
                 switch (ge) {
                     case Board::empty:
                         // cout << "Location " << i << " " << j << " is empty\n";
                         break;
                     case Board::boo:
                         // cout << "Location " << i << " " << j << " has a Boo and a blue coin square\n";
                         tracker.push_back(new Boo(IID_BOO, SPRITE_WIDTH *i, SPRITE_HEIGHT *j, this));
                         tracker.push_back(new CoinSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, true, 0, this));
                         break;
                     case Board::bowser:
                         // cout << "Location " << i << " " << j << " has a Bowser and a blue coin square\n";
                         tracker.push_back(new Bowser(IID_BOWSER, SPRITE_WIDTH *i, SPRITE_HEIGHT *j, this));
                         tracker.push_back(new CoinSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, true, 0, this));
                         break;
                     case Board::player:
                         // cout << "Location " << i << " " << j << " has Peach & Yoshi and a blue coin square\n";
                         
                         m_Yoshi = new Yoshi(IID_YOSHI, SPRITE_WIDTH *i, SPRITE_HEIGHT *j, this);
                         m_Peach = new Peach(IID_PEACH, SPRITE_WIDTH *i, SPRITE_HEIGHT *j, this);
                         tracker.push_back(new CoinSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, true, 0, this));
                         break;
                     case Board::blue_coin_square:
                         // cout << "Location " << i << " " << j << " has a blue coin square\n";
                         tracker.push_back(new CoinSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, true, 0, this));
                         break;
                     case Board::red_coin_square:
                         // cout << "Location " << i << " " << j << " has a red coin square\n";
                         tracker.push_back(new CoinSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, false, 0, this));
                         break;
                     case Board::star_square:
                         // cout << "Location " << i << " " << j << " has a star square\n";
                         tracker.push_back(new StarSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, 0, this));
                         break;
                         
                     case Board::up_dir_square:
                         
                         // cout << "Location " << i << " " << j << " has an up dir square\n";
                         tracker.push_back(new DirectionalSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, 90, this));
                         break;
                     case Board::down_dir_square:
                         tracker.push_back(new DirectionalSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, 270, this));
                         break;
                     case Board::left_dir_square:
                         tracker.push_back(new DirectionalSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, 180, this));
                         break;
                     case Board::right_dir_square:
                         tracker.push_back(new DirectionalSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, 0, this));
                         break;
                     case Board::bank_square:
                         tracker.push_back(new BankSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, 0, this));
                         break;
                     case Board::event_square:
                         tracker.push_back(new EventSquare(SPRITE_WIDTH *i, SPRITE_HEIGHT *j, 0, this));
                         break;
                 }
             }
         }
        // int amt;
//             ... suppose some code here gives amt the value 123.4
//             ostringstream oss;  // oss is a name of our choosing.
//             oss.setf(ios::fixed);
//             oss.precision(2);
//             oss << "$" << amt;  // puts "$123.40" in oss's internal storage
//             string s = oss.str();  // s gets "$123.40"

         setGameStatText("P1 Roll: 0 Stars: 0  $$3 | Time: 99 | Bank: | P2 Roll: 0 : Stars: 0 $$: 3");
     }
    
    
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::peachWon(){
    
    if(m_Peach->getStars() > m_Yoshi->getStars()){
        return true;
    }
    else if (m_Peach->getStars() < m_Yoshi->getStars()){
        return false;
    }
    else{
        if (m_Peach->getCoins() > m_Yoshi->getCoins()){
            return true;
        }
        else if (m_Peach->getCoins() < m_Yoshi->getCoins()){
            return false;
        }
        else{
            return true; //do later to randomize
            
        }
    }
    
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

    //setGameStatText("Game will end in a few seconds");
    
    if (timeRemaining() <= 0){
        
        playSound(SOUND_GAME_FINISHED);
        
        if (peachWon()){
            setFinalScore(m_Peach->getStars(), m_Peach->getCoins());
            return GWSTATUS_PEACH_WON;
        }
        else{
            setFinalScore(m_Yoshi->getStars(), m_Yoshi->getCoins());
            return GWSTATUS_YOSHI_WON;
        }
    }
    
    // The term "actors" refers to all actors, e.g., Peach, Yoshi,
    // baddies, squares, vortexes, etc.
    // Give each actor a chance to do something, incl. Peach and Yoshi
    cout << "Peach doSomething" << endl;
    m_Peach->doSomething();
    m_Yoshi->doSomething();
  
    for(int i = 0; i<tracker.size(); i++)
    {
        if (tracker[i]->isAlive()) {
            // tell that actor to do something
            tracker[i]->doSomething();
        }
    }
    // Remove newly-inactive actors after each tick
    //remove inactive/dead game objects
    for(int i = 0; i<tracker.size(); i++)
    {
     if (!tracker[i]->isAlive())
     {
     // tell that actor to do something
         delete tracker[i];
         tracker.erase(tracker.begin()+i);
     }
    }
    // Update the Game Status Line
    // update display text // update the coins/stars stats text at screen top
    
    // the game isn't over yet so continue playing
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_Board;
    m_Board = nullptr;
    delete m_Peach;
    m_Peach = nullptr;
    delete m_Yoshi;
    m_Yoshi = nullptr;
    
    //Delete the baddies
    
    for(int i = 0; i<tracker.size(); i++){
        delete tracker[i];
    }
    tracker.clear();
    
}

StudentWorld::~StudentWorld(){
    cleanUp();
}
