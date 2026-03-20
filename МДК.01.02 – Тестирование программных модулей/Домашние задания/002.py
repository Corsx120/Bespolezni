import tkinter as tk
from tkinter import messagebox

def check_age():
    age_input = entry.get()
    if age_input.isdigit():
        age = int(age_input)
        if age > 100:
            messagebox.showinfo("Результат", "Них... ты старый")
        elif age < 18:
            messagebox.showinfo("Результат", "Несовершеннолетний")
        elif age >= 18:
            messagebox.showinfo("Результат", "Совершеннолетний")
    else:
        messagebox.showerror("Ошибка", "Пожалуйста, введите числовое значение возраста")

root = tk.Tk()
root.title("Проверка возраста")

# Поле ввода
entry = tk.Entry(root)
entry.pack(pady=10)

# Кнопка проверки
button = tk.Button(root, text="Проверить возраст", command=check_age)
button.pack(pady=10)

root.mainloop()
