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

const Color sweepColor = Color(28,35,49,255);
const Color blockColor = Color(24,100,171,255);

void gridInitialize(){
    //std::random
    random_device rd;
    mt19937 mt(rd());
    //seed_seq ssq{rd()};
    //default_random_engine eng{ssq};
    uniform_int_distribution<int> dist(0,255);

    for(int i=0;i<level;i++){
        vector<bool> arr;
        for(int j=0;j<level;j++) arr.push_back(dist(mt)%2 == 0);
        Grid.push_back(arr);
    }
}

// Just for Visualization
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

// Just for Visualization
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
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2),sweepColor),
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH),sweepColor),
                    Vertex(Vector2f(j*CELLWIDTH,(i+1)*CELLWIDTH),sweepColor)
                };
                texture.draw(points,3,sf::Triangles);
                break;
            };
            case 2:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH),sweepColor),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2),sweepColor),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(i+1)*CELLWIDTH),sweepColor)
                };
                texture.draw(points,3,sf::Triangles);
                break;
            };
            case 3:{
                RectangleShape rect(Vector2f(CELLWIDTH,CELLWIDTH/2));
                rect.setFillColor(sweepColor);
                rect.setPosition(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2));
                texture.draw(rect);
                break;
            };
            case 4:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH),sweepColor),
                    Vertex(Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2),sweepColor),
                    Vertex(Vector2f((j+1)*CELLWIDTH,i*CELLWIDTH),sweepColor)
                };
                texture.draw(points,3,sf::Triangles);
                break;
            };
            case 5:{
                ConvexShape shape;
                shape.setFillColor(sweepColor);
                shape.setPointCount(6);
                shape.setPoint(0,Vector2f(j*CELLWIDTH,(i+1)*CELLWIDTH));
                shape.setPoint(1,Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2));
                shape.setPoint(2,Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH));
                shape.setPoint(3,Vector2f((j+1)*CELLWIDTH,i*CELLWIDTH));
                shape.setPoint(4,Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2));
                shape.setPoint(5,Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH));
                texture.draw(shape);
                break;
            };
            case 6:{
                RectangleShape rect(Vector2f(CELLWIDTH/2,CELLWIDTH));
                rect.setFillColor(sweepColor);
                rect.setPosition(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH));
                texture.draw(rect);
                break;
            };
            case 7:{
                ConvexShape shape;
                shape.setFillColor(sweepColor);
                shape.setPointCount(5);
                shape.setPoint(0,Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH));
                shape.setPoint(1,Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2));
                shape.setPoint(2,Vector2f(j*CELLWIDTH,(i+1)*CELLWIDTH));
                shape.setPoint(3,Vector2f((j+1)*CELLWIDTH,(i+1)*CELLWIDTH));
                shape.setPoint(4,Vector2f((j+1)*CELLWIDTH,i*CELLWIDTH));
                texture.draw(shape);
                break;
            };
            case 8:{
                Vertex points[] = {
                    Vertex(Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH),sweepColor),
                    Vertex(Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2),sweepColor),
                     Vertex(Vector2f(j*CELLWIDTH,i*CELLWIDTH),sweepColor)
                };
                texture.draw(points,3,sf::Triangles);
                break;
            };
            case 9:{
                RectangleShape rect(Vector2f(CELLWIDTH/2,CELLWIDTH));
                rect.setFillColor(sweepColor);
                rect.setPosition(Vector2f(j*CELLWIDTH,i*CELLWIDTH));
                texture.draw(rect);
                break;
            };
            case 10:{
                ConvexShape shape;
                shape.setFillColor(sweepColor);
                shape.setPointCount(6);
                shape.setPoint(0,Vector2f(j*CELLWIDTH,i*CELLWIDTH));
                shape.setPoint(1,Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH));
                shape.setPoint(2,Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2));
                shape.setPoint(3,Vector2f((j+1)*CELLWIDTH,(i+1)*CELLWIDTH));
                shape.setPoint(4,Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH));
                shape.setPoint(5,Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2));        
                texture.draw(shape);
                break;
            };
            case 11:{
                ConvexShape shape;
                shape.setFillColor(sweepColor);
                shape.setPointCount(5);
                shape.setPoint(0,Vector2f(j*CELLWIDTH,i*CELLWIDTH));
                shape.setPoint(1,Vector2f((2*j+1)*CELLWIDTH/2,i*CELLWIDTH));
                shape.setPoint(2,Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2));
                shape.setPoint(3,Vector2f((j+1)*CELLWIDTH,(i+1)*CELLWIDTH));
                shape.setPoint(4,Vector2f(j*CELLWIDTH,(i+1)*CELLWIDTH));
                texture.draw(shape);
                break;
            };
            case 12:{
                RectangleShape rect(Vector2f(CELLWIDTH,CELLWIDTH/2));
                rect.setFillColor(sweepColor);
                rect.setPosition(Vector2f(j*CELLWIDTH,i*CELLWIDTH));
                texture.draw(rect);
                break;
            };
            case 13:{
                ConvexShape shape;
                shape.setFillColor(sweepColor);
                shape.setPointCount(5);
                shape.setPoint(0,Vector2f(j*CELLWIDTH,i*CELLWIDTH));
                shape.setPoint(1,Vector2f((j+1)*CELLWIDTH,i*CELLWIDTH));
                shape.setPoint(2,Vector2f((j+1)*CELLWIDTH,(2*i+1)*CELLWIDTH/2));
                shape.setPoint(3,Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH));
                shape.setPoint(4,Vector2f(j*CELLWIDTH,(i+1)*CELLWIDTH));
                texture.draw(shape);
                break;
            };
            case 14:{
                ConvexShape shape;
                shape.setFillColor(sweepColor);
                shape.setPointCount(5);
                shape.setPoint(0,Vector2f(j*CELLWIDTH,i*CELLWIDTH));
                shape.setPoint(1,Vector2f((j+1)*CELLWIDTH,i*CELLWIDTH));
                shape.setPoint(2,Vector2f((j+1)*CELLWIDTH,(i+1)*CELLWIDTH));
                shape.setPoint(3,Vector2f((2*j+1)*CELLWIDTH/2,(i+1)*CELLWIDTH));
                shape.setPoint(4,Vector2f(j*CELLWIDTH,(2*i+1)*CELLWIDTH/2));
                texture.draw(shape);
                break;
            };
            case 15:{
                RectangleShape rect(Vector2f(CELLWIDTH,CELLWIDTH));
                rect.setFillColor(sweepColor);
                rect.setPosition(Vector2f(j*CELLWIDTH,i*CELLWIDTH));
                texture.draw(rect);
                break;
            }
            default:
                break;
            }
        }
    }
}

#endif //CELL