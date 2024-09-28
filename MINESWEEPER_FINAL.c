/* Include files */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/* Definitions */
#define BOARD_SIZE 20
#define TRUE 1
#define FALSE 0

/* Global Variables */
char board[BOARD_SIZE][BOARD_SIZE];
char game_board[BOARD_SIZE][BOARD_SIZE];
int lost = 0;

/* Function prototypes */
void display_welcome();
void build_board();
void build_gboard();
void create_mines();
void print_board();
void print_fullboard();
void start();
int play_game();
void play_again();
int check_win_game();
void check_for_mine(int row, int col);
int check_for_nearby_mines(int, int);

// Main function
int main ()
{
    display_welcome();
    printf("\nAny time you're ready... Just press ENTER. :)");

    //Get rid of welcme screen
    getchar();
    system ("cls");

    start();

    return 0;



}

/* Build board used for created random mines */
void build_board()
{

    int i, j;
    for(i = 0; i < BOARD_SIZE; i++)
        for(j = 0; j < BOARD_SIZE; j++)
            board[i][j] = 'o';

    // Place mines in this board, it remains
    // hidden from user until the game has
    // finished.
    create_mines();
}

/* Build game board for user input */
void build_gboard()
{

    int i, j;
    int row, col, cur = 4;
    printf("Creating game board....\nReady..set..\nPLAY!\n\n");
    //----------------------------------------
    // Assign char 'o' for all board elements
    //----------------------------------------
    for(i = 0; i < BOARD_SIZE; i++)
        for(j = 0; j < BOARD_SIZE; j++)
            game_board[i][j] = 'o';

    //--------------------------------
    // Print board
    //--------------------------------
    for(col = 0; col < BOARD_SIZE; col++)
        printf("%2d ", col + 1);

    printf("\n\n");

    for(row = 0; row < BOARD_SIZE; row++)
    {
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf("%2c ", game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}

/* Create 10 random places in the array for mines */
void create_mines()
{
    int i, random, count = 0;

    // Seeding srand() with time(0) so that
    // mine locations aren't the same every
    // time the game is played.
    srand(time(0));

    while (count < 10) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (board[row][col] != '*') {
            board[row][col] = '*';
            count++;
        }
    }
}


/* Print the game board */
void print_board()
{
    int row, col;

    system("cls");
    printf("   ");
    for(col = 0; col < BOARD_SIZE; col++)
        printf("%2d ", col + 1);

    printf("\n");

    for(row = 0; row < BOARD_SIZE; row++)
    {
        printf("%2d ", row + 1);
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf(" %c ", game_board[row][col]);
        }
        printf("\n");
    }
}

/* Print the full board showing mines */
void print_fullboard()
{
    int row, col;

    system("cls");
    printf("   ");
    for(col = 0; col < BOARD_SIZE; col++)
        printf("%2d ", col + 1);

    printf("\n");

    for(row = 0; row < BOARD_SIZE; row++)
    {
        printf("%2d ", row + 1);
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf(" %c ", board[row][col]);
        }
        printf("\n");
        }
}


