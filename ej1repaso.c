#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo
{
    Tarea T;
    Nodo *Siguiente;
} typedef Nodo;

/*1) Desarrolle una interfaz de carga de tareas para solicitar tareas pendientes, en la cual se
solicite descripción y duración de la misma (el id debe ser generado automáticamente por
el sistema, de manera autoincremental comenzando desde el número 1000). Al cabo de
cada tarea consulte al usuario si desea ingresar una nueva tarea o finalizar la carga.*/

int generarId(int id);
Nodo *crearNodo(Tarea *tarea);
void insertarTareaPend(Nodo **ListaPendientes, Tarea tareaPendiente);

int main()
{
    int opc;
    
    Nodo *listaTareasPendientes = NULL;
    Nodo *listaTareasRealizadas = NULL;
    Tarea tarea;

    printf("========================SELECCIONE UNA OPCION========================");
    printf("\n");
    printf("1 | Cargar Tarea Pendiente\n");
    scanf("%d", &opc);

    switch (opc)
    {
    case 1:
        insertarTareaPend(&listaTareasPendientes, tarea);

        break;
    
    default:
        break;
    }

    return 0;
}

int generarId(int id)
{
    int aux = 1000;
    int idGenerado;

    if (id > 1000)
    {
        idGenerado = id + 1;
    }
    else
    {
        idGenerado = aux;
    }
    

    return idGenerado;
}

Nodo *crearNodo(Tarea *tarea)
{
    char desc[100];
    int duracion = 0;
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    
    printf("Ingrese la Descripción de la Tarea: \n");
    scanf("%s", &desc);
    nodo->T.Descripcion = (char *)malloc(strlen(desc) + 1);
    strcpy(nodo->T.Descripcion, desc);
    
    nodo->T.TareaID = generarId(nodo->T.TareaID);
    
    printf("Ingrese la Duración de la Tarea (entre 10 y 100): ");
    scanf("%d", &duracion);
    if (duracion >= 10 || duracion <= 100)
    {
        nodo->T.Duracion = duracion;
    }
    else
    {
        printf("La duracion debe ser entre 10 y 100. Ingrese nuevamente");
    }
    
    nodo->Siguiente = NULL;

    return nodo;
}

void insertarTareaPend(Nodo **ListaPendientes, Tarea tareaPendiente)
{
    Nodo *nuevaTareaPend = crearNodo(&tareaPendiente);
    nuevaTareaPend->Siguiente = *ListaPendientes;
    *ListaPendientes = nuevaTareaPend;
}
