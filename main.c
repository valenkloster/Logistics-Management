#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                /*ESTRUCTURAS*/
typedef struct Pedidos //estructura para los pedidos
{
    char RazonSocial[20], Producto[20], Servicio[20];
    int CantProduct; //chequear stock
    float TotalPagar;
    float CostoTotal; //para la empresa metalurgica
    struct Pedidos* siguiente;
}NodoPedidos;
struct Direccion
{
    char Calle[20];
    int Altura, CP, Piso;
    char Depto;
};

struct FechaUltCompra
{
    int Dia, Mes, Anio;
};
typedef struct //estructura para guardar los datos de los clientes
{
    char Nombre[20], Apellido[20];
    struct Direccion direccion; //estructura anidada
    struct FechaUltCompra fecha_ult_compra; //estructura anidada
}Clientes;

typedef struct //estructura para guardar los datos de los productos
{
    char Nombre[20], Descripcion[50];
    int Stock;
    float Costo; //lo que le cuesta a la empresa metalurgica comprarlo o fabricarlo
    float PrecioTotal;
}Productos;

typedef struct //estructura para guardar los datos de los servicios
{
    char Nombre[20], Descripcion[50];
    float CostoHora, CantidadHorasBrindar;
    float PrecioTotal; //cálculo automático entre el costo y la cantidad de horas a brindar
    int porcentaje;
}Servicios;
                /*ESTRUCTURAS*/


             /*PROTOTIPOS FUNCIONES*/
void IngresarClientes (Clientes c);
void IngresarServicios (Servicios s);
void IngresarProductos (Productos p);

NodoPedidos *crearNodoPedidos(Productos p, Servicios s);
void inserFinalPedidos (NodoPedidos **cabezaPedidos, Productos p, Servicios s);
void ResumenDiario (NodoPedidos **cabeza);

void ImprimirLista(NodoPedidos **cabeza);
             /*PROTOTIPOS FUNCIONES*/


             /*ARCHIVOS*/
FILE *ArchivoProductos = NULL;
char *NombreArchivoProductos = "Productos.txt";

FILE *ArchivoServicios = NULL;
char *NombreArchivoServicios = "Servicios.txt";
             /*ARCHIVOS*/
