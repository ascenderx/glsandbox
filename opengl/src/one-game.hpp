#ifndef GAME_HPP
#define GAME_HPP

/****************************************************************************
 * 
 ****************************************************************************/
#include "one-player.hpp"

/****************************************************************************
 * 
 ****************************************************************************/
typedef const char * CString;

/****************************************************************************
 * 
 ****************************************************************************/
class Game {
public:
    // constructors
    Game();
    
    // destructor
    ~Game();

    // logic functions
    void input();
    void update();
    void render();

private:
    Player mPlayer;
    bool   mPaused;
    bool   mShowCursor;
};

#endif // GAME_HPP