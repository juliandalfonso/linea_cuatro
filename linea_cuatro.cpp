#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
const int filas = 7, columnas = 9;
void partidarapida();
void preptablero();
void llenar();
void ficha();
void reglas();
bool buscarganador(int, int, char);
bool buscarganadorv(int, int, char);
bool buscarganadorh(int, int, char);
bool diago1(int, int, char);
bool diago2(int, int, char);
void imprimirestadisticas();
bool buscarganadord(int, int, char);
void visualizar();
void editarestadis();
bool buscarganadordi(int, int, char);
void mensajeganador(char);
void estadisticas(int);
void torneo(int);
void final();

char tablero[filas][columnas];
char simbolo = 'O', opcion;
int posc, coordenada, ultimapos, a, b, contador = 0, numero, numero1, numero2, v;
bool fin = false;
int cont = 0;

bool listo = false;
struct jugador
{

    string nombre;
    int partidas;
    int partidasganadas;
    int partidasperdidas;
    int partidasempatadas;
} jugadores[100];

int main()
{
    numero = 0;
    opcion = 0;
    preptablero();
    system("cls");
    while (opcion == 5 || opcion < 1)
    {

        cout << "Que desea hacer: \n"
             << "1.Partida rapida" << endl
             << "2.Torneo" << endl
             << "3.Estadisticas" << endl
             << "4.Reglas" << endl
             << "5.Salir" << endl;
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case '1':
            numero = 2;
            estadisticas(numero);
            simbolo = 'X';
            partidarapida();
            break;
        case '2':
            simbolo = 'X';
            cout << "digite jugadores para el torneo tiene que ser un numero par multiplo de 4 :";
            cin >> numero;
            estadisticas(numero);
            torneo(numero);
            break;
        case '3':
            visualizar();
            break;
        case '4':
            reglas();
            break;

        case '5':
            abort();
            break;
        }
    }

    return 0;
}
void partidarapida()
{
    int seguir = 0;
    system("cls");
    llenar();

    if (buscarganadorh(ultimapos, coordenada, simbolo) || buscarganadorv(ultimapos, coordenada, simbolo) || diago2(ultimapos, coordenada, simbolo) || diago1(ultimapos, coordenada, simbolo))
    {
        cout << "desea seguir?si=1 no =0\n";
        cin >> seguir;
        if (seguir == 1)
        {

            preptablero();
            simbolo = 'X';
            v = 2;
            partidarapida();
        }
        else
        {

            system("pause");
            main();
        }
    }

    if (simbolo == 'X')
    {
        simbolo = 'O';
    }
    else
    {
        simbolo = 'X';
    }

    cout << "\nEn que columa quiere su ficha: \n";
    cin >> posc;
    if (posc > 9 || posc < 1)
    {
        cout << "\nValor ingresado no valido!\n";
        cout << "\nEn que columa quiere su ficha: \n";
        cin >> posc;
    }
    else
    {
        coordenada = posc - 1;
        ficha();
    }
    partidarapida();

    return;
}
void preptablero()
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            tablero[i][j] = '-';
        }
    }
}
void llenar()
{
    int posiciones[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            cout << setw(2) << tablero[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < 9; i++)
    {
        cout << " " << posiciones[i];
    }
}
void ficha()
{
    // Recorrer fila por fila a ver si esta vacio el espacio
    for (int i = 0; i < filas; i++)
    {
        if (tablero[i][coordenada] == '-')
        {
            // Si estamos en la fila de arriba no "borramos" el espacio
            if (i > 0)
            {
                tablero[i - 1][coordenada] = '-';
            }
            // Poner X o O en la posicion
            tablero[i][coordenada] = simbolo;
            // Guardamos la ultima posicion de fila en la que quedó la ficha
            ultimapos = i;
        }
    }
}

bool buscarganadorh(int ultimapos, int coordenada, char simbolo)
{

    contador = 1;
    a = coordenada;
    fin = false;
    // Buscar ganador horizontal
    while (!fin)
    {
        // Iniciamos a-- para comprobar izquierda y despues derecha de la ficha inicial
        a--;
        if (a >= 0)
        {
            if (tablero[ultimapos][a] == simbolo)
            {
                contador++;
            }
            else
            {
                fin = true;
            }
        }
        else
        {
            fin = true;
        }
    }
    a = coordenada;
    fin = false;
    while (!fin)
    {
        // Iniciamos a++ para comprobar por derecha
        a++;
        if (a < filas)
        {
            if (tablero[ultimapos][a] == simbolo)
            {
                contador++;
            }
            else
            {
                fin = true;
            }
        }
        else
        {
            fin = true;
        }
    }
    if (contador >= 4)
    {

        mensajeganador(simbolo);
        return true;
    }
    return false;
}
bool buscarganadorv(int ultimapos, int coordenada, char simbolo)
{
    // Revisar el ganador vertical
    contador = 1;
    a = ultimapos;
    fin = false;
    while (!fin)
    {
        a++;
        if (a <= filas)
        {
            if (tablero[a][coordenada] == simbolo)
            {
                contador++;
            }
            else
            {
                fin = true;
            }
        }
        else
        {
            fin = true;
        }
    }
    if (contador >= 4)
    {

        mensajeganador(simbolo);
        return true;
    }
    return false;
}

bool diago2(int i, int j, char t)
{
    cont = 1;
    a = i;
    b = j;
    listo = false;
    // Izquierda
    while (!listo)
    {

        if (a < filas && b > 0)
        {
            if (tablero[a][b] == t)
            {
                cont++;
            }
            else
            {
                listo = true;
            }
        }
        else
        {
            listo = true;
        }
        a++;
        b--;
    }
    a = i;
    b = j;
    listo = false;
    // Derecha
    while (!listo)
    {
        a--;
        b++;
        if (a > 0 && b < columnas)
        {
            if (tablero[a][b] == t)
            {
                cont++;
            }
            else
            {
                listo = true;
            }
        }
        else
        {
            listo = true;
        }
        a--;
        b++;
    }
    if (cont >= 4)
    {
        mensajeganador(simbolo);
        return true;
    }
    return false;
}

bool diago1(int i, int j, char t)
{
    cont = 1;
    a = i;
    b = j;
    listo = false;
    // Derecha
    while (!listo)
    {
        a++;
        b++;
        if (a < filas && b < columnas)
        {
            if (tablero[a][b] == t)
            {
                cont++;
            }
            else
            {
                listo = true;
            }
        }
        else
        {
            listo = true;
        }
    }
    a = i;
    b = j;
    listo = false;
    // Izquierda
    while (!listo)
    {
        a--;
        b--;
        if (a > 0 && b > 0)
        {
            if (tablero[a][b] == t)
            {
                cont++;
            }
            else
            {
                listo = true;
            }
        }
        else
        {
            listo = true;
        }
    }
    if (cont >= 4)
    {
        mensajeganador(simbolo);
        return true;
    }
    return false;
}

void mensajeganador(char simbolo)
{
    int i = 0 + v;

    if (simbolo == 'O')
    {
        cout << "\n Felicidades " << jugadores[i].nombre << " Logro conectar 4 en linea!\n";
        jugadores[i].partidasganadas += 1;
        jugadores[i + 1].partidasperdidas += 1;
    }
    else if (simbolo == 'X')
    {
        cout << "\n Felicidades " << jugadores[i + 1].nombre << " Logro conectar 4 en linea!\n";
        jugadores[i + 1].partidasganadas += 1;
        jugadores[i].partidasperdidas += 1;
    }
    else
    {
        cout << "Empate!\n";
        jugadores[i].partidasempatadas += 1;
        jugadores[i + 1].partidasempatadas += 1;
    }
    imprimirestadisticas();
}
void torneo(int numero)
{
    int y = 0, p = numero / 2;
    y = numero;
    do
    {

        partidarapida();

    } while (p == 1);

    if (p == 1)
    {

        final();
    }
}
void estadisticas(int numero)
{

    for (int i = 0; i < numero; i++)
    {
        fflush(stdin);
        cout << "digite nombre:" << endl;
        getline(cin, jugadores[i].nombre);

        jugadores[i].partidas = jugadores[i].partidas + 1;
    }
}

void reglas()
{
    cout << "El objetivo del juego es lograr ser el primero en colocar cuatro fichas en linea vertical, horizontal o diagonal, teniendo en cuenta que por la columna que se elija para insertar una pieza, esta caera hasta el fondo. Es posible que en un juego dado no exista ningun ganador. " << endl;
    cout << endl;
    cout << "Si se selecciona el juego rapido este lanzara un tablero para que puedan jugar dos personas." << endl;
    cout << endl;
    cout << "En caso de seleccionar torneo este sera el formato: " << endl;
    cout << endl;
    cout << "jugador2----------           ----------jugaro3" << endl;
    cout << "                  |---------|" << endl;
    cout << "                  |---------|" << endl;
    cout << "jugador1----------           ----------jugador4" << endl;
    system("pause");
    main();
}
void imprimirestadisticas()
{

    ofstream jugadoresesta1;

    jugadoresesta1.open("jugadoresesta1.txt", ios::out);
    if (jugadoresesta1.fail())
    {

        cout << "No se puede abrir el archivo";
        exit(1);
    }
    for (int i = 0; i < numero; i++)
    {
        jugadoresesta1 << jugadores[i].nombre << ',';
        jugadoresesta1 << jugadores[i].partidas << ',';
        jugadoresesta1 << jugadores[i].partidasganadas << ',';
        jugadoresesta1 << jugadores[i].partidasperdidas << ',';
        jugadoresesta1 << jugadores[i].partidasempatadas << ',';
    }
    jugadoresesta1.close();
}

void editarestadis()
{

    ofstream jugadoresesta1; // modo de escritura

    jugadoresesta1.open("jugadoresesta1.txt", ios::app);

    if (jugadoresesta1.fail())
    {

        cout << "No se puede abrir el archivo";
        exit(1);
    }

    for (int i = 0; i < numero; i++)
    {
        jugadoresesta1 << jugadores[i].nombre << ',';
        jugadoresesta1 << jugadores[i].partidas << ',';
        jugadoresesta1 << jugadores[i].partidasganadas << ',';
        jugadoresesta1 << jugadores[i].partidasperdidas << ',';
        jugadoresesta1 << jugadores[i].partidasempatadas << ',';
    }

    jugadoresesta1.close();
}

void visualizar()
{
    ifstream("jugadoresesta1.txt");
    for (int i = 0; i < numero; i++)
    {
        cout << "Nombre: " << jugadores[i].nombre << ',';
        cout << "Jugadas: " << jugadores[i].partidas << ',';
        cout << "Ganadas: " << jugadores[i].partidasganadas << ',';
        cout << "Perdidas: "<< jugadores[i].partidasperdidas << ',';
        cout << "Empates: " <<jugadores[i].partidasempatadas << ',';
    }
    system("pause");
    main();
    
}
void final()
{
    int seguir = 0;
    system("cls");
    llenar();

    if (buscarganadorh(ultimapos, coordenada, simbolo) || buscarganadorv(ultimapos, coordenada, simbolo) || diago2(ultimapos, coordenada, simbolo) || diago1(ultimapos, coordenada, simbolo))
    {

        main();
    }

    if (simbolo == 'X')
    {
        simbolo = 'O';
    }
    else
    {
        simbolo = 'X';
    }

    cout << "\nEn que columa quiere su ficha: \n";
    cin >> posc;
    if (posc > 9 || posc < 1)
    {
        cout << "\nValor ingresado no valido!\n";
        cout << "\nEn que columa quiere su ficha: \n";
        cin >> posc;
    }
    else
    {
        coordenada = posc - 1;
        ficha();
    }
    partidarapida();
}
