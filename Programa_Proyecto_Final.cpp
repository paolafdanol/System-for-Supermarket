#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
using namespace std;
#define ASCENDENTE 1

class pdv{   //Este nodo lo usamos paara poner nuestras variables y funciones que usaremos en otros nodos que estaran vinculados por listas amigas 
	public:
		pdv(int v,string z,int pr,pdv *sig=NULL, pdv *ant=NULL): 
			valor(v), prod(z), precio(pr), siguiente(sig), anterior(ant){
			}
	
	private:
		int total;
		string prod; 
		int precio;
		int valor;
		int cant;
		pdv *siguiente;
		pdv *anterior;
		
		friend class jefe;   //se agregan como friend para poder manejar la informacion de total las lista y las hace ligadas
		friend class cliente;
};
typedef pdv *ppdv;  //Se crea un objeto para poder trabajar las listas siguientes

class cliente{  //Se crea una nueva lista doblemente ligadas que la utilizara el cliente
	public:
		cliente():pcliente(NULL){}		//constructor
		~cliente();      //destructor
		void insertar(int v, string z, int pr);
		void borrar(int v);//es para cancelar compras
		bool listaVacia(){return pcliente == NULL;}
		void mostrar(int);
		void siguiente();
		void anterior();
		void primero();
		void piezas(int v,int p);
		int monto(int v){  //esta funcion la iniciamos dentro de la misma lista(class) para poder dar el reusltado cuanto sera el pago de cada prenda por
			int a,b,c;
							//la cantidad comprada de piezas		
			ppdv nodo,aux;
			nodo = pcliente;
	while(nodo && nodo->valor < v)nodo = nodo->siguiente;
	while(nodo && nodo->valor > v)nodo = nodo->anterior;
	if(!nodo||nodo->valor!=v){
	}else{
		b=nodo->precio;
		c=nodo->cant;
		a=b*c;
			return a; 
	}
		
		}
		int c_total();   //esta funcion nos ayudara a crear un suma donde mas adelante les explico como funciona totalmente 
		void ultimo();
		bool actual(){return pcliente != NULL;}
		int valorActual(){return pcliente->valor;}
		
		void buscar(int v);
	private:
		ppdv pcliente;
	friend class jefe;		
};

class jefe{  //Aqui tenemos nuestra lista(class) que sera la responsable de interactuar con los datos del administrador
	public:
		jefe():pjefe(NULL){}
		~jefe();
		void Insertar(int v, string z, int pr);
		void Borrar(int v);
		bool ListaVacia(){return pjefe == NULL;}
		void Mostrar(int);
		void Siguiente();
		void Anterior();
		void Primero();
		void Agregar();
		void Ultimo();
		bool Actual(){return pjefe != NULL;}  //Le dimos valores al constructor para que me retorne un valor o de lo contrario sea un valor null
		int ValorActual(){return pjefe->valor;}
		int Valorc(int v);
		string NomActual(char v);
		int Precioprod(int v);
		
		void Buscar(int v);
		int buscar(int v); //se creo para poder returnar valores en condiciones
	private:
		ppdv pjefe;	//aqui tenemos un puntero-objeto llamado nodo que crea 	
};

cliente::~cliente(){  //se creo la funcion del destructor donde borramos algun los datos al termino del programa para que no se llene al memoria
	ppdv aux;
	primero();
	while(pcliente){
		aux = pcliente;
		pcliente = pcliente->siguiente;
		delete aux; 
	}
}

int cliente::c_total(){   //Esta funcion nos va a sumar todos los datos que estan en la funcion del monto
	int t=0;
	ppdv nodo;
	primero();
	nodo=pcliente;
	//nodo==pcliente;
		while(nodo){
		t=t+(nodo->precio*nodo->cant);
			nodo=nodo->siguiente;
		}	
		cout <<"Tu pago total es de: $"<<t;
}

