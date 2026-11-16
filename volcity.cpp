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

class city
{
    // each cell of the board is a block
    struct block
    {
      // default empty block, "." with population 0
      string display = ".";
      int pop = 0;
    // bType is the internal building type so we aren't relying on the display string
    // may change to a char and lookup on a map later
      string bType = "Empty";
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
        for(i = 0; i < board.size(); i++){
            for(j = 0; j < board[i].size(); j++) delete &board[i][j];
        }
      }

      void reset()
      {
        size_t i, j;

        /*
        for(i = 0; i < board.size(); i++){
            for(j = 0; j < board[i].size(); j++) delete &board[i][j];
        } 
        */

        board.resize(0);
        totalPop = 1;          
        cash = 10000;
        name = "Knoxville";
        day = 1;              
        mood = 0.5; 
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
        cout << "Day: " << day << "   Total Population: " << totalPop << "     Happiness: " << mood << "     Money: " << cash << endl;
        
      }        

      // print information about tile(i,j) TODO:
      void info(int i, int j)
      {
        cout << board[i][j].bType << ", population: " << board[i][j].pop << endl;
      }

      // save board to a file, TODO: need to decide on formatting
      void save(string s) const
      {
        size_t i, j;
        ofstream fout;
        fout.open(s);
        
        cout << "Saving " << name << " to " << s << "..." << endl;

        fout << name << endl;
        fout << totalPop << " " << day << " " << cash << " " << mood << endl;
        fout << board.size() << " " << board[0].size() << endl;
        for(i = 0; i < board.size(); i++){
            for(j = 0; j < board[1].size(); j++){
                fout << board[i][j].display << " " << board[i][j].pop << " " << board[i][j].bType << " ";
            }
            fout << endl;
        }
      }

      void load(string s)
      {
        size_t i, j, ini, inj;
        int pop;
        string display, bType;
        block *b;
        ifstream fin;
        if(!empty()) reset();
        fin.open(s);

        getline(fin, name);
        cout << "Loading " << name << "..." << endl;
        fin >> totalPop >> day >> cash >> mood;
        fin >> ini >> inj;
        board.resize(ini);
        for(i = 0; i < ini; i++){
            for(j = 0; j < inj; j++){
                b = new block;
                board[i].push_back(*b);
            }
        }

        for(i = 0; i < ini; i++){
            for(j = 0; j < inj; j++){
               fin >> display >> pop >> bType;
               board[i][j].display = display;
               board[i][j].pop = pop;
               board[i][j]. bType = bType;
            }
        }
        cout << "Loaded!\n";
      }

      void advance(int waitTime){
        day += waitTime;
        /*
        algorithm to update population and such goes here, growth probably based on happiness
        population increases -> happiness decays without intervention -> eventually stablizes/decreases
        no idea how to practically implement this
        */
      }

        // TODO:  add more

        // bool edit(char c) to change a tile? t/f if allowed

      // helpers
      bool empty() const
      {
        // return true iff every tile is '.'
        size_t i, j;
        if(board.size() == 0) return true;
        for(i = 0; i < board.size(); i++){
            for(j = 0; j < board[i].size(); j++){
                if(board[i][j].display != ".") return false;
            }
        }
        return true;
      }    

      int getPop() const{return totalPop;}
      int getCash() const{return cash;}
      string getName() const{return name;}
      void setCash(int c){cash = c;}
      void setName(string s){name = s;}
      void updateMood(int c){mood += c;}


    protected:
      vector<vector<block> > board;
      // default starting values
      int totalPop = 1;          // you!
      int cash = 10000;
      string name = "Knoxville";
      int day = 1;               // each action will advance day by one (not checking info)
      double mood = 0.5;       // [0,1] percentage happiness of city

};

int main(int argc, char *argv[])
{
    city yours;
    char input, ci;
    string name, file;
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
                    cin >> file;
                    yours.load(file);
                    name = yours.getName();
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
        yours.load((string)argv[2]);
        name = yours.getName();
        play = 1;
        // TODO: known error, asks for extra cin for no reason when loading like this
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
                cout << "Name save file: ";
                cin >> file;
                yours.save(file);
            break;

            // likely not needed, board will only update (and print) after certain actions like build/wait
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
                cin >> i;
                yours.advance(i);
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