/* Take user input for playing of the game */
int play_game()
{
    int r_selection = 0, c_selection = 0,
        nearbymines = 0, nearbymines2 = 0,
        nearbymines3 = 0, nearbymines4 = 0,
        nearbymines5 = 0, nearbymines6 = 0,
        nearbymines7 = 0, nearbymines8 = 0,
        i = 0;

    //----------------------------------------------
    // Recieves data from the user, first the row
    // number, then the column number...
    // I could think of other ways to do it, but
    // this one seemed easiest.
    //----------------------------------------------
    do {
    printf("\nMake a selection (ie. row [ENTER] col): \n");
    printf("Row--> ");
    scanf("%d", &r_selection);
    printf("Col--> ");
    scanf("%d", &c_selection);

    } while(r_selection < 1 || r_selection > BOARD_SIZE || c_selection < 1 || c_selection > BOARD_SIZE);
    // ^ Checks for any invalid input statements from user.

    check_for_mine(r_selection - 1, c_selection - 1);

    if(lost == 1)
        return -1;

    // Checks for nearby mines at every direction from user
    // input location. Assigns that location the number
    // of mines found nearby, updating the board.
    nearbymines = check_for_nearby_mines(r_selection - 1, c_selection - 1);
    game_board[r_selection - 1][c_selection - 1] = (char)( ((int)'0') + nearbymines );

    //--------------------------------------------------
    // The following checks for mines nearby elements

    // It also changes the game_board[] with '0' if no
    // mines are found.
    if(nearbymines == 0)
    {
        if(c_selection != BOARD_SIZE)
        {
            i = 0;
            while(nearbymines == 0 && (c_selection - 1 + i) < BOARD_SIZE)
            {
                // This is checking elements to the right
                nearbymines = check_for_nearby_mines(r_selection - 1, (c_selection - 1 + i));
                if(nearbymines != -1)
                {
                game_board[r_selection - 1][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines );
                i++;
                }
            }
                if(r_selection != 1)
                {
                    i = 0;
                    while(nearbymines5 == 0 && (c_selection - 1 + i) < BOARD_SIZE && (r_selection - 1 - i) > 0)
                    {
                        // This is checking elements to the diagonal-uright
                        nearbymines5 = check_for_nearby_mines((r_selection - 1 - i), (c_selection - 1 + i));
                        if(nearbymines5 != -1)
                        {
                        game_board[(r_selection - 1) - i][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines5);
                        i++;
                        }
                    }
                }
                if(r_selection != BOARD_SIZE)
                {
                    i = 0;
                    while(nearbymines6 == 0 && (r_selection - 1 + i) < BOARD_SIZE && (c_selection - 1 + i) < BOARD_SIZE )
                    {
                        // This is checking elements to the diagonal-dright
                        nearbymines6 = check_for_nearby_mines((r_selection - 1 + i), (c_selection - 1 + i));
                        if(nearbymines != -1)
                        {
                        game_board[(r_selection - 1) + i][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines6);
                        i++;
                        }
                    }
                }
        }

        if(r_selection != BOARD_SIZE)
        {
            i = 0;
            while(nearbymines2 == 0 && (r_selection - 1 + i) < BOARD_SIZE)
            {
                // This is checking elements heading down
                nearbymines2 = check_for_nearby_mines((r_selection - 1 + i), c_selection - 1);
                if(nearbymines2 != -1)
                {
                game_board[(r_selection - 1) + i][c_selection - 1] = (char) ( ((int)'0') + nearbymines2 );
                i++;
                }
            }

            if(c_selection != BOARD_SIZE)
            {
                i = 0;
                while(nearbymines7 == 0 && (r_selection - 1 + i) < BOARD_SIZE && (c_selection - 1 - i) > 0)
                {
                    // This is checking elements to the diagonal-dleft
                    nearbymines7 = check_for_nearby_mines((r_selection - 1 + i), (c_selection - 1 - i));
                    if(nearbymines != -1)
                    {
                    game_board[(r_selection - 1) + i][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines7);
                    i++;
                    }
                }
            }
        }

        if(r_selection != 1)
        {
            i = 0;
            while(nearbymines3 == 0 && (r_selection - i) > 0)
            {
                // This is checking elements heading up
                nearbymines3 = check_for_nearby_mines((r_selection - 1 - i), c_selection - 1);
                if(nearbymines3 != -1)
                {
                game_board[(r_selection - 1) - i][c_selection - 1] = (char) ( ((int)'0') + nearbymines3 );
                i++;
                }
            }
            if(c_selection != BOARD_SIZE)
            {
                while(nearbymines8 == 0 && (c_selection - 1 - i) > 0 && (r_selection - 1 - i) > 0)
                {
                    // This is checking elements to the diagonal-uleft
                    nearbymines8 = check_for_nearby_mines((r_selection - 1 - i), (c_selection - 1 - i));
                    if(nearbymines8 != -1)
                    {
                    game_board[(r_selection - 1) - i][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines8);
                    i++;
                    }
                }
            }
        }

        if(c_selection != 1)
        {
            i = 0;
            while(nearbymines4 == 0 && (c_selection - i) > 0)
            {
                // This is checking elements to the left
                nearbymines4 = check_for_nearby_mines(r_selection - 1, (c_selection - 1 - i));
                if(nearbymines4 != -1)
                {
                game_board[r_selection - 1][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines4 );
                i++;
                }
            }
        }
    }



    // Handles a player winning.
    if(check_win_game() == TRUE)
    {
        system("cls");
        print_fullboard();
        printf("\n\nYou've won the game!! Congrats!!\n\n");
        play_again();
    }

    return 0;
}

