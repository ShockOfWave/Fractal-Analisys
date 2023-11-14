#include "markArea.h"
#include "Coord.h"

#include <stack>

void markArea(int x, int y, int mark, std::vector<std::vector<int> >&& matrix, int width, int height, int targetValue) {
    std::stack<Coord> stack;
    stack.push(Coord(x, y));

    while (!stack.empty()) {
        Coord current = stack.top();
        stack.pop();

        if (matrix[current.y][current.x] == targetValue) {
            matrix[current.y][current.x] = mark;

            // Массив смещений для 4-связной связности
            int dx[] = { 1, 0, -1, 0 };
            int dy[] = { 0, 1, 0, -1 };

            for (int i = 0; i < 4; i++) {
                int newX = current.x + dx[i];
                int newY = current.y + dy[i];

                if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                    stack.push(Coord(newX, newY));
                }
            }
        }
    }
}
