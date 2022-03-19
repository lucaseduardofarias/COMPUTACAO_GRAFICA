#include "../headers//system/System.h"
#include "../headers/Cubo.h"
#include <vector>
#include <stdio.h>

int main() {

    Cubo* cubo = new Cubo(800, 600, "Lista de Exercicio");
    
    System* system = new System(cubo);
    
    if (system->GLFWInit() != 0) {
        return EXIT_FAILURE;
    }
   
    system->run();

}
