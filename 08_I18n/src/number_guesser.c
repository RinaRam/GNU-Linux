#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include "config.h"

#define _(STRING) gettext(STRING)


int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    bindtextdomain ("number_guesser", LOCALE_PATH);
    textdomain ("number_guesser");

    int low = 1;
    int high = 100;
    int guess;
    char answer[6];

    printf(_("Guess a number between 1 and 100.\n"));

    while (low <= high) {
        guess = (low + high) / 2;

        printf(_("Is your number greater than %d? (yes/no): "), guess);
        scanf("%s", answer);

        if (strcmp(answer, _("yes")) == 0) {
            low = guess + 1;
        } else if (strcmp(answer, _("no")) == 0) {
            high = guess;
        } else {
            printf(_("Incorrect answer. Please answer 'yes' or 'no'.\n"));
            continue;
        }

        if (low > high) {
            printf(_("You made a mistake or guessed a number outside the range of 1 to 100.\n"));
            break;
        }
        
        if (low == high) {
            printf(_("Your number is: %d\n"), low);
            break;
        }
    }

    return 0;
}
