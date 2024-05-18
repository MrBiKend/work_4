#include <iostream>
#include <string>

// Класс Книга
class TBook {
private:
  std::string title; // Название книги
  std::string author; // Автор книги
  int count; // Количество экземпляров книги

public:
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
};

int main() {
  // Создаем объект книги
  TBook book("Программирование на C++", "Иван Иванов", 5);

  // Выводим информацию о книге
  std::cout << "Название: " << book.getTitle() << std::endl;
  std::cout << "Автор: " << book.getAuthor() << std::endl;
  std::cout << "Количество экземпляров: " << book.getCount() << std::endl;

  return 0;
}
