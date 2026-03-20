import tkinter as tk
from tkinter import ttk

class TrackWidget(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        super().__init__(parent, *args, **kwargs)

        # Название трека
        self.track_name_label = tk.Label(self, text="Название трека:")
        self.track_name_entry = tk.Entry(self)

        # Исполнитель
        self.artist_label = tk.Label(self, text="Исполнитель:")
        self.artist_entry = tk.Entry(self)

        # Жанр
        self.genre_label = tk.Label(self, text="Жанр:")
        self.genre_entry = tk.Entry(self)

        # Кнопка «Выбрать»
        self.select_button = tk.Button(self, text="Выбрать", command=self.on_select)

        # Расположение виджетов
        self.track_name_label.grid(row=0, column=0, padx=5, pady=5, sticky='e')
        self.track_name_entry.grid(row=0, column=1, padx=5, pady=5)

        self.artist_label.grid(row=1, column=0, padx=5, pady=5, sticky='e')
        self.artist_entry.grid(row=1, column=1, padx=5, pady=5)

        self.genre_label.grid(row=2, column=0, padx=5, pady=5, sticky='e')
        self.genre_entry.grid(row=2, column=1, padx=5, pady=5)

        self.select_button.grid(row=3, column=0, columnspan=2, pady=10)

        # Событие, которое можно привязать к внешним обработчикам
        self.on_select_callback = None

    def on_select(self):
        # Получить данные из полей
        track = self.track_name_entry.get()
        artist = self.artist_entry.get()
        genre = self.genre_entry.get()

        # Создать словарь с данными или передать их в callback
        data = {
            'track': track,
            'artist': artist,
            'genre': genre
        }

        # Вызвать callback, если он установлен
        if self.on_select_callback:
            self.on_select_callback(data)

# Главное окно
def main():
    root = tk.Tk()
    root.title("Музыкальный плейлист")

    def handle_track_selected(data):
        print(f"Выбран трек: {data['track']}, Исполнитель: {data['artist']}, Жанр: {data['genre']}")

    # Создаем наш пользовательский виджет
    track_widget = TrackWidget(root)
    track_widget.pack(padx=10, pady=10)

    # Назначаем обработчик события
    track_widget.on_select_callback = handle_track_selected

    root.mainloop()

if __name__ == "__main__":
    main()
