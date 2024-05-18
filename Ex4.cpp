#include <iostream>
#include <string>
#include <vector>

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
  std::string getTitle() const {
    return title;
  }

  // Метод для получения автора книги
  std::string getAuthor() const {
    return author;
  }

  // Метод для получения количества экземпляров книги
  int getCount() const {
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

  // Метод для проверки наличия экземпляров книги
  bool isAvailable() const {
    return count > 0;
  }

  // Метод для выдачи книги (уменьшение количества экземпляров)
  bool borrowBook() {
    if (isAvailable()) {
      count--;
      return true;
    } else {
      return false;
    }
  }

  // Метод для возврата книги (увеличение количества экземпляров)
  void returnBook() {
    count++;
  }
};

// Класс Библиотека
class Library {
private:
  std::vector<TBook> books; // Коллекция книг

public:
  // Метод для добавления книги в библиотеку
  void addBook(const TBook& book) {
    books.push_back(book);
  }

  // Метод для поиска книги по названию
  TBook* findBookByTitle(const std::string& title) {
    for (auto& book : books) {
      if (book.getTitle() == title) {
        return &book;
      }
    }
    return nullptr;
  }

  // Метод для поиска книги по автору
  TBook* findBookByAuthor(const std::string& author) {
    for (auto& book : books) {
      if (book.getAuthor() == author) {
        return &book;
      }
    }
    return nullptr;
  }

  // Метод для отображения информации обо всех книгах
  void displayAllBooks() const {
    for (const auto& book : books) {
      book.displayInfo();
      std::cout << std::endl;
    }
  }
};

int main() {
  // Создаем объект библиотеки
  Library library;

  // Добавляем книги в библиотеку
  library.addBook(TBook("Программирование на C++", "Иван Иванов", 5));
  library.addBook(TBook("Продвинутое программирование на C++", "Петр Петров", 3));

  // Выводим информацию обо всех книгах в библиотеке
  std::cout << "Все книги в библиотеке:\n";
  library.displayAllBooks();

  // Поиск книги по названию и выдача книги
  TBook* book = library.findBookByTitle("Программирование на C++");
  if (book != nullptr) {
    std::cout << "\nКнига найдена:\n";
    book->displayInfo();
    if (book->borrowBook()) {
      std::cout << "Книга успешно выдана.\n";
    } else {
      std::cout << "Книга недоступна для выдачи.\n";
    }
  } else {
    std::cout << "Книга не найдена.\n";
  }

  // Возврат книги
  if (book != nullptr) {
    book->returnBook();
    std::cout << "\nКнига возвращена:\n";
    book->displayInfo();
  }

  return 0;
}
