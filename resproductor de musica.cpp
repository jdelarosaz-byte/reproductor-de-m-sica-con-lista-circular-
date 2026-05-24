#include <iostream>
#include <string>
#include <limits>
#include <conio.h>   
#include <windows.h> 

using namespace std;

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define TECLA_ENTER 13

void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

class Alumno {
private:
    string nombres;
    string apellidos;
    string carnet;
    string email;
    string telefono;
    double notas[5];

public:
    void pedirDatos() {
        cambiarColor(11);
        cout << "\n--- Ingrese Datos del Alumno ---\n";
        cambiarColor(7);
        cout << "Nombres: ";
        getline(cin, nombres);
        cout << "Apellidos: ";
        getline(cin, apellidos);
        cout << "Carnet: ";
        getline(cin, carnet);
        cout << "Email: ";
        getline(cin, email);
        cout << "Telefono: ";
        getline(cin, telefono);

        for (int i = 0; i < 5; i++) {
            while (true) {
                cout << "  Ingrese nota " << (i + 1) << " (0-10): ";
                if (cin >> notas[i] && notas[i] >= 0 && notas[i] <= 10) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cambiarColor(12);
                cout << "  [Error] La nota debe estar entre 0 y 10 puntos. Intente de nuevo.\n";
                cambiarColor(7);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    double calcularPromedio() const {
        double suma = 0;
        for (int i = 0; i < 5; i++) {
            suma += notas[i];
        }
        return suma / 5.0;
    }

    void mostrarInformacion() const {
        cout << "---------------------------------------------------------\n";
        cout << "Carnet:    " << carnet << "\n";
        cout << "Alumno:    " << nombres << " " << apellidos << "\n";
        cout << "Email:     " << email << "\n";
        cout << "Telefono:  " << telefono << "\n";
        cout << "Notas:     [";
        for (int i = 0; i < 5; i++) {
            cout << notas[i] << (i < 4 ? ", " : "");
        }
        cout << "]\n";
        cambiarColor(10);
        cout << "Promedio:  " << calcularPromedio() << "\n";
        cambiarColor(7);
    }
};

struct Nodo {
    Alumno objetoAlumno;
    Nodo* siguiente;
};

int crearMenuInteractivo(string titulo, string opciones[], int totalOpciones) {
    int seleccionada = 0;
    int tecla;

    while (true) {
        system("cls");
        cambiarColor(14);
        cout << "=========================================================\n";
        cout << "   " << titulo << "\n";
        cout << "=========================================================\n";
        cambiarColor(7);

        for (int i = 0; i < totalOpciones; i++) {
            if (i == seleccionada) {
                cambiarColor(240);
                cout << " -> [ " << opciones[i] << " ] " << endl;
                cambiarColor(7);
            }
            else {
                cout << "    " << opciones[i] << endl;
            }
        }
        cout << "=========================================================\n";

        tecla = _getch();

        if (tecla == 224) { // Detecta si se presiono una flecha del teclado
            tecla = _getch();
            if (tecla == TECLA_ARRIBA) {
                seleccionada = (seleccionada - 1 + totalOpciones) % totalOpciones;
            }
            else if (tecla == TECLA_ABAJO) {
                seleccionada = (seleccionada + 1) % totalOpciones;
            }
        }
        else if (tecla == TECLA_ENTER) { // Detecta si se presiono la tecla Enter
            return seleccionada;
        }
    }
}

int main() {
    Nodo* inicio = nullptr;
    Nodo* ultimo = nullptr;

    string opcionesMenu[] = {
        "Registrar Nuevo Alumno",
        "Mostrar Reporte de Alumnos & Promedios",
        "Salir del Sistema"
    };
    int totalOpciones = 3;
    bool ejecutar = true;

    while (ejecutar) {
        int seleccion = crearMenuInteractivo("SISTEMA ACADEMICO (Navega con flechas arriba/abajo)", opcionesMenu, totalOpciones);

        switch (seleccion) {
        case 0: {
            system("cls");
            Nodo* nuevoNodo = new Nodo();
            nuevoNodo->objetoAlumno.pedirDatos();
            nuevoNodo->siguiente = nullptr;

            if (inicio == nullptr) {
                inicio = nuevoNodo;
                ultimo = nuevoNodo;
            }
            else {
                ultimo->siguiente = nuevoNodo;
                ultimo = nuevoNodo;
            }

            cambiarColor(10);
            cout << "\n[Exito] Alumno registrado localmente.\n";
            cambiarColor(7);
            cout << "Presione cualquier tecla para regresar al menu...";
            _getch();
            break;
        }
        case 1: {
            system("cls");
            cambiarColor(11);
            cout << "=========================================================\n";