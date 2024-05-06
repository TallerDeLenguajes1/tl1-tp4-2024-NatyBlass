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

Nodo *CrearNodo(int tID, const char *descripcion, int duracion);
void insertarTarea(Nodo **lista, Tarea tarea);
void cargarTarea(Nodo **tareaPendiente, int *ID);
void moverTarea(Nodo **tareaPendiente, Nodo **TareaRealizada, int ID);
void listarTareas(Nodo *lista, char *tipoTarea);
void consultarTarea(Nodo *tareaPendiente, Nodo *tareaRealizada, int ID);

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

Nodo *CrearNodo(int tID, const char *descripcion, int duracion) 
{
    Nodo *nodo = malloc(sizeof(Nodo));
    if (!nodo) {
        printf("No se pudo asignar memoria.\n");
        exit(1);
    }
    nodo->T.TareaID = tID;
    nodo->T.Descripcion = malloc(strlen(descripcion) + 1); // Asignar memoria para la descripción
    strcpy(nodo->T.Descripcion, descripcion);
    nodo->T.Duracion = duracion;
    nodo->Siguiente = NULL;
    return nodo;
}

void insertarTarea(Nodo **lista, Tarea tarea) 
{
    Nodo *nuevoNodo = CrearNodo(tarea.TareaID, tarea.Descripcion, tarea.Duracion);
    nuevoNodo->Siguiente = *lista;
    *lista = nuevoNodo;
}

void cargarTarea(Nodo **tareaPendiente, int *ID) {
    char desc[100];
    int duracion;
    Tarea nuevaTarea;

    while (1) 
    {
        printf("===========================================\n");
        printf("Ingrese descripción de la tarea: ");
        scanf("%s", &desc);

        printf("Ingrese duración de la tarea (del 10 al 100): ");
        scanf("%d", &duracion);

        while (duracion < 10 || duracion > 100) {
            printf("Duración inválida. Debe estar entre 10 y 100.\n");
            printf("Ingrese duración de la tarea (del 10 al 100): ");
            scanf("%d", &duracion);
        }

        nuevaTarea.TareaID = *ID;
        nuevaTarea.Descripcion = malloc(strlen(desc) + 1);
        strcpy(nuevaTarea.Descripcion, desc);
        nuevaTarea.Duracion = duracion;

        insertarTarea(tareaPendiente, nuevaTarea);
        (*ID)++;

        int ingTarea;
        printf("¿Desea ingresar otra tarea? 1 = SI || 0 = NO\n");
        scanf("%d", &ingTarea);
        if (ingTarea == 0) {
            break;
        }
    }
}

void moverTarea(Nodo **tareaPendiente, Nodo **TareaRealizada, int ID) 
{
    Nodo *anterior = NULL;
    Nodo *actual = *tareaPendiente;

    while (actual && actual->T.TareaID != ID) //busco la tarea
    {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if (actual) // si encuentro la tarea
    {
        
        if (anterior) // se elimina ded pendientes
        {
            anterior->Siguiente = actual->Siguiente;
        } 
        else 
        {
            *tareaPendiente = actual->Siguiente;
        }

        actual->Siguiente = *TareaRealizada; // la inserto en realizadas
        *TareaRealizada = actual;

        printf("Tarea ID %d movida a la lista de tareas realizadas.\n", ID);
    } 
    else 
    {
        printf("No se encontró la tarea con ID %d.\n", ID);
    }
}

void listarTareas(Nodo *lista, char *tipoTarea) 
{
    Nodo *actual = lista;
    
    printf("\nLista de %s:\n", tipoTarea);
    while (actual) 
    {
        printf("ID: %d\n",actual->T.TareaID);
        printf("Descripción: %s\n", actual->T.Descripcion);
        printf("Duración: %d\n", actual->T.Duracion);
        
        actual = actual->Siguiente;
    }
    printf("\n");
}

void consultarTarea(Nodo *tareaPendiente, Nodo *tareaRealizada, int ID) 
{
    Nodo *actual = tareaPendiente;
    while (actual) {
        if (actual->T.TareaID == ID) {
            printf("Tarea encontrada en tareas pendientes:\n");
            printf("ID: %d, Descripción: %s, Duración: %d\n",
                   actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
            return;
        }
        actual = actual->Siguiente;
    }

    actual = tareaRealizada;
    while (actual) {
        if (actual->T.TareaID == ID) {
            printf("Tarea encontrada en tareas realizadas:\n");
            printf("ID: %d, Descripción: %s, Duración: %d\n",
                   actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
            return;
        }
        actual = actual->Siguiente;
    }

    printf("No se encontró la tarea con ID %d.\n", ID);
}
