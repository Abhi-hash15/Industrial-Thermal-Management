#include "../include/fan_controller.h"
#include "../include/thermal_monitor.h"
#include "../driver/fan_driver.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int WINDOW_WIDTH = 1100;
const int WINDOW_HEIGHT = 650;

struct DataPoint
{
    double temperature;
    int fanSpeed;
};

// ------------------------------------------------------------
// Draw text
// ------------------------------------------------------------
void drawText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const std::string& text,
    int x,
    int y,
    SDL_Color color)
{
    SDL_Surface* surface =
        TTF_RenderUTF8_Blended(
            font,
            text.c_str(),
            color);

    if (!surface)
        return;

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(
            renderer,
            surface);

    if (!texture)
    {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destination{
        x,
        y,
        surface->w,
        surface->h};

    SDL_RenderCopy(
        renderer,
        texture,
        nullptr,
        &destination);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// ------------------------------------------------------------
// Draw panel
// ------------------------------------------------------------
void drawPanel(
    SDL_Renderer* renderer,
    int x,
    int y,
    int width,
    int height)
{
    SDL_SetRenderDrawColor(
        renderer,
        35, 42, 50, 255);

    SDL_Rect panel{
        x,
        y,
        width,
        height};

    SDL_RenderFillRect(
        renderer,
        &panel);
}

// ------------------------------------------------------------
// Draw bar
// ------------------------------------------------------------
void drawBar(
    SDL_Renderer* renderer,
    int x,
    int y,
    int width,
    int height,
    double percentage,
    SDL_Color color)
{
    SDL_SetRenderDrawColor(
        renderer,
        55, 62, 70, 255);

    SDL_Rect background{
        x,
        y,
        width,
        height};

    SDL_RenderFillRect(
        renderer,
        &background);

    double value =
        std::clamp(
            percentage,
            0.0,
            100.0);

    int filledWidth =
        static_cast<int>(
            width * value / 100.0);

    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        255);

    SDL_Rect filled{
        x,
        y,
        filledWidth,
        height};

    SDL_RenderFillRect(
        renderer,
        &filled);
}

// ------------------------------------------------------------
// Status color
// ------------------------------------------------------------
SDL_Color getStatusColor(
    const std::string& status)
{
    if (status == "EMERGENCY")
        return {220, 50, 50, 255};

    if (status == "CRITICAL")
        return {240, 110, 40, 255};

    if (status == "HIGH")
        return {230, 190, 40, 255};

    if (status == "NORMAL")
        return {60, 180, 100, 255};

    return {90, 130, 200, 255};
}

// ------------------------------------------------------------
// Draw threshold line
// ------------------------------------------------------------
void drawThresholdLine(
    SDL_Renderer* renderer,
    TTF_Font* font,
    int graphX,
    int graphY,
    int graphWidth,
    int graphHeight,
    double temperature,
    const std::string& label,
    SDL_Color color)
{
    int lineY =
        graphY +
        graphHeight -
        static_cast<int>(
            temperature / 100.0 *
            graphHeight);

    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        255);

    SDL_RenderDrawLine(
        renderer,
        graphX,
        lineY,
        graphX + graphWidth,
        lineY);

    drawText(
        renderer,
        font,
        label,
        graphX + graphWidth - 70,
        lineY - 18,
        color);
}

