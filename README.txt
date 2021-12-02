Para la compilación de este proyecto se ejecuta el siguiente comando :

	g++ -pthread -I. practica4_main.cpp -std=c++11 -o practica4
	
Esto generará un ejecutable llamado practica4, se deberá ejecutar de forma
similar a la siguiente:

	./practica4 [height] [width] [raysPerPixel] [textura_fondo] [textura_suelo] ...
	
	Ejemplo: ./practica4 2000 2000 150 xokas bricks bricks bricks pepe
	
			