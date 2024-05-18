#include <iostream>
#include <string>

// Класс Книга
class TBook {
private:
  std::string title; // Название книги
  std::string author; // Автор книги
  int count; // Количество экземпляров книги

public:
  // Конструктор по умолчанию
  TBook() : title(""), author(""), count(0) {}

  // Конструктор с параметрами
  TBook(const std::string& bookTitle, const std::string& bookAuthor, int bookCount) {
    title = bookTitle;
    author = bookAuthor;
    count = bookCount;
  }

  // Метод для получения названия книги
  std::string getTitle() {
    return title;
  }

  // Метод для получения автора книги
  std::string getAuthor() {
    return author;
  }

  // Метод для получения количества экземпляров книги
  int getCount() {
    return count;
  }

  // Метод для установки нового значения количества экземпляров книги
  void setCount(int newCount) {
    count = newCount;
  }

  // Метод для установки названия и автора книги
  void setDetails(const std::string& newTitle, const std::string& newAuthor) {
    title = newTitle;
    author = newAuthor;
  }

  // Метод для отображения информации о книге
  void displayInfo() const {
    std::cout << "Название: " << title << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Количество экземпляров: " << count << std::endl;
  }
};

int main() {
  // Создаем объект книги
  TBook book("Программирование на C++", "Иван Иванов", 5);

  // Выводим информацию о книге
  book.displayInfo();

  // Изменяем количество экземпляров книги
  book.setCount(7);

  // Изменяем название и автора книги
  book.setDetails("Продвинутое программирование на C++", "Петр Петров");

  // Выводим обновленную информацию о книге
  book.displayInfo();

  return 0;
}
