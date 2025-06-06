#include <windows.h>
#include <cmath>

const int screenWidth = 320;
const int screenHeight = 240;
const int cellSize = 64; // Размер ячейки карты

// Карта мира (1 - стена, 0 - пусто)
int worldMap[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

// Позиция игрока
double posX = 3.0, posY = 3.0;
// Направление взгляда
double dirX = -1.0, dirY = 0.0;
// Плоскость камеры (FOV)
double planeX = 0.0, planeY = 0.66;

void RayCast(HDC hdc) {
    for (int x = 0; x < screenWidth; x++) {
        // Координаты луча в пространстве камеры
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // Текущая позиция луча
        double rayPosX = posX;
        double rayPosY = posY;

        // Расстояние до следующей грани
        double sideDistX, sideDistY;

        // Шаг и расстояние до следующей стороны
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        int stepX, stepY;
        int hit = 0; // Столкновение
        int side;   // Горизонтальная/вертикальная стена

        // Определение начального шага
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - rayPosX) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (rayPosX + 1.0 - posX) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - rayPosY) * deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (rayPosY + 1.0 - posY) * deltaDistY;
        }

        // Алгоритм DDA (Digital Differential Analysis)
        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                rayPosX += stepX;
                side = 0;
            }
            else {
                sideDistY += deltaDistY;
                rayPosY += stepY;
                side = 1;
            }

            // Проверка попадания в стену
            if (worldMap[(int)rayPosX][(int)rayPosY] > 0) hit = 1;
        }

        // Расчет перпендикулярного расстояния
        double perpWallDist;
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else perpWallDist = (sideDistY - deltaDistY);

        // Высота стены на экране
        int lineHeight = (int)(screenHeight / perpWallDist);

        // Начало и конец рисования стены
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Выбор цвета в зависимости от типа стены и стороны
        COLORREF color;
        if (worldMap[(int)rayPosX][(int)rayPosY] == 1) {
            color = side ? RGB(200, 0, 0) : RGB(150, 0, 0); // Красные стены
        }
        else {
            color = side ? RGB(0, 200, 0) : RGB(0, 150, 0); // Зеленые стены
        }

        // Рисование вертикальной линии
        for (int y = drawStart; y <= drawEnd; y++) {
            SetPixel(hdc, x, y, color);
        }

        // Рисование пола и потолка
        for (int y = 0; y < drawStart; y++) {
            SetPixel(hdc, x, y, RGB(50, 50, 150)); // Синий потолок
        }
        for (int y = drawEnd + 1; y < screenHeight; y++) {
            SetPixel(hdc, x, y, RGB(100, 100, 100)); // Серый пол
        }
    }
}

// Оконная процедура

// Точка входа
void Game() {
    HDC hdc = GetDC(GetConsoleWindow());
    RayCast(hdc);
  
}
