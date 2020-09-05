#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

struct alfabeto_E { //estructura para nodos de alfabeto de entrada
    char simbolo;
    alfabeto_E *sig;
};

alfabeto_E *inicio_e = NULL;
alfabeto_E *fin_e = NULL;
alfabeto_E *nuevo_e = NULL;
alfabeto_E *ptr_e = NULL;

struct alfabeto_S { //estructura para nodos de alfabeto de salida
    char simbolo;
    alfabeto_S *sig;
};

alfabeto_S *inicio_s = NULL;
alfabeto_S *fin_s = NULL;
alfabeto_S *nuevo_s = NULL;
alfabeto_S *ptr_s = NULL;

struct matriz; //forward declaration

struct estados { //estructura para nodos de estados posibles
    string dato;
    bool validacion;
    estados *sig;
    matriz *aristas; //apunta a los nodos (aristas) de la matriz
};

estados *inicio = NULL;
estados *fin = NULL;
estados *nuevo = NULL;
estados *ptr = NULL;
estados *q0 = NULL;

struct matriz { //estructura para nodos de la matriz
    char simbolo;
    char traduccion;
    estados *transicion; //apunta a los estados posibles
    matriz *sig;
};

matriz *inicio_m = NULL;
matriz *fin_m = NULL;
matriz *nuevo_m = NULL;
matriz *ptr_m = NULL;

void Header(); //Encabezado con datos que siempre se deben mostrar "estático"
void Alfabeto_E(); //Ingresar alfabeto de entrada
void Alfabeto_S(); //Ingresar alfabeto de salida
void Estados(); //Conjunto de Estados Posibles
void Estado_Inicial(); //Estado Inicial de Operación
void Estados_Aceptacion(); //Conjunto de Estados de Aceptación
void Matriz_Transicion(); //llena matriz con datos de transición
void Matriz_Traduccion(); //llena matriz con datos de traducción
void Palabra_T();
void Palabra_V();
void Borrar_Datos(); //borra todos los datos del afd 

void Datos_Ingresados(); //Muestra los datos ya guardados en la consola

int total_afd = 0;
int afd_trad = 0;
int afd_valid = 0;
int total_estados;
int total_palabras;
int palabras_t;
int palabras_v;

int main() {
    int opc;
    do {
        Header();
        cout << endl;
        cout << "Indique el tipo de Autómata Finito Determinista a registrar: " << endl;
        cout << "1. Traducción\n" << "2. Validación\n" << "3. Salir\n" << "Opción: ";
        cin>>opc;
        cout << endl;
        if (cin.fail()) {
            cout << "---Opción inválida---\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n'); //Para vaciar el buffer y pida de nuevo un cin
        } else {
            switch (opc) {
                case 1: Header();
                    cout << endl;
                    Alfabeto_E();
                    cout << "\n*Alfabeto de entrada guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Alfabeto_S();
                    cout << "\n*Alfabeto de salida guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Estados();
                    cout << "\n*Conjunto de Estados Posibles guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Estado_Inicial();
                    cout << "\n*Estado Inicial de Operación guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Estados_Aceptacion();
                    cout << "\n*Conjunto de Estados de Aceptación guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Matriz_Transicion();
                    cout << "\n*Matriz de Transición guardada*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Matriz_Traduccion();
                    Datos_Ingresados();
                    cout << "\n*Matriz de Traducción guardada*\n" << endl;
                    Header();
                    cout << endl;
                    Palabra_T();
                    ++total_afd;
                    ++afd_trad;
                    Borrar_Datos();
                    break;
                case 2: Header();
                    cout << endl;
                    Alfabeto_E();
                    cout << "\n*Alfabeto de entrada guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Estados();
                    cout << "\n*Conjunto de Estados Posibles guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Estado_Inicial();
                    cout << "\n*Estado Inicial de Operación guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Estados_Aceptacion();
                    cout << "\n*Conjunto de Estados de Aceptación guardado*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Matriz_Transicion();
                    cout << "\n*Matriz de Transición guardada*\n" << endl;
                    Header();
                    Datos_Ingresados();
                    cout << endl;
                    Palabra_V();
                    ++total_afd;
                    ++afd_valid;
                    Borrar_Datos();
                    break;
                case 3: cout << endl;
                    Header();
                    cout << "\n" << endl;
                    cout << "El total de AFDs Ingresados fue de: " << total_afd << endl;
                    cout << "El total de AFDs de Traducción fue de: " << afd_trad << endl;
                    cout << "El total de AFDs de Validación fue de: " << afd_valid << endl;
                    cout << "El total de palabras ingresadas fue de: " << total_palabras << endl;
                    cout << "El total de palabras traducidas fue de: " << palabras_t << endl;
                    cout << "El total de palabras validas fue de: " << palabras_v << endl;
                    cout << "El total de palabras inválidas fue de: " << total_palabras - palabras_v << endl;
                    cout << "\n¡Gracias!... Cerrando sistema" << endl;
                    break;
                default: cout << "---Opción inválida---\n" << endl;
            }
        }
    } while (opc != 3);

    return 0;
}

