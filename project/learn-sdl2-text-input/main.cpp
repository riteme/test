#include <SDL2/SDL.h>

extern void InitVideo();
extern void Redraw();

int main() {
    SDL_bool done = SDL_FALSE;
    char *text;
    char *composition;
    Sint32 cursor;
    Sint32 selection_len;

    InitVideo();
    /* ... */

    SDL_StartTextInput();
    while (!done) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    /* Quit */
                    done = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    /* Add new text onto the end of our text */
                    strcat(text, event.text.text);
                    break;
                case SDL_TEXTEDITING:
                    /*
                    Update the composition text.
                    Update the cursor position.
                    Update the selection length (if any).
                    */
                    composition = event.edit.text;
                    cursor = event.edit.start;
                    selection_len = event.edit.length;
                    break;
            }
        }
        Redraw();
    }

    SDL_Quit();

    return 0;
}

void InitVideo() {}

void Redraw() {}