// ------------------------------------------------------------
// Draw graph
// ------------------------------------------------------------
void drawGraph(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const std::vector<DataPoint>& history)
{
    const int graphX = 70;
    const int graphY = 375;
    const int graphWidth = 960;
    const int graphHeight = 155;

    // Background
    SDL_SetRenderDrawColor(
        renderer,
        28, 34, 40, 255);

    SDL_Rect background{
        graphX,
        graphY,
        graphWidth,
        graphHeight};

    SDL_RenderFillRect(
        renderer,
        &background);

    // Grid
    SDL_SetRenderDrawColor(
        renderer,
        60, 68, 76, 255);

    for (int value = 0;
         value <= 100;
         value += 20)
    {
        int y =
            graphY +
            graphHeight -
            static_cast<int>(
                value / 100.0 *
                graphHeight);

        SDL_RenderDrawLine(
            renderer,
            graphX,
            y,
            graphX + graphWidth,
            y);

        drawText(
            renderer,
            font,
            std::to_string(value),
            graphX - 35,
            y - 8,
            {160, 170, 180, 255});
    }

    // Thresholds
    drawThresholdLine(
        renderer,
        font,
        graphX,
        graphY,
        graphWidth,
        graphHeight,
        45,
        "45 C",
        {100, 150, 220, 255});

    drawThresholdLine(
        renderer,
        font,
        graphX,
        graphY,
        graphWidth,
        graphHeight,
        65,
        "65 C",
        {230, 190, 60, 255});

    drawThresholdLine(
        renderer,
        font,
        graphX,
        graphY,
        graphWidth,
        graphHeight,
        75,
        "75 C",
        {240, 110, 50, 255});

    drawThresholdLine(
        renderer,
        font,
        graphX,
        graphY,
        graphWidth,
        graphHeight,
        85,
        "85 C",
        {230, 50, 50, 255});

    // Temperature curve
    if (history.size() < 2)
        return;

    SDL_SetRenderDrawColor(
        renderer,
        70, 190, 255, 255);

    for (size_t i = 1;
         i < history.size();
         ++i)
    {
        int x1 =
            graphX +
            static_cast<int>(
                (i - 1) *
                graphWidth /
                static_cast<double>(
                    history.size() - 1));

        int x2 =
            graphX +
            static_cast<int>(
                i *
                graphWidth /
                static_cast<double>(
                    history.size() - 1));

        int y1 =
            graphY +
            graphHeight -
            static_cast<int>(
                history[i - 1].temperature /
                100.0 *
                graphHeight);

        int y2 =
            graphY +
            graphHeight -
            static_cast<int>(
                history[i].temperature /
                100.0 *
                graphHeight);

        SDL_RenderDrawLine(
            renderer,
            x1,
            y1,
            x2,
            y2);
    }
}

// ------------------------------------------------------------
// Draw control box
// ------------------------------------------------------------
void drawControlBox(
    SDL_Renderer* renderer,
    TTF_Font* font,
    int x,
    int y,
    int width,
    const std::string& text,
    SDL_Color color)
{
    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        255);

    SDL_Rect box{
        x,
        y,
        width,
        30};

    SDL_RenderDrawRect(
        renderer,
        &box);

    drawText(
        renderer,
        font,
        text,
        x + 10,
        y + 5,
        color);
}

