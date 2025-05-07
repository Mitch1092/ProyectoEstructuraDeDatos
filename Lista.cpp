#include <iostream>
using namespace std;

class Nodo{
    public:
        int prioridad;
        string nombre;
        string descripcion;
        Nodo * sig;
        Nodo * ant;

        Nodo(int dato, string n, string d){
          nombre = n;
          descripcion = d;
          prioridad = dato;
          ant = nullptr;
          sig = nullptr;
        }


        Nodo * cabeza;
        Nodo * cola;

        void inicializar(){
          cabeza = nullptr;
          cola = nullptr;
        }

        bool empty(){
          return cabeza == nullptr;
        }

        void insertarfinal(int prioridad, string nombre, string descripcion){
          Nodo * nuevo = new Nodo(prioridad, nombre, descripcion);
          if (empty()){
            cabeza = nuevo;
            cola = nuevo;
          }else {
            cola->sig = nuevo;
            nuevo->ant = cola;
            cola = nuevo;
          }
        }

        int prioridadBaja() {
          if (empty()){
            return 0;
          }else{
            int baja = cola->prioridad;
            return baja;
          }
        }

        int prioridadAlta() {
          if (empty()){
            return 1000000000;
          }else{
            int alta = cabeza->prioridad;
            return alta;
          }
        }

        void insertar(int prioridad, string nombre, string descripcion){
          int baja = prioridadBaja();
          if(prioridad > baja){
            insertarfinal(prioridad, nombre, descripcion);
            return;
          }
          Nodo * nuevo = new Nodo(prioridad, nombre, descripcion);
          if(prioridad <= prioridadAlta()){
            nuevo -> sig = cabeza;
            if(cabeza != NULL){
              cabeza -> ant = nuevo;
              cabeza = nuevo;
            }else{
              cola = cabeza;
            }

            return;
          }
          Nodo * aux = cabeza;
          while (aux != NULL && prioridad <= aux -> sig -> prioridad){
            aux = aux->sig;
          }
          nuevo -> sig = aux -> sig;
          nuevo -> ant = aux;
          aux -> sig = nuevo;
          if(aux -> sig != NULL){
            nuevo -> sig -> ant = nuevo;
          }

        }

        void eliminarPosicion(int posicion){
          if(empty()){
            cout << "La lista esta vacia." << endl;
            return;
          }
          Nodo * aux = cabeza;
          if (posicion == 1){
            cabeza = cabeza -> sig;
            if (cabeza != NULL){
              cabeza -> ant = NULL;
            }else{
              cola=NULL;
            }
            delete aux;
            cout << "Se elimino la tarea en la posicion " << posicion << "." << endl;
            return;
          }
          int contador = 1;
          while (aux != NULL && contador < posicion){
            aux = aux -> sig;
            ++contador;
          }
          if (aux==NULL){
            cout << "La posicion esta fuera de rango" << endl;
            return;
          }
          if(aux -> sig != NULL){
            aux -> sig -> ant = aux -> ant;
          }
          if(aux -> ant != NULL){
            aux -> ant -> sig = aux -> sig;
          }
          if(aux == cola){
            cola = cola -> ant;
          }
          delete aux;
          cout << "Se elimino el dato en la posicion " << posicion << "." << endl;
        }

        void mostrar() {
          if(empty()){
            cout << "La lista esta vacia." << endl;
            return;
          }
          int cont = 1;
          Nodo * aux = cabeza;
          while (aux != NULL){
            cout << cont << ".  Prioridad: " << aux -> prioridad << "  Tarea:  " << aux -> nombre << ".  " << aux -> descripcion << endl;
            aux = aux -> sig;
            ++cont;
          }
          cout << endl;
        }

        void editar(int posicion, int prioridad) {
          string nombre, descripcion;
          if(empty()){
            cout << "La lista esta vacia." << endl;
            return;
          }
          Nodo * aux = cabeza;
          if (posicion == 1){
            nombre = cabeza -> nombre;
            descripcion = cabeza -> descripcion;
            cabeza = cabeza -> sig;
            if (cabeza != NULL){
              cabeza -> ant = NULL;
            }else{
              cola=NULL;
            }
            delete aux;
            return;
          }
          int contador = 1;
          while (aux != NULL && contador < posicion){
            aux = aux -> sig;
            ++contador;
          }
          if (aux==NULL){
            cout << "La tarea no existe" << endl;
            return;
          }
          nombre = aux -> nombre;
          descripcion = aux -> descripcion;
          if(aux -> sig != NULL){
            aux -> sig -> ant = aux -> ant;
          }
          if(aux -> ant != NULL){
            aux -> ant -> sig = aux -> sig;
          }
          if(aux == cola){
            cola = cola -> ant;
          }
          delete aux;
          insertar(prioridad,nombre,descripcion);
        }

        int numeroNodos(){
          if (empty()){
            return 0;
          }else{
            Nodo * aux = cabeza;
            int contador = 0;
            while (aux != NULL){
              contador++;
              aux = aux->sig;
            }
            return contador;
          }
        }

        void destruir(){
          Nodo * aux = cabeza;
          Nodo * sig;
          while(aux!=NULL){
            sig = aux ->sig;
            delete aux;
            aux = sig;
          }
        }
};

