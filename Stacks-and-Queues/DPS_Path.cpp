
#include <iostream>

struct offsets {
  int a, b;//行移动步数与列移动步数
};

//方向 东南西北
enum directions { N, NE, E, SE, S, SW, W, NW };
offsets move[8]={
(-1,0),
(-1,1),
(0,1),
(1,1),
(1,0),
(1,-1),
(0,-1),
(-1,-1),
};

struct Items {
  int x, y, dir;//行坐标，列坐标，方向
};


//（1，1）to（m，p）
//maze[][]为迷宫（0为可走的，1为墙壁）
//mark[][]标记此坐标是否走过
void Path(int const m, int const p) {
  mark[1][1] = 1;//起点
  Stack<Items> stack(m * p);
  Items temp(1, 1, E);
  stack.Push(temp);

  while (!stack.IsEmpty()) {
    temp = stack.Top();
    stack.Pop();
    int i = temp.x;
    int j = temp.y;
    int d = temp.dir;
    while (d < 8) {
      int g = i + move[d].a;
      int h = j + move[d].b;
      if (g == m && h == p) {
        std::cout << stack;//输出栈中路径
        std::cout << i << " " << j << std::endl;//输出终点前一步
        std::cout << m << " " << p << std::endl;//终点
        return;
      }
      if (!maze[g][h] && !mark[g][h]) {
        mark[g][h] = 1;
        temp.x     = i;
        temp.y     = j;
        temp.dir   = d + 1;
        stack.Push(temp);//注意第一层循环的stack.pop
        i = g;
        j = h;
        d = N;
      } else {
        d++;
      }
    }
  }
  std::cout << "No path in maze" << std::endl;
}
