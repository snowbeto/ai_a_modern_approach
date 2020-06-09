/*
 * Daniel Vazquez
 * Aritifiacial Intelligence for Robots
 * MAS Winter 2014
 * Assignment 3
 *
 * agent.hpp
 * */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>
#include <utility>
#include <string>
using namespace std;

class Agent
{
    public:
        Agent(vector<vector<string> >, const int *, int, int);
        ~Agent();

        void run();
    private:

        vector<vector<string> > map;
        const int * initial_pos ;
        int number_of_goals;
        int search_option;
        vector<pair<int, int> > goal_positions;
        int max_number_of_stored_nodes;
        int number_of_visited_nodes;
        int total_of_stored_nodes;
        double exc_time;
        
        void print_map();
        int bfs();
        int dfs();
	bool can_add(int col, int row);

        void print_final_results(string);
        void print_found_goal_positions();


};



#endif
