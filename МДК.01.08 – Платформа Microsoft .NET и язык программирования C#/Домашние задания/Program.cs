using System;

class Program
{
    static void Main()
    {
        // Запрос веса у пользователя
        Console.Write("Введите вес в килограммах: ");
        string weightInput = Console.ReadLine();

        // Запрос роста у пользователя
        Console.Write("Введите рост в метрах: ");
        string heightInput = Console.ReadLine();

        // Попытка преобразовать ввод в числовые значения
        if (double.TryParse(weightInput, out double weight) && double.TryParse(heightInput, out double height))
        {
            // Расчет Индекса Массы Тела (ИМТ)
            double bmi = weight / (height * height);

            // Вывод результата с использованием интерполяции строк
            Console.WriteLine($"Ваш индекс массы тела (ИМТ): {bmi:F2}");
        }
        else
        {
            Console.WriteLine("Некорректный ввод данных. Пожалуйста, введите числовые значения.");
        }
    }
}
