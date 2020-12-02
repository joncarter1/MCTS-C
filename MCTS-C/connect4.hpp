//
//  connect4.hpp
//  MCTS-C
//
//  Created by Jonathan Carter on 26/11/2020.
//

#ifndef connect4_hpp
#define connect4_hpp

#define ROWS 6
#define COLS 7
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

enum Moves {ILLEGAL = -1, LEGAL = 0, EXPLORED = 1};

class Connect4Board{
protected:
  int state[ROWS][COLS];  // Array of board
  int col_tallies[COLS];  // Counter of pieces per column
  string turn = "X"; // Player indicator, changes between -1 and 1
  int last_action = NULL; // Stores the column index of the last action
  bool game_started = false;
  bool game_end = false;
  int moves_played = 0;
  string win_type = "";
  string outcome = "";
public:
  Connect4Board()
  {
    for (int i = 0; i < COLS; ++i){
      col_tallies[i] = 0;
      for (int j = 0; j < ROWS; ++j){
        state[j][i] = 0;
      }
    }
  }
  void print_board();
  void print_win();
  int get_colspace(int col_idx);
  int get_last_action();
  string get_turn();
  string get_wintype();
  string get_outcome();
  void switch_turn();
  bool add_counter(int column);
  void random_move();
  bool check_legal(int col_idx);
  bool check_end();
  bool check_sum(int board_sum);
  void check_draw();
  void check_horizontal_win();
  void check_vertical_win();
  void check_udiagonal_win();
  void check_ldiagonal_win();
};

void test_game();

#endif /* connect4_hpp */