void cliente::piezas(int v,int p){  //nos va a multiplicar las piezas que el cliente vaya a comprar por el precio del producto que es llamado por el ID
	ppdv nodo,aux;
	nodo = pcliente;
	while(nodo && nodo->valor < v)nodo = nodo->siguiente;
	while(nodo && nodo->valor > v)nodo = nodo->anterior;
	if(!nodo||nodo->valor!=v){
		
	}else{
		nodo->cant=p;
		return;
	}	
			
}

void cliente::buscar(int v){    //Como su nombre lo dice nos ayudara a buscar productos agregados a la canasta
	ppdv nodo,aux;
	nodo = pcliente;
	while(nodo && nodo->valor < v)nodo = nodo->siguiente;
	while(nodo && nodo->valor > v)nodo = nodo->anterior;
	if(!nodo||nodo->valor!=v){
		cout <<"El dato "<<v<<"que buscas, No existe"<<endl;
	}else{
		cout <<"El dato "<<v<<"que buscas, Si existe"<<endl;
		return;
	}
}
void cliente::insertar(int v, string z, int pr){   //nos ayuda a seleccionar los productos que vamos a comprar mediante el ID
	ppdv nuevo, Cliente;
	ultimo();
	if(listaVacia()||pcliente->valor>v){
		nuevo=new pdv(v,z,pr,pcliente);
			if (!pcliente)pcliente=nuevo;
			else pcliente->anterior=nuevo;
	}else{
		while(pcliente->siguiente&&pcliente->siguiente->valor<=v)
		siguiente();
		nuevo=new pdv(v,z,pr, pcliente->siguiente,pcliente);
		pcliente->siguiente=nuevo;
		if(nuevo->siguiente)nuevo->siguiente->anterior=nuevo; 	
	}
}
void cliente::borrar(int v){   //Nos quitara los productos que el cliente agregue al carrito 
	ppdv nodo,aux;
	nodo=pcliente;
	while(nodo&&nodo->valor<v)nodo=nodo->siguiente;
	while(nodo&&nodo->valor>v)nodo=nodo->anterior;
	if(!nodo||nodo->valor!=v){
		cout <<"El dato "<<v<<"que buscas no existe"<<endl;
		return;
	}//Borrar el nodo
	if(nodo->anterior==NULL&&nodo->siguiente==NULL){
		primero();
		while(pcliente){
		aux=pcliente;
		pcliente=pcliente->siguiente;
		delete aux;
		return;
		}
	}
	if(nodo->anterior==NULL&&nodo->siguiente!=NULL){
		aux=nodo;
		aux->anterior=NULL;
		nodo=aux->siguiente;
		aux->siguiente=NULL;
		nodo->anterior=NULL;
		delete aux;
		pcliente=nodo;
		return;
	}else{
		if(nodo->anterior)//no es el primer elemento
		nodo->anterior->siguiente=nodo->siguiente;
		if(nodo->siguiente)//no es el ultimo nodo
		nodo->siguiente->anterior=nodo->anterior;
		delete nodo;
	}
}
void cliente::mostrar(int orden){ //nos imprimira de forma ascendente los prodcutos tomados por el ID
	ppdv nodo;
	primero();
	nodo=pcliente;
	nodo==pcliente;
	if(orden==ASCENDENTE){
		while(nodo){
		cout<<"\nID    PRODUCTO     PRECIO\n";
		cout <<nodo->valor<<"    "<<nodo->prod<<"       "<<"$"<<nodo->precio;
			nodo=nodo->siguiente;
		}
	}else{
		ultimo();
		nodo=pcliente;
		while(nodo){
		cout<<"ID    PRODUCTO     PRECIO\n";
		cout <<nodo->valor<<"    "<<nodo->prod<<"       "<<"$"<<nodo->precio<<"n";
		nodo=nodo->anterior;
		}
	}
	cout <<endl;
}

void cliente::siguiente(){
		if(pcliente)pcliente=pcliente->siguiente;
}
void cliente::anterior(){
		if(pcliente)pcliente=pcliente->anterior;
}
void cliente::primero(){
	while(pcliente&&pcliente->anterior)pcliente=pcliente->anterior;
}
void cliente::ultimo(){
	while(pcliente&&pcliente->siguiente)pcliente=pcliente->siguiente;
}


