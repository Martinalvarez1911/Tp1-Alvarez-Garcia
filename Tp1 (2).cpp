#include <iostream>
#include <fstream>

using namespace std;
const int dprod {5};

//Funciones
void mostrarcli(string vec[], int dim)
{
	for (int i = 0; i < dim; i++)
		cout << i << ": " << vec[i] << endl;
}

void mostrarprod(string vec[], int dim) 
{
    for(int i = 0; i < dim; ++i)
        cout << i << ": " <<  vec[i] << endl;
}



void listado(float mat[][5], int dclie, string clientes[], string productos[]) //Punto 1
{   
    
    cout << "\nListado por clientes, de los tipos de productos que superen los 13000 Kg acumulados: ";
    cout << endl;
    for(int i = 0; i < dclie; ++i) {
        for (int j = 0; j < dprod; ++j) {
        if (mat[i][j] > 13000) {
        cout << clientes[i] << " : " << productos[j] << endl; 
        }  
       }
      }
    }

void mostrarprodmax(float v[], int dim, string productos[],int vpos[]) //Punto 2
{
    for (int i = 0; i < dim; ++i) {
        cout << productos[vpos[i]] << " : " <<  v[i] << endl;
    }
}

void listasc(float vec[], int dim, int vaux[])   //Punto 2
                                                //Algoritmo de seleccion(ligeramente modificicado)
{
   int i, ipos, imin;
    for(ipos = 0 ; ipos < dim - 1 ; ipos++ ) {
        imin = ipos;
    for(i = ipos+1 ; i < dim ; i++){
        if (vec[i] < vec[imin]) {
            imin=i; }
    }
    swap(vec[ipos],  vec[imin]);
    swap(vaux[ipos], vaux[imin]);
    
    }
}

int mayorcant(float m[][5], int dclie)      //Punto 2
{                                           //Busqueda de mayor cantidad de productos
    int max  {0};
    int aux  {0};
    int pos {0};
    for(int i = 0; i < dclie; ++i) {
        for (int j = 0; j < dprod; ++j) {
        if (m[i][j] > 13000) {
            aux++;
        }
    }
    if (aux > max)
    {
        max = aux;
        pos = i;
    }
    aux = 0;
}
return pos;
}



int main() 
{   
    //Declaraciones
    const int nprod {5};
    const int ncli {8};
    int list[ncli][nprod]; //Punto 1
    float pesos[ncli][nprod] {}; //Punto 1
    float kilometros[ncli][nprod] {}; //Punto 2
    int maxprod; //Punto 2
    int v[nprod]; //Punto 2
    float pmax[nprod]; //Punto 2
    float entregas[nprod] {}; //Punto 3
    
    string clientes[ncli];
    string productos[nprod];
    ifstream datos;
    
   
    //Archivos
    datos.open("Nombres.txt");
    if (!datos) {
        cout << "No se puede abrir el archivo " << endl;
        return 1;
    }
    for (int i = 0; i < ncli && datos >> clientes[i]; ++i);
    for (int i = 0; i < nprod && datos >> productos[i]; ++i);
    datos.close();

    datos.open("Datos.txt");
    if (!datos) {
        cout << "No se puede abrir el archivo " << endl;
        return 1;
    }
    int icli, iprod {0}; 
    double ipeso, idist {0};
    while (datos >> icli >> iprod >> ipeso >> idist) {
       pesos[icli][iprod] += ipeso;
       kilometros[icli][iprod] += idist;
       entregas[iprod]++;
        }

datos.close();
    
//Salidas
    cout << " Datos proporcionados: " << endl;
    cout << endl;
   
    cout << " Clientes: " << endl;
    
    mostrarcli(clientes, ncli);
    cout << endl;

    cout << " Productos: " << endl;
    mostrarprod(productos, nprod);

//Punto 1
     listado(pesos, ncli, clientes, productos);

//Punto 2

     maxprod = mayorcant(pesos,ncli);
    

    for(int i = 0; i < ncli; ++i)
    {
        for (int j = 0; j < nprod; ++j)
        {
            v[j] = j;
            pmax[j] = kilometros[maxprod][j];
        }
    }

listasc(pmax, nprod, v);
cout << " Listado de Km recorridos por tipo de producto (ascendente): " << endl;
mostrarprodmax(pmax, nprod, productos, v);

//Punto 3

cout << " Cantidad de entregas para el tipo de producto Textiles: " << entregas[3];
//Tambien se puede hacer llamando a una funcion que busque el mayor, pero como en este
//caso se busca en una lista ascendente es suficiente con mostrar el indice donde se encuentra
//el ultimo valor.

return 0;




}