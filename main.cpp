#include <iostream>
#include <unistd.h>
#include "./headers/Cell.hpp"
using namespace std;

int main(){
    gridInitialize();
    try{
        Event evt;
        RenderWindow window(VideoMode((level-1)*CELLWIDTH,(level-1)*CELLWIDTH),"Procedural Cave Generator",Style::Close);
        RenderTexture texture; 
        texture.create((level-1)*CELLWIDTH,(level-1)*CELLWIDTH);
        texture.clear(blockColor);
        //(texture);
        //drawPoints(texture);
        drawCave(texture);
        texture.display();
        window.draw(Sprite(texture.getTexture()));
        window.display();
        while(window.isOpen()){
            while(window.pollEvent(evt)){
                if(evt.type == Event::Closed){
                    window.close();
                    cout<<"Window Closed"<<endl;
                    return EXIT_SUCCESS;
                }
                if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::S){
                    Image img = texture.getTexture().copyToImage();
                    img.saveToFile("./Cave.png");
                    cout<<"Image exported Successfully"<<endl;
                }
            }
            // Game Code goes here
            texture.clear(blockColor);
            Grid.clear();
            gridInitialize();
            drawCave(texture);
            usleep(50000);
            texture.display();
            window.draw(Sprite(texture.getTexture()));
            window.display();        
        }
    }
    catch(exception exc){
        cerr<<exc.what()<<endl;
        return EXIT_FAILURE;
    }
    return 0;
}