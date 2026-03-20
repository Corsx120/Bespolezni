
from PyQt5.QtWidgets import (QApplication, QWidget, QVBoxLayout,
                             QLineEdit, QPushButton, QLabel, QMessageBox)
import sys

class ConverterService:
    def to_binary(self, number: int) -> str:
        if not isinstance(number, int):
            raise TypeError("Input must be an integer.")
        return bin(number)[2:] # bin() returns '0b...', [2:] removes the '0b' prefix

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.converter_service = ConverterService()
        self.initUI()

    def initUI(self):
        self.layout = QVBoxLayout()

        self.input_field = QLineEdit(self)
        self.input_field.setPlaceholderText("Введите целое число")
        self.layout.addWidget(self.input_field)

        self.convert_button = QPushButton("Конвертировать в двоичный", self)
        self.convert_button.clicked.connect(self.on_convert_click)
        self.layout.addWidget(self.convert_button)

        self.result_label = QLabel("Результат: ", self)
        self.layout.addWidget(self.result_label)

        self.setLayout(self.layout)
        self.setWindowTitle("Конвертер в двоичный формат")

    def on_convert_click(self):
        input_text = self.input_field.text()
        try:
            # Пробуем преобразовать в целое число
            number = int(input_text)
            # Вызываем сервис для конвертации
            binary_representation = self.converter_service.to_binary(number)
            # Выводим результат
            self.result_label.setText(f"Двоичное представление: {binary_representation}")
        except ValueError:
            # Если int() не смог преобразовать, значит ввод некорректен
            self.result_label.setText("Некорректный ввод")
            QMessageBox.warning(self, "Ошибка ввода", "Пожалуйста, введите корректное целое число.")
        except TypeError as e:
            # Обработка ошибки из сервиса (хотя наша проверка int() должна это предотвратить)
            self.result_label.setText(f"Ошибка сервиса: {e}")
            QMessageBox.warning(self, "Ошибка сервиса", str(e))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec_())
