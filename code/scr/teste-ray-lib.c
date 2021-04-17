#include "raylib.h"
#include "screens_disp.h"


#define SQUARE_SIZE  10
#define MARGEM 30
#define DISPLAY_SCREEN_WIDTH 840
#define DISPLAY_SCREEN_HEIGHT 480
#define BUTTON_MARGEM 40

#define COLOR_DISPLAY CLITERAL(Color){ 178, 255, 102, 100 }

static const int screenWidth  = DISPLAY_SCREEN_WIDTH  + 2*MARGEM;
static const int screenHeight = DISPLAY_SCREEN_HEIGHT + 2*MARGEM;
static const int windownWidth = screenWidth;
static const int windownHeight = screenHeight + BUTTON_MARGEM;

typedef struct Position
{
    int x;
    int y;
    
}Position;


void DrawGridPixel(void);
void DrawPixelDisplay(int posX, int posY);
void DrawButtons(void);
void print_char(char *buffer);
void screen_draw_line_8_bits(Position offset, uint8_t buffer);
void screen_draw_line_16_bits(Position offset, uint8_t *buffer);
void screen_draw_16_x_n(Position offset, int n, uint8_t *buffer);



int main()
{
    InitWindow(windownWidth , windownHeight, "Tamagotchi");
    SetTargetFPS(60);
    //Image icon = LoadImage("C:/Users/luca_/OneDrive/Área de Trabalho/y.png");
    //Image icon = LoadImage("C:/Users/luca_/OneDrive/Área de Trabalho/Untitled-03.png");
    //noun_angry_2203573
    //SetWindowIcon(icon); 
    
    while( !WindowShouldClose() )
    {
        DrawRectangle(MARGEM , MARGEM , DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, COLOR_DISPLAY); 
        DrawGridPixel();
        //DrawButtons();
        
        DrawPixelDisplay(84, 48);
        DrawPixelDisplay(1, 1);
        DrawPixelDisplay(1, 48);
        DrawPixelDisplay(84, 1);
        
        Position p = {.x = 10 , .y = 10};
        //screen_draw_line_8_bits(p, 0xFF);
        
        uint8_t buffer[4] = {0xFF, 0xAA, 0xFF, 0xFF};
        
        //screen_draw_line_16_bits(p,buffer );
        screen_draw_16_x_n(p, 16, char_2);
        

    }
    CloseWindow();   
}




void DrawGridPixel(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for(int i = 0; i < screenWidth/SQUARE_SIZE + 1 - (2*MARGEM)/SQUARE_SIZE; i++)
    {
        DrawLineV((Vector2){(i*SQUARE_SIZE + MARGEM), MARGEM}, (Vector2) {(i*SQUARE_SIZE + MARGEM), screenHeight - MARGEM}, LIGHTGRAY);
    }
    
    for(int i = 0; i < screenHeight/SQUARE_SIZE + 1 - (2*MARGEM)/SQUARE_SIZE; i++)
    {
        DrawLineV((Vector2){MARGEM, (i*SQUARE_SIZE + MARGEM)}, (Vector2) {screenWidth - MARGEM, (i*SQUARE_SIZE + MARGEM)}, LIGHTGRAY);
    }
    
    EndDrawing();    
}

void DrawPixelDisplay(int posX, int posY)
{
    
    
    DrawRectangle(SQUARE_SIZE*posX + MARGEM - 1*SQUARE_SIZE, SQUARE_SIZE*posY + MARGEM -1*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, BLACK); 
}

void DrawButtons(void)
{
    DrawCircle(windownWidth - 40 , windownHeight - 40, 15, BLACK);
}



void print_char(char *buffer)
{
    
};

void screen_draw_line_8_bits(Position offset, uint8_t buffer)
{
    uint8_t val = 0;
    for(int col = 0; col <  8; col++)
    {
        val = (buffer >> col) & (uint8_t)0x01;
        
        if( val == 0x01) 
        {
            DrawPixelDisplay(col + offset.x +1, offset.y+1);  
        }
        
    }
};

void screen_draw_line_16_bits(Position offset, uint8_t *buffer)
{
    screen_draw_line_8_bits(offset, *(buffer));
    offset.x += 8;
    buffer++;
    screen_draw_line_8_bits(offset, *(buffer));
    
};

void screen_draw_16_x_n(Position offset, int n, uint8_t *buffer)
{
    for(int i = 0; i < n; i++)
    {
        screen_draw_line_16_bits(offset, (buffer));
        ++buffer;
        ++buffer;
        offset.y++;
    }
}

