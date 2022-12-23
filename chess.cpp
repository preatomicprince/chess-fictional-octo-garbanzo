#include "chess.hpp"
#include <iostream>

/******************************************************************************
*******************************************************************************
**                                                                           **
**                                FUNCTIONS                                  **
**                                                                           **
*******************************************************************************
******************************************************************************/

int piece::get_id(){
  return id;
}

int piece::set_colour(piece_colour col){
  colour = col;
  return 1;
}

int piece::get_colour(){
  return colour;
}

piece_type piece::get_type(){
  return type;
}

vec2 piece::get_pos(){
  vec2 pos;
  pos.x = x_pos;
  pos.y = y_pos;
  return pos; 
}

int piece::move(int x, int y){ //finish later maybe
  for (int i = 0; i < 32; i++) {

    if (moves[i].x == x && moves[i].y == y){
      if (board[x][y]->get_colour() != gray){
        for (int j = 0; j < 32; j++) {
          if(taken_pieces[j]->get_id() == 0){
            taken_pieces[j] = board[x][y];
          }
        }
      board[x][y] = this;
      }
      return 1;
    }
  }
  return -1;
}

int print_board(){
  char board_row[8];
  for (size_t y = 0; y < 8; y++){
    for (size_t x = 0; x < 8; x++){
      switch (board[x][y]->get_type()){
        case paw:
          board_row[x] = *"p";
          break;

        case bis:
          board_row[x] = *"b";
          break;

        case kni:
          board_row[x] = *"h";
          break;

        case que:
          board_row[x] = *"q";
          break;

        case kin:
          board_row[x] = *"k";
          break;
        
        case nun:
          board_row[x] = *"x";
          break;
      }
    }

    for (size_t i = 0; i < 8; i++){
      std::cout << board_row[i];
    }
    std::cout<<"\n";
  }
  return 1;
}

int set_piece(piece piece){
  board[piece.get_pos().x][piece.get_pos().y] = &piece;
  return 1;
}


/******************************************************************************
*******************************************************************************
**                                                                           **
**                                CONSTRUCTORS                               **
**                                                                           **
*******************************************************************************
******************************************************************************/


piece::piece(){
  colour = gray;
  x_pos = 0;
  y_pos = 0;
  type = nun;
}
pawn::pawn(piece_colour col, int x, int y){
  colour = col;
  x_pos = x;
  y_pos = y;
  type = paw;
}

/******************************************************************************
*******************************************************************************
**                                                                           **
**                               CHECK MOVES                                 **
**                                                                           **
*******************************************************************************
******************************************************************************/

int pawn::check_moves(){
  for (int  i = 0; i < 32; i++) { //reset moves list
    moves[i].x = 0;
    moves[i].y = 0;
  }

  int move_count = 0;
  switch(colour){
    case white:
      if (y_pos  == 1){ //Starting double move WHITE
        moves[move_count].x = x_pos;
        moves[move_count].y = y_pos+2;
        move_count += 1;
      }
      moves[move_count].x = x_pos; //standard single move WHITE
      moves[move_count].y = y_pos+1;
      move_count += 1;

      if (board[x_pos-1][y_pos+1]->get_colour() == black){ //take piece to left WHITE
        moves[move_count].x = x_pos-1;
        moves[move_count].y = y_pos+1;
        move_count += 1;
      }

      if (board[x_pos+1][y_pos+1]->get_colour() == black){ //take piece to right WHITE
        moves[move_count].x = x_pos+1;
        moves[move_count].y = y_pos+1;
        move_count += 1;
      }
      break;
    case black:
      if (y_pos  == 6){ //Starting double move BLACK
        moves[move_count].x = x_pos;
        moves[move_count].y = y_pos-2;
        move_count += 1;
      }

      moves[move_count].x = x_pos; //standard single move BLACK
      moves[move_count].y = y_pos-1;
      move_count += 1;


      if (board[x_pos-1][y_pos-1]->get_colour() == black && //take piece to left BLACK
          x_pos-1 >= 0){
        moves[move_count].x = x_pos-1;
        moves[move_count].y = y_pos-1;
        move_count += 1;
      }

      if (board[x_pos+1][y_pos-1]->get_colour() == black && //take piece to right BLACK
          x_pos+1 < 8){
        moves[move_count].x = x_pos+1;
        moves[move_count].y = y_pos-1;
        move_count += 1;
      }
      break;
    case gray:
        return -1;
  }
  return 1;
}


