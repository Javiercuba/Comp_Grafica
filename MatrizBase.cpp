#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef float f4d1[4];
class MatrizBase
{

public:
    void setMatrizBase(float Matriz_Base[4][4], int Tipo_tranformacao)
    {
        if (Tipo_tranformacao = 20)
           // setBezier(Matriz_Base);
        if (Tipo_tranformacao = 21)
            setBspline(Matriz_Base);
        if (Tipo_tranformacao = 22)
            setCatMullrom(Matriz_Base);
    }
    float setBezier(f4d1 Matriz_Base[4])
    {

        Matriz_Base[0][0] = -1.0f;
        Matriz_Base[0][1] = 3.0f;
        Matriz_Base[0][2] = -3.0f;
        Matriz_Base[0][3] = 1.0f;
        Matriz_Base[1][0] = 3.0f;
        Matriz_Base[1][1] = -6.0f;
        Matriz_Base[1][2] = 3.0f;
        Matriz_Base[1][3] = 0.0f;
        Matriz_Base[2][0] = -3.0f;
        Matriz_Base[2][1] = 3.0f;
        Matriz_Base[2][2] = 0.0f;
        Matriz_Base[2][3] = 0.0f;
        Matriz_Base[3][0] = 1.0f;
        Matriz_Base[3][1] = 0.0f;
        Matriz_Base[3][2] = 0.0f;
        Matriz_Base[3][3] = 0.0f;
        return Matriz_Base[4][4];
    }
    float setBspline(float Matriz_Base[4][4])
    {
        Matriz_Base[0][0] = -1.0f / 6.0;
        Matriz_Base[0][1] = 3.0f / 6.0;
        Matriz_Base[0][2] = -3.0f / 6.0;
        Matriz_Base[0][3] = 1.0f / 6.0;
        Matriz_Base[1][0] = 3.0f / 6.0;
        Matriz_Base[1][1] = -6.0f / 6.0;
        Matriz_Base[1][2] = 3.0f / 6.0;
        Matriz_Base[1][3] = 0.0f;
        Matriz_Base[2][0] = -3.0f / 6.0;
        Matriz_Base[2][1] = 0.0f / 6.0;
        Matriz_Base[2][2] = 3.0f / 6.0;
        Matriz_Base[2][3] = 0.0f;
        Matriz_Base[3][0] = 1.0f / 6.0;
        Matriz_Base[3][1] = 4.0f / 6.0;
        Matriz_Base[3][2] = 1.0f / 6.0;
        Matriz_Base[3][3] = 0.0;
        return Matriz_Base[4][4];
    }
    float setCatMullrom(float Matriz_Base[4][4])
    {
        return Matriz_Base[0][0] = -1.0f / 2.0;
        Matriz_Base[0][1] = 3.0f / 2.0;
        Matriz_Base[0][2] = -3.0f / 2.0;
        Matriz_Base[0][3] = 1.0f / 2.0;
        Matriz_Base[1][0] = 2.0f / 2.0;
        Matriz_Base[1][1] = -5.0f / 2.0;
        Matriz_Base[1][2] = 4.0f / 2.0;
        Matriz_Base[1][3] = -1.0f / 2.0;
        Matriz_Base[2][0] = -1.0f / 2.0;
        Matriz_Base[2][1] = 0.0f / 2.0;
        Matriz_Base[2][2] = 1.0f / 2.0;
        Matriz_Base[2][3] = 0.0f / 2.0;
        Matriz_Base[3][0] = 0.0f / 2.0;
        Matriz_Base[3][1] = 2.0f / 2.0;
        Matriz_Base[3][2] = 0.0f / 2.0;
        Matriz_Base[3][3] = 0.0f / 2.0;
        return Matriz_Base[4][4];
    }
};
