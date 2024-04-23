#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea{
    int TareaID; // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *CrearNodo(int tID, char *descripcion, int duracion);
void insertarTarea(Nodo **lista, Tarea tarea);
void cargarTarea(Nodo **tareaPendiente, int *ID);
void moverTarea(Nodo **tareaPendiente, Nodo **TareaRealizada, int *ID);


int main()
{
    int opc = 0, ultID = 1000, id;
    Nodo *TareasPendientes = NULL;
    Nodo *TareasRealizadas = NULL;

    printf("==========OPCIONES==========\n");
    printf("1 - Cargar Tareas Pendientes\n");;
    printf("2 - Mover tarea de pendientes a realizadas\n");
    printf("3 - Listar todas las tareas pendientes y realizadas\n");
    printf("4 - Consultar tarea por ID\n");
    printf("=============================\n");
    printf("Ingrese la opcion que quiere llevar a cabo:\n");
    scanf("%d", &opc);
    
    switch (opc)
    {
    case 1:
        cargarTarea(&TareasPendientes, &ultID);
        break;
    case 2:
        printf("Ingrese el ID de la tarea a mover de pendientes a realizadas: ");
        scanf("%d", &id);
        moverTarea(&TareasPendientes, &TareasRealizadas, id);
        break;
                
    case 3:
        listarTareas(TareasPendientes, "Tareas pendientes");
        listarTareas(TareasRealizadas, "Tareas realizadas");
        break;
                
    case 4:
        printf("Ingrese el ID de la tarea a consultar: ");
        scanf("%d", &id);
        consultarTarea(TareasPendientes, TareasRealizadas, id);
        
        break;
                
    default:
        printf("Opcion no valida\n");
        break;
    }

}

Nodo *CrearNodo(int tID, char *descripcion, int duracion) {
    Nodo *nodo = malloc(sizeof(Nodo));
    nodo->T.TareaID = tID;
    nodo->T.Descripcion = strcpy(nodo->T.Descripcion, descripcion);
    nodo->T.Duracion = duracion;
    nodo->Siguiente = NULL;
    return nodo;
}

void insertarTarea(Nodo **lista, Tarea tarea) {
    Nodo *nuevoNodo = CrearNodo(tarea.TareaID, tarea.Descripcion, tarea.Duracion);
    nuevoNodo->Siguiente = *lista;
    *lista = nuevoNodo;
}

void cargarTarea(Nodo **tareaPendiente, int *ID)
{
    char desc[100];
    int duracion, ingTarea = 1;
    Tarea nuevaTarea;
        
    while(ingTarea != 0)
    {
        printf("===========================================\n");
        printf("Ingrese descripcion de la tarea: ");
        fflush(stdin);
        gets(desc);
        printf("Ingrese duracion de la tarea (del 10 al 100):\n");
        scanf("%d", &duracion);
        if (duracion < 10 || duracion > 100)
        {
            printf("La tarea debe durar entre 10 y 100\n");
            printf("Ingrese duracion de la tarea (del 10 al 100):\n");
            scanf("%d", &duracion);
        }

        nuevaTarea.TareaID = *ID;
        nuevaTarea.Descripcion = strcpy(nuevaTarea.Descripcion, desc);
        nuevaTarea.Duracion = duracion;
        
        Nodo *nuevoNodo = CrearNodo(*ID, desc, duracion);
        InsertarNodo(tareaPendiente, nuevoNodo);

        printf("===========================================\n");
        printf("Desea ingresar otra tarea? 1 = SI || 0 = NO\n");
        scanf("%d", &ingTarea);
    }
}

void moverTarea(Nodo **tareaPendiente, Nodo **TareaRealizada, int *ID)
{
    Nodo *nodoAMover = BuscarNodo(tareaPendiente, ID);
    if (nodoAMover)
    {
        EliminarNodo(tareaPendiente, ID);
        InsertarNodo(TareaRealizada, nodoAMover);
    }
}

