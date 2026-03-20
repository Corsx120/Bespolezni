using System;
using System.Threading;

class Program
{
    static int width = 10;
    static int height = 10;
    static int playerX, playerY;
    static int monsterX, monsterY;
    static int moveCount = 0;
    static int maxMoves = 20;
    static Random random = new Random();

    static void Main()
    {
        InitializeGame();

        while (true)
        {
            DrawMap();
            Console.WriteLine($"Ходы выживания: {moveCount}/{maxMoves}");
            Console.WriteLine("Управление: W - вверх, S - вниз, A - влево, D - вправо");
            char input = ReadInput();

            MovePlayer(input);
            MoveMonster();

            moveCount++;

            if (IsGameOver())
                break;

            Thread.Sleep(200); // небольшая задержка для удобства
        }

        DrawMap();

        if (moveCount >= maxMoves)
        {
            Console.WriteLine("Поздравляем! Вы выжили 20 ходов и победили!");
        }
        else
        {
            Console.WriteLine("Монстр догнал вас! Игра окончена.");
        }
    }

    static void InitializeGame()
    {
        playerX = 0;
        playerY = 0;

        // размещение монстра в случайном месте, не совпадающем с игроком
        do
        {
            monsterX = random.Next(width);
            monsterY = random.Next(height);
        } while (monsterX == playerX && monsterY == playerY);
    }

    static void DrawMap()
    {
        Console.Clear();

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (x == playerX && y == playerY)
                {
                    Console.Write("P ");
                }
                else if (x == monsterX && y == monsterY)
                {
                    Console.Write("M ");
                }
                else
                {
                    Console.Write(". ");
                }
            }
            Console.WriteLine();
        }
    }

    static char ReadInput()
    {
        char input;
        do
        {
            input = Console.ReadKey(true).KeyChar;
        } while ("WwSsAaDd".IndexOf(input) == -1);
        return Char.ToUpper(input);
    }

    static void MovePlayer(char direction)
    {
        int newX = playerX;
        int newY = playerY;

        switch (direction)
        {
            case 'W':
                newY -= 1;
                break;
            case 'S':
                newY += 1;
                break;
            case 'A':
                newX -= 1;
                break;
            case 'D':
                newX += 1;
                break;
        }

        // Проверка границ карты
        if (newX >= 0 && newX < width && newY >= 0 && newY < height)
        {
            playerX = newX;
            playerY = newY;
        }
    }

    static void MoveMonster()
    {
        int dx = 0, dy = 0;

        if (monsterX < playerX)
            dx = 1;
        else if (monsterX > playerX)
            dx = -1;

        if (monsterY < playerY)
            dy = 1;
        else if (monsterY > playerY)
            dy = -1;

        // Предпочитаем сначала горизонтальное движение
        if (dx != 0)
            monsterX += dx;
        else if (dy != 0)
            monsterY += dy;
    }

    static bool IsGameOver()
    {
        // Проверка, если монстр поймал игрок
        if (monsterX == playerX && monsterY == playerY)
            return true;

        // Проверка, если игрок выжил 20 ходов
        if (moveCount >= maxMoves)
            return true;

        return false;
    }
}
