//
//  mcts.cpp
//  MCTS-C
//
//  Created by Jonathan Carter on 26/11/2020.
//

#include "mcts.hpp"
#include "connect4.hpp"


class Node{
protected:
    Connect4Board game_state;
    Node *parent;
    int action;
    int games = 0;
    int c = 0;
    Node *children[7]; // Up to seven possible Connect4 moves
    string turn = game_state.get_turn();
    float pts = 0;
public:
    Node(Connect4Board game, Node* parent_node, int parent_action){
        game_state = game;
        parent = parent_node;
        action = parent_action;
    }
    void update(string outcome){
        if (outcome == "-"){
            pts += 0.5;
        } else if (outcome == "X"){
            pts += 1;
        }
    }
    
};
