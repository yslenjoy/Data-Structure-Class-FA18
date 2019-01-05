#include "maze.h"
#include "dsets.h"
#include <stdlib.h> // rand
#include <queue>
#include <map>
#include <algorithm> // std::random_shuffle

using namespace std;

SquareMaze::SquareMaze() {
  // do nothing
}

void SquareMaze::makeMaze(int width, int height) {
  height_ = height;
  width_ = width;
  for (int i = 0; i < width * height; i++) {
    dWall.push_back(true);
    rWall.push_back(true);
  }

  DisjointSets dsets;
  dsets.addelements(width_*height_);

  // "until there are no more walls that could be deleted without creating a cycle."
  // means that every cell in the last low can have it's own solutions
  // therefore, in solveMaze() function: lastRows.size() = width_ - 1

  // // random shuffle all the points
  // vector<pair<int, int>> all_coords;
  // for (int w = 0; w < width_; w++) {
  //   for (int h = 0; h < height_; h++) {
  //     pair<int, int> coord(w, h);
  //     all_coords.push_back(coord);
  //   }
  // }
  // srand(time(0)); // make sure get a different random at each shuffle
  // random_shuffle(all_coords.begin(), all_coords.end());

  // while loop condition: untill all the cells are connected >> size
  // of each element should be width_ * height_
  while (dsets.size(0) != width_ * height_) {
    int randX = rand() % width_;
    int randY = rand() % height_;
    bool randR = rand() % 2; // 1 true to break right wall, or down wall
    int cur = randX + randY * width_;
    int curRight = randX + randY * width_ + 1;
    int curDown = randX + (randY + 1) * width_;
    // X < width_ -1 or Y < height_ - 1: make sure not to break the wall on the perimeter
    if (randR) {
      if (randX < (width_ - 1) && rWall[cur] && dsets.find(cur) != dsets.find(curRight)) {
           // break the right wall
           // cout << "here=-------- X:" << randX << endl;
           dsets.setunion(cur, curRight);
           rWall[cur] = false;
         }
    } else if (randY < (height_ - 1) && dWall[cur] && dsets.find(cur) != dsets.find(curDown)) {
      dsets.setunion(cur, curDown);
      dWall[cur] = false;
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  if (dir == 0) {
    return !rWall[x + y * width_];
  }
  if (dir == 1) {
    return !dWall[x + y * width_];
  }
  if (dir == 2) {
    if (x == 0) {
      return false;
    }
    return !rWall[x + y * width_ - 1];
  }
  if (dir == 3) {
    if (y == 0) {
      return false;
    }
    return !dWall[x + (y - 1) * width_];
  }
  return false;
}


void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if (dir == 0) {
    rWall[x + y * width_] = exists;
  }
  else if (dir == 1) {
    dWall[x + y * width_] = exists;
  }
}


vector<int> SquareMaze::solveMaze() {
  queue<int> q; // stack used for BFS: elements: 0 ~ (width_ * height_ - 1);
  vector<bool> visited;
  vector<int> lastRows; // used to trace all the possible path to the last row
  map<int, int> directions; // the direction from one cell to another cell

  // constructor for BFS
  for (int i = 0; i < width_ * height_; i++) {
    visited.push_back(false);
  }
  visited[0] = true;
  q.push(0);

  while (!q.empty()) {
    int arr_idx = q.front();
    q.pop();
    int x = arr_idx % width_;
    int y = arr_idx / width_;

    if (y == height_ - 1) { // at the last row
      lastRows.push_back(arr_idx);
    }

    // 4 different directions
    if (canTravel(x, y, 0) && !visited[arr_idx+1]) {
      visited[arr_idx+1] = true;
      q.push(arr_idx+1);
      directions.insert(pair<int, int> (arr_idx+1, arr_idx));

    }
    if (canTravel(x, y, 1) && !visited[arr_idx + width_]) {
      visited[arr_idx + width_] = true;
      q.push(arr_idx + width_);
      directions.insert(pair<int, int> (arr_idx + width_, arr_idx));
    }
    if (canTravel(x, y, 2) && !visited[arr_idx - 1]) {
      visited[arr_idx - 1] = true;
      q.push(arr_idx - 1);
      directions.insert(pair<int, int> (arr_idx-1, arr_idx));
    }
    if (canTravel(x, y, 3) && !visited[arr_idx - width_]) {
      visited[arr_idx - width_] = true;
      q.push(arr_idx - width_);
      directions.insert(pair<int, int> (arr_idx - width_, arr_idx));
    }
  }

  vector<int> path;
  int last = width_ - 1;
  while (lastRows[last] == lastRows[last - 1]) {
    last -= 1; // goes to the cell with smallest x in the last row
  }
  int start = lastRows[last];
  while (start != 0) { // trace back
    int prev = directions[start];
    if (start == prev + 1) {
      path.push_back(0);
    } else if (start == prev + width_) {
      path.push_back(1);
    } else if (start == prev - 1) {
      path.push_back(2);
    } else if (start == prev - width_) {
      path.push_back(3);
    }
    start = prev;
  }
  reverse(path.begin(), path.end()); // no push_front() function for vector
  return path;
}


PNG* SquareMaze::drawMaze() const {
  PNG* mazePNG = new PNG(width_*10+1, height_*10 + 1);

  // darken topmost wall
  for (int i = 0; i < height_ * 10 + 1; i++) {
    HSLAPixel* pixel = & mazePNG->getPixel(0, i);
    pixel->l = 0;
  }

  // darken leftmost wall except the entrance from (1, 0) to (9, 0) (in terms of pixel,rathan than cells)
  for (int j = 10; j < width_ * 10 + 1; j++) {
    HSLAPixel* pixel = & mazePNG->getPixel(j, 0);
    pixel->l = 0;
  }

  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      if (rWall[x + y * width_]) { // darken right walls
        for (int k = 0; k < 11; k++) { // for k from 0 to 10 as required by the documentation
          HSLAPixel* pixel = & mazePNG->getPixel((x+1)*10,y*10+k);
          pixel->l = 0;
        }
      }
      if (dWall[x + y * width_]) { // darken down walls
        for (int k = 0; k < 11; k++) { // for k from 0 to 10 as required by the documentation
          HSLAPixel* pixel = & mazePNG->getPixel(x*10+k, (y+1)*10);
          pixel->l = 0;
        }
      }
    }
  }

  return mazePNG;
}

