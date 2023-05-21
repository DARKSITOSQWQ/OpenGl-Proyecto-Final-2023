
#include "glm.h"

//Carga Museo


    GLMmodel* piso = NULL;

    GLMmodel* arbol_tronco = NULL;
    GLMmodel* arbol_hojas = NULL;




 void CargaPiso(){

    piso = glmReadOBJ("modelos/escenario/piso/piso.obj");

 };

 void CargaArbol(){

    arbol_tronco = glmReadOBJ("modelos/escenario/arbol/tronco/tronco.obj");
    arbol_hojas = glmReadOBJ("modelos/escenario/arbol/hojas/hojas.obj");

 };
