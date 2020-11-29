//
//  manual.cpp
//  MCTS-C
//
//  Created by Jonathan Carter on 28/11/2020.
//

#include <stdio.h>
#include "connect4.hpp"

void manual()
{
  for (int i = 0; i < 1000; ++i)
  {
    Connect4Board user_game;
    //user_game.print_board();
    while(!user_game.check_end()){
       //cout << "Player " << user_game.get_turn() << " : Choose a column [1-7]: "; // Type a number and press enter
       bool counter_added = true;
       while (!counter_added)
       {
       //cin >> col_idx; // Get user input from the keyboard
       //counter_added = user_game.add_counter(col_idx-1);
       
       }
       user_game.random_move();
       if (user_game.check_end()) {user_game.print_board(); break;}
       user_game.random_move();
       //user_game.print_board();
     }
  }
}
