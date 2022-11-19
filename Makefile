compile:
	g++ -I ./headers main.cpp -o cave -lsfml-graphics -lsfml-window -lsfml-system && echo "Build completed Successfully"