//
//  mcts.cpp
//  MCTS-C
//
//  Created by Jonathan Carter on 02/12/2020.
//

#include "mcts.hpp"

Node::Node(Connect4Board game, Node* parent_node, int parent_action){
  turn = game.get_turn();  // Whose turn does node correspond to?
  for (int i = 0; i < COLS; ++i)
  {
    children[i] = NULL;  // Set all child pointers null.
    if (game.check_legal(i))
    {
      moves[i] = LEGAL;
      ++num_unexplored_moves;
    } else {
      moves[i] = ILLEGAL;
    }
  }
  parent = parent_node;
  action = parent_action;
}

void Node::update(string outcome){
  if (outcome == "-"){
    pts += 0.5;  // Draw
  } else if (outcome != turn){
    pts += 1;  // If loss for player associated with node, increase score for node above.
  }
  if (outcome== "")
  {
    throw 2;
  }
  games += 1;
}

Node* Node::expand(Connect4Board game_state, int action)
{
  assert(moves[action] != ILLEGAL);
  moves[action] = EXPLORED;
  --num_unexplored_moves;
  Node *child = new Node(game_state, this, action);
  children[action] = child;
  return child;
}

double Node::value()
{
  return (pts/games);
}

double Node::ucb_value()
{
  return (pts/games) + c_ucb*sqrt(2 * log(parent->games)/games);
}


Node* Node::get_best_child(bool greedy)
{
  double best_child_value = -1;
  double child_value;
  Node* best_child = NULL;
  for (int i = 0; i < COLS; ++i){
    if (moves[i] != ILLEGAL)
    {
      child_value = (greedy) ? children[i]->value(): child_value = children[i]->ucb_value();
      
      if (child_value >= best_child_value)
      {
        best_child = children[i];
        best_child_value = child_value;
      }
    }
  }
  assert(best_child != NULL);
  return best_child;
}

string Node::get_turn() { return turn;}
Node* Node::get_parent() {return parent;}
Node* Node::get_child(int action)
{
  if (children[action] == NULL){
    return NULL;
  }
  return children[action];
}

/**
 * Traverse MCTS tree until we reach a node that isn't fully explored.
 *
 * @param node : Pointer to initial node.
 * @return node : Pointer to leaf node for expansion.
 */
Node* MCTSagent::_select(Node *node)
{
  while((node->num_unexplored_moves == 0) && !(simulation_game.check_end()))
  {
    node = node->get_best_child(false);
    simulation_game.add_counter(node->action);  // Take action leading to best child
  }
  return node;
}

/**
 * Expand MCTS tree by taking a random unexplored action from a leaf node.
 *
 * @param node : Pointer to initial node.
 * @return node : Pointer to new leaf node.
 */
Node* MCTSagent::_expand(Node* node)
{
  if ((node->num_unexplored_moves == 0) || simulation_game.check_end())
  {
    return node;
  }
  int action_idx = rand() % node->num_unexplored_moves;
  
  int action = -1;
  int i = 0;
  int j = 0;
  while ((action == -1) && (i < 7))
  {
    if (node->moves[i] == LEGAL)
    {
      if (j == action_idx)
      {
        action = i;
      }
      ++j;
    }
    ++i;
  }
  bool done = simulation_game.add_counter(action);  // Take new random action
  
  Node* child = node->expand(simulation_game, action);
  return child;
}

/**
 * Take random actions till completion from a given node.
 *
 * @param node : Pointer to initial node.
 */
void MCTSagent::_simulate(Node* node)
{
  while(!simulation_game.check_end())
  {
    simulation_game.random_move();
  }
}

/**
 * Update all traversed nodes with outcome of simulation.
 *
 * @param node : Pointer to leaf node.
 */
void MCTSagent::_update(Node* node)
{
  while (node != NULL){
    node->update(simulation_game.get_outcome());
    node = node->get_parent();
  }
}

/**
 * Traverse MCTS tree until we reach a node that isn't fully explored.
 *
 * @param current_game : Inital state of the Connect4Board.
 * @param iterations : Number of simulations through the search tree.
 * @return node : Optimal MCTS agent action.
 */
int MCTSagent::run(Connect4Board current_game, int iterations)
{
  
  for (int i = 0; i < iterations; ++i)
  {
    simulation_game = current_game;
    Node* node = root_node;
    node = _select(node);
    node = _expand(node);
    _simulate(node);
    _update(node);
  }
  return root_node->get_best_child(true)->action;
}

void MCTSagent::move_root(int action)
{
  root_node = root_node->get_child(action);
}

void MCTSagent::print_move_ratings()
{
  cout << "Agent Move Ratings: " << endl << "[";
  for (int i=0; i < 7; ++i)
  {
    Node* child = root_node->get_child(i);
    if (child != NULL)
    {
      cout << i+1 << " : " << child->value() << ", ";
    } else
    {
      cout << i+1 << " : -" << endl;
    }
  }
  cout << "]" << endl;
}
