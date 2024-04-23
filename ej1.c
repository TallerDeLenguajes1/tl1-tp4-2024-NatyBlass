#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct{
    Tarea T;
    Nodo *Siguiente;
}typedef Nodo;

Nodo *CrearNodo(int tID, char *descripcion, int duracion);
void insertarTarea(Nodo **lista, Tarea tarea);
void cargarTarea(Nodo **tareaPendiente, int *ID);

int main()
{
    int opc = 0, ultID = 1000;
    Nodo *TareasPendientes = NULL;
    Nodo *TareasaRealizadas = NULL;

    printf("==========OPCIONES==========\n");
    printf("1 - Cargar Tareas Pendientes\n");

    printf("=============================\n");
    printf("Ingrese la opcion que quiere llevar a cabo:\n");
    scanf("%d", &opc);
    
    switch (opc)
    {
    case 1:
        cargarTarea(&TareasPendientes, &ultID);
        break;
    
    default:
        break;
    }

}

Nodo *CrearNodo(int tID, char *descripcion, int duracion) {
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->T.TareaID= tID;
    nodo->T.Descripcion = strdup(descripcion);
    nodo->T.Duracion = duracion;
    nodo->Siguiente = NULL;
    return nodo;
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
