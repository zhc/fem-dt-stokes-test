#include "solverfactory.h"
#include <fstream>
//#define NDEBUG
#include <assert.h>


using namespace dolfin;

/*
- две настройки
    - псевдо-точное решение
    - тестируемое решение
- в ходе каждого решения
    - создать файл с временным слоем и временем решения
    - где-то оставить информацию про псевдоточное решение

проблемы:
- настройки псевдоточного и тестируемого решателей
- какие временные слои сохранять (самые грубые)
- как происходит интерполяция найденных функций
- формула для нахождения L2 нормы
- формат сохранения для визуализации графика погрешности
*/

int main(int argc, char *argv[]){
    Settings settings(argc, argv);
    info("Using parameters: " + settings.toString());
    SolverFactory factory(settings);

    BaseSolver *solverTest = factory.createTest();
    solverTest->solve();

    BaseSolver *solverEx = factory.createEx();
    solverEx->solve();

    solverTest->compare(solverEx);

    delete solverTest;
    delete solverEx;
}
