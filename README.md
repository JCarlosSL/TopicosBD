# Sistema de recomendación de filtro colaborativo basado en items y usuarios
Este sistema de recomendación esta escrito en el lenguaje **C++** , permite hacer prediciones con los algoritmos .

Filtro colaborativo basado en items:


- KNN

Filtro colaborativo basado en usuarios:

- SlopeOne
- Ajuste del coseno
## Pre-requisitos
Para poder compilar el proyecto , antes se  debe contar con la libreria  [Boost](https://www.boost.org/) . A continuacion se detalla la manera de instalar esta libreria en **Ubuntu** .
### Instalar Boost
```
sudo apt install libboost-all-dev

sudo apt install aptitude

aptitude search boost
```

## Compilar
 ```
 g++ -o m main.cpp -std=c++0x -lboost_serialization
 ./m
 ```
 ## Construido con 🛠️
 
 - C++
 
 ## Autores
 
 - Kevin Salazar Torres
 - Fernando Villanueva Sanchez
 - Jean Carlos Soncco Lupa
 - Raúl Edgar Quispe Totocayo
 - Jesus Lazo Quevedo
 
