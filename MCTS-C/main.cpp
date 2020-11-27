//
//  main.cpp
//  MCTS-C
//
//  Created by Jonathan Carter on 26/11/2020.
//

#include <iostream>
#include <string>
#include "connect4.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here..
    Connect4Board user_game;
    while(!user_game.won()){
        cout << "Player " << user_game.get_turn() << " : Choose a column [1-7]: "; // Type a number and press enter
        int col_idx;
        cin >> col_idx; // Get user input from the keyboard
        user_game.add_counter(col_idx-1);
        user_game.print_board();
    }
    return 0;
}
