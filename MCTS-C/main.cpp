//
//  main.cpp
//  MCTS-C
//
//  Created by Jonathan Carter on 26/11/2020.
//

#include <iostream>
#include <string>
#include "connect4.hpp"
#include "mcts.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
  srand((int)time(NULL));
  Connect4Board user_game;
  Node* node1 = new Node(user_game, NULL, NULL);
  MCTSagent mcts(node1);
  
  int col_idx = -1;
  while(!user_game.check_end())
  {
    int cpu_action = mcts.run(user_game, 3000);
    
    mcts.print_move_ratings();
    user_game.add_counter(cpu_action);
    cout << "CPU Chose column " << cpu_action+1 << endl;
    mcts.move_root(cpu_action);
    if (user_game.check_end()) {user_game.print_board(); break;}
    user_game.print_board();
    cout << "Player " << user_game.get_turn() << " : Choose a column [1-7]: "; // Type a number and press enter
    bool added = false;
    while(!added)
    {
      cin >> col_idx; // Get user input from the keyboard
      added = user_game.add_counter(col_idx-1);
    }
    mcts.move_root(col_idx-1);
    user_game.print_board();
  }
  user_game.print_win();
  return 0;
}
