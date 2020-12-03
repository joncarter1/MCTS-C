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
  test_game();
  bool keep_playing = true;
  while (keep_playing)
  {
    int search_depth = 3000; // Super human performance
    string user_input;
    cout << "Enter which player to control, X or O : " << endl;
    string user = "-";
    bool user_set = false;
    while (!user_set)
    {
      cin >> user;
      if ((user == "X") or (user == "O"))
      {
        user_set = true;
        cout << "Player " << user << " chosen." << endl << endl;
      } else {
        cout << "Invalid input, please enter either X or O: " << endl << endl;
      }
    }
    cout << "Set number of search iterations per turn (Integer 10-100000). Note: 1000+ is approx. super-human." << endl;
    cout << "Enter number of iterations: " << endl;
    bool search_set = false;
    string::size_type st;
    while (!search_set)
    {
      cin >> user_input; // Get user input from the keyboard
      try {
        search_depth = stoi(user_input, &st);
        if ((search_depth < 10) or (search_depth > 100000)){throw invalid_argument("");}
        cout << "Agent search depth set to : " << search_depth << endl;
        search_set = true;
      } catch(invalid_argument) {
        cout << "Invalid input. Please try again : " << endl;
      }
    }
    
    srand((int)time(NULL));
    Connect4Board user_game;
    Node* node1 = new Node(user_game, NULL, NULL);
    MCTSagent mcts(node1);
    int col_idx = -1;  // Default out of range.
    bool added = false;
    int cpu_action = mcts.run(user_game, search_depth);
    if (user == "X")
    {
      while(!added)
      {
        user_game.print_board();
        cout << "Player " << user_game.get_turn() << " : Choose a column [1-7]: "; // Type a number and press enter
        cin >> user_input; // Get user input from the keyboard
        try {
          col_idx = stoi(user_input, &st);
        } catch(invalid_argument) {
          col_idx = -1; // Catch conversion error
        }
        added = user_game.add_counter(col_idx-1);
      }
      mcts.move_root(col_idx-1);
      user_game.print_board();
    }
    
    while(!user_game.check_end())
    {
      cpu_action = mcts.run(user_game, search_depth);
      mcts.print_move_ratings();
      user_game.add_counter(cpu_action);
      cout << "CPU Chose column " << cpu_action+1 << endl;
      mcts.move_root(cpu_action);
      
      if (user_game.check_end()) {user_game.print_board(); break;}
      user_game.print_board();
      cpu_action = mcts.run(user_game, search_depth);
      cout << "Player " << user_game.get_turn() << " : Choose a column [1-7]: "; // Type a number and press enter
      col_idx = -1;
      added = false;
      
      while(!added)
      {
        cin >> user_input; // Get user input from the keyboard
        try {
          col_idx = stoi(user_input, &st);
        } catch(invalid_argument) {
          col_idx = -1; // Catch conversion error
        }
        added = user_game.add_counter(col_idx-1);
        
      }
      mcts.move_root(col_idx-1);
      user_game.print_board();
    }
    user_game.print_win();
    cout << "Play again? Y or N : ";
    cin >> user_input;
    keep_playing = (user_input == "Y") ? true : false;
  }
  return 0;
}