int rook::check_moves(){
  for (int  i = 0; i < 32; i++) { //reset moves list
    moves[i].x = 0;
    moves[i].y = 0;
  }
  int move_count = 0;

  int hp_halt = 0;  //Horizontal +ve halt
  int hn_halt = 0;  //Horizontal -ve halt
  int vp_halt = 0;  //Vertical +ve halt
  int vn_halt = 0;  //vertical -ve halt

  for (int i = 0; i < 8; i++) {
    if (hp_halt == 0 && x_pos+i <= 8) { //Horizontal moves RIGHT
      if (board[x_pos+i][y_pos]->get_colour() != colour){
        moves[move_count].x = x_pos+i;
        moves[move_count].y = y_pos;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        hp_halt = 1;
      }
    }

    if (hn_halt == 0 && x_pos-i >= 1) { //Horizontal moves LEFT
      if (board[x_pos-i][y_pos]->get_id() == 0 ||
          board[x_pos-i][y_pos]->get_colour() != colour){
        moves[move_count].x = x_pos-i;
        moves[move_count].y = y_pos;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        hn_halt = 1;
      }
    }

    if (vp_halt == 0 && y_pos+i <= 8) { //Vertical moves UP
      if (board[x_pos][y_pos+i]->get_colour() != colour){
        moves[move_count].x = x_pos;
        moves[move_count].y = y_pos+1;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        vp_halt = 1;
      }
    }

    if (vn_halt == 0 && y_pos-i >= 1) { //Vertical moves DOWN
      if (board[x_pos][y_pos-i]->get_colour() != colour){
        moves[move_count].x = x_pos;
        moves[move_count].y = y_pos-i;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        vn_halt = 1;
      }
    }
  }
  return 1;
}

int bishop::check_moves(){
  for (int  i = 0; i < 32; i++) { //reset moves list
    moves[i].x = 0;
    moves[i].y = 0;
  }
  int move_count = 0;
  int hpvp_halt = 0;  //Horizontal +ve halt
  int hpvn_halt = 0;  //Horizontal -ve halt
  int hnvp_halt = 0;  //Vertical +ve halt
  int hnvn_halt = 0;  //vertical -ve halt

  for (int i = 0; i < 8; i++){
    if (hpvp_halt == 0 && x_pos+i <= 8 && y_pos <= 8) { //Horizontal POSITIVE & Vertical POSITIVE
      if (board[x_pos+i][y_pos+i]->get_colour() != colour){
        moves[move_count].x = x_pos+i;
        moves[move_count].y = y_pos+i;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        hpvp_halt = 1;
      }
    }

    if (hpvn_halt == 0 && x_pos+i <= 8 && y_pos <= 8) { //Horizontal POSITIVE & Vertical NEGATIVE
      if (board[x_pos+i][y_pos-i]->get_colour() != colour){
        moves[move_count].x = x_pos+i;
        moves[move_count].y = y_pos-i;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        hpvn_halt = 1;
      }
    }

    if (hnvp_halt == 0 && x_pos+i <= 8 && y_pos <= 8) { //Horizontal NEGATIVE & Vertical POSITIVE
      if (board[x_pos-i][y_pos+i]->get_colour() != colour){
        moves[move_count].x = x_pos-i;
        moves[move_count].y = y_pos+i;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        hnvp_halt = 1;
      }
    }
    if (hnvn_halt == 0 && x_pos+i <= 8 && y_pos <= 8) { //Horizontal NEGATIVE & Vertical NEGATIVE
      if (board[x_pos-i][y_pos-i]->get_colour() != colour){
        moves[move_count].x = x_pos-i;
        moves[move_count].y = y_pos-i;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        hnvp_halt = 1;
      }
    }
  }
  return 1;
}

int knight::check_moves(){
  for (int  i = 0; i < 32; i++) { //reset moves list
    moves[i].x = 0;
    moves[i].y = 0;
  }
  int move_count = 0;

  vec2 knight_moves[8];

  knight_moves[0].x = -2;
  knight_moves[0].y = -1;

  knight_moves[1].x = -1;
  knight_moves[1].y = -2;

  knight_moves[2].x = 2;
  knight_moves[2].y = 1;

  knight_moves[3].x = 1;
  knight_moves[3].y = 2;

  knight_moves[4].x = -2;
  knight_moves[4].y = 1;

  knight_moves[5].x = -1;
  knight_moves[5].y = 2;

  knight_moves[6].x = 1;
  knight_moves[6].y = -2;

  knight_moves[7].x = 2;
  knight_moves[7].y = -1;

  for (int i = 0; i < 8; i++) {
    if(board[knight_moves[i].x][knight_moves[i].y]->get_colour() != colour){
          moves[move_count] = knight_moves[i];
          move_count += 1;
        }
  }
  return 1;
}