/* Check whether user input has selected a mine */
void check_for_mine(int row, int col)
{
    if(board[row-1][col-1] == '*')
    {
        printf("\n\nBOOM!!! You hit a mine. Game over!\n");
        lost = 1;  // Set the global "lost" variable to 1 to indicate the game is over
    }
    else
    {
        int nearbymines = check_for_nearby_mines(row, col);

        if(nearbymines > 0)
        {
            game_board[row-1][col-1] = nearbymines + '0';
        }
        else
        {
            game_board[row-1][col-1] = ' ';
        }
    }

    // Check if user has won the game
    if (check_win_game()) {
        printf("\n\nCongratulations, you have won the game!\n");
        lost = 1; // Set the global "lost" variable to 1 to indicate the game is over
    }

    // Check if user has hit 3 mines
    static int mines_hit = 0; // Static variable to keep track of mines hit across function calls
    if (board[row-1][col-1] == '*' && ++mines_hit == 3) {
        printf("\n\nCongratulations, you have hit 3 mines! You win!\n");
        lost = 1; // Set the global "lost" variable to 1 to indicate the game is over
    }
}

int check_for_nearby_mines(int r_select, int c_select)
{
    int nearby_mine_count = 0;

    if(board[r_select][c_select] == '*')
    {
        return -1;
    }
    // Check for mines below and to the right.
    if(r_select < (BOARD_SIZE - 1) && c_select < (BOARD_SIZE - 1))
    {
        // Check for mine below
        if(board[r_select + 1][c_select] == '*')
            nearby_mine_count++;
        // Check for mine to the right.
        if(board[r_select][c_select + 1] == '*')
            nearby_mine_count++;
        // Check for mine diagonal-dright.
        if(board[r_select + 1][c_select + 1] == '*')
            nearby_mine_count++;

        // Check whether the columns to the left can be checked
        if(c_select != 0)
        {
            // Check for mine diagonal-dleft
            if(board[r_select + 1][c_select - 1] == '*')
                nearby_mine_count++;
            // Check for mine to the left
            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;
        }
        // Check whether the rows above can be checked
        if(r_select != 0)
        {
            // Check for mine above
            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;
            // Check for mine diagonal-uright
            if(board[r_select - 1][c_select + 1] == '*')
                nearby_mine_count++;
            // Check whether columns to the left can be checked
            if(c_select != 0)
            {
                // Check for mine diagonal-uleft
                if(board[r_select - 1][c_select - 1] == '*')
                    nearby_mine_count++;
            }
        }
    }
    // Check if selection is in last row
    if(r_select == (BOARD_SIZE - 1) && c_select != (BOARD_SIZE - 1))
    {
        // Check for mine above
            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;
        // Check for mine diagonal-uright
            if(board[r_select - 1][c_select + 1] == '*')
                nearby_mine_count++;
    }
    // Check if selection is in last column
    if(c_select == (BOARD_SIZE - 1) && r_select != (BOARD_SIZE - 1))
    {
        // Check for mine to the left
            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;
        // Check for mine diagonal-dleft
            if(board[r_select + 1][c_select - 1] == '*')
                nearby_mine_count++;
    }
    // Check whether selection is last in element
    if(r_select == (BOARD_SIZE - 1) && c_select == (BOARD_SIZE - 1))
    {
        // Check for mine to the left
            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;
        // Check for mine diagonal-dleft
            if(board[r_select - 1][c_select - 1] == '*')
                nearby_mine_count++;
        // Check for mine above
            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;
    }

    return nearby_mine_count;
}

/* Check if user has won game */
int check_win_game()
{
    int row, col;

    for(row = 0; row < BOARD_SIZE; row++)
        for(col = 0; col < BOARD_SIZE; col++)
        {
            if(game_board[row][col] == 'o' && board[row][col] != '*')
                return FALSE;
        }

    return TRUE;
}
// Ask user if they wish to play again.
void play_again()
{
    char ans;

    printf("\n\nWould you like to play again? (y/n) --> ");
    scanf(" %c", &ans);

    if(toupper(ans) == 'Y')
    {
        system("cls");
        start();
    }

    else
    {
        printf("\n\nThanks for playing! Bye.");
        (void) getchar();
        exit(EXIT_SUCCESS);
    }
}
// Displays the welcome message, and the GNU License
void display_welcome()
{
    printf("-----------------------Welcome to Minesweeper!---------------------------");

    printf("\n Press [ENTER] to start game!");
    printf("\n\n");
}

void start()
{
    lost = 0;    // User hasn't lost yet
    // Build both game boards (one for the user to see,
    // and the one with the mines).
    build_board();
    build_gboard();

    // Start playing game
    do
    {
    play_game();
    print_board();
    } while(lost != 1);    // While the user hasn't lost, loop.

    // Once user is lost, print the board with all the mines.
    print_fullboard();

    // Play again?
    play_again();
}
