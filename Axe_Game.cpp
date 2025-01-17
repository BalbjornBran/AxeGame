//Include the libraries that we are going to use.
//Lets first include the Raylib library. It is an external library, so #include uses "" instead of <> as it is not part of the C++ Standard Library.
//Also include the string library for using standar c++ strings on screen.
#include "raylib.h"
#include <string>

// This is the main function that is initiated at start of the program
int main ()
{

    // Creating the variables for the size of the window
    constexpr int WindowWidth = 1024;
    // Another way to declare an initialize a variable is using {}
    constexpr int WindowHeight {768};

    //*****************************************************************************************************************************
    //Game State
    // We will be using a Game state to determine if the game is in the initial state, playing, Winning or Game over
    int game_state{0}; //0 -> Initial State, 1 -> Playing, 2 -> Game Over, 3-> Winning the game

    //*****************************************************************************************************************************
    //Player Character
    //The object that the player is going to control, is represented by a circle in this game, so lets create the variables for it.
    //Initialization of the circle at begin play. The player will be in the middle of the screen.
    int circle_x{WindowWidth/2};
    int circle_y{WindowHeight/2};
    
    //Character Dimensions and positions
    constexpr int circle_radius{25};
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    //Player variables
    int player_score {0};
    constexpr int max_score {100};
    constexpr int player_speed {10};

    //*****************************************************************************************************************************
    //Axe Object Variables
    //This is the Axe's size
    int axe_length {100};
    //This is the Axe's coordinates at begin play
    int axe_x{WindowWidth/2 - axe_length};
    int axe_y{0};
    //Direction of movement of the axe
    int axe_direction = 5;
    // Axes Dimensions
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_length};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + axe_length};

    //*****************************************************************************************************************************
    //Rings Variables
    Vector2 ring_center{WindowWidth*0.3,WindowHeight/2};
    float ring_i_r{25};
    float ring_o_r{35};
    //Ring Dimentions
    int l_ring_x{ring_center.x-ring_o_r};
    int r_ring_x{ring_center.x+ring_o_r};
    int u_ring_y{ring_center.y-ring_o_r};
    int b_ring_y{ring_center.y+ring_o_r};
    
    //*****************************************************************************************************************************
    //Gameplay Variables
    bool bcollision_with_axe {false};
    bool bcollision_with_ring {false};
    
    //*****************************************************************************************************************************
    //First action is to create a popup window where we can see the game.
    InitWindow(WindowWidth, WindowHeight, "Axe Game by Tony Hmt");  

    //We are going to use a function from Raylib to set the frames per second of the program to be 60, just to prevent this program to run extremely fast.
    SetTargetFPS(60);

    //As long as the player doesn't want to close the window, we check if it should close or not with Raylibs "WindowShouldClose" function.
    //We will create a while loop as loong as should close is false.
    while (WindowShouldClose() == false)
    {
        //This function set up the PopUp window to let us draw stuff into it every frame.
        BeginDrawing();
        //Setting a black background
        ClearBackground(BLACK);
        
        //With this switch, we will be changing the game's screen based on the game state.
        switch (game_state)
        {
            case 0: //This is the intro screen
                DrawText("Use WASD for moving and try to collect as much rings as possible.", 10, WindowHeight/2 - 20, 20, WHITE);
                DrawText("Press WASD to start...", 10, WindowHeight/2 + 20, 20, WHITE);

                // if the palyer uses the movement keys
                if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))
                {
                    game_state = 1; // we change the state to playing
                }
            break;

            case 1: //Game logic begins
                if (bcollision_with_axe)
                {
                    game_state = 2; // we change the state to Game Over
                    
                } else if (player_score >= max_score)
                {
                    game_state = 3; // we change the state to Win
                }
                else
                {
                    //Here we draw every frame
                    DrawCircle(circle_x,circle_y,circle_radius,BLUE);
                    DrawRectangle(axe_x,axe_y,axe_length,axe_length,RED);
                    DrawRing(ring_center,ring_i_r,ring_o_r,0.0,360.0,24,YELLOW);
                    DrawText(("Player score = " + std::to_string(player_score)).c_str(), 10,30,20,WHITE);

                    //Update Dimensions positions
                    //Circle Position
                    l_circle_x = circle_x - circle_radius;
                    r_circle_x = circle_x + circle_radius;
                    u_circle_y = circle_y - circle_radius;
                    b_circle_y = circle_y + circle_radius;

                    //Axe position
                    l_axe_x = axe_x;
                    r_axe_x = axe_x + axe_length;
                    u_axe_y = axe_y;
                    b_axe_y = axe_y + axe_length;

                    //Ring Position
                    l_ring_x = ring_center.x-ring_o_r;
                    r_ring_x = ring_center.x+ring_o_r;
                    u_ring_y = ring_center.y-ring_o_r;
                    b_ring_y = ring_center.y+ring_o_r;
                    

                    //Update collision state
                    bcollision_with_axe =  (b_axe_y >= u_circle_y) && 
                                        (u_axe_y <= b_circle_y) && 
                                        (r_axe_x >= l_circle_x) && 
                                        (l_axe_x <= r_circle_x);

                    bcollision_with_ring =  (u_circle_y <= b_ring_y) &&
                                            (b_circle_y >= u_ring_y) && 
                                            (l_circle_x <= r_ring_x) && 
                                            (r_circle_x >= l_ring_x);

                    //Movement of the Axe
                    axe_y += axe_direction;
                    if (axe_y > WindowHeight-axe_length || axe_y < 0)
                    {
                        axe_direction = -axe_direction;
                    }

                    // If the player Presses D or A, the circle moves right or left.
                    if (IsKeyDown(KEY_D) && circle_x < WindowWidth )
                    {
                        circle_x += player_speed;
                    }
                    
                    if (IsKeyDown(KEY_A) && circle_x > 0)
                    {
                        circle_x -= player_speed;
                    }

                    // If the player Presses W or S, the circle moves up or down.
                    if (IsKeyDown(KEY_W) && circle_y > 0+circle_radius )
                    {
                        circle_y -= player_speed;
                    }
                    
                    if (IsKeyDown(KEY_S) && circle_y < WindowHeight-circle_radius)
                    {
                        circle_y += player_speed;
                    }

                    if  (bcollision_with_ring)
                    {
                        player_score += 10;
                        ring_center.x = (GetRandomValue(0+ring_o_r, WindowWidth-ring_o_r));
                        ring_center.y = (GetRandomValue(0+ring_o_r, WindowHeight-ring_o_r));
                    }
                    
                }
            break;

            case 2:
                {
                    int text_width = MeasureText("Game Over!", 20);
                    DrawText("Game Over!", (WindowWidth - text_width) / 2, WindowHeight / 2, 20, RED);
                    DrawText("Press R to Restart", WindowWidth / 2 - 50, WindowHeight / 2 + 40, 20, WHITE);

                    // Restart the game if R is pressed
                    if (IsKeyPressed(KEY_R))
                    {
                        game_state = 0;
                        player_score = 0;
                        circle_x = WindowWidth / 2;
                        circle_y = WindowHeight / 2;
                        axe_y = 0;
                        bcollision_with_axe = false;
                    }
                }
            break;
            
            case 3:
                DrawText("You win!",WindowWidth/2,WindowHeight/2,20,GREEN);
            break;
            default:
            break;
        }
        //Game Logic ends
                   
    EndDrawing();
    }

}