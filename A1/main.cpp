#include <iostream>
#include <fstream>

/*
    Ethan Dakin
    SN: 8209194
*/

const int SIZE = 50000;
// I was advised by the subject coordinator for 10, but I increased it to 20.
const int WORD_SIZE = 20;

// Array for string pool
char text[SIZE * WORD_SIZE];
int start[SIZE];

// Record for word (simplifies sorting)
struct word
{
    char word[WORD_SIZE];
    int count;
};

// Record array
word count[SIZE];

// Function initialization

// Checks if a character is a whitespace character or not.
bool is_whitespace(char c);
// Checks if a character is one of the 26 alphabet letters
bool is_alphabet(char c);
// Lowers an uppercase alphabetical letter
char lower(char c);
// Compares two strings (this is the code from string.h)
int strcmp(const char *s1, const char *s2);
// Copies a word from a destination into a source
void copy_word(char dest[WORD_SIZE], char src[WORD_SIZE]);
// Swaps two word records
void swap(word &a, word &b);
// Creates partition for quicksort
int partition(word arr[SIZE], int low, int high);
// Basic quicksort implementation, which compares count first, then sorts lexicographically.
void quickSort(word arr[SIZE], int low, int high);

int main()
{
    // Initialize ifstream object
    char filename[WORD_SIZE];
    std::ifstream input;

    // Prompt user input
    std::cerr << "Please enter the name of the input file: " << std::endl;
    std::cin >> filename;

    // Open file
    input.open(filename);

    // Input error handling
    if (!input)
    {
        std::cerr << "Error opening file " << filename << ". Program will exit. " << std::endl;
        return -1;
    }

    // Initialize variables for string pool
    char character; // The current character being read
    int index = 0; // The character index in the string pool
    int words = 0; // The amount of words
    int char_index = 0; // The character index for each word

    while (input.get(character))
    {
        if (!is_whitespace(character))
        {
            // When a new word starts
            if (char_index == 0)
            {
                // Add the starting index to the start array
                start[words] = index;
            }

            // If the character is in the alphabet
            if (is_alphabet(character))
            {
                // Add it to the text array after converting to lowercase, and increase index
                text[index] = lower(character);
                index++;
            }

            // If the next character (input.peek()) is whitespace
            if (is_whitespace(input.peek()))
            {
                // Increase word count and return character index to 0
                words++;
                char_index = 0;
            }
            else
            {
                // Continue adding to the character index
                char_index++;
            }
        }
    }

    // Count index for count array
    int count_index = 0;
    // For each word
    for (int i = 0; i < words; i++)
    {
        // Get the start and end position for the character array
        int begin = start[i];
        int end = start[i + 1] - 1;

        // Edge case for if i overflows
        if (i == (words - 1))
        {
            end = index - 1;
        }

        // Create temporary character array
        char temp[WORD_SIZE];

        // For each character in the selected word (i)
        for (int j = 0; j <= (end - begin); j++)
        {
            // Add it to the array
            temp[j] = text[j + begin];
        };

        // Terminate the 'string'
        temp[(end - begin) + 1] = '\0';

        // Variable for if a word was found in count array
        int found = -1;

        // Note - worst case scenario is O(n^2), as this loops through word count inside a loop for word count.
        for (int j = 0; j < words; j++)
        {
            // If the string in temp is the same as the word found, set found index to the index.
            if (strcmp(temp, count[j].word) == 0)
            {
                found = j;
                break;
            }
        }

        // If found is greater than 0 then
        if (found >= 0)
        {
            // Add to the count
            count[found].count++;
        }
        else
        {
            // Else, add the word to count array
            copy_word(count[count_index].word, temp);
            count[count_index].count = 1;
            // Note, that I increase count_index here.
            // As I am already looping through each word, it saves on memory usage for a count_words function.
            count_index++;
        }
    }

    // Quick sort count array
    quickSort(count, 0, count_index - 1);

    // Print output.
    std::cout << std::endl << "The first 10 words sorted alphabetically within frequency:" << std::endl;;

    for (int i = 0; i < 10; i++)
    {
        std::cout << "The word: " << count[i].word << " occurs " << count[i].count << " times." << std::endl;
    }

    std::cout << std::endl << "The last 10 words sorted alphabetically within frequency:" << std::endl;

    for (int i = count_index - 10; i < count_index; i++)
    {
        std::cout << "The word: " << count[i].word << " occurs " << count[i].count << " times." << std::endl;
    }

    std::cout << std::endl << "The unique words sorted alphabetically:" << std::endl;

    for (int i = 0; i < count_index; i++)
    {
        // Only print if the count is 1
        // Note, this array is already sorted alphabetically, so there is no need to worry about wrong order.
        if (count[i].count == 1)
        {
            std::cout << "The word: " << count[i].word << " occurs " << count[i].count << " times." << std::endl;
        }
    }

    // Terminate program
    return 0;
}

// Checks if a character is whitespace, and returns true if it is, and false if not.
bool is_whitespace(char c)
{
    if ((c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'))
    {
        return true;
    }

    return false;
}

// Checks if a character in in the alphabet, by using ASCII numeric comparison.
bool is_alphabet(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }

    return false;
}

// Returns a lowercase character, by adding 32 to the ASCII value.
char lower(char c)
{
    if (c <= 'Z' && c >= 'A')
    {
        return c + 32;
    }

    return c;
}

// Compares two strings, and returns 0 if they are the same
// Note: this code is in the string.h c library, however, we were not permitted to use the string library.
int strcmp(const char *s1, const char *s2)
{
    while (*s1 == *s2++)
        if (*s1++ == '\0')
            return (0);
    return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}

// Copies a word from a source character array into a destination character array.
void copy_word(char dest[WORD_SIZE], char src[WORD_SIZE])
{
    for (int i = 0; i < WORD_SIZE; ++i)
    {
        dest[i] = src[i];
    }
}

// Swaps two word records.
void swap(word &a, word &b)
{
    word temp = a;
    a = b;
    b = temp;
}

// Quick sort partition function
int partition(word arr[SIZE], int low, int high)
{
    word pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        // First it compares count
        if (arr[j].count > pivot.count)
        {
            i++;
            swap(arr[i], arr[j]);
        }
        // Then it compares by alphabetical order, if it is the same count.
        else if (arr[j].count == pivot.count)
        {
            if (strcmp(arr[j].word, pivot.word) < 0)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick sort function.
void quickSort(word arr[SIZE], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