jefe::~jefe(){   //este destructor nos ayudara a borrar los datos ingresados para que no se llene la memoria 
	ppdv aux;
	Primero();
	while(pjefe){
		aux = pjefe;
		pjefe = pjefe->siguiente;
		delete aux;
	}
}
void jefe::Buscar(int v){   //buscara por medio del ID solamente para imprimir en pantalla
	ppdv nodo, aux;
	nodo = pjefe;
	while(nodo && nodo->valor < v)nodo = nodo->siguiente;
	while(nodo && nodo->valor > v)nodo = nodo->anterior;
	if(!nodo||nodo->valor!=v){
		cout <<"El dato "<<v<<" que buscas no existe"<<endl;
	}else{
		cout <<"El producto es:"<<nodo->prod<<" y su precio es de: "<<nodo->precio<< endl;
		return ;
	} 		
}

int jefe::buscar(int v){   //esta funcion buscara y recorrera de adelante hacia atras y viceversa
	ppdv nodo, aux;
	nodo = pjefe;
	while(nodo && nodo->valor < v)nodo = nodo->siguiente;
	while(nodo && nodo->valor > v)nodo = nodo->anterior;
	if(!nodo||nodo->valor!=v){
		cout <<"El dato "<<v<<" que buscas no existe"<<endl;
		return 0;
	}else{
		return 1;
	if(!nodo||nodo->valor!=v){
		cout <<"El dato "<<v<<" que buscas no existe"<<endl;
		return 0;
	}else{
		return 1;
	} 		
}	
}
void jefe::Insertar(int v, string z, int pr){   //Guardara los datos que el administrador de los productos 
	ppdv nuevo;
	Primero();
	
	if(ListaVacia()||pjefe->valor>v){
		nuevo =new pdv(v,z,pr,pjefe);
		if(!pjefe)pjefe=nuevo;
		else pjefe->anterior=nuevo; 
	}else{
	while(pjefe->siguiente&& pjefe->siguiente->valor<=v)
	Siguiente();
	nuevo=new pdv (v, z,pr,pjefe->siguiente, pjefe);
	pjefe->siguiente=nuevo;
	if(nuevo->siguiente)nuevo->siguiente->anterior=nuevo; 		
	}
	
}

void jefe::Borrar(int  v){   //Borrar el dato que el dato que desea el administrador
	ppdv nodo,aux;
	nodo=pjefe;
	while(nodo&&nodo->valor<v)nodo=nodo->siguiente;
	while(nodo&&nodo->valor>v)nodo=nodo->anterior;
	if(!nodo||nodo->valor!=v){
		cout <<"El dato "<<v<<"que buscas no existe"<<endl;
		return;
	}//Borrar el nodo
	if(nodo->anterior==NULL&&nodo->siguiente==NULL){
		Primero();
		while(pjefe){
		aux=pjefe;
		pjefe=pjefe->siguiente;
		delete aux;
		return;
		}
	}
	if(nodo->anterior==NULL&&nodo->siguiente!=NULL){
		aux=nodo;
		aux->anterior=NULL;
		nodo=aux->siguiente;
		aux->siguiente=NULL;
		nodo->anterior=NULL;
		delete aux;
		pjefe=nodo;
		return;
	}else{
		if(nodo->anterior)//no es el primer elemento
		nodo->anterior->siguiente=nodo->siguiente;
		if(nodo->siguiente)//no es el ultimo nodo
		nodo->siguiente->anterior=nodo->anterior;
		delete nodo;
	}
}

