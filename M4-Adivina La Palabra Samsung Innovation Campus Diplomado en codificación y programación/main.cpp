#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
string arrayPalabras[4] = {"", "", "", ""}; //se selecciona la palabra con la variable indiceDeLaPalabra
string arrayPalabrasOcultas[4],palabraFinal;
int indiceDeLaPalabra=0; 
int intentos=5;
char letra ='a'; // es necesario inicializar el char 
string ocultarPalabra(int indexPalabra){ //esta funcion crea una copia de la palabra seleccionada y la reemplaza por ****
    string temp = "";
    int tamanoArray = sizeof(arrayPalabrasOcultas)/sizeof(arrayPalabrasOcultas[0]);
    for (int i = 0; i < arrayPalabras[indexPalabra].length(); i++){
        temp += "*";
    }
    arrayPalabrasOcultas[indexPalabra]=temp;
    return temp;
}
string entradaDeLetras(char entrada){ //esta funcion recibe, busca y posiciona (si es necesario) las letras
    string palabra= arrayPalabras[indiceDeLaPalabra];
    string palabraOc= arrayPalabrasOcultas[indiceDeLaPalabra];
    for (int i = 0; i <palabra.size(); i++){
        if(palabra[i]==entrada){
            palabraOc[i]=entrada;
        }
    }
    arrayPalabrasOcultas[indiceDeLaPalabra]=palabraOc;
    return palabraOc;
}
int main(){
	system ("color 1F");
	for(int k=0; k<4; k++){
		cout<<"\n\n\tADIVINA LA PALABRA \nTienes 5 intentos\nA jugar!";
		cout<<"\nIngresa la palabra: ";
		cin>>arrayPalabras[k];
		cout<<"\t\t\t\t Palabra "<<k+1<<" de "<<4<<"\n\n"<<endl;
		ocultarPalabra(indiceDeLaPalabra);
		for (int i=0; i<5; i++){
		 	cout << "Palabra Oculta: " << arrayPalabrasOcultas[indiceDeLaPalabra] << endl;
         	cout << "Intentos Restantes: " << intentos << endl;
         	cout << "Introduzca Una Letra: ";
         	cin >> letra;
         	entradaDeLetras(letra);
         	intentos--;
         	cout<<endl;
        		if(arrayPalabrasOcultas[indiceDeLaPalabra]==arrayPalabras[indiceDeLaPalabra]){
					cout<<"\nGANASTE! ADIVINASTE LA PALABRA"<<endl;
					cout<<"Palabra: "<<arrayPalabras[indiceDeLaPalabra]<<endl;
					break;
				}
		}
		cout << "Palabra Oculta: " << arrayPalabrasOcultas[indiceDeLaPalabra] << endl;
		cout<< "\nSE TERMINARON LOS 5 INTENTOS \nEs hora de adivinar \nEscribe la palabra completa: ";
		cin>>palabraFinal;
			if(palabraFinal==arrayPalabras[indiceDeLaPalabra]){
				cout<<"\n\tGANASTE! \nADIVINASTE LA PALABRA"<<endl;
				cout<<"Palabra: "<<arrayPalabras[indiceDeLaPalabra]<<endl;
			}else{
				cout<<"\n\tPERDISTE! :( \nLa palabra era: "<<arrayPalabras[indiceDeLaPalabra]<<endl;
			}
		indiceDeLaPalabra++; intentos=5;
	}
    system("pause");
    return 0;
}

