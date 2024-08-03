#ifndef GAME_H
#define GAME_H

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Surface SDL_Surface;

class Game {
public:
    Game();
    void Run();

private:
    static const int SCREEN_HEIGHT = 720;
    static const int SCREEN_WIDTH = 1280;

    // Window used for program rendering
    SDL_Window* window;

    // Surface contained by the window
    SDL_Surface* screenSurface;

    // Image that will be shown on the screen
    SDL_Surface* imgSurface;

    bool Init();
    bool LoadMedia();
    void EventHandler();
    void Close();
};

#endif