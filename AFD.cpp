#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

struct alfabeto_E { //nodo para alfabeto de entrada
    char simbolo;
    alfabeto_E *sig;
};

alfabeto_E *inicio_e = NULL;
alfabeto_E *fin_e = NULL;
alfabeto_E *nuevo_e = NULL;
alfabeto_E *ptr_e = NULL;

struct alfabeto_S { //nodo para alfabeto de salida
    char simbolo;
    alfabeto_S *sig;
};

alfabeto_S *inicio_s = NULL;
alfabeto_S *fin_s = NULL;
alfabeto_S *nuevo_s = NULL;
alfabeto_S *ptr_s = NULL;

void Header(); //Encabezado con datos que siempre se deben mostrar "estático"
void Alfabeto_E(); //Ingresar alfabeto de entrada
void Alfabeto_S(); //Ingresar alfabeto de salida
void Estados(); //Conjunto de Estados Posibles

int total_afd = 0;
int afd_trad = 0;
int afd_validos = 0;

int main() {
    int opc;
    do {
        cout << "\nIndique el tipo de Autómata Finito Determinista a registrar: " << endl;
        cout << "1. Traducción\n" << "2. Validación\n" << "3. Salir\n" << "Opción: ";
        cin>>opc;
        if (cin.fail()) {
            cout << "---Opción inválida---\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n'); //Para vaciar el buffer y pida de nuevo un cin
        } else {
            switch (opc) {
                case 1: Alfabeto_E();
                    cout << "\nAlfabeto de entrada guardado\n" << endl;
                    Alfabeto_S();
                    cout << "\nAlfabeto de salida guardado\n" << endl;
                    Estados();
                    break;
                case 2:
                    break;
                case 3: cout << endl;
                    cout << "El total de AFDs Ingresados fue de: " << total_afd << endl;
                    cout << "El total de AFDs Traducidos fue de: " << afd_trad << endl;
                    cout << "El total de AFDs Válidos es de: " << afd_validos << endl;
                    cout << "El total de AFD's Inválidos es de: " << total_afd - afd_validos << endl;
                    cout << "\nGracias!... Cerrando sistema" << endl;
                    break;
                default: cout << "---Opción inválida---\n" << endl;
            }
        }
    } while (opc != 3);

    return 0;
}

void Header() {

}

void Alfabeto_E() {
    if (inicio_e != NULL) {
        ptr_e = inicio_e;
        while (ptr_e->sig != NULL) {
            ptr_e = inicio_e;
            inicio_e = ptr_e->sig;
            delete(ptr_e);
        }
        cout << "ya se borró" << endl;
        delete(inicio_e);
        inicio_e = NULL;
        fin_e = NULL;
        ptr_e = NULL;
        nuevo_e = NULL;
    }
    string simb_t;
    int i = 1;
    bool check;
    cout << "Ingrese el alfabeto de entrada (seleccione '*' para terminar: " << endl;
    while (true) {
        cout << i << ": ";
        cin>>simb_t;
        if (simb_t.length() != 1) //Verificar la longitud de caracteres ingresados, máximo 1
            cout << "Solamente puede ingresar un símbolo a la vez\n" << endl;
        else {
            if (simb_t == "*") {
                if (inicio_e == NULL)
                    cout << "El alfabeto de entrada NO puede estar vacío\n";
                else
                    break;
            }
            char simb = simb_t[0]; //Pasar el string a un char
            int ascii_simb = (int) simb; //regresa el valor ingresado en codigo ASCII
            cout << "ascii: " << ascii_simb << endl;
            if (ascii_simb >= 48 && ascii_simb <= 57 || ascii_simb >= 65 && ascii_simb <= 90 || ascii_simb >= 97 && ascii_simb <= 122 || ascii_simb == -15 || ascii_simb == -47) {
                //Para que solo admita letras en español mayúsculas, minúsculas y números del 0 al 9
                cout << "es bueno" << endl;
                if (inicio_e == NULL) {
                    nuevo_e = new(alfabeto_E);
                    nuevo_e->simbolo = simb;
                    inicio_e = nuevo_e;
                    fin_e = nuevo_e;
                    fin_e->sig = NULL;
                    cout << "no había nafi" << endl;
                    ++i;
                } else {
                    check = true;
                    ptr_e = inicio_e;
                    while (ptr_e != NULL) {
                        if (ptr_e->simbolo == simb) {
                            check = false;
                            break;
                        }
                        ptr_e = ptr_e->sig;
                    }
                    if (check == false)
                        cout << "No se pueden ingresar simbolos repetidos\n" << endl;
                    else {
                        nuevo_e = new(alfabeto_E);
                        nuevo_e->simbolo = simb;
                        fin_e->sig = nuevo_e;
                        fin_e = nuevo_e;
                        fin_e->sig = NULL;
                        cout << "si había algo" << endl;
                        ++i;
                    }
                }
            } else
                cout << "El símbolo ingresado no es válido" << endl;
        }
    }
    ptr_e = inicio_e;
    while (ptr_e != NULL) {
        cout << "El dato es: " << ptr_e->simbolo << endl;
        ptr_e = ptr_e->sig;
    }
}