void Header() {
    time_t tSac = time(NULL);
    struct tm* tmP = localtime(&tSac);
    system("clear");
    cout << setw(57) << "David Asaf Hernández Aznar\n";
    cout << setw(48) << "#0121920211\n";
    cout << setw(51) << "Métodos Formales\n";
    cout << setw(45) << "UNIVA\n";
    cout << setw(40) << "Hora: " << tmP->tm_hour << ":" << tmP->tm_min << ":" << tmP->tm_sec << endl;
    cout << setw(40) << "Fecha: " << tmP->tm_mday << "/" << tmP->tm_mon + 1 << "/" << tmP->tm_year + 1900 << endl;
}

void Datos_Ingresados() {
    ptr_e = inicio_e;
    cout << "E: ";
    while (ptr_e != NULL) {
        cout << ptr_e->simbolo << " ";
        ptr_e = ptr_e->sig;
    }
    cout << endl;

    if (inicio_s != NULL) {
        ptr_s = inicio_s;
        cout << "S: ";
        while (ptr_s != NULL) {
            cout << ptr_s->simbolo << " ";
            ptr_s = ptr_s->sig;
        }
        cout << endl;
    }

    if (inicio != NULL) {
        ptr = inicio;
        cout << "Q: ";
        while (ptr != NULL) {
            cout << ptr->dato << " ";
            ptr = ptr->sig;
        }
        cout << endl;
    }

    if (q0 != NULL) {
        cout << "q0: " << q0->dato << endl;
    }

}

void Alfabeto_E() {
    string simb_t;
    int i = 1;
    bool check; //checar si ya se ingresó el símbolo anteriormente. 
    //check true = no existe el dato; check = false ya existe
    cout << "Ingrese el alfabeto de entrada (seleccione '*' para terminar): " << endl;
    while (true) {
        cout << i << ": ";
        cin>>simb_t;
        if (simb_t.length() != 1) //Verificar la longitud de caracteres ingresados, máximo 1
            cout << "--Solamente puede ingresar un símbolo a la vez--\n" << endl;
        else {
            if (simb_t == "*") {
                if (inicio_e == NULL)
                    cout << "--El alfabeto de entrada NO puede estar vacío--\n";
                else
                    break;
            }
            char simb = simb_t[0]; //Pasar el string a un char
            int ascii_simb = (int) simb; //regresa el valor ingresado en codigo ASCII
            if (ascii_simb >= 48 && ascii_simb <= 57 || ascii_simb >= 65 && ascii_simb <= 90 || ascii_simb >= 97 && ascii_simb <= 122 || ascii_simb == -15 || ascii_simb == -47) {
                //Para que solo admita letras en español mayúsculas, minúsculas y números del 0 al 9
                if (inicio_e == NULL) {
                    nuevo_e = new(alfabeto_E);
                    nuevo_e->simbolo = simb;
                    inicio_e = nuevo_e;
                    fin_e = nuevo_e;
                    fin_e->sig = NULL;
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
                        cout << "--No se pueden ingresar simbolos repetidos--\n" << endl;
                    else {
                        nuevo_e = new(alfabeto_E);
                        nuevo_e->simbolo = simb;
                        fin_e->sig = nuevo_e;
                        fin_e = nuevo_e;
                        fin_e->sig = NULL;
                        ++i;
                    }
                }
            } else {
                if (simb_t != "*")
                    cout << "--El símbolo ingresado no es válido--\n" << endl;
            }
        }
    }
    ptr_e = inicio_e;
    cout << "El Afabeto de Entrada es: ";
    while (ptr_e != NULL) {
        cout << ptr_e->simbolo << " ";
        ptr_e = ptr_e->sig;
    }
    cout << endl;
}

