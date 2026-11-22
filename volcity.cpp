/*
main.cpp
11/21/26
Latest update: building/destroying tiles
Most of the work to be done is in the advance function
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

class city
{
    // each cell of the board is a block
    struct block
    {
      string display = ".";            // what this block displays when printing
      string bType = "Empty";          // building type
      int pop = 0;                     // current population
      int maxPop = 0;                  // max possible population
      int level = 0;                   // can only upgrade to level 1 from level 0, 1-> 2....
      int vPos = 0;                    // internal building type for switch statements
    };

    public:
      /* 
      constructor, define initial game state here
      */
      city()
      {
        size_t i, j;
        block *b;

        // initialize block types map for copying later
        initBlockTypes();

        // fill in with empty block structs, default size 5x5
        board.resize(5);
        for(i = 0; i < 5; i++){
            for(j = 0; j < 5; j++){
                b = new block;
                board[i].push_back(*b);
            }
        }

        // set tiles by copying from vector
        board[0][0] = types[2];
        maxPop += 10;
        board[0][0].pop = 10;
        totalPop += 10;
        board[0][1] = types[3];
        maxPop += 10;
        board[0][2] = types[5];
        maxPop += 200;

        for(i = 0; i < board.size(); i++){
            board[1][i] = types[1];
        }
        
      }

      // destroying blocks as they were initialized with pointers
      // TODO: check with valgrind before submission
      ~city()
      {
        map<string,block>::iterator mit;
        size_t i, j;
        for(i = 0; i < board.size(); i++){
            for(j = 0; j < board[i].size(); j++) delete &board[i][j];
        }
        //for(mit = types.begin(); mit != types.end(); mit++) delete &mit;
      }

      // initialize block types - would be a nice thing to load from a file in the future
      void initBlockTypes()
      {
        if(!types.empty()) return;

        block *b; 
        b = new block;
        b->bType = "Empty";
        types.push_back(*b);

        b = new block;
        b->bType = "Road";
        b->vPos = 1;
        b->display = "=====";
        types.push_back(*b);
        
        b = new block;
        b->bType = "House";
        b->display = "[:]";
        b->vPos = 2;
        b->maxPop = 10;
        types.push_back(*b);

        b = new block;
        b->bType = "Townhouse";
        b->display = "[::]";
        b->vPos = 3;
        b->maxPop = 100;
        b->level = 1;
        types.push_back(*b);

        b = new block;
        b->bType = "Apartment";
        b->display = "[:::]";
        b->vPos = 4;
        b->maxPop = 200;
        b->level = 2;
        types.push_back(*b);

        b = new block;
        b->bType = "Hospital";
        b->display = "=H=";
        b->vPos = 5;
        b->maxPop = 200;
        b->level = 1;
        types.push_back(*b);
        
        b = new block;
        b->bType = "Park";
        b->display = "{+}";
        b->vPos = 6;
        b->maxPop = 5;
        b->level = 1;
        types.push_back(*b);
      }
      
      void reset()
      {
        // resizing like this may cause memory leak, check w/ valgrind later
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
            // a-z then just numbers. aa, ab... would be cooler, maybe later
            if(i <= 26) printf("%c ", i + 'a');
            else printf("%d ", i - 'a');
            // width of 5 for each string, change if needed
            for(j = 0; j < board[i].size(); j++){
                s = board[i][j].display;
                printf("%5s", s.c_str());
            }
            cout << endl;
        }
        stats();
      }        

      // print city stats (board size, population...)
      void stats() const
      {
        cout << "Day: " << day << "   Total Population: " << totalPop << "     Happiness: " << (mood * 100) << "%     Money: " << cash << endl;
        
      }        

      // print information about tile(i,j)
      void info(int i, int j)
      {
        if(i < 0 || j < 0 || i >= board.size() || j >= board.size()){
            cerr << "Out of bounds!\n";
            return;
        }
        cout << board[i][j].bType << ", population: " << board[i][j].pop << "/" << board[i][j].maxPop << endl;
      }

      // save board to a file
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
            for(j = 0; j < board[i].size(); j++){
                fout << board[i][j].vPos << " " << board[i][j].pop << " ";
            }
            if(i < board.size() -1) fout << endl;
        }
      }

      void load(string s)
      {
        size_t i, j, ini, inj;
        int pop, vPos;
        string display;
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
                fin >> vPos >> pop;
                board[i][j] = types[vPos];
                board[i][j].pop = pop;
            }
        }
        cout << "Loaded!\n";
      }

	  // added primitive population growth
      void advance(int waitTime)
      {
        day += waitTime;
		int stable = 0;
		
		int growth = sqrt(totalPop) * (2 * mood);
		if (growth > 0) {
			if (mood > 0.2) {
				mood = mood - (growth/(totalPop + growth));
			}
			else {
				mood = mood + (growth/(totalPop + growth));
			}
		}

		if((totalPop + growth) <= maxPop) totalPop = totalPop + growth;

        cash += 100 * ((double)totalPop/10); // allowance of $100 per 10 people per day, for now


        /*TODO:: 
        1. check if the post-growth pop. exceeds city's maxPop  (DONE)
        2. assign the growing population to the current buildings
            this seems like a network flow problem but thats complicated, can just scan the whole board linearly
        3. update mood depending on difference between totalPop and maxPop
        4. run BFS in this advance section to check for road connections too
        */
      }

      // build/upgrade
      void edit(char ic, int j)
      {
        int i, pop;
        char input;
        i = ic - 'a';
        if(i < 0 || j < 0 || i >= board.size() || j >= board.size()){
            cerr << "Out of bounds!\n";
            return;
        }

        // only allowing house upgrades and empty building for now
        switch(board[i][j].vPos){
            case 0:
                cout << "What would you like to build?\n b - house, $100   h - hospital, $1000   p - park, $100   r - road, $50" << endl;
                cin >> input;                
                switch(input){
                    case 'b':
                        board[i][j] = types[2];
                        maxPop += board[i][j].maxPop;
                        cash -= 100;
                    break;

                    case 'h':
                        board[i][j] = types[5];
                        maxPop += board[i][j].maxPop;
                        cash -= 1000;
                    break;

                    case 'p':
                        board[i][j] = types[6];
                        maxPop += board[i][j].maxPop;
                        cash -= 100;
                    break;

                    case 'r':
                        board[i][j] = types[1];
                        cash -= 50;
                    break;
                }
                
            break;
            case 2:
                cout << "Upgrade house to townhouse for $200? y/n" << endl;
                cin >> input;
                if(input != 'y') break;
                pop = board[i][j].pop;
                maxPop -= board[i][j].maxPop;
                board[i][j] = types[3];
                board[i][j].pop = pop;
                maxPop += board[i][j].maxPop;
                cash -= 200;
            break;
            case 3:
                cout << "Upgrade townhouse to apartment for $1000? y/n" << endl;
                cin >> input;
                if(input != 'y') break;
                pop = board[i][j].pop;
                maxPop -= board[i][j].maxPop;
                board[i][j] = types[4];
                board[i][j].pop = pop;
                maxPop += board[i][j].maxPop;
                cash -= 1000;
            break;
            default:
                cerr << "Invalid operation!\n";
        }
        advance(1);
        print();
        return;
      }

      void destroy(char ic, int j)
      {
        int i;
        char input;
        i = ic - 'a';
        if(i < 0 || j < 0 || i >= board.size() || j >= board.size()){
            cerr << "Out of bounds!\n";
            return;
        }
        cout << "Destroy " << board[i][j].bType << "? y/n" << endl;
        cin >> input;
        if(input != 'y') return;
        if(totalPop > board[i][j].pop) totalPop -= board[i][j].pop;
        else totalPop = 1;
        board[i][j] = types[0];

        advance(1);
        print();
        return;
      }

      // 'buy new land'
      void expand()
      {
        int i, size;
        char input;
        block *b;
        cout << "Buy new land for $1000? y/n" << endl;
        cin >> input;
        if(input != 'y') return;
        size = board.size();
        board.resize(size + 1);
        
        for(i = 0; i < size; i++){
            b = new block;
            board[size].push_back(*b);
        }

        for(i = 0; i < size + 1; i++){
            b = new block;
            board[i].push_back(*b);
        }
        cash -= 1000;
        print();
      }



      // helpers
      bool empty() const
      {
        // return true iff every tile is '.'
        size_t i, j;
        if(board.size() == 0) return true;
        for(i = 0; i < board.size(); i++){
            for(j = 0; j < board[i].size(); j++){
                if(board[i][j].vPos != 0) return false;
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
      vector<vector<block> > board;   // hold block structs for city
      vector<block> types;            // define basic block types with default values to copy from
      // default starting values
      int totalPop = 1;               // you!
      int maxPop = 0;
      int cash = 10000;
      string name = "Knoxville";
      int day = 1;                    // each action will advance day by one (not checking info)
      double mood = 0.5;              // [0,1] percentage happiness of city

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

        // user interface
        switch(input){
            // list commands
            case 'h':
                cout << "'h' - Help   's' - Save   'q' - Quit   't' - Total stats   'i [i] [j]' - Info about tile (i,j)   'b [i] [j]' - Edit tile (i,j)"   
                << "'d' - Destroy tile (i,j)    'e' - Expand board" << endl;
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
                yours.info(ci - 'a', j);
            break;

            case 't':
                yours.stats();
            break;

            // "wait" a certain amount of time for the city to develop
            case 'w':
                // allow only wait 1 day for now
                //cin >> i;
                yours.advance(1);
                yours.print();
            break;

            case 'b':
                cin >> ci >> j;
                yours.edit(ci, j);
            break;

            case 'd':
                cin >> ci >> j;
                yours.destroy(ci, j);
            break;
            
            case 'e':
                yours.expand();
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