void Alfabeto_S() {
    if (inicio_s != NULL) {
        ptr_s = inicio_s;
        while (ptr_s->sig != NULL) {
            ptr_s = inicio_s;
            inicio_s = ptr_s->sig;
            delete(ptr_s);
        }
        cout << "ya se borró" << endl;
        delete(inicio_s);
        inicio_s = NULL;
        fin_s = NULL;
        ptr_s = NULL;
        nuevo_s = NULL;
    }
    string simb_t;
    int i = 1;
    bool check;
    cout << "Ingrese el alfabeto de salida (seleccione '*' para terminar: " << endl;
    while (true) {
        cout << i << ": ";
        cin>>simb_t;
        if (simb_t.length() != 1) //Verificar la longitud de caracteres ingresados, máximo 1
            cout << "Solamente puede ingresar un símbolo a la vez\n" << endl;
        else {
            if (simb_t == "*") {
                if (inicio_s == NULL)
                    cout << "El alfabeto de salida NO puede estar vacío\n";
                else
                    break;
            }
            char simb = simb_t[0]; //Pasar el string a un char
            int ascii_simb = (int) simb; //regresa el valor ingresado en codigo ASCII
            cout << "ascii: " << ascii_simb << endl;
            if (ascii_simb >= 48 && ascii_simb <= 57 || ascii_simb >= 65 && ascii_simb <= 90 || ascii_simb >= 97 && ascii_simb <= 122 || ascii_simb == -15 || ascii_simb == -47) {
                //Para que solo admita letras en español mayúsculas, minúsculas y números del 0 al 9
                cout << "es bueno" << endl;
                if (inicio_s == NULL) {
                    nuevo_s = new(alfabeto_S);
                    nuevo_s->simbolo = simb;
                    inicio_s = nuevo_s;
                    fin_s = nuevo_s;
                    fin_s->sig = NULL;
                    cout << "no había nafi" << endl;
                    ++i;
                } else {
                    check = true;
                    ptr_s = inicio_s;
                    while (ptr_s != NULL) {
                        if (ptr_s->simbolo == simb) {
                            check = false;
                            break;
                        }
                        ptr_s = ptr_s->sig;
                    }
                    if (check == false)
                        cout << "No se pueden ingresar simbolos repetidos\n" << endl;
                    else {
                        nuevo_s = new(alfabeto_S);
                        nuevo_s->simbolo = simb;
                        fin_s->sig = nuevo_s;
                        fin_s = nuevo_s;
                        fin_s->sig = NULL;
                        cout << "si había algo" << endl;
                        ++i;
                    }
                }
            } else
                cout << "El símbolo ingresado no es válido" << endl;
        }
    }
    ptr_s = inicio_s;
    while (ptr_s != NULL) {
        cout << "El dato es: " << ptr_s->simbolo << endl;
        ptr_s = ptr_s->sig;
    }

}

void Estados() {
    string estado;
    int i = 1;
    bool check;          //verificar el estado ya se registró
    bool v_estado;      //verificar que el estado sea válido
    cout << "Ingrese el conjunto de estados posibles 'Q' (seleccione '*' para terminar: " << endl;
    while (true) {
        cout << i << ": ";
        cin>>estado;
        if (estado.length() > 15) //Verificar la longitud de caracteres ingresados, máximo 15
            cout << "La longitud máxima permitida de la palabra es de 15 caracteres\n" << endl;
        else {
            if (estado == "*") {
                if (inicio_e == NULL)
                    cout << "El conjunto de estados posibles NO puede estar vacío\n";
                else
                    break;
            }
            int longitud = estado.length();
            cout << "La longitud es: " << longitud << endl;
            int j;
            for (j = 0; j < longitud; j++) {
                char simb = estado[j]; //Pasar el string a un char
                int ascii_simb = (int) simb; //regresa el valor ingresado en codigo ASCII
                cout << "ascii: " << ascii_simb << endl;
                if (ascii_simb >= 48 && ascii_simb <= 57 || ascii_simb >= 65 && ascii_simb <= 90 || ascii_simb >= 97 && ascii_simb <= 122 || ascii_simb == -15 || ascii_simb == -47)
                    //Para que solo admita letras en español mayúsculas, minúsculas y números del 0 al 9
                    cout << "es bueno" << endl;
                else {
                    cout << "El estado contiene símbolos inválidos\n" << endl;
                    break;
                }
            }
            if(j==longitud)
                v_estado=true;
        }
    }
}