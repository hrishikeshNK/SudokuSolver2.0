#include <iostream>
#include<vector>
#include<fstream>

using namespace std;

class cell{
 public:
     int cell_value = 0;
     bool tapped = false;
     vector<int> candidates = {1,2,3,4,5,6,7,8,9};
     void flush_candidates(int value);
     void find_and_remove(int value);
     bool is_absent(int value);
     bool fix_value();
     void view_candidates();
};

void cell :: view_candidates(){
    cout<<endl;
    for(int i = 0; i < candidates.size(); i++)
        cout<<candidates[i]<<" ";
    cout<<endl;
}

void cell :: flush_candidates(int value){
   while(candidates.size() > 1)
       candidates.pop_back();
   candidates[0] = value;
}

void cell :: find_and_remove(int value){
   bool found = false;
   for(int i = 0; i < candidates.size(); i++){
        if(candidates[i] == value)
            found = true;
        if(found && i < candidates.size()-1)
            candidates[i] = candidates[i+1];
   }
   if(found && candidates.size()>1) candidates.pop_back();
}

bool cell :: is_absent(int value){
   for(int i = 0; i < candidates.size(); i++){
        if(candidates[i] == value)
            return false;
   }
   return true;
}

bool cell :: fix_value(){
    if(candidates.size() == 1){
        cell_value = candidates[0];
        return true;
    }
    return false;
}

cell puzzle[9][9];

bool solved(){
    int sum = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            sum = sum + puzzle[i][j].cell_value;

        }
    }

    if(sum == 405) return true;

    return false;
}

void display(){
    for(int i = 0; i < 9; i++){
       for(int j = 0; j < 9; j++){
           cout<<puzzle[i][j].cell_value<<" ";
       }cout<<endl;
   }
  cout<<endl;
}

void read_puzzle(){
  ifstream cin("in.txt");
   for(int i = 0; i < 9; i++){
       for(int j = 0; j < 9; j++){
           cin>>puzzle[i][j].cell_value;
           if(puzzle[i][j].cell_value != 0)
              puzzle[i][j].flush_candidates(puzzle[i][j].cell_value);
       }
   }
}

void tap(int x, int y){

  int block_x, block_y;
  for(int i = 0; i < 9; i++){
   if(i!=y )
    puzzle[x][i].find_and_remove(puzzle[x][y].cell_value);
   if(i!=x)
    puzzle[i][y].find_and_remove(puzzle[x][y].cell_value);
  }

  if(x >= 6) block_x = 6;
  else if(x >= 3) block_x = 3;
  else block_x = 0;

  if(y >= 6) block_y = 6;
  else if(y >= 3) block_y = 3;
  else block_y = 0;

  for(int i = block_x; i < block_x+3; i++){
    for(int j = block_y; j < block_y+3; j++){
       if(!(i == x && j == y))
          puzzle[i][j].find_and_remove(puzzle[x][y].cell_value);
    }
  }

}

void flushh(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(puzzle[i][j].tapped==false && puzzle[i][j].cell_value!=0){
                 tap(i,j);
                 puzzle[i][j].tapped = true;
            }
        }
    }
}

int MVP(int x, int y){

   bool break_flag = false;
   int counter = 0;
   for(int num = 1; num < 10; num++){
     for(int i = 0; i < 9; i++){

         if(i == y) continue;

         if(puzzle[x][i].cell_value == num){
            break_flag = true;
            break;
         }

         if(puzzle[x][i].is_absent(num))
          counter++;
    }

    if(counter == 8){
         puzzle[x][y].cell_value = num;
         puzzle[x][y].flush_candidates(num);
         tap(x,y);
         return 1;
    }
    counter = 0;


    for(int i = 0; i < 9; i++){

       if(i == x) continue;

       if(puzzle[i][y].cell_value == num){
          break_flag = true;
          break;
       }

       if(puzzle[i][y].is_absent(num))
          counter++;
    }


    if(counter == 8){
       puzzle[x][y].cell_value = num;
       puzzle[x][y].flush_candidates(num);
       tap(x,y);

       return 1;
    }
    counter = 0;


    int block_x, block_y;

    if(x >= 6) block_x = 6;
    else if(x >= 3) block_x = 3;
    else block_x = 0;

    if(y >= 6) block_y = 6;
    else if(y >= 3) block_y = 3;
    else block_y = 0;

    for(int r = block_x; r < block_x + 3; r++){

      if(break_flag == true){
        break;
      }
      for(int c = block_y; c < block_y + 3; c++){
          if(!(r == x && c == y)){
              if(puzzle[r][c].cell_value == num){
                   break_flag = true;
                   break;
              }
            if(puzzle[r][c].is_absent(num))
                counter++;
           }
        }
     }

    if(counter == 8){
       puzzle[x][y].cell_value = num;
       puzzle[x][y].flush_candidates(num);
       tap(x,y);
       return 1;
     }
    counter = 0;
 }
 return 0;
}

void solve(){

  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
        if(puzzle[i][j].cell_value == 0){
            if(puzzle[i][j].candidates.size() == 1){
                puzzle[i][j].cell_value = puzzle[i][j].candidates[0];
                flushh();
            }
            else{
                int did_you_add_a_number = MVP(i,j);
              }
            }
          }
        }
 }

int main()
{
    read_puzzle();
    flushh();
    display();

    while(!solved()){
       solve();
       //flushh();
    }

    display();
    return 0;
}
