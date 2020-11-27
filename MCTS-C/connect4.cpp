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

int Connect4Board::get_colspace(int col_idx)
{
    return col_tallies[col_idx];
}

string Connect4Board::get_turn(){
    return turn;
}

string Connect4Board::get_wintype()
{
    return win_type;
}

void Connect4Board::switch_turn()
{
    (turn == "X") ? turn = "O" : turn = "X";
}

int *Connect4Board::legal_moves()
{
    int *free_columns = (int *) malloc(7*sizeof(int));
    for (int i=0; i < COLS; ++i)
    {
        (col_tallies[i] < ROWS) ? *(free_columns+i) = 1 : *(free_columns+i) = 0;
    }
    return free_columns;
}

void Connect4Board::add_counter(int column){
    if (game_won)
    {
        cout << "Can't place counter, game already won!\n";
        return;
    } else if (col_tallies[column] == 6)
    {
        cout << "Trying to place counter in a full column. Please try again.\n";
        return;
    } else if (not ((0 <= column) & (column < COLS)))
    {
        cout << "Index out of range. Please enter a number between 1 and 7.\n";
        return;
    }
        
    last_action = column;
    int row = col_tallies[column];
    int player_no;  // 1 or -1 indicate player X or O respectively
    (turn == "X") ? player_no = 1 : player_no = -1;
    state[row][column] = player_no;
    col_tallies[column] += 1;
    check_win();
    switch_turn();
}

bool Connect4Board::won()
{
    return  game_won;
}

bool Connect4Board::check_win()
{
    
    check_vertical_win();
    check_horizontal_win();
    check_ldiagonal_win();
    check_udiagonal_win();
    return game_won;
}

bool Connect4Board::check_sum(int board_sum)
{
    if (board_sum >= 4)
    {
        outcome = "X";
        game_won = true;
    } else if (board_sum <= -4)
    {
        outcome = "O";
        game_won = true;
    }
    return game_won;
}

void Connect4Board::check_horizontal_win()
{
    if (game_won) {return;}
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
    if (game_won) {return;}
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
    if (game_won) {return;}
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
    if (game_won) {return;}
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