void Alfabeto_S() {
    string simb_t;
    int i = 1;
    bool check; //check true = no existe el dato; check = false ya existe
    cout << "Ingrese el alfabeto de salida (seleccione '*' para terminar): " << endl;
    while (true) {
        cout << i << ": ";
        cin>>simb_t;
        if (simb_t.length() != 1) //Verificar la longitud de caracteres ingresados, máximo 1
            cout << "--Solamente puede ingresar un símbolo a la vez--\n" << endl;
        else {
            if (simb_t == "*") {
                if (inicio_s == NULL)
                    cout << "--El alfabeto de salida NO puede estar vacío--\n";
                else
                    break;
            }
            char simb = simb_t[0]; //Pasar el string a un char
            int ascii_simb = (int) simb; //regresa el valor ingresado en codigo ASCII
            if (ascii_simb >= 48 && ascii_simb <= 57 || ascii_simb >= 65 && ascii_simb <= 90 || ascii_simb >= 97 && ascii_simb <= 122 || ascii_simb == -15 || ascii_simb == -47) {
                //Para que solo admita letras en español mayúsculas, minúsculas y números del 0 al 9
                if (inicio_s == NULL) {
                    nuevo_s = new(alfabeto_S);
                    nuevo_s->simbolo = simb;
                    inicio_s = nuevo_s;
                    fin_s = nuevo_s;
                    fin_s->sig = NULL;
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
                        cout << "--No se pueden ingresar simbolos repetidos--\n" << endl;
                    else {
                        nuevo_s = new(alfabeto_S);
                        nuevo_s->simbolo = simb;
                        fin_s->sig = nuevo_s;
                        fin_s = nuevo_s;
                        fin_s->sig = NULL;
                        ++i;
                    }
                }
            } else {
                if (simb_t != "*")
                    cout << "--El símbolo ingresado no es válido--\n" << endl;
            }
        }
    }
    ptr_s = inicio_s;
    cout << "El Afabeto de Salida es: ";
    while (ptr_s != NULL) {
        cout << ptr_s->simbolo << " ";
        ptr_s = ptr_s->sig;
    }
    cout << endl;

}