// ============================================================
// MAIN
// ============================================================
int main()
{
    ThermalConfig config{};

    if (!loadConfig(
            "config/config.txt",
            config))
    {
        std::cerr
            << "Error: Unable to load configuration.\n";

        return 1;
    }

    // --------------------------------------------------------
    // SDL initialization
    // --------------------------------------------------------

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr
            << "SDL initialization failed: "
            << SDL_GetError()
            << "\n";

        return 1;
    }

    if (TTF_Init() != 0)
    {
        std::cerr
            << "SDL_ttf initialization failed: "
            << TTF_GetError()
            << "\n";

        SDL_Quit();

        return 1;
    }

    // --------------------------------------------------------
    // Window
    // --------------------------------------------------------

    SDL_Window* window =
        SDL_CreateWindow(
            "Industrial Thermal Management - IoT Simulation",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr
            << "Window creation failed: "
            << SDL_GetError()
            << "\n";

        TTF_Quit();
        SDL_Quit();

        return 1;
    }

    SDL_Renderer* renderer =
        SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cerr
            << "Renderer creation failed: "
            << SDL_GetError()
            << "\n";

        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();

        return 1;
    }

    // --------------------------------------------------------
    // Fonts
    // --------------------------------------------------------

    const char* fontPath =
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";

    TTF_Font* font =
        TTF_OpenFont(
            fontPath,
            18);

    TTF_Font* largeFont =
        TTF_OpenFont(
            fontPath,
            38);

    TTF_Font* titleFont =
        TTF_OpenFont(
            fontPath,
            28);

    if (!font || !largeFont || !titleFont)
    {
        std::cerr
            << "Unable to load font: "
            << TTF_GetError()
            << "\n";

        if (font)
            TTF_CloseFont(font);

        if (largeFont)
            TTF_CloseFont(largeFont);

        if (titleFont)
            TTF_CloseFont(titleFont);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        TTF_Quit();
        SDL_Quit();

        return 1;
    }

    // --------------------------------------------------------
    // Fan driver
    // --------------------------------------------------------

    FanDriver fan;

    if (!fan.initialize())
    {
        TTF_CloseFont(font);
        TTF_CloseFont(largeFont);
        TTF_CloseFont(titleFont);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        TTF_Quit();
        SDL_Quit();

        return 1;
    }

    // --------------------------------------------------------
    // Simulation state
    // --------------------------------------------------------

    bool running = true;
    bool paused = false;
    bool autoMode = true;

    double manualTemperature = 40.0;

    std::vector<DataPoint> history;

    Uint32 lastUpdate = SDL_GetTicks();

    // ========================================================
    // MAIN LOOP
    // ========================================================

    while (running)
    {
        SDL_Event event;

        // ----------------------------------------------------
        // Keyboard / Window events
        // ----------------------------------------------------

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_KEYDOWN)
            {
                SDL_Keycode key =
                    event.key.keysym.sym;

                // ESC = Exit
                if (key == SDLK_ESCAPE)
                {
                    running = false;
                }

                // SPACE = Pause / Resume
                else if (key == SDLK_SPACE)
                {
                    paused = !paused;
                }

                // A = Auto mode
                else if (key == SDLK_a)
                {
                    autoMode = true;
                    paused = false;
                }

                // M = Manual mode
                else if (key == SDLK_m)
                {
                    autoMode = false;
                    paused = false;
                }

                // R = Reset
                else if (key == SDLK_r)
                {
                    autoMode = false;
                    paused = false;

                    manualTemperature = 40.0;

                    history.clear();

                    fan.setFanSpeed(0);
                }

                // UP = Increase manual temperature
                else if (
                    !autoMode &&
                    key == SDLK_UP)
                {
                    manualTemperature += 1.0;

                    if (manualTemperature > 90.0)
                        manualTemperature = 90.0;
                }

                // DOWN = Decrease manual temperature
                else if (
                    !autoMode &&
                    key == SDLK_DOWN)
                {
                    manualTemperature -= 1.0;

                    if (manualTemperature < 40.0)
                        manualTemperature = 40.0;
                }
            }
        }

        // ----------------------------------------------------
        // Update simulation once per second
        // ----------------------------------------------------

        Uint32 currentTime =
            SDL_GetTicks();

        if (!paused &&
            currentTime - lastUpdate >= 1000)
        {
            lastUpdate = currentTime;

            double temperature;

            if (autoMode)
            {
                temperature =
                    getSimulatedTemperature();
            }
            else
            {
                temperature =
                    manualTemperature;
            }

            int fanSpeed =
                calculateFanSpeed(
                    temperature,
                    config);

            fan.setFanSpeed(
                fanSpeed);

            history.push_back({
                temperature,
                fanSpeed});

            if (history.size() > 100)
            {
                history.erase(
                    history.begin());
            }
        }

        // ----------------------------------------------------
        // Current values
        // ----------------------------------------------------

        double temperature;

        if (history.empty())
        {
            temperature =
                autoMode
                    ? 40.0
                    : manualTemperature;
        }
        else
        {
            temperature =
                history.back().temperature;
        }

        int fanSpeed =
            calculateFanSpeed(
                temperature,
                config);

        std::string status =
            getThermalStatus(
                temperature,
                config);

        // ----------------------------------------------------
        // Clear screen
        // ----------------------------------------------------

        SDL_SetRenderDrawColor(
            renderer,
            18, 22, 27, 255);

        SDL_RenderClear(renderer);

        // ====================================================
        // HEADER
        // ====================================================

        drawText(
            renderer,
            titleFont,
            "INDUSTRIAL THERMAL MANAGEMENT",
            325,
            12,
            {235, 240, 245, 255});

        drawText(
            renderer,
            font,
            "IoT THERMAL CONTROL SIMULATION",
            420,
            45,
            {150, 160, 170, 255});

        // ====================================================
        // TEMPERATURE PANEL
        // ====================================================

        drawPanel(
            renderer,
            50,
            75,
            480,
            235);

        drawText(
            renderer,
            font,
            "TEMPERATURE SENSOR",
            75,
            95,
            {185, 195, 205, 255});

        drawText(
            renderer,
            largeFont,
            std::to_string(
                static_cast<int>(
                    temperature)) +
                " C",
            75,
            135,
            {70, 190, 255, 255});

        drawBar(
            renderer,
            75,
            205,
            400,
            30,
            temperature,
            {70, 180, 255, 255});

        drawText(
            renderer,
            font,
            "40 C",
            75,
            245,
            {145, 155, 165, 255});

        drawText(
            renderer,
            font,
            "90 C",
            435,
            245,
            {145, 155, 165, 255});

        // ====================================================
        // FAN PANEL
        // ====================================================

        drawPanel(
            renderer,
            570,
            75,
            480,
            235);

        drawText(
            renderer,
            font,
            "FAN PWM DRIVER",
            595,
            95,
            {185, 195, 205, 255});

        drawText(
            renderer,
            largeFont,
            std::to_string(
                fanSpeed) +
                " %",
            595,
            135,
            {70, 220, 135, 255});

        drawBar(
            renderer,
            595,
            205,
            400,
            30,
            fanSpeed,
            {70, 200, 120, 255});

        drawText(
            renderer,
            font,
            "0 %",
            595,
            245,
            {145, 155, 165, 255});

        drawText(
            renderer,
            font,
            "100 %",
            940,
            245,
            {145, 155, 165, 255});

        // ====================================================
        // STATUS
        // ====================================================

        SDL_Color statusColor =
            getStatusColor(status);

        SDL_SetRenderDrawColor(
            renderer,
            statusColor.r,
            statusColor.g,
            statusColor.b,
            255);

        SDL_Rect statusBox{
            400,
            315,
            300,
            42};

        SDL_RenderFillRect(
            renderer,
            &statusBox);

        drawText(
            renderer,
            font,
            "STATUS: " + status,
            480,
            326,
            {255, 255, 255, 255});

        // ====================================================
        // MODE / RUNNING
        // ====================================================

        drawText(
            renderer,
            font,
            autoMode
                ? "MODE: AUTO"
                : "MODE: MANUAL",
            70,
            320,
            {200, 210, 220, 255});

        drawText(
            renderer,
            font,
            paused
                ? "PAUSED"
                : "RUNNING",
            920,
            320,
            paused
                ? SDL_Color{240, 190, 60, 255}
                : SDL_Color{70, 200, 120, 255});

        // ====================================================
        // GRAPH TITLE
        // ====================================================

        drawText(
            renderer,
            font,
            "LIVE TEMPERATURE HISTORY",
            70,
            355,
            {190, 200, 210, 255});

        // ====================================================
        // GRAPH
        // ====================================================

        drawGraph(
            renderer,
            font,
            history);

        // ====================================================
        // MANUAL TEMPERATURE
        // ====================================================

        if (!autoMode)
        {
            drawText(
                renderer,
                font,
                "MANUAL TEMPERATURE: " +
                    std::to_string(
                        static_cast<int>(
                            manualTemperature)) +
                    " C",
                70,
                540,
                {80, 190, 255, 255});
        }
        else
        {
            drawText(
                renderer,
                font,
                "AUTOMATIC SENSOR SIMULATION",
                70,
                540,
                {100, 180, 220, 255});
        }

        // ====================================================
        // CONTROLS
        // ====================================================

        drawControlBox(
            renderer,
            font,
            70,
            575,
            120,
            "SPACE: PAUSE",
            {200, 210, 220, 255});

        drawControlBox(
            renderer,
            font,
            205,
            575,
            100,
            "A: AUTO",
            {70, 200, 120, 255});

        drawControlBox(
            renderer,
            font,
            320,
            575,
            120,
            "M: MANUAL",
            {80, 180, 230, 255});

        drawControlBox(
            renderer,
            font,
            455,
            575,
            110,
            "UP/DOWN",
            {230, 190, 60, 255});

        drawControlBox(
            renderer,
            font,
            580,
            575,
            100,
            "R: RESET",
            {200, 150, 150, 255});

        drawControlBox(
            renderer,
            font,
            695,
            575,
            100,
            "ESC: EXIT",
            {220, 120, 120, 255});

        // ====================================================
        // EMERGENCY / NORMAL MESSAGE
        // ====================================================

        if (status == "EMERGENCY")
        {
            drawText(
                renderer,
                font,
                "!!! EMERGENCY - FAN 100% !!!",
                810,
                610,
                {240, 60, 60, 255});
        }
        else
        {
            drawText(
                renderer,
                font,
                "System Monitoring Active",
                830,
                610,
                {100, 170, 120, 255});
        }

        // ----------------------------------------------------
        // Display
        // ----------------------------------------------------

        SDL_RenderPresent(renderer);

        SDL_Delay(30);
    }

    // ========================================================
    // CLEANUP
    // ========================================================

    fan.shutdown();

    TTF_CloseFont(font);
    TTF_CloseFont(largeFont);
    TTF_CloseFont(titleFont);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
