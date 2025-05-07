#include <fstream>
#include <iostream>
#include "json.hpp"
#include "Lista.cpp"
using namespace std;
using json = nlohmann::json;

int leerInt() {
    int n;
    cin >> n;
    while (cin.fail() || n < 0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valor invalido. Intente de nuevo: " ;
        cin >> n;
    }
    return n;
}
void mostrarTareas(Nodo a){
    a.mostrar();
}

Nodo eliminarTarea(Nodo a){
    a.mostrar();
    int posicion;
    cout << "Selecciona la tarea a eliminar o '0' para regresar: ";
    cin >> posicion;
    while (cin.fail() || posicion > a.numeroNodos() || posicion < 0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valor invalido. Intente de nuevo: " ;
        cin >> posicion;
    }
    if (posicion == 0) {
        return a;
    }
    a.eliminarPosicion(posicion);
    return a;
}

Nodo agregarTarea(Nodo a){
    int prioridad;
    string nombre, descripcion;
    cout << "Nombre de la tarea: ";
    cin.ignore();
    getline(cin, nombre, '\n');
    cout << "Prioridad: ";
    cin >> prioridad;
    while (cin.fail() || prioridad < 0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valor invalido. Intente de nuevo: " ;
        cin >> prioridad;
    }
    cout << "Descripcion: ";
    cin.ignore();
    getline(cin, descripcion, '\n');
    a.insertar(prioridad,nombre,descripcion);
    return a;
}

Nodo editarTarea(Nodo a) {
    a.mostrar();
    int posicion, prioridad;
    cout << "Selecciona la tarea a modificar o '0' para regresar: ";
    cin >> posicion;
    while (cin.fail() || posicion > a.numeroNodos() || posicion < 0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valor invalido. Intente de nuevo: " ;
        cin >> posicion;
    }
    if (posicion == 0) {
        return a;
    }
    cout << "Nueva prioridad: ";
    cin >> prioridad;
    while (cin.fail() || prioridad < 0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Valor invalido. Intente de nuevo: " ;
        cin >> prioridad;
    }
    a.editar(posicion, prioridad);
    return a;
}

void guardarEnArchivo(Nodo a){
    ofstream file("Data.json");

    if (a.empty()) {
        file.close();
        cout << "La lista esta vacia, no hat nada para exportar" << endl;
        return;
    }

    json tareas = json::array();
    Nodo *aux = a.cabeza;
    while (aux != NULL) {
        json tarea = {
            {"prioridad",aux -> prioridad},
            {"nombre", aux -> nombre},
            {"descripcion", aux -> descripcion},
        };
        tareas.push_back(tarea);
        aux = aux -> sig;
    }
    file << tareas.dump(3) << endl;
    file.close();
    cout << "Se exportaron las tareas";
}

Nodo cargarDesdeArchivo(Nodo a){
    ifstream file;
    file.open("Data.json");
    json tareas;
    file >> tareas;
    int b = tareas.size();
    file.close();
    if (b == 0) {
        cout << "No hay nada en memoria" << endl;
        return a;
    }

    for (const auto& i : tareas) {
        int prioridad = i["prioridad"].get<int>();
        string nombre = i["nombre"].get<string>();
        string descripcion = i["descripcion"].get<string>();
        a.insertar(prioridad,nombre,descripcion);
    }
    cout << "Se importaron las tareas." << endl;
    return a;
}


void menu(Nodo nodo){
    int a;
    do {
        cout << "\nSelecciona una opcion:" << endl;
        cout << "1. Mostrar lista de tareas" << endl;
        cout << "2. Agregar tarea" << endl;
        cout << "3. Cambiar prioridad de tarea" << endl;
        cout << "4. Eliminar tarea" << endl;
        cout << "5. Importar tareas" << endl;
        cout << "6. Exportar tareas" << endl;
        cout << "7. Salir" << endl;
        cout << "Opcion:  ";
        cin >> a;
        while (cin.fail() || a > 7 || a < 1){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Valor invalido. Intente de nuevo: " ;
            cin >> a;
        }
        switch(a){
            case 1:
                mostrarTareas(nodo);
                break;
            case 2:
                nodo = agregarTarea(nodo);
                break;
            case 3:
                nodo = editarTarea(nodo);
                break;
            case 4:
                nodo = eliminarTarea(nodo);
                break;
            case 5:
                nodo = cargarDesdeArchivo(nodo);
                break;
            case 6:
                guardarEnArchivo(nodo);
                break;
            case 7:
                cout << "Cerrando el sistema." << endl;
                return;
            default:
                cout << "Valor invalido." << endl;
                break;
        }
    }while (a != 7);
}

int main() {
    Nodo nodo(1,"xd","lol");

    nodo.inicializar();
    menu(nodo);
    nodo.destruir();

    return 0;
}
