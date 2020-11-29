//
//  connect4.cpp
//  MCTS-C
//
//  Created by Jonathan Carter on 26/11/2020.
//

#include "connect4.hpp"

void Connect4Board::print_board()
{
  cout << "Board state: \n";
  for (int i = ROWS-1; i >= 0; --i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      if (state[i][j] == 0)
      {
        cout << "-";
      } else if (state[i][j] == 1)
      {
        cout << "X";
      } else
      {
        cout << "O";
      }
    }
    cout << "\n";
  }
  cout << "\n";
}

void Connect4Board::print_win()
{
  if (outcome == "-")
  {
    cout << "Game drawn!" << endl;
    return;
  }
  cout << "Player " << outcome << " Wins!" << endl;
}

int Connect4Board::get_colspace(int col_idx)
{
  return col_tallies[col_idx];  // Number of counters in column
}

bool Connect4Board::check_legal(int col_idx)
{
  if (!((col_idx >= 0) && (col_idx < COLS)))
  {
    return false;
  }
  
  if (game_end)
  {
    return false;
  }
  return (get_colspace(col_idx) < ROWS);
}

string Connect4Board::get_turn(){
  return turn;
}

string Connect4Board::get_wintype()
{
  return win_type;
}

int Connect4Board::get_last_action()
{
  return last_action;
}

void Connect4Board::switch_turn()
{
  (turn == "X") ? turn = "O" : turn = "X";
}

bool Connect4Board::add_counter(int column){
  if (game_end)
  {
    cout << "Can't place counter, game already won!\n";
    return false;
  } else if (!check_legal(column))
  {
    cout << "Trying to place counter in a full column. Please try again.\n";
    return false;
  } else if (not ((0 <= column) && (column < COLS)))
  {
    cout << "Index out of range. Please enter a number between 1 and 7.\n";
    return false;
  }
  
  last_action = column;
  int row = col_tallies[column];
  int player_no;  // 1 or -1 indicate player X or O respectively
  (turn == "X") ? player_no = 1 : player_no = -1;
  state[row][column] = player_no;
  col_tallies[column] += 1;
  ++moves_played;
  check_end();
  switch_turn();
  return true;
}

void Connect4Board::random_move()
{
  int legal_moves[7];
  int num_legal_moves = 0;
  for (int i=0; i < COLS; ++i)
  {
    if (check_legal(i))
    {
      legal_moves[num_legal_moves] = i;
      ++num_legal_moves;
    }
  }
  int random_idx = rand() % num_legal_moves;
  add_counter(legal_moves[random_idx]);
}

string Connect4Board::get_outcome()
{
  return outcome;
}

bool Connect4Board::check_end()
{
  if (moves_played == 0){return false;}
  check_draw();
  check_vertical_win();
  check_horizontal_win();
  check_ldiagonal_win();
  check_udiagonal_win();
  return game_end;
}

bool Connect4Board::check_sum(int board_sum)
{
  if (board_sum >= 4)
  {
    outcome = "X";
    game_end = true;
  } else if (board_sum <= -4)
  {
    outcome = "O";
    game_end = true;
  }
  return game_end;
}

void Connect4Board::check_draw()
{
  if (game_end){ return;}
  for (int i = 0; i < COLS; ++i)
  {
    if (check_legal(i))  // Draw if no more legal moves
    {return;}
  }
  game_end = true;
  outcome = "-";
  
}
void Connect4Board::check_horizontal_win()
{
  if (game_end) {return;}
  
  int row_idx = col_tallies[last_action] - 1;
  int row_sum;
  for (int i = max(0, last_action-3); i <= 3 ; ++i){
    row_sum = 0;
    for (int j = 0; j < 4; ++j)
    {
      row_sum += state[row_idx][i+j];
    }
    if (check_sum(row_sum)) {
      win_type="horizontal";
      break;
    }
  }
}

void Connect4Board::check_vertical_win()
{
  if (game_end) {return;}
  int row_idx = col_tallies[last_action] - 1;
  int col_sum;
  for (int i = max(0, row_idx-3); i <= 2 ; ++i){
    col_sum = 0;
    for (int j = 0; j < 4; ++j)
    {
      col_sum += state[i+j][last_action];
    }
    if (check_sum(col_sum)) {
      win_type = "vertical";
      break;
    }
  }
}

void Connect4Board::check_udiagonal_win()
{
  if (game_end) {return;}
  int row_height = col_tallies[last_action] - 1;
  int offset = row_height - last_action;  // Diagonal offset of last counter placed.
  
  int row;
  int col;
  
  if (offset < 0)
  {
    row = 0;
    col = abs(offset);
  } else {
    row = offset;
    col = 0;
  }
  
  while ((row <= ROWS - 4) && (col <= COLS - 4))
  {
    int diag_sum = 0;
    for (int j = 0; j < 4; ++j)
    {
      if ((row + j >= ROWS) or (col+j >= COLS))
      {
        break;
      }
      diag_sum += state[row+j][col+j];
    }
    ++row;
    ++col;
    if (check_sum(diag_sum)) {
      win_type="diagonal";
      break;
    }
  }
}

void Connect4Board::check_ldiagonal_win()
{
  if (game_end) {return;}
  int row_height = col_tallies[last_action] - 1;
  int offset =  (ROWS-1-row_height) - last_action;  // Off-diagonal offset of last counter placed.
  
  int row;
  int col;
  
  if (offset < 0)
  {
    row = ROWS - 1;
    col = abs(offset);
  } else {
    row = ROWS - 1 - offset;
    col = 0;
  }
  
  
  while ((row >= 3) && (col <= COLS - 4))
  {
    int diag_sum = 0;
    for (int j = 0; j < 4; ++j)
    {
      if ((row - j < 0) or (col+j) >= COLS)
      {
        break;
      }
      diag_sum += state[row-j][col+j];
    }
    --row; ++col;
    if (check_sum(diag_sum)) {
      win_type = "off_diagonal";
      break;
    }
  }
  
}