void Estados() {
    total_estados = 0;
    string estado;
    int i = 1;
    bool s;
    bool check; //verificar si el estado ya se registró 
    //check true = no existe el dato; check = false ya existe
    cout << "Ingrese el conjunto de estados posibles 'Q' (seleccione '*' para terminar): " << endl;
    while (true) {
        cout << i << ": ";
        cin>>estado;
        if (estado.length() > 15) //Verificar la longitud de caracteres ingresados, máximo 15
            cout << "--La longitud máxima permitida de la palabra es de 15 caracteres--\n" << endl;
        else {
            if (estado == "*") {
                if (inicio == NULL)
                    cout << "--El conjunto de estados posibles NO puede estar vacío--\n";
                else
                    break;
            }
            int longitud = estado.length();
            int j;
            for (j = 0; j < longitud; j++) {
                char simb = estado[j]; //Pasar el string a un char
                int ascii_simb = (int) simb; //regresa el valor ingresado en codigo ASCII
                if (ascii_simb >= 48 && ascii_simb <= 57 || ascii_simb >= 65 && ascii_simb <= 90 || ascii_simb >= 97 && ascii_simb <= 122 || ascii_simb == -15 || ascii_simb == -47)
                    //Para que solo admita letras en español mayúsculas, minúsculas y números del 0 al 9
                    s = true;
                else {
                    if (estado != "*")
                        cout << "--El estado contiene símbolos inválidos--\n" << endl;
                    break;
                }
            }
            if (j == longitud) {
                if (inicio == NULL) {
                    nuevo = new(estados);
                    nuevo->dato = estado;
                    inicio = nuevo;
                    fin = nuevo;
                    fin->sig = NULL;
                    ++i;
                } else {
                    check = true;
                    ptr = inicio;
                    while (ptr != NULL) {
                        if (ptr->dato == estado) {
                            check = false;
                            break;
                        }
                        ptr = ptr->sig;
                    }
                    if (check == false)
                        cout << "--No se pueden ingresar simbolos repetidos--\n" << endl;
                    else {
                        nuevo = new(estados);
                        nuevo->dato = estado;
                        fin->sig = nuevo;
                        fin = nuevo;
                        fin->sig = NULL;
                        ++i;
                    }
                }
            }
        }
    }
    total_estados = i - 1;
    cout << "El total de estados es: " << total_estados << endl;
    ptr = inicio;
    cout << "El Conjunto de estados de Posibles es: ";
    while (ptr != NULL) {
        cout << ptr->dato << " ";
        ptr = ptr->sig;
    }
    cout << endl;
}

void Estado_Inicial() {
    string q;
    bool check; //check true = no existe el dato; check = false ya existe
    while (true) {
        cout << "Ingrese el Estado inicial de Operación 'q0' (debe pertenecer a Q): ";
        cin >> q;
        check = true;
        ptr = inicio;
        while (ptr != NULL) {
            if (ptr->dato == q) {
                check = false;
                break;
            }
            ptr = ptr->sig;
        }
        if (check == false) {
            q0 = ptr;
            cout << "El estado inicial es: " << q0->dato << endl;
            break;
        } else
            cout << "--El estado ingresado no pertenece a Q, vuelva a intentar--\n" << endl;
    }
}

void Estados_Aceptacion() {
    char estado;
    bool validar_opc; //valida que el "estado" sea T o F, otro caracter marca opción inválida
    cout << "Determine el conjunto de Estados de Aceptación\n";
    cout << "'T' = True (Estado aceptado)\n" << "'F' = False (Estado NO aceptado)" << endl;
    ptr = inicio;
    while (ptr != NULL) {
        do {
            validar_opc = true;
            cout << ptr->dato << "---------->";
            cin>>estado;
            switch (estado) {
                case 'T': ptr->validacion = true;
                    break;
                case 'F': ptr->validacion = false;
                    break;
                default: cout << "\n--Opción Inválida, vuelve a intentar--\n" << endl;
                    validar_opc = false;
            }
        } while (validar_opc != true);
        ptr = ptr->sig;
    }
    cout << "Los Estados de Aceptación del conjunto son: ";
    ptr = inicio;
    while (ptr != NULL) {
        if (ptr->validacion == true)
            cout << ptr->dato << " ";
        ptr = ptr->sig;
    }
    cout << endl;
}

