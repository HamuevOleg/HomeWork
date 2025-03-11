import java.util.regex.*;
import java.util.Vector;

class Book {
    int emotional_rating;
    int number_of_plot_twists;
    String title;
    String author;
    String humor_level;
    boolean interactivity;

    Book() {
        System.out.println("Book Constructor");
    }

    Book(int emotional_rating, int number_of_plot_twists, String title, String author, String humor_level, boolean interactivity) {
        this();
        this.emotional_rating = emotional_rating;
        this.number_of_plot_twists = number_of_plot_twists;
        this.title = title;
        this.author = author;
        this.humor_level = humor_level;
        this.interactivity = interactivity;
    }

    void is_fine() {
        System.out.println("Is fine");
    }

    public void is_fine(boolean cool) {
        if (emotional_rating > 5 && number_of_plot_twists > 2) {
            System.out.println("Is not fine, is really cool");
        }
    }

    public void is_fine(int cost, String genre) {
        if (cost > 1000 && genre.equalsIgnoreCase("Sci-Fi")) {
            System.out.println("It's expensive, but the sci-fi is worth it!");
        } else if (cost < 500 && genre.equalsIgnoreCase("Horror")) {
            System.out.println("A cheap horror movie? Maybe not very scary...");
        } else {
            System.out.println("The price and genre are OK, you can read it.");
        }
    }

    int number_of_books(int[] n) {
        return n.length;
    }

    boolean isPageTurner() {
        return emotional_rating > 7 && number_of_plot_twists > 3;
    }
}

class Library extends Book {

    Vector<Book> books;

    Library() {
        super();
        this.books = new Vector<>();
    }

    void addBook(Book book) {
        books.add(book);
    }

    Vector<Book> findBooksByAuthor(String author) {
        Vector<Book> result = new Vector<>();
        for (Book book : books) {
            if (book.author.equalsIgnoreCase(author)) {
                result.add(book);
            }
        }
        return result;
    }

    int number_of_books() {
        return books.size();
    }

    String checkBookAvailability(String title) {
        for (Book book : books) {
            if (book.title.equalsIgnoreCase(title)) {
                return "Book is available";
            }
        }
        return "Book not found";
    }
}

public class Main {
    public static void main(String[] args) {
        Book book1 = new Book(8, 3, "The Great Gatsby", "F. Scott Fitzgerald", "Low", false);
        Book book2 = new Book(7, 4, "1984", "George Orwell", "Medium", true);

        // Создание объекта класса Library
        Library library = new Library();
        library.addBook(book1);
        library.addBook(book2);

        System.out.println("Number of books in library: " + library.number_of_books());

        // Вызов метода для поиска книг по автору
        Vector<Book> foundBooks = library.findBooksByAuthor("F. Scott Fitzgerald");
        System.out.println("Found books by F. Scott Fitzgerald: " + foundBooks.size());

        // Вызов метода для проверки доступности книги
        String availability = library.checkBookAvailability("1984");
        System.out.println(availability);
    }
}
