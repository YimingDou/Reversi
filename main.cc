#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;
  vector<int> check;

  // Add code here
  int acc = 0;
  int size = 0;

  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      size = n;
      // Add code here
      //g = Grid();
      g.init(n);
      cout << g;
      for (int i = 0; i < n * n; ++i) {
          check.push_back(0);
      }
      check[(n/2-1) * n + n/2-1] = 1;
      check[(n/2-1) * n + n/2] = 1;
      check[(n/2) * n + n/2-1] = 1;
      check[(n/2) * n + n/2] = 1;
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      // Add code here
      Colour colour = acc % 2 == 0 ? Colour::Black : Colour::White;
      if (!(r >= 0 && r < size && c >= 0 && c < size && check[r * size + c] == 0)) {
          continue;
      }
      check[r * size + c] = 1;
      g.setPiece(r, c, colour);
      acc++;
      cout << g ;
      if (g.isFull()) {
          string winMsg = g.whoWon() == Colour::Black ? "Black Wins!" : "White Wins!";
          cout << winMsg << endl;
          return 0;
      }
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