int main()
{
    //Creamos el puntero que apuntara al primer nodo de la lista enlazada simple que contiene los Pedidos.
    NodoPedidos *cabezaPedidos = NULL;

    /*Variables*/
    Clientes c;
    Servicios s;
    Productos p;
    int opcion;
    /*Variables*/

    do
    {
        system("cls"); //limpiamos pantalla
        printf("\t\t\t\tMENU DE OPCIONES\n"); //imprimimos menu de opciones en pantalla
        printf("\t1) Ingresar Nuevos Clientes\n\t2) Ingresar Productos\n\t3) Ingresar Servicios\n\t4) Gestion de Compras\n\t5) Salir");
        printf("\n\nIngrese la opcion deseada: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            IngresarClientes(c); //llamamos a la funcion ingresar clientes
            break;

        case 2:
            IngresarProductos(p); //llamamos a la funcion ingresar productos
            break;

        case 3:
            IngresarServicios(s); //llamamos a la funcion ingresar servicios
            break;

        case 4:
            system("cls"); //limpiamos pantalla
            printf("\t\t\t\tSUB-MENU DE OPCIONES\n"); //imprimimps el sub menu de opciones
            printf("\n\t1) Tomar Pedido\n\t2) Imprimir Resumen Diario\n\t3) Volver al Menu Principal");
            printf("\n\nIngrese la opcion deseada: ");
            scanf("%d", &opcion);
            switch (opcion)
            {
            case 1:
                inserFinalPedidos(&cabezaPedidos, p, s); //registramos el pedido
                break;

            case 2:
                ResumenDiario(&cabezaPedidos); //llamamos a la funcion que se encarga de imprimir el resumen diario
                break;
            case 3:
                main();
                break;
            }
        }
    } while (opcion!=5);

    printf("\n\tFin del dia, adios!!\n");
    return 0;
}
//Esta funcion se encargará de cargar los clientes que el empleado ingrese y los guardara en un archivo de texto
void IngresarClientes (Clientes c)
{
    //Creamos el archivo de texto donde guardaremos los datos del cliente
    FILE *ArchivoClientes = NULL;
    char *nombrearchivo = "Clientes.txt";

    system("cls");

    //Tomamos los datos del cliente
    printf("Datos del cliente:\n");
    printf("Nombre: ");
    fflush(stdin);
    gets( c.Nombre);
    printf("\nApellido: ");
    fflush(stdin);
    gets( c.Apellido);
    printf("\nDireccion:\n\t");
    printf("Calle: ");
    fflush(stdin);
    gets( c.direccion.Calle);
    printf("\n\tAltura: ");
    scanf("%d", &c.direccion.Altura);
    printf("\n\tCP: ");
    scanf("%d", &c.direccion.CP);
    printf("\n\tPiso: ");
    scanf("%d", &c.direccion.Piso);
    printf("\n\tDepartamento: ");
    fflush(stdin);
    scanf("%c", &c.direccion.Depto);
    printf("\nFecha Ultima Compra: ");
    printf("\n\tDia: ");
    scanf("%d", &c.fecha_ult_compra.Dia);
    printf("\n\tMes: ");
    scanf("%d", &c.fecha_ult_compra.Mes);
    printf("\n\tAnio: ");
    scanf("%d", &c.fecha_ult_compra.Anio);

    ArchivoClientes = fopen(nombrearchivo, "a"); //abrimos el archivo de texto en modo append
    if (ArchivoClientes == NULL) //corroboramos
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }
    else
    {
        //imprimimos la informacion en el archivo
        fprintf(ArchivoClientes, "Nombre y Ampellido: %s %s", c.Nombre, c.Apellido);
        fprintf(ArchivoClientes, "\nDireccion:\n\tCalle:%s", c.direccion.Calle);
        fprintf(ArchivoClientes, "\n\tAltura: %d", c.direccion.Altura);
        fprintf(ArchivoClientes, "\n\tCP:%d", c.direccion.CP);
        fprintf(ArchivoClientes, "\n\tPiso:%d", c.direccion.Piso);
        fprintf(ArchivoClientes, "\n\tDepto:%c", c.direccion.Depto);
        fprintf(ArchivoClientes, "\nFecha ultima compra: %d - %d - %d\n", c.fecha_ult_compra.Dia, c.fecha_ult_compra.Mes, c.fecha_ult_compra.Anio);
        fputc('\n', ArchivoClientes); //salto
        fclose(ArchivoClientes); //cierro archivo
        printf("\nDatos del cliente cargados correctamente!\n");
        system("pause"); //agrego una pausa
    }

}
//Esta funcion se encarga tomar y guardar la informacion de los productos en la estructura Productos y cargarlas en el archivo de texto correspondinte
void IngresarProductos (Productos p)
{
    system("cls");

    //Guardamos los datos del producto en la estructura Productos
    printf("Datos del Producto:\n");
    printf("Nombre: ");
    fflush(stdin);
    gets( p.Nombre);
    printf("\nDescripcion: ");
    fflush(stdin);
    gets( p.Descripcion);
    printf("\nCantidad en Stock: ");
    scanf("%d", &p.Stock);
    printf("\nCosto: ");
    scanf("%f", &p.Costo);
    printf("\nPrecio Total: ");
    scanf("%f", &p.PrecioTotal);

    //realizamos una comparacoin del costo y el precio para identificar si generan perdiadas o ganancias
    if (p.Costo == p.PrecioTotal)
    {
        printf("\nEl producto no genera ganancias ni perdidas");
    }
    else if (p.Costo > p.PrecioTotal)
    {
        printf("\nEl producto genera perdidas");
    }
    else
    {
        printf("\nEl producto genera ganancias");
    }


    ArchivoProductos = fopen(NombreArchivoProductos, "a"); //abrimos el archivo de los productos en modo append para que no se sobreescriba la informacion
    if (ArchivoProductos == NULL) //corroboramos
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }
    else
    {
        //imprimimos la informacion en el archivo
        fprintf(ArchivoProductos, "%s", p.Nombre);
        fprintf(ArchivoProductos, "\n%s", p.Descripcion);
        fprintf(ArchivoProductos, "\n%d", p.Stock);
        fprintf(ArchivoProductos, "\n%f", p.Costo);
        fprintf(ArchivoProductos, "\n%f\n", p.PrecioTotal);
        fputc('\n', ArchivoProductos); //imprimimos espacio
        fclose(ArchivoProductos); //cerramos archivo
        printf("\n\nDatos del producto correctamente!\n");
        system("pause"); //agragamos una pausa
    }
}