PNG* SquareMaze::drawMazeWithSolution() {
  PNG* mazeSolved = drawMaze();
  vector<int> path = solveMaze();

  // for (int i = 0; i < 20; i++) {
  //   cout << path[i] <<", ";
  // }
  // cout << "" << endl;

  // starting pixel
  int px = 5;
  int py = 5;
  // draw the solution
  for (auto i : path) {
    // cout << "here i: " << i << endl;
    if (i == 0) {
      for (int k = 0; k < 10; k++) {
        // cout << "here00----------" << py << endl;
        HSLAPixel* solPixel = & mazeSolved->getPixel(px, py);
        solPixel->l = 0.5;
        solPixel->s = 1;
        // default h = 0 and a = 1, don't need to change
        px++;
      }
    }
    else if (i == 1) {
      for (int k = 0; k < 10; k++) {
        // cout << "here11----------" << py << endl;
        HSLAPixel* solPixel = & mazeSolved->getPixel(px, py);
        solPixel->l = 0.5;
        solPixel->s = 1;
        // default h = 0 and a = 1, don't need to change
        py++;
      }
    }
    else if (i == 2) {
      for (int k = 0; k < 10; k++) {
        // cout << "here22----------" << py << endl;
        HSLAPixel* solPixel = & mazeSolved->getPixel(px, py);
        solPixel->l = 0.5;
        solPixel->s = 1;
        // default h = 0 and a = 1, don't need to change
        px -= 1;
      }
    }
    else if (i == 3) {
      for (int k = 0; k < 10; k++) {
        // cout << "here33----------" << py << endl;
        HSLAPixel* solPixel = & mazeSolved->getPixel(px, py);
        solPixel->l = 0.5;
        solPixel->s = 1;
        // default h = 0 and a = 1, don't need to change
        py -= 1;
      }
    }
  }

  // to make the output image exact the same as the solution image (using the compare command)
  HSLAPixel* solPixel = & mazeSolved->getPixel(px, py);
  solPixel->l = 0.5;
  solPixel->s = 1;

  // make the exit (set white)
  // observed the solution png, the last step is at the last row (haven't
  // step into the perimeter), therefore y need to +5
  px -= 4;
  py += 5;
  for (int k = 0; k < 9; k++) { // k != 10: just to make the image exact the same as the given image
    HSLAPixel* whiteExit = & mazeSolved->getPixel(px, py);
    whiteExit->l = 1;
    px++;
  }
  return mazeSolved;
}


