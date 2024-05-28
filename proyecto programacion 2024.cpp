#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int FILAS = 7, COLUMNAS = 9;

void partidaRapida();
void prepararTablero();
void llenarTablero();
void colocarFicha();
void mostrarReglas();
bool buscarGanador(int, int, char);
bool buscarGanadorVertical(int, int, char);
bool buscarGanadorHorizontal(int, int, char);
bool buscarDiagonal1(int, int, char);
bool buscarDiagonal2(int, int, char);
void imprimirEstadisticas();
void visualizarEstadisticas();
void editarEstadisticas();
void mostrarMensajeGanador(char);
void actualizarEstadisticas(int);
void iniciarTorneo(int);
void juegoFinal();

char tablero[FILAS][COLUMNAS];
char simbolo = 'O';
int opcion;
int posicionColumna, coordenada, ultimaPosicion, a, b, contador = 0, numeroJugadores, jugadoresActivos, indiceJugador, totalJugadores;
bool finJuego = false;
int cont = 0;
bool listo = false;
int contadorMovimientos = 0;

struct Jugador
{
    string nombre;
    int partidas;
    int partidasGanadas;
    int partidasPerdidas;
    int partidasEmpatadas;
    int puntos;
} jugadores[100];

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa() {
    cout << "Presiona Enter para continuar...";
    cin.ignore();
    cin.get();
}

int main()
{
    bool continuar = true;
    while (continuar)
    {
        numeroJugadores = 0;
        opcion = 0;
        prepararTablero();
        limpiarPantalla();
        
        cout << "¿Qué desea hacer?: \n"
             << "1. Partida rápida" << endl
             << "2. Torneo" << endl
             << "3. Estadísticas" << endl
             << "4. Reglas" << endl
             << "5. Salir" << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            numeroJugadores = 2;
            actualizarEstadisticas(numeroJugadores);
            simbolo = 'X';
            contadorMovimientos = 0;
            partidaRapida();
            break;
        case 2:
            simbolo = 'X';
            do {
                cout << "Digite el número de jugadores para el torneo (debe ser un número par múltiplo de 4): ";
                cin >> numeroJugadores;
                if (numeroJugadores % 4 != 0 || numeroJugadores <= 0) {
                    cout << "Número de jugadores no válido. Debe ser un número par múltiplo de 4." << endl;
                }
            } while (numeroJugadores % 4 != 0 || numeroJugadores <= 0);
            actualizarEstadisticas(numeroJugadores);
            contadorMovimientos = 0;
            iniciarTorneo(numeroJugadores);
            break;
        case 3:
            visualizarEstadisticas();
            break;
        case 4:
            mostrarReglas();
            break;
        case 5:
            cout << "Saliendo del programa..." << endl;
            continuar = false;
            break;
        default:
            cout << "Opción no válida. Por favor intente de nuevo." << endl;
        }
    }
    return 0;
}

void partidaRapida()
{
    int seguir = 0;
    limpiarPantalla();
    llenarTablero();

    if (buscarGanadorHorizontal(ultimaPosicion, coordenada, simbolo) || buscarGanadorVertical(ultimaPosicion, coordenada, simbolo) || buscarDiagonal2(ultimaPosicion, coordenada, simbolo) || buscarDiagonal1(ultimaPosicion, coordenada, simbolo))
    {
        cout << "¿Desea seguir? (si=1, no=0): ";
        cin >> seguir;
        if (seguir == 1)
        {
            prepararTablero();
            simbolo = 'X';
            jugadoresActivos = 2;
            contadorMovimientos = 0;
            partidaRapida();
        }
        else
        {
            pausa();
            return;
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

    cout << "\n¿En qué columna quiere colocar su ficha?: ";
    cin >> posicionColumna;
    if (posicionColumna > 9 || posicionColumna < 1)
    {
        cout << "\n¡Valor ingresado no válido!\n";
        cout << "\n¿En qué columna quiere colocar su ficha?: ";
        cin >> posicionColumna;
    }
    else
    {
        coordenada = posicionColumna - 1;
        colocarFicha();
    }
    partidaRapida();
}

void prepararTablero()
{
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            tablero[i][j] = '-';
        }
    }
}