//Esta funcion se encarga tomar y guardar la informacion de los servicios en la estructura Servicios y cargarlas en el archivo de texto correspondinte
void IngresarServicios (Servicios s)
{
    system("cls");

    //guardamos infromacion de los servicios
    printf("Datos del Servicio:\n");
    printf("Nombre: ");
    fflush(stdin);
    gets( s.Nombre);
    printf("\nDescripcion: ");
    fflush(stdin);
    gets( s.Descripcion);
    printf("\nCosto por Hora: ");
    scanf("%f", &s.CostoHora);
    printf("\nCantidad de Horas a Brindar: ");
    scanf("%f", &s.CantidadHorasBrindar);
    s.PrecioTotal = s.CostoHora * s.CantidadHorasBrindar; //calculamos el precio total multiplicando el costo por la cantidad de horas a brindar

    printf("\nIngrese el porcentaje de ganancia: ");
    scanf("%d", &s.porcentaje);
    s.porcentaje = (s.porcentaje * s.PrecioTotal)/100; //calculamos el porcentaje en base al precio total
    s.PrecioTotal = s.PrecioTotal + s.porcentaje; //sumamos la diferencia calculada al precio total

    ArchivoServicios = fopen(NombreArchivoServicios, "a"); //abrimos archivo en modo append
    if (ArchivoServicios == NULL) //corroboramos
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }
    else
    {
        //imprimimos la estructura de servicios en el archivo
        fprintf(ArchivoServicios, "%s", s.Nombre);
        fprintf(ArchivoServicios, "\n%s", s.Descripcion);
        fprintf(ArchivoServicios, "\n%f", s.CostoHora);
        fprintf(ArchivoServicios, "\n%f", s.CantidadHorasBrindar);
        fprintf(ArchivoServicios, "\n%f\n", s.PrecioTotal);
        fputc('\n', ArchivoServicios); //salto de linea
        fclose(ArchivoServicios); //cerramos archivo
        printf("\nDatos del servicios correctamente!\n");
        system("pause"); //agregamos una pausa
    }
}
//Esta funcion se encarga de registrar un pedido y guardar los datos en un nodo que formara parte de la lista enlazada simple de los pedidos
NodoPedidos *crearNodoPedidos(Productos p, Servicios s)
{
           /*VARIABLES*/
    FILE *Archivo_Aux = NULL; //archivo auxiliar que usaremos para ir guardando los datos e ir modificandolos en caso de que sea necesario. Luego, mandaremos los datos modificados al archivo de texto correspondiente
    char *nombreArchivoAux = "ArchivoAux.txt";

    int flagProduct = 0, flagServicios = 0; //flags con las cuales verificamos que se encontró el producto o servicio deseado
    int Stock = 0; //stock es un flag para verificar si hay suficiente stock del producto ingresado por teclado
    int len; //variable de tipo int que va a almacenar el largo de las cadenas
          /*VARIABLES*/


    NodoPedidos *a; //creo puntero a del tipo nodo
    a = (NodoPedidos*)malloc(sizeof(NodoPedidos)); //pido espacio en memoria dinamica de tamaño NodoPedidos
    if (a == NULL) //verifico que se haya asigando correctamente la memoria
    {
        printf("La memoria no se asigno correctamente\n");
        return 0;
    }
    else
    {
        //pedimos los datos del pedido
        printf("\nIngrese los datos del Pedido: \n");
        printf("\tRazon Social del cliente: ");
        fflush(stdin);
        gets( a->RazonSocial);
        printf("\n\tNombre del Producto: ");
        fflush(stdin);
        gets( a->Producto);
        //cada vez que guardabamos un string, al final se agregaba automaticamente un '\n' por lo que investigando en internet encontramos la siguiente forma de resolverlo
        len = strlen( a->Producto); //guardamos el largo de la cadena
        if( a->Producto[len-1] == '\n' ) //si el ultimp cadracter es '\n' lo eliminamos
        a->Producto[len-1] = 0;

        printf("\n\tCantidad del Producto: ");
        scanf("%d", &a->CantProduct);
        printf("\n\tNombre del Servicio: ");
        fflush(stdin);
        gets( a->Servicio);
        a->CostoTotal = 0; //inicializamos en 0 para evitar residuos
        a->TotalPagar = 0; //inicializamos en 0 para evitar residuos

        //abrimos el archivo de texto de los Productos en modo lectura para poder verificar la existencia de los productos y el stock del mismo
        ArchivoProductos = fopen(NombreArchivoProductos, "r");
        if (ArchivoProductos == NULL) //corroboramos que la apertura del archivo se haya realizado correctamente
        {
            printf("Error al abrir el archivo\n");
            return 0;
        }
        else
        {
            Archivo_Aux = fopen(nombreArchivoAux, "w"); //abrimos el archivo auxiliar donde guardaremos los datos momentaneamente
            if (ArchivoProductos == NULL) //verificamos
            {
                printf("Error al abrir el archivo\n");
                return 0;
            }
            else
            {
                rewind(ArchivoProductos); //llevamos el cursor hacia el inicio del archivo para poder empezar a recorrerlo

                /*guardamos informacion del archivo en estructura pedidos*/
                fgets(p.Nombre , 20, ArchivoProductos);
                //cada vez que guardabamos un string, al final se agregaba automaticamente un '\n' por lo que investigando en internet encontramos la siguiente forma de resolverlo
                len = strlen( p.Nombre); //guardamos lo que te devuelve la funcion strlen en la variable len
                if( p.Nombre[len-1] == '\n' ) //borramos el '\n' de la palabra
                p.Nombre[len-1] = 0;

                fgets(p.Descripcion , 50, ArchivoProductos);
                //repetimos proceso
                len = strlen( p.Descripcion);
                if( p.Descripcion[len-1] == '\n' )
                p.Descripcion[len-1] = 0;
                fscanf(ArchivoProductos, "%d" , &p.Stock);
                fscanf(ArchivoProductos, "%f" , &p.Costo);
                fscanf(ArchivoProductos, "%f" , &p.PrecioTotal);
                fgetc(ArchivoProductos); //leemos salto de linea
                fgetc(ArchivoProductos); //leemos salto de linea

                do //recorremos el archivo de texto con un do-while
                {
                   if (flagProduct == 0) // en caso de que encuentre este producto no va a comparar mas
                   {
                        if(strcmp(a->Producto, p.Nombre) == 0) //verificamos si el producto del archivo coincide con el producto pedido por el cliente, en el caso de que lo haga ingresa al if
                        {
                            flagProduct++; //incrementamos el flagProduct

                            //Corroboramos el stock a traves de una comparación. En caso de que haya stock ingresa al if
                            if (a->CantProduct <= p.Stock)
                            {
                                printf("\nHay Stock suficiente\n"); //imprimimos mensaje en pantalla
                                system("pause"); //agregamos una pausa
                                a->TotalPagar = p.PrecioTotal; //guardamos el precio del producto
                                a->TotalPagar = a->TotalPagar * a->CantProduct; //multiplicamos el precio del producto por la cantidad que pidio el cliente y lo guardo en el totalPagar
                                a->CostoTotal = p.Costo; //guardo el costo del producto para luego poder imprimir el resumen diario
                                p.Stock = p.Stock - a->CantProduct; //modificamos el stock de la estructura que luego imprimiremos en el archivo
                                Stock++; //incrementamos la variable stock en 1
                            }
                            else
                            {
                                printf("\nNo hay stock suficiente\n"); //imprimimos mensaje en pantalla
                                system("pause"); //agregamos una pausa
                            }
                        }
                   }
                   //mandamos la informacion al archivo aux
                    fprintf(Archivo_Aux, "%s", p.Nombre);
                    fprintf(Archivo_Aux, "\n%s", p.Descripcion);
                    fprintf(Archivo_Aux, "\n%d", p.Stock);
                    fprintf(Archivo_Aux, "\n%f", p.Costo);
                    fprintf(Archivo_Aux, "\n%f\n", p.PrecioTotal);
                    fputc('\n', Archivo_Aux); //imprimimos espacio


                    //leemos nuevamente la informacion del archivo y la guardamos en estructura producto
                    fgets(p.Nombre , 20, ArchivoProductos);
                    //repetimos proceso para borrar el '\n' del final del string
                    len = strlen( p.Nombre); //guardamos lo que te devuelve la funcion strlen en la variable len2
                    if( p.Nombre[len-1] == '\n' ) //borramos el '\n' de la palabra
                    p.Nombre[len-1] = 0;

                    fgets(p.Descripcion , 50, ArchivoProductos);
                    len = strlen( p.Descripcion);
                    if( p.Descripcion[len-1] == '\n' )
                    p.Descripcion[len-1] = 0;
                    fscanf(ArchivoProductos, "%d" , &p.Stock);
                    fscanf(ArchivoProductos, "%f" , &p.Costo);
                    fscanf(ArchivoProductos, "%f" , &p.PrecioTotal);
                    fgetc(ArchivoProductos); //leemos salto de linea
                    fgetc(ArchivoProductos); //leemos salto de linea

                } while(!feof(ArchivoProductos)); //recorre el archivo hasta el final

                fclose(ArchivoProductos); //cerramos el archivo de Productos
                fclose(Archivo_Aux); //cerramos el archivo Auxiliar


                ArchivoServicios = fopen(NombreArchivoServicios, "r"); //abrimos el archivo que contiene los datos de los servicios en modo lectura
                if (ArchivoServicios == NULL) //verificamos
                {
                     printf("Error al abrir el archivo\n");
                     return 0;
                }
                else
                {
                     rewind(ArchivoServicios); //llevamos el cursor hacia el inicio del archivo para poder empezar a recorrerlo

                    //leemos la informacion del archivo y la guardamos en estructura servicios
                    fgets(s.Nombre , 20, ArchivoServicios);
                    //cada vez que guardabamos un nombre al final se agregaba automaticamente un \n por lo que investigando en internet encontramos esta forma de resolverlo
                    len = strlen( s.Nombre); //guardamos lo que te devuelve la funcion strlen en la variable len
                    if( s.Nombre[len-1] == '\n' ) //borramos el '\n' de la palabra
                    s.Nombre[len-1] = 0;

                    fgets(s.Descripcion , 50, ArchivoServicios);
                    len = strlen( s.Descripcion);
                    if( s.Descripcion[len-1] == '\n' )
                    s.Descripcion[len-1] = 0;
                    fscanf(ArchivoServicios, "%f" , &s.CostoHora);
                    fscanf(ArchivoServicios, "%f" , &s.CantidadHorasBrindar);
                    fscanf(ArchivoServicios, "%f" , &s.PrecioTotal);
                    fscanf(ArchivoServicios, "%d" , &s.porcentaje);
                    fgetc(ArchivoServicios); //leemos salto de linea
                    fgetc(ArchivoServicios); //leemos salto de linea

                    do
                    {
                        if (strcmp(a->Servicio, s.Nombre) == 0)
                        {
                            //le sumo los costos y ganancias de la empresa al nodo de pedidos e incremento el flag de servicios en uno
                            a->CostoTotal = a->CostoTotal + s.CostoHora;
                            a->TotalPagar = a->TotalPagar + s.PrecioTotal;
                            flagServicios++;
                        }
                        else
                        {
                            //leemos la informacion del archivo y la guardamos en estructura servicios
                            fgets(s.Nombre , 20, ArchivoServicios);
                            //cada vez que guardabamos un nombre al final se agregaba automaticamente un \n por lo que investigando en internet encontramos esta forma de resolverlo
                            len = strlen( s.Nombre); //guardamos lo que te devuelve la funcion strlen en la variable len
                            if( s.Nombre[len-1] == '\n' ) //borramos el '\n' de la palabra
                            s.Nombre[len-1] = 0;

                            fgets(s.Descripcion , 50, ArchivoServicios);
                            int len;
                            len = strlen( s.Descripcion);
                            if( s.Descripcion[len-1] == '\n' )
                            s.Descripcion[len-1] = 0;
                            fscanf(ArchivoServicios, "%f" , &s.CostoHora);
                            fscanf(ArchivoServicios, "%f" , &s.CantidadHorasBrindar);
                            fscanf(ArchivoServicios, "%f" , &s.PrecioTotal);
                            fscanf(ArchivoServicios, "%d" , &s.porcentaje);
                            fgetc(ArchivoServicios); //leemos salto de linea
                            fgetc(ArchivoServicios); //leemos salto de linea
                        }
                    } while(!feof(ArchivoServicios)); //hasta llegar al final del archivo
                    fclose(ArchivoServicios); //cerramos archivo
                }

                if ((flagProduct == 0) && (flagServicios == 0)) //si no coinciden ni el producto ni el servicio
                {
                    printf("\nEse servicio y ese producto no se encuentra en la lista\n"); //imprimimos mensaje en pantalla
                    system("pause");
                }
                else if (flagServicios == 0) //si no existe ese servicio
                {
                    printf("\nEse servicio no se encuentra en la lista\n");//imprimimos mensaje en pantalla
                    system("pause");
                }
                else
                {
                    if(flagProduct == 0) //si no se encontró el producto
                    {
                        printf("\nEse producto no se encuentra en la lista\n");//imprimimos mensaje en pantalla
                        system("pause");
                    }
                    else if (Stock != 0) //si se contro el producto y habia stock
                    {
                        ArchivoProductos = fopen(NombreArchivoProductos, "w"); //abrimos el archivo en modo w para imprimir la informacion modificada
                        if (ArchivoProductos == NULL)//verificamos
                        {
                            printf("Error al abrir el archivo\n");
                            return 0;
                        }
                        else
                        {
                            Archivo_Aux = fopen(nombreArchivoAux, "r"); //abrimos el archivo auxiliar donde guardaremos los datos momentaneamente en modo lectura
                            if (ArchivoProductos == NULL) //verificamos
                            {
                                printf("Error al abrir el archivo\n");
                                return 0;
                            }
                            else
                            {
                                //leemos la informacion del archivo Aux y la guardamos en estructura productos, luego la mandamos al archivo productos
                                fgets(p.Nombre , 20, Archivo_Aux);
                                //cada vez que guardabamos un nombre al final se agregaba automaticamente un \n por lo que investigando en internet encontramos esta forma de resolverlo
                                len = strlen( p.Nombre); //guardamos lo que te devuelve la funcion strlen en la variable len
                                if( p.Nombre[len-1] == '\n' ) //borramos el '\n' de la palabra
                                p.Nombre[len-1] = 0;

                                fgets(p.Descripcion , 50, Archivo_Aux);
                                len = strlen( p.Descripcion);
                                if( p.Descripcion[len-1] == '\n' )
                                p.Descripcion[len-1] = 0;
                                fscanf(Archivo_Aux, "%d" , &p.Stock);
                                fscanf(Archivo_Aux, "%f" , &p.Costo);
                                fscanf(Archivo_Aux, "%f" , &p.PrecioTotal);
                                fgetc(Archivo_Aux); //leemos salto de linea
                                fgetc(Archivo_Aux); //leemos salto de linea

                                do
                                {
                                    //imprimimos informacion en archivo productos
                                    fprintf(ArchivoProductos, "%s", p.Nombre);
                                    fprintf(ArchivoProductos, "\n%s", p.Descripcion);
                                    fprintf(ArchivoProductos, "\n%d", p.Stock);
                                    fprintf(ArchivoProductos, "\n%f", p.Costo);
                                    fprintf(ArchivoProductos, "\n%f\n", p.PrecioTotal);
                                    fputc('\n', ArchivoProductos); //imprimimos espacio

                                    //volvemos a leer los datos del archivo auxiliar
                                    fgets(p.Nombre , 20, Archivo_Aux);
                                    //cada vez que guardabamos un nombre al final se agregaba automaticamente un \n por lo que investigando en internet encontramos esta forma de resolverlo
                                    len = strlen( p.Nombre); //guardamos lo que te devuelve la funcion strlen en la variable len
                                    if( p.Nombre[len-1] == '\n' ) //borramos el '\n' de la palabra
                                    p.Nombre[len-1] = 0;

                                    fgets(p.Descripcion , 50, Archivo_Aux);
                                    len = strlen( p.Descripcion);
                                    if( p.Descripcion[len-1] == '\n' )
                                    p.Descripcion[len-1] = 0;
                                    fscanf(Archivo_Aux, "%d" , &p.Stock);
                                    fscanf(Archivo_Aux, "%f" , &p.Costo);
                                    fscanf(Archivo_Aux, "%f" , &p.PrecioTotal);
                                    fgetc(Archivo_Aux); //leemos salto de linea
                                    fgetc(Archivo_Aux); //leemos salto de linea

                                } while (!feof(Archivo_Aux)); //hasta que llegue al final del archivo auxiliar
                                fclose(Archivo_Aux); //cerramos archivo
                                fclose(ArchivoProductos); //cerramos archivo
                            }
                        }
                     }
                }
           }

    }
    if (((flagProduct !=0) && (Stock != 0)) || (flagServicios !=0)) //si el producto fue encontrado y ademas hay stock o si el servicio existe
    {
        a->siguiente = NULL; //el puntero lo inicializo en NULL
        return a; //retorno el puntero
    }
    else //si no no se toma el pedido
    {
        //pongo las variables de costo y de precio total en cero para que cuando se imprima el resumen diario no se tomen en cuenta
        a->CostoTotal = 0;
        a->TotalPagar = 0;

        a->siguiente = NULL; //el puntero lo inicializo en NULL
        return a; //retorno el puntero
    }
}
}

