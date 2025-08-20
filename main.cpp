#include <SFML/Graphics.hpp>
#include <unordered_set>


const int ScreenWidth = 1280;
const int ScreenHeight = 720;


//Hash table for the sets
struct HashVector2f
{
    std::size_t operator()(const sf::Vector2f &vector) const
        {
           return (vector.y * ScreenWidth + vector.x);
        }
};

class GameOfLife
{
private:
    //2 sets of each to make sure the updates happen in a single instance
    //Also have Potential grid for cells they may become alive but aren't. Also makes it easier to make sure which ones are alive
    std::unordered_set<sf::Vector2f, HashVector2f> CURRENT_GRID;
    std::unordered_set<sf::Vector2f, HashVector2f> NEXT_GRID;
    std::unordered_set<sf::Vector2f, HashVector2f> POTENTIAL_GRID;
    std::unordered_set<sf::Vector2f, HashVector2f> POTENTIAL_NEXT_GRID;
    sf::RectangleShape cell;
    
public:
    GameOfLife()
    {
        cell.setSize(sf::Vector2f(1,1));
        
        for(int r = 0; r <= ScreenWidth; r ++)
        {
            int k = ScreenHeight/2;
            NEXT_GRID.insert(sf::Vector2f(r,k));
            CURRENT_GRID.insert(sf::Vector2f(r,k));
            for (int y = -1; y <= 1; y++)
                for (int x = -1; x <= 1; x++)
                    POTENTIAL_NEXT_GRID.insert(sf::Vector2f(x + r, y + k));
            
        }
    }
    
    int isActive(const sf::Vector2f &v) //Returns 1 if cell is alive 0 if dead
    {
        return CURRENT_GRID.contains(v) ? 1 : 0;
    }
    
    void insertPotentialNear(const sf::Vector2f &v) //Takes in cell curent position and and adds surounding cell for potential
    {
        for (int j = -1; j <= 1; j++)
        {
            for (int i = -1; i <= 1; i++)
            {
                POTENTIAL_NEXT_GRID.insert(v + sf::Vector2f(i, j));
            }
        }
    }
    
    void gameInput(sf::RenderWindow &window)
    {
        auto mouse = sf::Mouse::getPosition(window);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))     //Used to draw with the mouse
        {
           
            NEXT_GRID.insert(sf::Vector2f(mouse));
            CURRENT_GRID.insert(sf::Vector2f(mouse));
            insertPotentialNear(sf::Vector2f(mouse));
        }
    }
    
    void gameLoop(sf::RenderWindow &window)
    {
        //Grids are set to eachother at once to not break the simulation
        
        CURRENT_GRID = NEXT_GRID;
        NEXT_GRID.clear();
        NEXT_GRID.reserve(CURRENT_GRID.size());
        POTENTIAL_GRID = POTENTIAL_NEXT_GRID;
        POTENTIAL_NEXT_GRID = CURRENT_GRID;
        
        for(const auto &c : POTENTIAL_GRID)
        {
            gameInput(window); //Used for drawing with mouse
            
            //Will check surounding cells to see if they are alive and add them up
            int Neighbours = (
            isActive(sf::Vector2f(c.x-1,c.y+1)) +
            isActive(sf::Vector2f(c.x,c.y+1))   +
            isActive(sf::Vector2f(c.x+1,c.y+1)) +
            isActive(sf::Vector2f(c.x-1,c.y))   +
            isActive(sf::Vector2f(c.x+1,c.y))   +
            isActive(sf::Vector2f(c.x-1,c.y-1)) +
            isActive(sf::Vector2f(c.x,c.y-1))   +
            isActive(sf::Vector2f(c.x+1,c.y-1)));
            
            if (isActive(c) == 1) // Checks to see if cell is alive and if it is returns 1
            {
                int s = (Neighbours == 2 || Neighbours == 3); // Returns 1 if there is 2 or 3 neighbours 0 if not

                if (s == 0)
                {
                    insertPotentialNear(c);     //Takes in nearby cell positions and cell dies
                }
                else
                {
                    NEXT_GRID.insert(c);        //Cell lives on
                }
            }
            else
            {
                int s = (Neighbours == 3);
                if (s == 1)
                {
                    NEXT_GRID.insert(c);        //Creates new cell if there is 3 neighbors
                    insertPotentialNear(c);
                }
            }                                   //Cell stays dead otherwise
        }
        
        for(auto x : CURRENT_GRID)              //itterates through the alive grid and draws them
        {
            cell.setPosition(x);
            cell.setFillColor(sf::Color::White);
            window.draw(cell);
            
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Game of Life");
    window.setFramerateLimit(10);
    GameOfLife game;
    bool pause = false;

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }
        window.clear();
        
        game.gameLoop(window);
        
        window.display();
    }
    return EXIT_SUCCESS;
}
