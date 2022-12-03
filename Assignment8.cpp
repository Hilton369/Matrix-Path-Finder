#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "stack.h"

struct state{
    int row;
    int col;
    int sum;
    int p_row;
    int p_col;
    char symb;
    //char fail_symbol
};


//Function for getting matrix input from txt file
//Input: File name
//Output: 2D matrix filled with numbers from txt file
std::vector<std::vector <int>> read_file(std::string name){
    int row, col, num;
    std::ifstream fin;
    fin.open(name);
    fin>>row>>col;
    std::vector<std::vector<int>> m(row, std::vector<int>(col));
    if(fin.is_open()){
        for(int i = 0; i < m.size(); i++){
            for(int j = 0; j < m[i].size(); j++){
                fin>>m[i][j];
            }
        }
        fin.close();
    }
    return m;
}

//Function for checking if index is within bounds
//Input: struct with index row and col, 2D array
//Output: True if within bounds, False if out of bounds
bool within_bounds(state s, const std::vector<std::vector<int>> & m){
    return (!(s.row >= m.size() || s.col >= m[0].size() || s.row < 0 || s.col < 0));
}

//Function that finds path through 2D array and draws path that leads to a positive sum on second matrix.
//Input: Matrix with numbers, Empty matrix for drawing path
//Output: True if path found, false if no path found
bool path_finder(std::vector<std::vector<int>> & m, std::vector<std::vector<char>> & empty){
    stack<state> s;
    s.push({0,0,0,0,0,'x'});
    while(!s.isEmpty()){
        state curr = s.pop();
        if(!within_bounds(curr, m) || empty[curr.row][curr.col] != '-'){
            //IF DOWN ARROW SET PREVIOUS TO '-'
            if(curr.symb == 'v'){
                empty[curr.p_row][curr.p_col] = '-';
            }
        }
        //ELSE IF TERMINAL CONDITION SET PREVIOUS TO DASH
        else if(curr.symb == 'T'){
            empty[curr.p_row][curr.p_col] = '-';
        }
        else if(curr.row == m.size()-1 && curr.col == m[curr.row].size()-1){
            curr.sum += m[curr.row][curr.col];
            if(curr.sum >= 0){
                empty[curr.p_row][curr.p_col] = curr.symb;
                empty[curr.row][curr.col] = 'X';
                return true;
            }
            else{
                //IF DOWN ARROW SET PREVIOUS TO '-'
                if(curr.symb = 'v'){
                    empty[curr.p_row][curr.p_col] = '-';
                }
            }
        }
        else{
            empty[curr.p_row][curr.p_col] = curr.symb; //Mark previous index
            curr.sum += m[curr.row][curr.col];
            s.push({curr.row + 1, curr.col, curr.sum, curr.row, curr.col, 'T'}); //PUSH WITH TERMINAL SYMBOL
            s.push({curr.row + 1, curr.col, curr.sum, curr.row, curr.col, 'v'});
            s.push({curr.row, curr.col + 1, curr.sum , curr.row, curr.col, '>'});
            s.push({curr.row - 1, curr.col, curr.sum, curr.row, curr.col, '^'});
            s.push({curr.row, curr.col - 1, curr.sum, curr.row, curr.col, '<'});
        }
    }
    return false;    
}



//Function to print matrices
//Input: Matrix that needs printing
//Output: Displays all elements of matrix in order
template <typename T>
void print(const std::vector<std::vector<T>> & m){
        for(auto r : m){
        for(auto c : r){
            std::cout<<std::setw(4);
            std::cout<<c<<" ";
        }
        std::cout<<std::endl;
    }
}

int main(){
    std::vector<std::vector<int>> m = read_file("Matrix4.txt");
    std::vector<std::vector<char>> empty(m.size(), std::vector<char>(m[0].size(), '-'));
    std::cout << "Original Matrix:" << std::endl;
    print(m);
    std::cout<< std::endl;
    std::cout << "Path Matrix:" << std::endl;
    if(path_finder(m, empty)){
        print(empty);
    }
    else{
        print(empty);
        std::cout << "No path found" << std::endl;
    }
}