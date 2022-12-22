
class vec2{
public:
  int x, y;
};

enum piece_colour {white,
            black,
            gray};

class piece{
protected:
  int id;
  piece_colour colour;
  int x_pos;
  int y_pos;

public:
  piece();
  vec2 moves[32];
  int check_moves();
  int move(int x, int y);
  int get_id();
  int set_colour(piece_colour col);
  int get_colour();
  vec2 get_pos();
  int set_pos(int x, int y);
};

class pawn: public piece{
public:
  pawn(piece_colour col, int x, int y);
  int check_moves();
};

class rook: public piece{
  public: rook(piece_colour colour, int x, int y);
  int check_moves();
};

class bishop: public piece{
  public: bishop(piece_colour colour, int x, int y);
  int check_moves();
};

class knight: public piece{
  public: knight(piece_colour colour, int x, int y);
  int check_moves();
};

class queen: public piece{
  public: queen(piece_colour colour, int x, int y);
  int check_moves();
};

class king: public piece{
  public: king(piece_colour colour, int x, int y);
  int check_moves();
};

piece *board[8][8];
piece *taken_pieces[32];
piece *white_pieces[16];
piece *black_pieces[16];

int assign_team(piece *this_piece);

int set_up_piece(piece *this_piece);




