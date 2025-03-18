import java.util.LinkedList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


class Book {
    int emotional_rating;
    int number_of_plot_twists;
    String title;
    String author;
    String humor_level;
    boolean interactivity;
    String description;

    Book() {
        System.out.println("New Book created");
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
        if (emotional_rating > 5 && number_of_plot_twists > 2 && cool) {
            System.out.println("Is not fine, is really cool");
        }
    }

    public void is_fine(Book book, int cost, String genre) {
        if (cost > 1000 && genre.equalsIgnoreCase("Sci-Fi")) {
            System.out.println("It's expensive, but the sci-fi is worth it!");
        } else if (cost < 500 && genre.equalsIgnoreCase("Horror")) {
            System.out.println("A cheap horror book? Maybe not very scary...");
        } else {
            System.out.println("The price and genre are OK, you can read it.");
        }
    }

    void number_of_books() {
        System.out.println("There is only one book");
    }

    boolean isPageTurner() {
        return emotional_rating > 7 && number_of_plot_twists > 3;
    }
}

class Library extends Book {
    LinkedList<Book> books;

    Library() {
        super();
        this.books = new LinkedList<>();
    }

    void addBook(Book book) {
        books.add(book);
    }

    @Override
    void number_of_books() {
        if (!books.isEmpty())
            System.out.println("Library has " + books.size() + " books");
    }

    @Override
    public void is_fine(Book book, int cost, String genre) {
        if (book.number_of_plot_twists > 5 && cost > 100 && genre.equalsIgnoreCase("Fairy Tale")) {
            System.out.println("It's really cool");
        }
        else{
            System.out.println("The price and genre are OK, you can read it.");
        }
    }

    @Override
    boolean isPageTurner() {
        if (books.size() > 2) {
            return super.isPageTurner();
        }
        return false;
    }

    void addBookDescription(Book book, String description) {
        book.description = description;
        Pattern pattern = Pattern.compile("\\b\\w+\\b");
        Matcher matcher = pattern.matcher(description);
        int wordCount = 0;
        while (matcher.find()) {
            wordCount++;
        }
        System.out.println("Description added! Word count: " + wordCount);
    }

    void findLongestWordInDescription(Book book) {
        Pattern pattern = Pattern.compile("\\b\\w+\\b");
        Matcher matcher = pattern.matcher(book.description);
        String longestWord = "";
        while (matcher.find()) {
            String word = matcher.group();
            if (word.length() > longestWord.length()) {
                longestWord = word;
            }
        }
        System.out.println("Longest word in description: " + longestWord);
    }
}
public class Main {
    public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            Library library = new Library();

            for (int i = 0; i < 3; i++) {
                System.out.println("Enter book " + (i + 1) + " details:");

                System.out.print("Enter title: ");
                String title = scanner.nextLine();

                System.out.print("Enter author: ");
                String author = scanner.nextLine();

                System.out.print("Enter emotional rating (1-10): ");
                int emotionalRating = scanner.nextInt();

                System.out.print("Enter number of plot twists: ");
                int plotTwists = scanner.nextInt();

                scanner.nextLine();

                System.out.print("Enter humor level (Low, Medium, High): ");
                String humorLevel = scanner.nextLine();

                System.out.print("Is the book interactive? (true/false): ");
                boolean interactivity = scanner.nextBoolean();

                scanner.nextLine();

                Book book = new Book(emotionalRating, plotTwists, title, author, humorLevel, interactivity);
                library.addBook(book);

                System.out.print("Enter book description: ");
                String description = scanner.nextLine();
                library.addBookDescription(book, description);
                library.findLongestWordInDescription(book);
                library.is_fine(book,500,"Fantasy");
                library.isPageTurner();
            }


            library.number_of_books();
            scanner.close();
        }
    }
