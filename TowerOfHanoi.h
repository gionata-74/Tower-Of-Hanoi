
// importing Stack and other necessary header files.
#include <math.h>
#include "Stack.h"
#include "UserDefinedExceptions.h"
#include <unistd.h>


// The tower game implementation.
class TowerGame {

    private:
        int diskSize, moveCount, maxMove, level;
        const static int MAX_LEVEL = 5, START_LEVEL = 1, MIN_DISK_SIZE = 1;
        // Indices of the towers for code readability
        const static int FIRST_TOWER = 0, SECOND_TOWER = 1, THIRD_TOWER = 2;
        // Declaration of towers as a three stack array.
        Stack<int> towers[3];


    public:
        // The constructor with paramater of initial disk size.
        TowerGame(int diskSize) 
        : moveCount(0) {
            if (diskSize >= MIN_DISK_SIZE) 
                this->diskSize = diskSize;
            else
                throw InvalidDiskSizeException();

            initGame(START_LEVEL);

        }

        // A method that starts the game
        void play() {
            int input;
            while (level <= MAX_LEVEL) {
                displayTowers();
                std::cout<<"\t\t: ";
                std::cin>>input;
                std::cout.flush();
                makeAMove(input);

                if (win()) {
                    this->diskSize++;
                    initGame(++level);
                    system("clear");
                    system("tput setaf 3"); // Linux
                    std::printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tLevel %d\n\n\n\n\n\n\n\n\t\t", level);
                    system("tput setaf 7"); // Linux
                    usleep(1700000);
                }
                else if (lose()) {
                    system("clear");
                    system("tput setaf 9"); // Linux
                    std::printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tGame Over!\n\n\n\n\n\n\n\n\t\t");
                    system("tput setaf 7"); // Linux
                    break;
                }
            }

            if (level >= MAX_LEVEL) {
                system("clear");
                system("tput setaf 3"); // Linux
                std::printf("\n\n\n\n\n\n\n\t\t\t\t\tYou completed all the levels. You pro! Congratulation!\n\n\n\n\n\n\n\n\t\t");
                system("tput setaf 7"); // Linux
            }

        }


    private:
        // initializes the game by seting the level and reseting the towers state.
        void initGame(int level) {
            this->level = level;
            for (auto& tower: towers)
                tower.clear();

            for (int i = diskSize; i > 0; i--)
                towers[FIRST_TOWER].push(i);

            // Calculateing the maximum move allowed in for each level 2^diskSize - 1 + RISERVE_MOVE
            maxMove = std::pow(2, diskSize) + 5 - this->level;
            moveCount = 0;

        }

        // Show towers and other necessay elements in a well formated way to the player.
        void displayTowers() {
            system("clear"); // For Linux
            std::cout<<"\n\n\n\t\t------------------------------------------------------------\n";
            system("tput setaf 45"); // For Linux
            std::printf("\t\t%40s", "Tower Of Hanoi\n");
            system("tput setaf 7"); // For Linux
            std::cout<<"\t\t------------------------------------------------------------\n";
            std::printf("\t\t\tMoves Left: %-3d \t\t\t  Level: %d\n", maxMove - moveCount, level);
            std::cout<<"\t\t------------------------------------------------------------\n";
            menu();
            std::cout<<"\t\t------------------------------------------------------------\n\n\n";
            system("tput setaf 84"); // For Linux
            for (int currentTowerLevel = diskSize; currentTowerLevel > 0; currentTowerLevel--) {
                for (auto& tower : towers) {

                    if (&tower == &towers[FIRST_TOWER])
                        std::cout<<"\t\t";
                        
                    if (tower.getSize() >= currentTowerLevel){
                        std::printf("\t  | %3d   |", tower.next()->getData());
                    }
                    else
                        std::printf("\t  | %3s   |", " ");
                }
                std::printf("\n");
            }            
            system("tput setaf 7"); // For Linux
            std::cout<<"\t\t============================================================\n";
        }
        
        // Used to move a disk from source tower to destination based on the game rule.
        void move(Stack<int>& src, Stack<int>& dst ) {
            if (!src.isEmpty() && (dst.isEmpty() || dst.peek() > src.peek())){
                dst.push(src.pop());
                std::cout<<"\a";
            }
            moveCount++;
        }

        // A method for mapping user input to move operations
        void makeAMove(int opt) {
            switch (opt) {
            case 1:
                move(towers[FIRST_TOWER], towers[SECOND_TOWER]);
                break;
            case 2:
                move(towers[FIRST_TOWER], towers[THIRD_TOWER]);
                break;
            case 3:
                move(towers[SECOND_TOWER], towers[FIRST_TOWER]);
                break;
            case 4:
                move(towers[SECOND_TOWER], towers[THIRD_TOWER]);
                break;
            case 5:
                move(towers[THIRD_TOWER], towers[FIRST_TOWER]);
                break;
            case 6:
                move(towers[THIRD_TOWER], towers[SECOND_TOWER]);
                break;
            }
        }

        //checks if the first two stacks are empty.
        bool win() {
            return towers[FIRST_TOWER].isEmpty() && towers[SECOND_TOWER].isEmpty();
        }

        bool lose() {
            return maxMove <= moveCount;
        }
        
        // Display what move options are available to the user.
        void menu(){
            system("tput setaf 91"); // Linux
            std::printf("\t\t\t <1> 1 -> 2 \t\t\t <4> 2 -> 3\n");
            std::printf("\t\t\t <2> 1 -> 3 \t\t\t <5> 3 -> 1\n");
            std::printf("\t\t\t <3> 2 -> 1 \t\t\t <6> 3 -> 2\n");
            system("tput setaf 7"); // Linux
        }
};