void jefe::Mostrar(int orden){  //hara un orden de manera ascendete de los productos que haya ingresado el administrador 
	ppdv nodo;
	Primero();
	nodo=pjefe;
	nodo==pjefe;
	if(orden==ASCENDENTE){
		while(nodo){
			cout<<"\nID    PRODUCTO     PRECIO\n" ;
			cout <<nodo->valor<<"    "<<nodo->prod<<"         "<<"$"<<nodo->precio;
			nodo=nodo->siguiente;
		}
	}else{
		Ultimo();
		nodo=pjefe;
		while(nodo){
		cout<<"ID    PRODUCTO     PRECIO\n";
		cout <<nodo->valor<<"    "<<nodo->prod<<"         "<<"$"<<nodo->precio;
		nodo=nodo->anterior;
		}
	}
	cout <<endl;
}
void jefe::Siguiente(){
	if(pjefe)pjefe=pjefe->siguiente;
}
void jefe::Anterior(){
	if(pjefe)pjefe=pjefe->anterior;
}
void jefe::Primero(){
	while(pjefe&&pjefe->anterior)pjefe=pjefe->anterior;
}
void jefe::Ultimo(){
	while(pjefe&&pjefe->siguiente)pjefe=pjefe->siguiente;
}
int jefe::Valorc(int v){   //recorrera de adelante hacia atras para poder actualizar el ID y poder realizar las operaciones realizadas 
	ppdv nodo, aux;
	nodo = pjefe;
	while(nodo && nodo->valor < v)nodo = nodo->siguiente;
	while(nodo && nodo->valor > v)nodo = nodo->anterior;
	if(!nodo||nodo->valor!=v){
		return 0;
	}else{
		
	if(!nodo||nodo->valor!=v){
		return 0;
	}else{
		
		return nodo->valor;
	}
 }		
}

int jefe::Precioprod(int v){  //recorrera de adelante hacia atras para poder actualizar el precio y poder realizar las operaciones realizadas 
	ppdv nodo, aux;
	nodo = pjefe;
	while(nodo && nodo->valor < v)nodo = nodo->siguiente;
	while(nodo && nodo->valor > v)nodo = nodo->anterior;
	if(!nodo||nodo->valor!=v){
		return 0;
	}else{
		
	if(!nodo||nodo->valor!=v){
		return 0;
	}else{
		cout<<"P="<<nodo->precio;
		return nodo->precio;
	}
 }
}

string jefe::NomActual(char v){  ////recorrera de adelante hacia atras para poder actualizar el nombre y poder realizar las operaciones realizadas 
	ppdv nodo, aux;
	nodo = pjefe;
	while(nodo && nodo->valor < v)nodo = nodo->siguiente;
	while(nodo && nodo->valor > v)nodo = nodo->anterior;
	if(!nodo||nodo->valor!=v){
		return 0;
	}else{
		
	if(!nodo||nodo->valor!=v){
		return 0;
	}else{
		cout<<"P="<<nodo->prod;
		return nodo->prod;
	}
 }
}

