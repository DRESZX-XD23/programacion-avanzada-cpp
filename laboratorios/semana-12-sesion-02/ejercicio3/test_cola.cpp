#include <gtest/gtest.h>
#include "cola_impresion.h"

TEST(ColaDeImpresion, VeinticincoPaginasTomanTresMinutos){
    EXPECT_EQ(minutosDeImpresion(25),3);
}


TEST(ColaDeImpresion, TrabajoDe45){
    ColaDeImpresion cola;
    cola.agregar(45);
    cola.dividirGrandes();
    EXPECT_EQ(cola.cantidad(),3);
    EXPECT_EQ(cola.paginasDe(0),20);
    EXPECT_EQ(cola.paginasDe(1),20);
    EXPECT_EQ(cola.paginasDe(2),5);

}