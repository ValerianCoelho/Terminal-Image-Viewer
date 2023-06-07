#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define HighlightLen 30

int NewChoice, OldChoice;

// Function to move the cursor to a specific position on the console
void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

// Function to print a specified number of spaces
void space(int n) {
    for (int i = 0; i < n; i++)
        printf(" ");
}

// Function to display the menu with options
void display(char header[], char options[][40], int n, int initialOptionHighlight) {
    system("cls"); // Clear the console
    printf("%s\n", header);

    for (int i = 0; i < n; i++) {
        if (i + 1 == initialOptionHighlight) {
            printf("%d) \033[30;107m%s", i + 1, options[i]); // Highlight the initial option
            space(HighlightLen - strlen(options[i]));
            printf("\n\033[0m");
            continue;
        }
        printf("%d) %s\n", i + 1, options[i]);
    }
    printf("Enter : ");
}

// Function to update the display when the choice changes
void UpdateDisplay(char options[][40], int n) {
    if (NewChoice == OldChoice)
        return;

    gotoxy(4, OldChoice + 2);
    printf("%s", options[OldChoice]);
    space(HighlightLen - strlen(options[OldChoice]));

    gotoxy(4, NewChoice + 2);
    printf("\033[30;107m%s", options[NewChoice]); // Highlight the new choice
    space(HighlightLen - strlen(options[NewChoice]));
    printf("\033[0m");

    OldChoice = NewChoice;
}

// Function to handle the menu and return the selected choice
int ReturnChoice(char header[], char options[][40], int n, int initialOptionHighlight) {
    char ch;
    NewChoice = OldChoice = initialOptionHighlight - 1;
    display(header, options, n, initialOptionHighlight);

    do {
        ch = getch();

        if (ch == 75 || ch == 72) { // Up or Left arrow key
            if (NewChoice == 0)
                continue;
            NewChoice--;
        } else if (ch == 77 || ch == 80) { // Right or Down arrow key
            if (NewChoice == n - 1)
                continue;
            NewChoice++;
        }

        UpdateDisplay(options, n);
    } while (ch != 13); // Enter key

    system("cls"); // Clear the console
    return NewChoice + 1; // Return the selected choice
}