void inserFinalPedidos (NodoPedidos **cabezaPedidos, Productos p, Servicios s)
{
    NodoPedidos *ultimo; //creo un puntero de tipo nodo
    ultimo = *cabezaPedidos; //ultimo va apuntar al mismo lugar que cabeza, es decir, al primer elemento

    if (ultimo == NULL) //si ultimo es NULL significa que la lista esta vacia
    {
        *cabezaPedidos = crearNodoPedidos(p, s); //creo el nodo
    }
    else
    {
      for (;ultimo ->siguiente;)   //recorro hasta llegar al nodo que apunta a null
      ultimo=ultimo->siguiente;
      ultimo->siguiente = crearNodoPedidos(p, s); //creo un nuevo nodo y hago que el ultimo nodo apunte a ese nuevo
    }
}

//Esta funcion se encarga de imprimir los gastos y ganancias del dia de la empresa metalurgica
void ResumenDiario (NodoPedidos **cabeza)
{
    NodoPedidos *nAux = *cabeza; //utilizamos un punero auxiliar para recorrer la lista enlazada
    float Costos = 0, Ganancias = 0; //en estas variables iremos guardando los costos y ganancias del dia

    if ( *cabeza == NULL) //en caso de que la lista este vacia
    {
        printf("\nNo se ha registrado ningun pedido\n");
        system("pause");
        main();
    }
    else
    {
        system("cls"); //limpiamos pantalla
        while( nAux != NULL)
        {
            Costos = Costos +  nAux->CostoTotal; //sumamos los gastos
            Ganancias = Ganancias + nAux->TotalPagar; //sumamos lo que la gente va a pagar, es decir una ganacia para la metalurgica
            nAux = nAux->siguiente; //apuntamos al siguiente nodo
        }
        printf("\t\t\t\t\t\tRESUMEN DIARIO");
        printf("\n\t\tCostos del dia: %.2f\n", Costos);
        printf("\t\tGanancias del dia: %.2f\n", Ganancias);
        system("pause");
    }
}
