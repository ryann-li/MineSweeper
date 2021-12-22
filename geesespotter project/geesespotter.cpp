#include "geesespotter_lib.h"
#include "iostream"

char * createBoard(std::size_t xdim, std::size_t ydim){
    char * p_memory = new char[xdim*ydim]();
     return p_memory;    
}
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
for (int i = 0; i < xdim*ydim; i++){
        //checking every entry until we hit a goose
        if (board[i] == 9){
            //increment above entry
            if (i >= xdim){
                if (board[i-xdim] != 9){
                    board[i-xdim]++;
                }
            }
            //increment down entry
            if (i < xdim*ydim-xdim){
                if (board[i+xdim] != 9){
                    board[i+xdim]++;
                }
            }
            //increment left entry
            if ((i % xdim) != 0){
                if (board[i-1] != 9){
                    board[i-1]++;
                }
            }
            //increment rightwards entry
            if ((i+1)%xdim != 0){
                if (board[i+1] != 9){
                    board[i+1]++;
                }
            }
            //increment up-left 
            if (i >= xdim && (i % xdim) != 0){
                if (board[i-xdim-1] != 9){
                    board[i-xdim-1]++;
                }
            }
            //increment up-right
            if (i >= xdim && (i+1)%xdim != 0){
                if (board[i-xdim+1] != 9){
                    board[i-xdim+1]++;
                }
            }
            //increment left down
            if (i < xdim*ydim-xdim && (i % xdim) != 0){
                if (board[i+xdim-1] != 9){
                    board[i+xdim-1]++;
                }
            }
            //increment right down
            if (i < xdim*ydim-xdim && (i+1)%xdim != 0){
                if (board[i+xdim+1] != 9){
                    board[i+xdim+1]++;
                }
            }
        }
    }
}
void cleanBoard(char *board){
    delete[] board;
    board = nullptr;
}
void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
    for (int i = 0; i < (xdim * ydim); ++i){
        board[i] |= hiddenBit();
    }
}
void printBoard(char *board, std::size_t xdim, std::size_t ydim){
     for (int i = 0; i < (xdim * ydim); ++i){
        //check if is marked
        if (board[i] & markedBit()){
            std::cout << 'M';
        }
        //check if is hidden 
        else if (board[i] & hiddenBit()){
            std::cout << '*';
        }
        else{
            std::cout << int(board[i]);
        }
        if (((i + 1) % xdim) == 0){
            std::cout << std::endl;
        }
    }}
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int i = yloc * xdim + xloc;
    if (board[i] & hiddenBit()){
        if (int(board[i] & valueMask()) == 9){
            //unhides value
            board[i] &= valueMask();
            return 9; 
        }
        else if (int(board[i] & valueMask()) == 0){
            board[i] &= valueMask();
            //up
            if (i >= xdim){
                board[i-xdim] &= valueMask();
            }
            //down
            if (i < xdim*ydim-xdim){
                board[i+xdim] &= valueMask();
            }
            //left
            if ((i % xdim) != 0){
                board[i-1] &= valueMask();
            }
            //right
            if ((i+1)%xdim != 0){
                board[i+1] &= valueMask();
            }
            //up-left
            if (i >= xdim && (i % xdim) != 0){
                board[i-xdim-1] &= valueMask();
            }
            //up-right
            if (i >= xdim && (i+1)%xdim != 0){
                    board[i-xdim+1] &= valueMask();
            }
            //down-left
            if (i < xdim*ydim-xdim && (i % xdim) != 0){
                
                    board[i+xdim-1] &= valueMask();
                
            }
            //down-right
            if (i < xdim*ydim-xdim && (i+1)%xdim != 0){    
                    board[i+xdim+1] &= valueMask();  
            }
            return 0;
        }
        else {
            board[i] &= valueMask(); 
            return 0;  
        }

    }
    else if (board[i] & markedBit()){
        return 1;
    }
    else{
        return 2;
    }
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int index = 0;
    for (int i = 0; i < xdim; ++i){
        for (int j = i*xdim; j < xdim + i*xdim; ++j){
            if (j == yloc * xdim + xloc){
                index = j;
            }
            }
        }
    for (int j = 0; j < xdim * ydim; ++j){
        if (j == index){
            if (!(board[j] & hiddenBit())){
                return 2;
            }
            
            else if (board[j] & markedBit()){
                board[j] ^= markedBit();
            }
            else{
                board[j] |= markedBit();
            }
            return 0;
        }
    }
}
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    bool flag = true;
    for (int i = 0; i < xdim * ydim; i++){
        //thsi checks if the value is not equal to 9 and hidden, in that case the 
        //game is not won
        if (int(board[i] & valueMask()) != 9 && (board[i] & hiddenBit())){
            flag = false;
        }

    }
    return flag;
}
