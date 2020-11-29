//
//  mcts.hpp
//  MCTS-C
//
//  Created by Jonathan Carter on 26/11/2020.
//

#ifndef mcts_hpp
#define mcts_hpp

#include <stdio.h>
#include <stdlib.h>
#include "connect4.hpp"
using namespace std;

class Node{
protected:
  Node *parent = NULL;
  int c_ucb = 1;  // UCB exploration constant
  int unexplored_moves[COLS];
  Node *children[COLS]; // Possible moves are number of columns in which counter can be dropped.
  string turn;
  
public:
  float pts = 0;
  int action;  // Action taken to reach node.
  int games = 0;
  int num_unexplored_moves = 0;
  int moves[7];
  Node(Connect4Board game, Node* parent_node, int parent_action);
  void update(string outcome);
  string get_turn();
  double value();
  double ucb_value();
  Node *get_parent();
  Node *get_child(int action);
  Node* get_best_child(bool greedy);
  Node *expand(Connect4Board game_state, int action);
};

class MCTSagent{
protected:
  Node* root_node=NULL;
  Connect4Board simulation_game;
  int num_nodes = 0;
  Node* _select(Node* node);
  Node* _expand(Node* node);
  void _simulate(Node* node);
  void _update(Node* node);
  
  
public:
  MCTSagent(Node* root_node)
  {
    this->root_node = root_node;
  }
  Node* get_root() {return root_node;};
  void move_root(int action);
  int run(Connect4Board current_game, int iterations);
  void print_move_ratings();
};


#endif /* mcts_hpp */
