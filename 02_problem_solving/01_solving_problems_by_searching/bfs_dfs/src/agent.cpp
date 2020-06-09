/*
 * Daniel Vazquez
 * Aritifiacial Intelligence for Robots
 * MAS Winter 2014
 * Assignment 3
 *
 * agent.cpp
 * */

#include <stdlib.h>
#include "agent.hpp"

#include <iostream>
#include <stack>
#include <queue>

#include <time.h>
#include <chrono>
#include <thread>

#define map_rows 25
#define map_cols 141

using namespace std;

Agent::Agent(vector<vector<string> > map, const int * initial_pos, int number_of_goals, int search_option):
map(map),
initial_pos(initial_pos),
number_of_goals(number_of_goals),
search_option(search_option),
max_number_of_stored_nodes(0),
number_of_visited_nodes(0),
total_of_stored_nodes(0),
exc_time(0.0)
{

}

Agent::~Agent()
{

}

void Agent::run()
{
    time_t t_start;
    time_t t_end;
    
    if (search_option == 1)
    {
      cout << "Running BFS " << endl;
      cout << "Number of goals " << number_of_goals << endl;
      //sleep(1);
      time(&t_start);
      bfs();
      time(&t_end);

    }
    else
    {
      cout << "Running DFS " << endl;
      cout << "Number of goals " << number_of_goals << endl;
      //sleep(1);
      time(&t_start);
      dfs();
      time(&t_end);
    }
    
    exc_time = difftime(t_end, t_start);
    cout << "Estimated Execution time: " << exc_time << endl;
}

void Agent::print_map()
{
    system("clear");

    for(int row = 0; row < map_rows; row++)
    {
        for(int col = 0; col < map_cols; col++)
        {
            cout << map[row][col];
        }    
        cout << endl;
    }
    
    this_thread::sleep_for(chrono::milliseconds(10));

}

int Agent::bfs()
{
    //queue stores a pair in the form (row, col)
    queue<pair<int, int> > nodes_queue;
    pair<int, int> current_node;

    //Add the initial node to the queue
    nodes_queue.push(make_pair(initial_pos[0], initial_pos[1]));
    total_of_stored_nodes++;

    
    while(nodes_queue.size() > 0)
    {
        
        //get the max number of stored nodes
        if(max_number_of_stored_nodes < nodes_queue.size())
        {
            max_number_of_stored_nodes = nodes_queue.size();
        }

        //increase the number of visited nodes
        number_of_visited_nodes++;

        //get current node positions
        current_node = nodes_queue.front();
        //remove node from queue
        nodes_queue.pop();
        
        if(map[current_node.first][current_node.second] == "*")
        {
            //store the position of the goal node
            goal_positions.push_back(current_node);
                                   
            if (goal_positions.size() == number_of_goals)
            {
                //mark the  last goal position as visited
                map[current_node.first][current_node.second] = "-";
                print_final_results("queue");
                return 1;
            }
            
            //remove goal mark
            map[current_node.first][current_node.second] = " ";

        }
        
        //analize the node only if it has not been maked as visited
        if(map[current_node.first][current_node.second] != "-")
        {
            //mark the position as visited
            map[current_node.first][current_node.second] = "-";
            
            //add node childrens
            
            //add  top child
            if(map[current_node.first - 1][current_node.second] == " " || map[current_node.first - 1][current_node.second] == "*")
            {
                nodes_queue.push(make_pair(current_node.first -1, current_node.second));
                total_of_stored_nodes++;
            }

            //add bottom child
            if(map[current_node.first + 1][current_node.second] == " " || map[current_node.first  + 1][current_node.second] == "*")
            {
                nodes_queue.push(make_pair(current_node.first + 1, current_node.second));
                total_of_stored_nodes++;
            }

            //add left child
            if(map[current_node.first][current_node.second - 1] == " " || map[current_node.first][current_node.second - 1] == "*")
            {
                nodes_queue.push(make_pair(current_node.first, current_node.second - 1));
                total_of_stored_nodes++;
            }
            
            //add right child
            if(map[current_node.first][current_node.second + 1] == " " || map[current_node.first][current_node.second + 1] == "*")
            {
                nodes_queue.push(make_pair(current_node.first, current_node.second + 1));
                total_of_stored_nodes++;
            }

            
            print_map();
        }

    }
 
    cout << "All the possible nodes have been explored " << endl; 
    print_final_results("queue");
    return -1;    
}

int Agent::dfs()
{
    //stack stores a pair in the form (row, col)
    stack<pair<int, int> > nodes_stack;
    pair<int, int> current_node;

    //Add the initial node to the queue
    nodes_stack.push(make_pair(initial_pos[0], initial_pos[1]));
    total_of_stored_nodes++;
    
    while(nodes_stack.size() > 0)
    {
        //get the max number of stored nodes
        if(max_number_of_stored_nodes < nodes_stack.size())
        {
            max_number_of_stored_nodes = nodes_stack.size();
        }

        //get current node positions
        current_node = nodes_stack.top();
        //remove node from queue
        nodes_stack.pop();
       
        //increase the number of visited nodes
        number_of_visited_nodes++;

        if(map[current_node.first][current_node.second] == "*")
        {

            //store the position of the goal node
            goal_positions.push_back(current_node);
                
            
            if (goal_positions.size() == number_of_goals)
            {
                //mark the last goal position as visited
                map[current_node.first][current_node.second] = "-";
                print_final_results("stack"); 
                return 1;
            }
            
            //mark remove the goal mark
            map[current_node.first][current_node.second] = " ";

        }
        
        //analize the node only if it has not been maked as visited
        if(map[current_node.first][current_node.second] != "-")
        {
            //mark the position as visited
            map[current_node.first][current_node.second] = "-";
            
            //add node childrens
            
            //add  top child
            if(map[current_node.first - 1][current_node.second] == " " || map[current_node.first - 1][current_node.second] == "*")
            {
                nodes_stack.push(make_pair(current_node.first -1, current_node.second));
                total_of_stored_nodes++;
            }

            //add bottom child
            if(map[current_node.first + 1][current_node.second] == " " || map[current_node.first  + 1][current_node.second] == "*")
            {
                nodes_stack.push(make_pair(current_node.first + 1, current_node.second));
                total_of_stored_nodes++;
            }

            //add left child
            if(map[current_node.first][current_node.second - 1] == " " || map[current_node.first][current_node.second - 1] == "*")
            {
                nodes_stack.push(make_pair(current_node.first, current_node.second - 1));
                total_of_stored_nodes++;
            }
            
            //add right child
            if(map[current_node.first][current_node.second + 1] == " " || map[current_node.first][current_node.second + 1] == "*")
            {
                nodes_stack.push(make_pair(current_node.first, current_node.second + 1));
                total_of_stored_nodes++;
            }

            print_map();
        }

    }

    cout << "All the possible nodes have been explored " << endl; 
    print_final_results("stack");
    return -1;    
}

void Agent::print_final_results(string data_structure_name)
{   
    print_map();
    cout << "Found " << goal_positions.size() << " of " << number_of_goals << endl;
    cout << "Maximum size of the " << data_structure_name << " : " << max_number_of_stored_nodes << endl;
    cout << "Total of stored nodes: " << total_of_stored_nodes << endl;
    cout << "Total of visited nodes: " << number_of_visited_nodes << endl;
    print_found_goal_positions();
} 

void Agent::print_found_goal_positions()
{
    cout << "Goals positon: " << endl;
    for(int i = 0; i < goal_positions.size(); i++)
    {
        cout << i + 1 << ": (" << goal_positions[i].first << ", " << goal_positions[i].second << ")" << endl;
    }
}