void Matriz_Transicion() {
    string temp; //temporal para seleccionar el estado a apuntar
    bool check; //check true = no existe el dato; check = false ya existe
    estados *ptr_temp = NULL;
    for (ptr = inicio; ptr != NULL; ptr = ptr->sig) { //Llena matriz con símbolos de alfabeto de entrada
        for (ptr_e = inicio_e; ptr_e != NULL; ptr_e = ptr_e->sig) {
            if (inicio_m == NULL) {
                nuevo_m = new(matriz);
                nuevo_m->simbolo = ptr_e->simbolo;
                inicio_m = nuevo_m;
                fin_m = nuevo_m;
                fin_m->sig = NULL;
            } else {
                nuevo_m = new(matriz);
                nuevo_m->simbolo = ptr_e->simbolo;
                fin_m->sig = nuevo_m;
                fin_m = nuevo_m;
                fin_m->sig = NULL;
            }
        }
        ptr->aristas = inicio_m;
        inicio_m = NULL;
        fin_m = NULL;
        nuevo_m = NULL;
    }
    cout << "Ingrese Matriz de Transición: " << endl;
    for (ptr = inicio; ptr != NULL; ptr = ptr->sig) {
        for (ptr_m = ptr->aristas; ptr_m != NULL; ptr_m = ptr_m->sig) {
            while (true) {
                cout << ptr->dato << " - " << ptr_m->simbolo << "---------->";
                cin >> temp;
                check = true;
                ptr_temp = inicio;
                while (ptr_temp != NULL) {
                    if (ptr_temp->dato == temp) {
                        check = false;
                        break;
                    }
                    ptr_temp = ptr_temp->sig;
                }
                if (check == false) {
                    ptr_m->transicion = ptr_temp;
                    break;
                } else
                    cout << "--El estado ingresado no pertenece a Q, vuelva a intentar--\n" << endl;
            }
        }
    }
    cout << "\n\n\n";
    for (ptr = inicio; ptr != NULL; ptr = ptr->sig) {
        for (ptr_m = ptr->aristas; ptr_m != NULL; ptr_m = ptr_m->sig) {
            cout << ptr->dato << " - " << ptr_m->simbolo << "---------->" << ptr_m->transicion->dato << endl;
        }
    }
}

void Matriz_Traduccion() {
    string temp;
    bool check; //check true = no existe el dato; check = false ya existe
    alfabeto_S *ptr_temp = NULL;
    cout << "Ingrese Matriz de Traducción: " << endl;
    for (ptr = inicio; ptr != NULL; ptr = ptr->sig) {
        for (ptr_m = ptr->aristas; ptr_m != NULL; ptr_m = ptr_m->sig) {
            while (true) {
                cout << ptr->dato << " - " << ptr_m->simbolo << "---------->";
                cin >> temp;
                if (temp.length() != 1) //Verificar la longitud de caracteres ingresados, máximo 1
                    cout << "--Solamente puede ingresar un símbolo a la vez--\n" << endl;
                else {
                    char simb = temp[0];
                    check = true;
                    ptr_temp = inicio_s;
                    while (ptr_temp != NULL) {
                        if (ptr_temp->simbolo == simb) {
                            check = false;
                            break;
                        }
                        ptr_temp = ptr_temp->sig;
                    }
                    if (check == false) {
                        ptr_m->traduccion = ptr_temp->simbolo;
                        break;
                    } else
                        cout << "--El símbolo ingresado no pertenece al Alfabeto de Salida, vuelva a intentar--\n" << endl;
                }
            }

        }
    }
    cout << "\n\n\n";
    for (ptr = inicio; ptr != NULL; ptr = ptr->sig) {
        for (ptr_m = ptr->aristas; ptr_m != NULL; ptr_m = ptr_m->sig) {
            cout << ptr->dato << " - " << ptr_m->simbolo << "---------->" << ptr_m->traduccion << endl;
        }
    }
}