int main(){   
	int precio,canti,ca;
	int c_total;
	char opc,o,l, opc_com;
	string nom,nom1;
	int j, k,f,p, pag;
	jefe Jefe;         //con el objecto jefe creamos una variable llamada Jefe
	cliente Cliente;  //con el objeto de cliente creamos una variable llamada Cliente
	int x, cant,z;
	int q,e;
	string prod;

	//agregar comentario por linea 
	do{
		cout <<"\n\n\t\t-----Menu Principal-----"<<endl;  //Este es nuestro menu principal donde elegiremos entre administrador o cliente y dependiendo de eso
		cout <<endl<<"\t\tBienvenido seas!!!"<<endl;      //nos llevara a nuestro cases 
		cout <<"\t\tQue deseas hacer?\n \t\tQue eres?\n"<<endl;
		cout <<"\t\t1.-Administrador"<<endl;//ingresar la parte de los archivos como un reporte de inventario en un archivo predeterminado(inventario.txt) en la clase del jefe
		cout <<"\t\t2.-Cliente"<<endl;
		cout <<"\t\t3.-Salir"<<endl;
		cout <<"\t\t--------------------------------"<<endl;
		fflush(stdin);
		scanf("%c",&opc);
		system("CLS");
		switch(opc){
				
			case '1':
				do{
					char z;
					cout <<"\n\n-----Menu Del Administrador-----"<<endl;
					cout <<"Que deseas hacer\n"<<endl;
					cout <<"1.-Ingresar productos"<<endl;
					cout <<"2.-Mostrar productos"<<endl;
					cout <<"3.-Ver ultimo producto"<<endl;
					cout <<"4.-Ver primer producto"<<endl;
					cout <<"5.-Buscar producto"<<endl;
					cout <<"6.-Eliminar producto"<<endl;
					cout <<"7.-Salir "<<endl;
					cout <<"--------------------------------"<<endl;
					cout <<endl;
					fflush(stdin);
					scanf("%c",&o);
					system("CLS");
					switch(o){
						//Inicia la seccion del Administrador para manejar datos *****//
						//*****Ingresaremos los datos para crear nuestra lista*****//
						case '1':
							cout <<"Cuantos datos desea ingresar:#";
							scanf("%i",&cant);
							for(int i = 0;i < cant; i++){
							cout <<endl<<"Ingresar el ID del producto:";
							scanf("%i",&x);
							cout <<endl<<"Ingresa el nombre del producto:";
							cin >>nom;
							cout <<endl<<"Ingresa el precio del procuto: $";
							scanf("%i",&j);
							Jefe.Insertar(x,nom,j);
							}
							system("CLS");
							cout <<"\nListo, datos guardados\n\n"<<endl;
							x = 0;
							break;
						
						//*****Mostrara los datos ingresados*****//
						case '2':
							if(Jefe.ListaVacia())
							cout <<"Tu lista esta vacia"<<endl;
							else{
								cout <<"Su lista es: "<<endl;
								Jefe.Mostrar(ASCENDENTE);
							}
							break;
							
						//*****Podremos ver el ultimo dato de nuestra lista*****//	
						case'3':
							if (Jefe.ListaVacia())
							cout <<"Tu lista esta vacia"<<endl;
							else{
								Jefe.Ultimo();
								cout <<"\nTu ultimo dato de la lista es: "<<Jefe.ValorActual()<<endl;
							}
							break;
							
						//*****Podremos ver el primer dato de nuestra lista*****//	
						case '4':	
							if(Jefe.ListaVacia())
							cout <<"Tu lista esta vacia"<<endl;
							else{
							Jefe.Primero();
							cout <<"\nTu primer dato de la lista es: "<<Jefe.ValorActual()<<endl;
							}
							break;
							
						//******Podemos buscar los datos por medio del ID*****//	
						case'5':
							if(Jefe.ListaVacia())
							cout <<"Tu lista esta vacia"<<endl;
							else{
								cout <<"Ingresa el dato que quieres buscar: ";
								scanf("%i",&x);
								Jefe.Buscar(x);
							}
							x = 0;
							break;
							
						//*****podemos borrar algun producto por medio del ID*****//	
						case '6':
							cout <<"Ingresa el dato que quieras eliminar:"<<endl;
							scanf("%i",&x);
							Jefe.Borrar(x);
							x = 0;
							break;
							
						//*****Salida del programa*****//	
						case'7':cout <<"Adios Jefe\nBuen dia :)!!"<<endl;
							break;
							
						//*****Una opcion para corregir el opcion*****//	
						default:cout <<"Opcion erronea \n Intenta de nuevoaa\n\n"<<endl; 
							break;					
				}
			}while(o!='7');		
			break;
			//Aqui comienza la parte del cliente
			case '2':
				do{
					cout <<"\n\n\t\t-----Menu Del Cliente-----"<<endl;
					cout <<"Que deseas hacer??"<<endl;
					cout <<"1.-Ver productos"<<endl;
					cout <<"2.-Agregar a compras"<<endl;
					cout <<"3.-Mostrar productos adquiridos"<<endl;
					cout <<"4.-Ver ultimo producto comprado"<<endl;
					cout <<"5.-Ver primer producto comprado"<<endl;
					cout <<"6.-Eliminar producto"<<endl;
					cout <<"7.-Salir\n\n!!!!"<<endl;
					cout <<"--------------------------------"<<endl;
					fflush(stdin);
					cout <<endl;
					scanf("%c",&l);
					system("CLS");
					switch(l){
						//*****Nos muestra los que el Administrador haya ingresado*****//
						case '1':
								if(Jefe.ListaVacia())
							cout <<"Tu lista esta vacia"<<endl;
							else{
								cout <<"Su lista es: "<<endl;
								Jefe.Mostrar(ASCENDENTE);
								
							}	
							break;
						//*****Agregar productos a la canasta*****//
						case '2':
						do{	
						if(Jefe.ListaVacia())
							cout <<"Tu lista esta vacia\n"<<endl;
							else{
								cout <<"\nQue desea comprar? ";
								cout <<"\nIngresa el ID del producto a comprar: ";
								scanf("%i",&x);  //nos pide el ID para poder mandar a traer los valores
								Jefe.Buscar(x);//nos buscara los datos de la lista Jefe
								q=Jefe.Valorc(x);//extraemos los datos de la class jefe para despues meterlos a mi lista cliente
								e=Jefe.Precioprod(q);//se extraen las variables del jefe a cliente
								prod=Jefe.NomActual(q);//Actualizar para que me de el nombre actual de q /////////// 
								
								Cliente.insertar(q,prod,e);
							cout <<"\nCantidad a comprar: ";
							scanf("%i",&k);  //variable para cantidad de productos
							Cliente.piezas(q,k);//guadamos 
							pag=Cliente.monto(q);
							cout <<"El total a pagara es de: "<<pag<<endl;	
							Cliente.c_total();					
								cout <<"\n\nSi desea hacer otra comprar oprima 1\nDe lo contrario oprime cualquier tecla\n";							
							fflush(stdin);
							scanf("%c",&opc_com);
								}
							}while(opc_com=='1');
							x=0;
							break;
						
						//*****Ver productos agregados al carrito*****//
						case'3':
							if(Cliente.listaVacia())
							cout <<"Tu lista esta vacia"<<endl;
							else{
								cout <<"Su lista de comprar por el momento: "<<endl;
								Cliente.mostrar(ASCENDENTE);
							}
							Cliente.c_total();
							break;

						//*****Ver ultimo producto*****//
						case '4':
							if (Cliente.listaVacia())
							cout <<"Tu lista esta vacia"<<endl;
							else{
							Cliente.ultimo();
							cout <<"\nTu ultimo dato de la lista es: "<<Cliente.valorActual()<<endl;
							}
							break;
						
						//*****Ver primer producto*****//
						case'5':
							if(Cliente.listaVacia())
							cout <<"Tu lista esta vacia"<<endl;
							else{
							Cliente.primero();
							cout <<"\nTu primer dato de la lista es: "<<Cliente.valorActual()<<endl;
							}
							break;
							//*****Borrar productos de la compra*****//
						case '6':
							cout <<"Ingresa el ID del producto  que quieras eliminar:"<<endl;
							cin >>x;
							Cliente.borrar(x);
				
							x = 0;
							break;
						case'7':cout <<"Fue un placer atenderlo\nLindo dia le desean Paola Fernanda Nolasco Ramirez y Juan Julian Rendon Galvez :)!!"<<endl;
							break;
						default:cout <<"Opcion erronea \n Intenta de nuevo\n\n"<<endl; 
							break;					
					}
				}while(l!='7');	
			break;
			
			case '3':
				cout <<"Adios!!!"<<endl;
			break;	
			
			//*****Opcion de error en opcion*****//
			default: 
			cout <<"Error en la opcion"<<endl;
			cout <<"Intenta de nuevo plis"<<endl;
			
			break;	
			
			}
		}while(opc!='3');
	system("PAUSE");
	return 0;
}

/*Creado por:
				Paola Fernanda Nolasco Ramirez    20110306
				Juan Julian Rendon Galvez         20110306
				Grupo K
				Alumnos del Plantel CETI Colomos 
	Materia: Programacion Orientada a Objetos			
	Programa: Punto de venta
	Este programa es de forma dinamico y con listas doblemente ligadas donde podemos guardar los archivos por un posible inventario*/				
