//
//  test_connect4.cpp
//  MCTS-C
//
//  Created by Jonathan Carter on 26/11/2020.
//
#include <iostream>
#include <string>
#include "connect4.hpp"

#include <stdio.h>
int test(int argc, const char * argv[]) {
  // insert code here..
  Connect4Board game1;
  int vertical_win_o[] = {0, 1, 0, 1, 2, 1, 0, 1};
  for (int i = 0; i < sizeof(vertical_win_o)/sizeof(*vertical_win_o); ++i){
    game1.add_counter(vertical_win_o[i]);
    
  }
  assert(game1.check_end());
  game1.print_board();
  
  Connect4Board game2;
  int horizontal_win_x[7] = {0, 0, 1, 1, 2, 2, 3};
  for (int i = 0; i < sizeof(horizontal_win_x)/sizeof(*horizontal_win_x); ++i){
    game2.add_counter(horizontal_win_x[i]);
  }
  assert(game2.check_end());
  game2.print_board();
  
  Connect4Board game3;
  int diagonal_win_x[] = {0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3};
  for (int i = 0; i < sizeof(diagonal_win_x)/sizeof(*diagonal_win_x); ++i){
    game3.add_counter(diagonal_win_x[i]);
  }
  assert(game3.check_end());
  game3.print_board();
  
  Connect4Board game4;
  int diagonal_win_o[] = {0, 0, 0, 0, 0, 1, 2, 2, 2, 3, 1, 1};
  for (int i = 0; i < sizeof(diagonal_win_o)/sizeof(*diagonal_win_o); ++i){
    game4.add_counter(diagonal_win_o[i]);
  }
  cout << game4.check_end() << "\n";
  game4.print_board();
  cout << game4.get_wintype();
  return 0;
}