void Palabra_T() {
    char opc;
    string palabra;
    bool check; //verificar si el símbolo ya se registró 
    //check true = no existe el dato; check = false ya existe
    do {
        ptr_e = inicio_e; //Muestra Alfabeto de Entrada
        cout << "E: ";
        while (ptr_e != NULL) {
            cout << ptr_e->simbolo << " ";
            ptr_e = ptr_e->sig;
        }
        cout << "\n" << endl;
        cout << "Ingrese palabra a Traducir: ";
        cin>> palabra;
        int longitud = palabra.length();
        int j;
        for (j = 0; j < longitud; j++) {
            char simb = palabra[j]; //Pasar el string a un char
            int ascii_simb = (int) simb; //regresa el valor ingresado en codigo ASCII
            if (ascii_simb >= 48 && ascii_simb <= 57 || ascii_simb >= 65 && ascii_simb <= 90 || ascii_simb >= 97 && ascii_simb <= 122 || ascii_simb == -15 || ascii_simb == -47)
                //Para que solo admita letras en español mayúsculas, minúsculas y números del 0 al 9
                check = true;
            else {
                cout << "--La palabra contiene símbolos inválidos--\n" << endl;
                break;
            }
        }
        for (j = 0; j < longitud; j++) {
            char simb = palabra[j];
            check = true;
            ptr_e = inicio_e;
            while (ptr_e != NULL) {
                if (ptr_e->simbolo == simb) {
                    check = false;
                    break;
                }
                ptr_e = ptr_e->sig;
            }
            if (check == true) {
                cout << "--La palabra contiene símbolos que no pertenecen al Alfabeto de Entrada--\n" << endl;
                break;
            }
        }
        int k = j;

        if (j == longitud) {
            cout << "La palabra traducida es: ";
            ptr_m = q0->aristas;
            j = 0;
            char simb = palabra [j];
            while (ptr_m != NULL) {
                if (ptr_m->simbolo == simb)
                    break;
                ptr_m = ptr_m->sig;
            }
            cout << ptr_m->traduccion;
            if (k > 1) {
                for (j = 1; j < longitud; j++) {
                    ptr = ptr_m->transicion; //Para saber en qué estado está la secuencia
                    ptr_m = ptr_m->transicion->aristas;
                    char simb = palabra [j];
                    while (ptr_m != NULL) {
                        if (ptr_m->simbolo == simb)
                            break;
                        ptr_m = ptr_m->sig;
                    }
                    cout << ptr_m->traduccion;
                }
            }
            cout << endl;
        }

        if (k == longitud) {
            if (k <= 1) {
                if (q0->validacion == true) {
                    cout << "La palabra es Válida\n" << endl;
                    ++palabras_v;
                } else
                    cout << "La palabra es Inválida\n" << endl;
                ++palabras_t;
                ++total_palabras;
            } else {
                if (ptr->validacion == true) {
                    cout << "La palabra es Válida\n" << endl;
                    ++palabras_v;
                } else
                    cout << "La palabra es Inválida\n" << endl;
                ++palabras_t;
                ++total_palabras;
            }
        }
        do {
            cout << "¿Desea ingresar otra palabra? (Si = 'S' ; No = 'N'): ";
            cin>>opc;
            cout << endl;
            switch (opc) {
                case 'S': Header();
                    cout << endl;
                case 'N':
                    break;
                default: Header();
                    cout << "--Opción Inválida--\n" << endl;
            }
        } while (opc != 'S' && opc != 'N');
    } while (opc != 'N');
}

