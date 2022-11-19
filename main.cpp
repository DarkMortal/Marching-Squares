#include <iostream>
#include "./headers/Cell.hpp"
using namespace std;

int main(){
    gridInitialize();
    try{
        Event evt;
        RenderWindow window(VideoMode((level-1)*CELLWIDTH,(level-1)*CELLWIDTH),"Procedural Cave Generator",Style::Close);
        RenderTexture texture; 
        texture.create((level-1)*CELLWIDTH,(level-1)*CELLWIDTH);
        texture.clear(Color(24,100,171,255));
        //initializeGrid(texture);
        //drawPoints(texture);
        drawCave(texture);
        texture.display();
        window.draw(Sprite(texture.getTexture()));
        window.display();
        while(window.isOpen()){
            while(window.pollEvent(evt)){
                if(evt.type == evt.Closed){
                    window.close();
                    cout<<"Window Closed"<<endl;
                    return EXIT_SUCCESS;
                }
            }
            // Game Code goes here
        }
    }
    catch(exception exc){
        cerr<<exc.what()<<endl;
        return EXIT_FAILURE;
    }
    return 0;
}