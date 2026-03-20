//task 1
/*#include <iostream>
#include <string>

class Book {
private:
    std::string title;
    int page_count;

public:
    // Default constructor
    Book() : title("Untitled"), page_count(0) {
        std::cout << "Book object created with default constructor." << std::endl;
    }

    // Parameterized constructor
    Book(const std::string& book_title, int pages) : title(book_title), page_count(pages) {
        std::cout << "Book object created with parameterized constructor: '" << title << "'." << std::endl;
    }

    // Method to display information
    void displayInfo() const {
        std::cout << "--------------------" << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Pages: " << page_count << std::endl;
        std::cout << "--------------------" << std::endl;
    }

    // Destructor (optional, but good practice to show)
    ~Book() {
        std::cout << "Book object '" << title << "' is being destroyed." << std::endl;
    }
};

int main() {
    // Using the default constructor
    Book defaultBook;
    defaultBook.displayInfo();

    std::cout << std::endl;

    // Using the parameterized constructor
    Book myBook("The Hitchhiker's Guide to the Galaxy", 224);
    myBook.displayInfo();

    return 0;
}
*/

//task 2
/*
#include <iostream>
#include <algorithm> // For std::fill

class DynamicBuffer {
private:
    int* buffer; // Pointer to the dynamically allocated array
    size_t size;  // Size of the array

public:
    // Constructor
    DynamicBuffer(size_t buffer_size) : size(buffer_size), buffer(nullptr) {
        if (size > 0) {
            // Allocate memory for the array
            buffer = new int[size];
            std::cout << "DynamicBuffer: Memory allocated for " << size << " integers." << std::endl;
        }
        else {
            std::cout << "DynamicBuffer: Size is 0, no memory allocated." << std::endl;
        }
    }

    // Destructor
    ~DynamicBuffer() {
        // Release allocated memory
        if (buffer != nullptr) {
            delete[] buffer;
            buffer = nullptr; // Good practice to nullify pointer after deletion
            std::cout << "DynamicBuffer: Memory released." << std::endl;
        }
        else {
            std::cout << "DynamicBuffer: No memory to release." << std::endl;
        }
    }

    // Method to fill the array
    // Fills the array with a specific value
    void fillArray(int value) {
        if (buffer != nullptr && size > 0) {
            // Using std::fill from <algorithm>
            std::fill(buffer, buffer + size, value);
            std::cout << "DynamicBuffer: Array filled with value " << value << "." << std::endl;
        }
        else {
            std::cout << "DynamicBuffer: Cannot fill array, buffer is not initialized or size is 0." << std::endl;
        }
    }

    // Method to display array contents (for verification)
    void displayArray() const {
        if (buffer != nullptr && size > 0) {
            std::cout << "DynamicBuffer contents: [ ";
            for (size_t i = 0; i < size; ++i) {
                std::cout << buffer[i] << (i == size - 1 ? "" : ", ");
            }
            std::cout << " ]" << std::endl;
        }
        else {
            std::cout << "DynamicBuffer: Array is empty or not initialized." << std::endl;
        }
    }

    // Preventing copy and assignment (Rule of Three/Five/Zero)
    // For simplicity in this example, we disable them.
    // In a real-world scenario, you might implement them properly.
    DynamicBuffer(const DynamicBuffer&) = delete;
    DynamicBuffer& operator=(const DynamicBuffer&) = delete;
};

int main() {
    // Create a DynamicBuffer of size 5
    DynamicBuffer myBuffer(5);

    // Fill the array with the value 7
    myBuffer.fillArray(7);
    myBuffer.displayArray(); // Should show [ 7, 7, 7, 7, 7 ]

    std::cout << std::endl;

    // Create another DynamicBuffer of size 3
    DynamicBuffer anotherBuffer(3);
    anotherBuffer.fillArray(10);
    anotherBuffer.displayArray(); // Should show [ 10, 10, 10 ]

    std::cout << std::endl;

    // Example with size 0
    DynamicBuffer zeroBuffer(0);
    zeroBuffer.fillArray(5); // This will print a message that it cannot fill.
    zeroBuffer.displayArray(); // Should show empty or not initialized message.

    // myBuffer, anotherBuffer, and zeroBuffer will be automatically destroyed
    // when they go out of scope, and their destructors will be called.

    return 0;
}
*/