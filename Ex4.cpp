#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>
#include <QString>
#include <vector>
#include <string>

class TBook {
private:
    std::string title;
    std::string author;
    int count;

public:
    TBook() : title(""), author(""), count(0) {}
    TBook(const std::string& bookTitle, const std::string& bookAuthor, int bookCount) 
        : title(bookTitle), author(bookAuthor), count(bookCount) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getCount() const { return count; }
    void setCount(int newCount) { count = newCount; }
    void setDetails(const std::string& newTitle, const std::string& newAuthor) {
        title = newTitle;
        author = newAuthor;
    }
    bool isAvailable() const { return count > 0; }
    bool borrowBook() {
        if (isAvailable()) {
            count--;
            return true;
        }
        return false;
    }
    void returnBook() { count++; }
};

class Library {
private:
    std::vector<TBook> books;

public:
    void addBook(const TBook& book) {
        books.push_back(book);
    }

    bool removeBookByTitle(const std::string& title) {
        auto it = std::remove_if(books.begin(), books.end(), [&title](const TBook& book) {
            return book.getTitle() == title;
        });
        if (it != books.end()) {
            books.erase(it, books.end());
            return true;
        }
        return false;
    }

    TBook* findBookByTitle(const std::string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                return &book;
            }
        }
        return nullptr;
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            std::cout << "Название: " << book.getTitle() << "\n";
            std::cout << "Автор: " << book.getAuthor() << "\n";
            std::cout << "Количество экземпляров: " << book.getCount() << "\n\n";
        }
    }
};

class MainWindow : public QWidget {
    Q_OBJECT

private:
    Library library;
    QLineEdit* titleLineEdit;
    QLineEdit* authorLineEdit;
    QSpinBox* countSpinBox;

public:
    MainWindow(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        titleLineEdit = new QLineEdit(this);
        authorLineEdit = new QLineEdit(this);
        countSpinBox = new QSpinBox(this);
        countSpinBox->setMinimum(1);
        countSpinBox->setMaximum(1000);

        QPushButton* addBookButton = new QPushButton("Добавить книгу", this);
        QPushButton* removeBookButton = new QPushButton("Удалить книгу", this);
        QPushButton* borrowBookButton = new QPushButton("Взять книгу", this);
        QPushButton* returnBookButton = new QPushButton("Вернуть книгу", this);
        QPushButton* displayBooksButton = new QPushButton("Показать все книги", this);

        connect(addBookButton, &QPushButton::clicked, this, &MainWindow::addBook);
        connect(removeBookButton, &QPushButton::clicked, this, &MainWindow::removeBook);
        connect(borrowBookButton, &QPushButton::clicked, this, &MainWindow::borrowBook);
        connect(returnBookButton, &QPushButton::clicked, this, &MainWindow::returnBook);
        connect(displayBooksButton, &QPushButton::clicked, this, &MainWindow::displayBooks);

        mainLayout->addWidget(new QLabel("Название книги:", this));
        mainLayout->addWidget(titleLineEdit);
        mainLayout->addWidget(new QLabel("Автор книги:", this));
        mainLayout->addWidget(authorLineEdit);
        mainLayout->addWidget(new QLabel("Количество экземпляров:", this));
        mainLayout->addWidget(countSpinBox);
        mainLayout->addWidget(addBookButton);
        mainLayout->addWidget(removeBookButton);
        mainLayout->addWidget(borrowBookButton);
        mainLayout->addWidget(returnBookButton);
        mainLayout->addWidget(displayBooksButton);

        setLayout(mainLayout);
    }

private slots:
    void addBook() {
        QString title = titleLineEdit->text();
        QString author = authorLineEdit->text();
        int count = countSpinBox->value();
        library.addBook(TBook(title.toStdString(), author.toStdString(), count));
        QMessageBox::information(this, "Информация", "Книга добавлена.");
        titleLineEdit->clear();
        authorLineEdit->clear();
        countSpinBox->setValue(1);
    }

    void removeBook() {
        QString title = titleLineEdit->text();
        if (library.removeBookByTitle(title.toStdString())) {
            QMessageBox::information(this, "Информация", "Книга удалена.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Книга не найдена.");
        }
    }

    void borrowBook() {
        QString title = titleLineEdit->text();
        TBook* book = library.findBookByTitle(title.toStdString());
        if (book) {
            if (book->borrowBook()) {
                QMessageBox::information(this, "Информация", "Книга успешно выдана.");
            } else {
                QMessageBox::warning(this, "Ошибка", "Книга недоступна для выдачи.");
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Книга не найдена.");
        }
    }

    void returnBook() {
        QString title = titleLineEdit->text();
        TBook* book = library.findBookByTitle(title.toStdString());
        if (book) {
            book->returnBook();
            QMessageBox::information(this, "Информация", "Книга успешно возвращена.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Книга не найдена.");
        }
    }

    void displayBooks() {
        QString allBooks;
        for (const auto& book : library.books) {
            allBooks += "Название: " + QString::fromStdString(book.getTitle()) + "\n";
            allBooks += "Автор: " + QString::fromStdString(book.getAuthor()) + "\n";
            allBooks += "Количество экземпляров: " + QString::number(book.getCount()) + "\n\n";
        }
        QMessageBox::information(this, "Все книги", allBooks);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

#include "main.moc"
