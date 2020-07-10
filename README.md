# Sistema de recomendación basado en filtro colaborativo basado en items y usuarios
Este sistema de recomendación esta escrito en el lenguaje **C++** , permite hacer prediccionnes con los algoritmos .

Filtro colaborativo basado en items:


- KNN

Filtro colaborativo basado en usuarios:


- Slopone
- Ajuste del coseno
## Pre-requisitos
Para poder compilar el proyecto , antes  debe contar con la libreria  [Boost](https://www.boost.org/) . A continuacion se detalla la manera de instalar esta libreria en **Ubuntu** .
## Instalar Boost
```
sudo apt install libboost-all-dev

sudo apt install aptitude

aptitude search boost
```

## Compilar
 ```g++ -o m main.cpp -std=c++0x -lboost_serialization```
