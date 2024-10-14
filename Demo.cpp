#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Function to draw a star using lines
void draw_star(SDL_Renderer *renderer, int x, int y, int size, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Top portion of star
    SDL_RenderDrawLine(renderer, x, y - size, x + (size / 3), y);
    SDL_RenderDrawLine(renderer, x, y - size, x - (size / 3), y);
    SDL_RenderDrawLine(renderer, x - (size / 3), y, x + (size / 3), y);

    // Right portion of star
    SDL_RenderDrawLine(renderer, x + (size / 3), y, x + (2 * size / 3), y + (size / 2));
    SDL_RenderDrawLine(renderer, x + (2 * size / 3), y + (size / 2), x + (size / 3), y);

    // Bottom right portion of star
    SDL_RenderDrawLine(renderer, x + (2 * size / 3), y + (size / 2), x + (size / 3), y + size);
    SDL_RenderDrawLine(renderer, x + (size / 3), y + size, x + (2 * size / 3), y + (size / 2));

    // Bottom left portion of star
    SDL_RenderDrawLine(renderer, x - (2 * size / 3), y + (size / 2), x - (size / 3), y + size);
    SDL_RenderDrawLine(renderer, x - (size / 3), y + size, x - (2 * size / 3), y + (size / 2));

    // Left portion of star
    SDL_RenderDrawLine(renderer, x - (2 * size / 3), y + (size / 2), x - (size / 3), y);
    SDL_RenderDrawLine(renderer, x - (size / 3), y, x - (2 * size / 3), y + (size / 2));
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Star Drawing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Set the colors
    SDL_Color star_color = {255, 255, 255, 255}; // White color for the star
    SDL_Color darkgray = {169, 169, 169, 255};  // Dark gray for background

    // Main loop flag
    int quit = 0;
    SDL_Event event;

    // Star coordinates
    int midx = WINDOW_WIDTH / 2;
    int midy = WINDOW_HEIGHT / 2;
    int size = 100;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Set background color to dark gray
        SDL_SetRenderDrawColor(renderer, darkgray.r, darkgray.g, darkgray.b, darkgray.a);
        SDL_RenderClear(renderer);

        // Draw star in the center of the screen
        draw_star(renderer, midx, midy, size, star_color);

        // Present the rendering to the window
        SDL_RenderPresent(renderer);

        // Wait for 2 seconds (2000 milliseconds)
        SDL_Delay(2000);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
