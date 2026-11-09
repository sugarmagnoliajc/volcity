/*
main.cpp
11/8/26
this version by Jeremiah Cummings
This is the main user interface for Volcity. Includes class for the city.
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>

using namespace std;

/*
complete transparency: I could not get header files to compile in VSCode
the only problem with having it here is clutter, I think
*/
class city
{
    // each cell of the board is a block
    struct block
    {
      // default empty block, "." with population 0
      string display = ".";
      int pop = 0;
      string bType = "Empty";
      // TODO: maybe like internal building type
    };

    public:
      /* 
      constructor, define initial game state here
      */
      city()
      {
        size_t i, j;
        block *b;
        // fill in with empty block structs
        // SET TEMP 5x5 BOARD FOR TESTING:
        board.resize(5);
        for(i = 0; i < 5; i++){
            for(j = 0; j < 5; j++){
                b = new block;
                board[i].push_back(*b);
            }
        }
        board[0][0].bType = "TestHouse";
        board[0][0].display = "/\\";
        board[0][0].pop = 999;
        board[0][1].bType = "TestHosp";
        board[0][1].display = "=H=";

        for(i = 0; i < board.size(); i++){
            board[1][i].display = "=====";
            board[1][i].bType = "TestRoad";
        }

      }

      // destroying blocks as they were initialized with pointers
      ~city()
      {
        size_t i, j;
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++) delete &board[i][j];
        }
      }

      // returns true if empty
      bool empty() const
      {
        if(board.size() == 0) return true;
        return false;
      }        

      // print board with each block's display string 
      void print() const
      {
        int i;
        size_t j;
        string s;
        cout << " ";
        for(i = 0; i < board.size(); i++) printf("%5d", i);
        cout << endl;
        for(i = 0; i < board.size(); i++) {
            // a-z then just numbers. aa, ab... would be cooler, TODO: later
            if(i <= 26) printf("%c ", i + 'a');
            else printf("%d ", i - 'a');
            // width of 5 for each string, change if needed
            for(j = 0; j < board[i].size(); j++){
                s = board[i][j].display;
                printf("%5s", s.c_str());
            }
            cout << endl;
        }
        
      }        

      // print city stats (board size, population...)
      void stats() const
      {
        cout << "Total Population: " << totalPop << "     Happiness: " << happiness << "     Money: " << cash << endl;
        
      }        

      // print information about tile(i,j) TODO:
      void info(int i, int j)
      {
        cout << board[i][j].bType << ", population: " << board[i][j].pop << endl;
      }

      // save board to a file, TODO: need to decide on formatting
      void save() const
      {
        cout << "Not saved! Not implemented yet!\n";

      }

      void load(string s)
      {
        cout << "Not loaded! Not implemented yet!\n";
      }

        // TODO:  add more

        // bool edit(char c) to change a tile?

      // helpers
      int getPop() const{return totalPop;}
      int getCash() const{return cash;}
      string getName() const{return name;}
      void setCash(int c){cash = c;}
      void setName(string s){name = s;}
      void setHappiness(int c){happiness += c;}


    protected:
      vector<vector<block> > board;
      // default starting values
      int totalPop = 1;          // you!
      int cash = 10000;
      string name = "Knoxville";
      int day = 1;               // each action will advance day by one (not checking info)
      int happiness = 0.5;       // [0,1] percentage happiness of city

};

int main(int argc, char *argv[])
{
    city yours;
    char input, ci;
    string name;
    int i, j;
    bool play;
    play = 0;
 
    
    // print a logo
    cout << " mm    mm    mmmm    mm           mmmm    mmmmmm   mmmmmmmm mmm    mmm\n";
    cout << " \"##  ##\"   ##\"\"##   ##         ##\"\"\"\"#   \"\"##\"\"   \"\"\"##\"\"\"  ##m  m##\n"; 
    cout << "  ##  ##   ##    ##  ##        ##\"          ##        ##      ##mm##\n";  
    cout << "  ##  ##   ##    ##  ##        ##           ##        ##       \"##\"\n";   
    cout << "   ####    ##    ##  ##        ##m          ##        ##        ##\n";    
    cout << "   ####     ##mm##   ##mmmmmm   ##mmmm#   mm##mm      ##        ##\n";  
    cout << "   \"\"\"\"      \"\"\"\"    \"\"\"\"\"\"\"\"     \"\"\"\"    \"\"\"\"\"\"      \"\"        \"\"";
    cout << endl;                                                                  

    // no input, ask for command
    if(argc == 1){
        // ask for input:
        cout << "'n' - New Game   'l' - Load File   'q' - Quit\n";

        while(play == 0){
            cout << "Volcity> ";
            cin >> input;
            switch(input){
                // list commands
                case 'h':
                    cout << "'h' - Help\n'n' - New Game\n'l' - Load File\n'q' - Quit\n"; 
                break;
            
                // new game
                case 'n':
                    cout << "New City: Enter your city's name:\nNew City> ";
                    cin.ignore();
                    getline(cin, name);
                    yours.setName(name);
                    // ask to change starting cash
                    cout << "Change starting cash? y/n\n" << name << "> ";
                    cin >> input;
                    if(input == 'y'){
                        cout << "Enter starting vash value:\n" << name << "> ";
                        cin >> i;
                        yours.setCash(i);
                    }
                    play = 1;
                break;

                // load file
                case 'l':
                    cin >> name;
                    yours.load(name);
                    play = 1;
                break;

                // quit program
                case 'q':
                    cout << "Exiting...\n";
                    return 0;
                break;

                default:
                    cerr << "Unknown command. 'h' for help.\n";
            }
        }
    }
    // "./volcity load <file> case" 
    else if(argc == 3 && (string)argv[1] == "load"){
        cout << "Not loaded! Not implemented yet!\n";
        return -1;
    }
    else{
        cerr << "Usage: './volcity' or './volcity load [FILENAME]\n";
    }

    if(play == 0){
        cerr << "You aren't supposed to be here!\n";
        return -1;
    } 

    // proceed here once play flag is 1, another input switch statement like above
    yours.print();
    cout << "Enter 'h' for a list of commands.\n";

    while(play == 1){
        cin.clear();
        cin.ignore();
        cout << name << "> ";
        cin >> input;

        switch(input){
        /*
        here: options like build i j, etc.
        focusing only on the basics for now
        */
            case 'h':
                //TODO: list commands
                cout << "'h' - Help   's' - Save   't' - Total stats   'i [i] [j]' - Info about tile (i,j)   'q' - Quit\n";
            break;

            case 's':
                yours.save();
            break;

            // likely not needed, board will only update after certain actions like build/wait
            case 'p':
                yours.print();
            break;

            // return info about tile board[ci - 'a'][j] ('a' corresponds to 0, 'b' --> 1...)
            case 'i':
                cin >> ci >> j;
                if(ci - 'a' < 0 || j < 0){
                    cerr << "Out of bounds!\n";
                    break;
                }
                yours.info(ci - 'a', j);
            break;

            case 't':
                yours.stats();
            break;

            // "wait" a certain amount of time for the city to develop
            case 'w':
                //TODO:
                yours.print();
            break;

            case 'q':
                cout << "Exit? Unsaved progress will be lost. y/n:\n" << name << "> ";
                cin >> input;
                if(input == 'y'){
                    cout << "Exiting...\n";
                    play = 0;
                }
            break;

            default:
                    cerr << "Unknown command. 'h' for help.\n";
        }
    }
    return 0;
}