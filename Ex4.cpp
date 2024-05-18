#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

  // Метод для удаления книги по названию
  bool removeBookByTitle(const std::string& title) {
    auto it = std::remove_if(books.begin(), books.end(),
      [&title](const TBook& book) {
        return book.getTitle() == title;
      });
    if (it != books.end()) {
      books.erase(it, books.end());
      return true;
    }
    return false;
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
  Library library;

  // Добавление книг в библиотеку
  library.addBook(TBook("Программирование на C++", "Иван Иванов", 5));
  library.addBook(TBook("Продвинутое программирование на C++", "Петр Петров", 3));
  library.addBook(TBook("Основы алгоритмов", "Николай Николаев", 7));

  while (true) {
    std::cout << "\nМеню:\n";
    std::cout << "1. Показать все книги\n";
    std::cout << "2. Найти книгу по названию\n";
    std::cout << "3. Найти книгу по автору\n";
    std::cout << "4. Добавить книгу\n";
    std::cout << "5. Удалить книгу по названию\n";
    std::cout << "6. Взять книгу\n";
    std::cout << "7. Вернуть книгу\n";
    std::cout << "8. Выйти\n";
    std::cout << "Выберите опцию: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
      std::cout << "Все книги в библиотеке:\n";
      library.displayAllBooks();
    } else if (choice == 2) {
      std::cout << "Введите название книги: ";
      std::string title;
      std::cin.ignore();
      std::getline(std::cin, title);
      TBook* book = library.findBookByTitle(title);
      if (book) {
        book->displayInfo();
      } else {
        std::cout << "Книга не найдена.\n";
      }
    } else if (choice == 3) {
      std::cout << "Введите автора книги: ";
      std::string author;
      std::cin.ignore();
      std::getline(std::cin, author);
      TBook* book = library.findBookByAuthor(author);
      if (book) {
        book->displayInfo();
      } else {
        std::cout << "Книга не найдена.\n";
      }
    } else if (choice == 4) {
      std::string title, author;
      int count;
      std::cout << "Введите название книги: ";
      std::cin.ignore();
      std::getline(std::cin, title);
      std::cout << "Введите автора книги: ";
      std::getline(std::cin, author);
      std::cout << "Введите количество экземпляров: ";
      std::cin >> count;
      library.addBook(TBook(title, author, count));
      std::cout << "Книга добавлена.\n";
    } else if (choice == 5) {
      std::cout << "Введите название книги для удаления: ";
      std::string title;
      std::cin.ignore();
      std::getline(std::cin, title);
      if (library.removeBookByTitle(title)) {
        std::cout << "Книга удалена.\n";
      } else {
        std::cout << "Книга не найдена.\n";
      }
    } else if (choice == 6) {
      std::cout << "Введите название книги для выдачи: ";
      std::string title;
      std::cin.ignore();
      std::getline(std::cin, title);
      TBook* book = library.findBookByTitle(title);
      if (book) {
        if (book->borrowBook()) {
          std::cout << "Книга успешно выдана.\n";
        } else {
          std::cout << "Книга недоступна для выдачи.\n";
        }
      } else {
        std::cout << "Книга не найдена.\n";
      }
    } else if (choice == 7) {
      std::cout << "Введите название книги для возврата: ";
      std::string title;
      std::cin.ignore();
      std::getline(std::cin, title);
      TBook* book = library.findBookByTitle(title);
      if (book) {
        book->returnBook();
        std::cout << "Книга успешно возвращена.\n";
      } else {
        std::cout << "Книга не найдена.\n";
      }
    } else if (choice == 8) {
      break;
    } else {
      std::cout << "Неверный выбор. Попробуйте снова.\n";
    }
  }

  return 0;
}