int queen::check_moves(){
  for (int  i = 0; i < 32; i++) { //reset moves list
    moves[i].x = 0;
    moves[i].y = 0;
  }
  int move_count = 0;

  int hp_halt = 0;  //Horizontal +ve halt
  int hn_halt = 0;  //Horizontal -ve halt
  int vp_halt = 0;  //Vertical +ve halt
  int vn_halt = 0;  //vertical -ve halt

  for (int i = 0; i < 8; i++) {
    if (hp_halt == 0 && x_pos+i < 8) { //Horizontal moves RIGHT
      if (board[x_pos+i][y_pos]->get_colour() != colour){
        moves[move_count].x = x_pos+i;
        moves[move_count].y = y_pos;
        move_count =+ 1;
      }
      if (board[x_pos+i][y_pos]->get_colour() != gray){
        hp_halt = 1;
      }
    }

    if (hn_halt == 0 && x_pos-i >= 0) { //Horizontal moves LEFT
      if (board[x_pos-i][y_pos]->get_colour() != colour){
        moves[move_count].x = x_pos-i;
        moves[move_count].y = y_pos;
        move_count =+ 1;
      }
      if (board[x_pos+i][y_pos]->get_colour() != gray){
        hn_halt = 1;
      }
    }

    if (vp_halt == 0 && y_pos+i < 8) { //Vertical moves UP
      if (board[x_pos][y_pos+i]->get_id() == 0 ||
          board[x_pos][y_pos+i]->get_colour() != colour){
        moves[move_count].x = x_pos;
        moves[move_count].y = y_pos+1;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos+i]->get_colour() != gray){
        vp_halt = 1;
      }
    }

    if (vn_halt == 0 && y_pos-i >= 0) { //Vertical moves DOWN
      if (board[x_pos][y_pos-i]->get_colour() != colour){
        moves[move_count].x = x_pos;
        moves[move_count].y = y_pos-i;
        move_count =+ 1;
      }
      if (board[x_pos][y_pos-i]->get_colour() != gray){
        vn_halt = 1;
      }
    }
  }
  int hpvp_halt = 0;  //Horizontal +ve halt
  int hpvn_halt = 0;  //Horizontal -ve halt
  int hnvp_halt = 0;  //Vertical +ve halt
  int hnvn_halt = 0;  //vertical -ve halt

  for (int i = 0; i < 8; i++){
    if (hpvp_halt == 0 && x_pos+i < 8 && y_pos < 8) { //Horizontal POSITIVE & Vertical POSITIVE
      if (board[x_pos+i][y_pos+i]->get_colour() != colour){
        moves[move_count].x = x_pos+i;
        moves[move_count].y = y_pos+i;
        move_count =+ 1;
      }
      if (board[x_pos+i][y_pos+i]->get_colour() != gray){
        hpvp_halt = 1;
      }
    }

    if (hpvn_halt == 0 && x_pos+i < 8 && y_pos < 8) { //Horizontal POSITIVE & Vertical NEGATIVE
      if (board[x_pos+i][y_pos-i]->get_colour() != colour){
        moves[move_count].x = x_pos+i;
        moves[move_count].y = y_pos-i;
        move_count =+ 1;
      }
      if (board[x_pos+i][y_pos-i]->get_colour() != gray){
        hpvn_halt = 1;
      }
    }

    if (hnvp_halt == 0 && x_pos+i < 8 && y_pos < 8) { //Horizontal NEGATIVE & Vertical POSITIVE
      if (board[x_pos-i][y_pos+i]->get_colour() != colour){
        moves[move_count].x = x_pos-i;
        moves[move_count].y = y_pos+i;
        move_count =+ 1;
      }
      if (board[x_pos-i][y_pos+i]->get_colour() != gray){
        hnvp_halt = 1;
      }
    }
    if (hnvn_halt == 0 && x_pos+i < 8 && y_pos < 8) { //Horizontal NEGATIVE & Vertical NEGATIVE
      if (board[x_pos-i][y_pos-i]->get_colour() != colour){
        moves[move_count].x = x_pos-i;
        moves[move_count].y = y_pos-i;
        move_count =+ 1;
      }
      if (board[x_pos-i][y_pos-i]->get_colour() != gray){
        hnvp_halt = 1;
      }
    }
  }
  return 1;
}

int king::check_moves(){
  for (int  i = 0; i < 32; i++) { //reset moves list
    moves[i].x = 0;
    moves[i].y = 0;
  }
  int move_count = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
        continue;
      } else{
        if (board[i][j]->get_colour() == colour) {
          continue;
        } else{
          moves[move_count].x = i;
          moves[move_count].y = j;
          move_count += 1;
        }
      }
    }
  }
  return 1;
}
int main(int argc, char const *argv[]) {
  piece blank_piece = piece();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = &blank_piece;
    }
  }
  pawn bp0(black, 0, 6);
  set_piece(bp0);
  pawn bp1(black, 1, 6);
  set_piece(bp1);
  pawn bp2(black, 2, 6);
  set_piece(bp2);
  pawn bp3(black, 3, 6);
  set_piece(bp3);
  pawn bp4(black, 4, 6);
  set_piece(bp4);
  pawn bp5(black, 5, 6);
  set_piece(bp5);
  pawn bp6(black, 6, 6);
  set_piece(bp6);
  pawn bp7(black, 7, 6);
  set_piece(bp7);
 
  pawn wp0(white, 0, 1);
  set_piece(wp0);
  pawn wp1(white, 1, 1);
  set_piece(wp1);
  pawn wp2(white, 2, 1);
  set_piece(wp2);
  pawn wp3(white, 3, 1);
  set_piece(wp3);
  pawn wp4(white, 4, 1);
  set_piece(wp4);
  pawn wp5(white, 5, 1);
  set_piece(wp5);
  pawn wp6(white, 6, 1);
  set_piece(wp6);
  pawn wp7(white, 7, 1);
  set_piece(wp7);
  
  wp2.check_moves();
  print_board();
  return 0;
}