void llenarTablero()
{
    int posiciones[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
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

void colocarFicha()
{
    for (int i = FILAS - 1; i >= 0; i--)
    {
        if (tablero[i][coordenada] == '-')
        {
            tablero[i][coordenada] = simbolo;
            ultimaPosicion = i;
            contadorMovimientos++;
            break;
        }
    }
}

bool buscarGanadorHorizontal(int ultimaPosicion, int coordenada, char simbolo)
{
    contador = 1;
    a = coordenada;
    finJuego = false;
    while (!finJuego)
    {
        a--;
        if (a >= 0)
        {
            if (tablero[ultimaPosicion][a] == simbolo)
            {
                contador++;
            }
            else
            {
                finJuego = true;
            }
        }
        else
        {
            finJuego = true;
        }
    }
    a = coordenada;
    finJuego = false;
    while (!finJuego)
    {
        a++;
        if (a < COLUMNAS)
        {
            if (tablero[ultimaPosicion][a] == simbolo)
            {
                contador++;
            }
            else
            {
                finJuego = true;
            }
        }
        else
        {
            finJuego = true;
        }
    }
    if (contador >= 4)
    {
        mostrarMensajeGanador(simbolo);
        return true;
    }
    return false;
}

bool buscarGanadorVertical(int ultimaPosicion, int coordenada, char simbolo)
{
    contador = 1;
    a = ultimaPosicion;
    finJuego = false;
    while (!finJuego)
    {
        a++;
        if (a < FILAS)
        {
            if (tablero[a][coordenada] == simbolo)
            {
                contador++;
            }
            else
            {
                finJuego = true;
            }
        }
        else
        {
            finJuego = true;
        }
    }
    if (contador >= 4)
    {
        mostrarMensajeGanador(simbolo);
        return true;
    }
    return false;
}

bool buscarDiagonal2(int i, int j, char t)
{
    cont = 1;
    a = i;
    b = j;
    listo = false;
    while (!listo)
    {
        if (a < FILAS && b > 0)
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
    while (!listo)
    {
        a--;
        b++;
        if (a > 0 && b < COLUMNAS)
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
        mostrarMensajeGanador(simbolo);
        return true;
    }
    return false;
}

bool buscarDiagonal1(int i, int j, char t)
{
    cont = 1;
    a = i;
    b = j;
    listo = false;
    while (!listo)
    {
        a++;
        b++;
        if (a < FILAS && b < COLUMNAS)
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
        mostrarMensajeGanador(simbolo);
        return true;
    }
    return false;
}

void mostrarMensajeGanador(char simbolo)
{
    int i = 0 + jugadoresActivos;

    if (simbolo == 'O')
    {
        cout << "\n¡Felicidades " << jugadores[i].nombre << "! Logró conectar 4 en línea con " << contadorMovimientos << " movimientos.\n";
        jugadores[i].partidasGanadas += 1;
        jugadores[i].puntos += 3;
        jugadores[i + 1].partidasPerdidas += 1;
    }
    else if (simbolo == 'X')
    {
        cout << "\n¡Felicidades " << jugadores[i + 1].nombre << "! Logró conectar 4 en línea con " << contadorMovimientos << " movimientos.\n";
        jugadores[i + 1].partidasGanadas += 1;
        jugadores[i + 1].puntos += 3;
        jugadores[i].partidasPerdidas += 1;
    }
    else
    {
        cout << "¡Empate!\n";
        jugadores[i].partidasEmpatadas += 1;
        jugadores[i].puntos += 1;
        jugadores[i + 1].partidasEmpatadas += 1;
        jugadores[i + 1].puntos += 1;
    }
    imprimirEstadisticas();
}

void iniciarTorneo(int numeroJugadores)
{
    int y = 0, p = numeroJugadores / 2;
    y = numeroJugadores;
    do
    {
        contadorMovimientos = 0;
        partidaRapida();
    } while (p == 1);

    if (p == 1)
    {
        juegoFinal();
    }
}

void actualizarEstadisticas(int numeroJugadores)
{
    for (int i = 0; i < numeroJugadores; i++)
    {
        fflush(stdin);
        cout << "Digite nombre:" << endl;
        cin.ignore();
        getline(cin, jugadores[i].nombre);

        jugadores[i].partidas += 1;
        jugadores[i].puntos = 0;
    }
}

void mostrarReglas()
{
    cout << "El objetivo del juego es lograr ser el primero en colocar cuatro fichas en línea vertical, horizontal o diagonal, teniendo en cuenta que por la columna que se elija para insertar una pieza, esta caerá hasta el fondo. Es posible que en un juego dado no exista ningún ganador. " << endl;
    cout << endl;
    cout << "Si se selecciona el juego rápido, este lanzará un tablero para que puedan jugar dos personas." << endl;
    cout << endl;
    cout << "En caso de seleccionar torneo, este será el formato: " << endl;
    cout << endl;
    cout << "jugador2----------           ----------jugador3" << endl;
    cout << "                  |---------|" << endl;
    cout << "                  |---------|" << endl;
    cout << "jugador1----------           ----------jugador4" << endl;
    pausa();
}

void imprimirEstadisticas()
{
    ofstream archivoEstadisticas;
    archivoEstadisticas.open("estadisticas.txt", ios::out);
    if (archivoEstadisticas.fail())
    {
        cout << "No se puede abrir el archivo";
        exit(1);
    }
    for (int i = 0; i < numeroJugadores; i++)
    {
        archivoEstadisticas << jugadores[i].nombre << "\n";
        archivoEstadisticas << jugadores[i].partidas << "\n";
        archivoEstadisticas << jugadores[i].partidasGanadas << "\n";
        archivoEstadisticas << jugadores[i].partidasPerdidas << "\n";
        archivoEstadisticas << jugadores[i].partidasEmpatadas << "\n";
        archivoEstadisticas << jugadores[i].puntos << "\n";
    }
    archivoEstadisticas.close();
}

void editarEstadisticas()
{
    ofstream archivoEstadisticas;
    archivoEstadisticas.open("estadisticas.txt", ios::app);
    if (archivoEstadisticas.fail())
    {
        cout << "No se puede abrir el archivo";
        exit(1);
    }
    for (int i = 0; i < numeroJugadores; i++)
    {
        archivoEstadisticas << jugadores[i].nombre << "\n";
        archivoEstadisticas << jugadores[i].partidas << "\n";
        archivoEstadisticas << jugadores[i].partidasGanadas << "\n";
        archivoEstadisticas << jugadores[i].partidasPerdidas << "\n";
        archivoEstadisticas << jugadores[i].partidasEmpatadas << "\n";
        archivoEstadisticas << jugadores[i].puntos << "\n";
    }
    archivoEstadisticas.close();
}

void visualizarEstadisticas()
{
    ifstream archivo("estadisticas.txt");
    if (!archivo) {
        cout << "No se puede abrir el archivo de estadísticas." << endl;
        return;
    }

    limpiarPantalla();
    string nombreBuscado;
    cout << "Ingrese el nombre del jugador para ver sus estadísticas: ";
    cin.ignore();
    getline(cin, nombreBuscado);

    cout << "Estadísticas de Jugadores:" << endl;
    string nombre;
    int partidas, ganadas, perdidas, empatadas, puntos;
    bool encontrado = false;

    while (getline(archivo, nombre)) {
        archivo >> partidas >> ganadas >> perdidas >> empatadas >> puntos;
        archivo.ignore();

        if (nombre == nombreBuscado) {
            cout << "Nombre: " << nombre << endl;
            cout << "Partidas: " << partidas << endl;
            cout << "Ganadas: " << ganadas << endl;
            cout << "Perdidas: " << perdidas << endl;
            cout << "Empatadas: " << empatadas << endl;
            cout << "Puntos: " << puntos << endl;
            cout << "--------------------------" << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Jugador no encontrado." << endl;
    }

    archivo.close();
    pausa();
}

void juegoFinal()
{
    int seguir = 0;
    limpiarPantalla();
    llenarTablero();

    if (buscarGanadorHorizontal(ultimaPosicion, coordenada, simbolo) || buscarGanadorVertical(ultimaPosicion, coordenada, simbolo) || buscarDiagonal2(ultimaPosicion, coordenada, simbolo) || buscarDiagonal1(ultimaPosicion, coordenada, simbolo))
    {
        mostrarMensajeGanador(simbolo);
        return;
    }

    if (simbolo == 'X')
    {
        simbolo = 'O';
    }
    else
    {
        simbolo = 'X';
    }

    cout << "\n¿En qué columna quiere colocar su ficha?: ";
    cin >> posicionColumna;
    if (posicionColumna > 9 || posicionColumna < 1)
    {
        cout << "\n¡Valor ingresado no válido!\n";
        cout << "\n¿En qué columna quiere colocar su ficha?: ";
        cin >> posicionColumna;
    }
    else
    {
        coordenada = posicionColumna - 1;
        colocarFicha();
    }
    partidaRapida();
}
