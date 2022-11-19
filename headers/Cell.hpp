#ifndef CELL
#define CELL

#define CELLWIDTH 20
#define level 30
#define ptRadius 3
#define bin_to_dec(a,b,c,d) a*8+b*4+c*2+d

#include <SFML/Graphics.hpp>
#include <random>
#include <sstream>
using namespace sf;
using namespace std;

vector<vector<bool>> Grid;

void gridInitialize(){
    //std::random
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0,256);

    for(int i=0;i<level;i++){
        vector<bool> arr;
        for(int j=0;j<level;j++) arr.push_back(dist(mt)%2 == 0);
        Grid.push_back(arr);
    }
}

// Jusr for Visualization
void initializeGrid(RenderTexture& texture){
    for(int i=0;i<level-1;i++){
        Vertex points1[] = {
            Vertex(Vector2f(i*CELLWIDTH,0)),
            Vertex(Vector2f(i*CELLWIDTH,CELLWIDTH*level))
        };
        Vertex points2[] = {
            Vertex(Vector2f(0,i*CELLWIDTH)),
            Vertex(Vector2f(CELLWIDTH*level,i*CELLWIDTH))
        };
        texture.draw(points1,2,sf::Lines);
        texture.draw(points2,2,sf::Lines);
    }
}

void drawPoints(RenderTexture& texture){
    for(int i=0;i<level;i++){
        for(int j=0;j<level;j++){
            CircleShape c(ptRadius);
            c.setPosition(Vector2f(i*CELLWIDTH-ptRadius,j*CELLWIDTH-ptRadius));
            c.setFillColor(Grid[i][j]?Color(0,0,0,255):Color(255,255,255,255));
            texture.draw(c); 
        }
    }
}

void drawCave(RenderTexture& texture){
    for(int i=0;i<level-1;i++){
        for(int j=0;j<level-1;j++){
            uint32_t state = bin_to_dec(
                Grid[j][i], Grid[j+1][i], Grid[j+1][i+1], Grid[j][i+1]
            );
            switch (state){
            case 1:{
                Vertex points[] = {
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 2:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH)),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 3:{
                Vertex points[] = {
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 4:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH)),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 5:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH)),
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH))
                };
                texture.draw(points,4,sf::Lines);
                break;
            };
            case 6:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH)),
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 7:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH)),
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 8:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH)),
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 9:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH)),
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 10:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH)),
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH))
                };
                texture.draw(points,4,sf::Lines);
                break;
            };
            case 11:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH)),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 12:{
                Vertex points[] = {
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 13:{
                Vertex points[] = {
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            case 14:{
                Vertex points[] = {
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2)),
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH))
                };
                texture.draw(points,2,sf::Lines);
                break;
            };
            default:
                break;
            }
        }
    }
}

#endif //CELL