void Palabra_V() {
    char opc;
    string palabra;
    bool check; //verificar si el símbolo ya se registró 
    //check true = no existe el dato; check = false ya existe
    do {
        ptr_e = inicio_e; //Muestra Alfabeto de Entrada
        cout << "E: ";
        while (ptr_e != NULL) {
            cout << ptr_e->simbolo << " ";
            ptr_e = ptr_e->sig;
        }
        cout << "\n" << endl;
        cout << "Ingrese palabra a Validar: ";
        cin>> palabra;
        int longitud = palabra.length();
        int j;
        for (j = 0; j < longitud; j++) {
            char simb = palabra[j]; //Pasar el string a un char
            int ascii_simb = (int) simb; //regresa el valor ingresado en codigo ASCII
            if (ascii_simb >= 48 && ascii_simb <= 57 || ascii_simb >= 65 && ascii_simb <= 90 || ascii_simb >= 97 && ascii_simb <= 122 || ascii_simb == -15 || ascii_simb == -47)
                //Para que solo admita letras en español mayúsculas, minúsculas y números del 0 al 9
                check = true;
            else {
                cout << "--La palabra contiene símbolos inválidos--\n" << endl;
                break;
            }
        }
        for (j = 0; j < longitud; j++) {
            char simb = palabra[j];
            check = true;
            ptr_e = inicio_e;
            while (ptr_e != NULL) {
                if (ptr_e->simbolo == simb) {
                    check = false;
                    break;
                }
                ptr_e = ptr_e->sig;
            }
            if (check == true) {
                cout << "--La palabra contiene símbolos que no pertenecen al Alfabeto de Entrada--\n" << endl;
                break;
            }
        }
        int k = j;
        cout << "k: " << k << endl;
        cout << "j: " << j << endl;
        cout << "long: " << longitud << endl;
        if (j == longitud) {
            cout << "La palabra ingresada es: ";
            ptr_m = q0->aristas;
            j = 0;
            char simb = palabra [j];
            while (ptr_m != NULL) {
                if (ptr_m->simbolo == simb)
                    break;
                ptr_m = ptr_m->sig;
            }
            if (j > 1) {
                for (j = 1; j < longitud; j++) {
                    ptr = ptr_m->transicion; //Para saber en qué estado está la secuencia
                    ptr_m = ptr_m->transicion->aristas;
                    char simb = palabra [j];
                    while (ptr_m != NULL) {
                        if (ptr_m->simbolo == simb)
                            break;
                        ptr_m = ptr_m->sig;
                    }
                }
            }
        }
        if (check = true) {
            if (k = 1) {
                if (q0->validacion == true) {
                    cout << "Válida" << endl;
                    ++palabras_v;
                } else
                    cout << "Inválida" << endl;
                ++palabras_t;
                ++total_palabras;
            } else {
                if (ptr->validacion == true) {
                    cout << "Válida" << endl;
                    ++palabras_v;
                } else
                    cout << "Inválida" << endl;
                ++palabras_t;
                ++total_palabras;
            }
        }
        do {
            cout << "\n¿Desea ingresar otra palabra? (Si = 'S' ; No = 'N'): ";
            cin>>opc;
            cout << endl;
            switch (opc) {
                case 'S': Header();
                    cout << endl;
                case 'N':
                    break;
                default:
                    cout << "--Opción Inválida--\n" << endl;
            }
        } while (opc != 'S' && opc != 'N');
    } while (opc != 'N');
}

void Borrar_Datos() {
    ptr_e = inicio_e; //Borra Alfabeto de Entrada
    while (ptr_e->sig != NULL) {
        ptr_e = inicio_e;
        inicio_e = ptr_e->sig;
        delete(ptr_e);
    }
    delete(inicio_e);
    inicio_e = NULL;
    fin_e = NULL;
    ptr_e = NULL;
    nuevo_e = NULL;

    if (inicio_s != NULL) { //Borra Alfabeto de Salida
        ptr_s = inicio_s;
        while (ptr_s->sig != NULL) {
            ptr_s = inicio_s;
            inicio_s = ptr_s->sig;
            delete(ptr_s);
        }
        delete(inicio_s);
        inicio_s = NULL;
        fin_s = NULL;
        ptr_s = NULL;
        nuevo_s = NULL;
    }
    cout << "borra alf salida" << endl;

    for (ptr = inicio; ptr->sig != NULL; ptr = ptr->sig) {
        inicio_m = ptr->aristas;
        ptr->aristas = NULL;
        while (inicio_m->sig != NULL) {
            ptr_m = inicio_m;
            inicio_m = ptr_m->sig;
            delete(ptr_m);
        }
        delete(inicio_m);
        inicio_m = NULL;
        fin_m = NULL;
        ptr_m = NULL;
        nuevo_m = NULL;
    }

    ptr = inicio; //Borra Estados Posibles
    while (ptr->sig != NULL) {
        ptr = inicio;
        inicio = ptr->sig;
        delete(ptr);
    }
    delete(inicio);
    inicio = NULL;
    fin = NULL;
    ptr = NULL;
    nuevo = NULL;
    q0 = NULL;
}