PNG* SquareMaze::drawCreativeMaze() {
  PNG* mazePNG = new PNG(width_*10+1, height_*10 + 1);

  /**
   * Draw maze
   */
  // darken topmost wall
  for (int i = 0; i < height_ * 10 + 1; i++) {
    HSLAPixel* pixel = & mazePNG->getPixel(0, i);
    pixel->h = 11;
    pixel->s = 1;
    pixel->l = 0.6;
  }
  // darken leftmost wall except the entrance from (1, 0) to (9, 0) (in terms of pixel,rathan than cells)
  for (int j = 10; j < width_ * 10 + 1; j++) {
    HSLAPixel* pixel = & mazePNG->getPixel(j, 0);
    pixel->h = 11;
    pixel->s = 1;
    pixel->l = 0.6;
  }

  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      if (rWall[x + y * width_]) { // darken right walls
        for (int k = 0; k < 11; k++) { // for k from 0 to 10 as required by the documentation
          HSLAPixel* pixel = & mazePNG->getPixel((x+1)*10,y*10+k);
          pixel->h = 11;
          pixel->s = 1;
          pixel->l = 0.6;
        }
      }
      if (dWall[x + y * width_]) { // darken down walls
        for (int k = 0; k < 11; k++) { // for k from 0 to 10 as required by the documentation
          HSLAPixel* pixel = & mazePNG->getPixel(x*10+k, (y+1)*10);
          pixel->h = 11;
          pixel->s = 1;
          pixel->l = 0.6;
        }
      }
    }
  }

  /**
   * Solve maze
   */
  int px = 5;
  int py = 5;
  // draw the solution
  vector<int> path = solveMaze();
  for (auto i : path) {
    // cout << "here i: " << i << endl;
    if (i == 0) {
      for (int k = 0; k < 10; k++) {
        // cout << "here00----------" << py << endl;
        HSLAPixel* solPixel = & mazePNG->getPixel(px, py);
        solPixel->h = 216;
        solPixel->s = 1;
        solPixel->l = 0.5;
        // default h = 0 and a = 1, don't need to change
        px++;
      }
    }
    else if (i == 1) {
      for (int k = 0; k < 10; k++) {
        // cout << "here11----------" << py << endl;
        HSLAPixel* solPixel = & mazePNG->getPixel(px, py);
        solPixel->h = 216;
        solPixel->l = 0.5;
        solPixel->s = 1;
        // default h = 0 and a = 1, don't need to change
        py++;
      }
    }
    else if (i == 2) {
      for (int k = 0; k < 10; k++) {
        // cout << "here22----------" << py << endl;
        HSLAPixel* solPixel = & mazePNG->getPixel(px, py);
        solPixel->h = 216;
        solPixel->l = 0.5;
        solPixel->s = 1;
        // default h = 0 and a = 1, don't need to change
        px -= 1;
      }
    }
    else if (i == 3) {
      for (int k = 0; k < 10; k++) {
        // cout << "here33----------" << py << endl;
        HSLAPixel* solPixel = & mazePNG->getPixel(px, py);
        solPixel->h = 216;
        solPixel->l = 0.5;
        solPixel->s = 1;
        // default h = 0 and a = 1, don't need to change
        py -= 1;
      }
    }
  }

  // to make the output image exact the same as the solution image (using the compare command)
  HSLAPixel* solPixel = & mazePNG->getPixel(px, py);
  solPixel->h = 216;
  solPixel->l = 0.5;
  solPixel->s = 1;

  // make the exit (set white)
  // observed the solution png, the last step is at the last row (haven't
  // step into the perimeter), therefore y need to +5
  px -= 4;
  py += 5;
  for (int k = 0; k < 9; k++) { // k != 10: just to make the image exact the same as the given image
    HSLAPixel* whiteExit = & mazePNG->getPixel(px, py);
    whiteExit->l = 1;
    px++;
  }

  return mazePNG;
}
