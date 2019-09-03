#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

string alfa="abcdefghijklmnopqrstuvwxyz0123456789.,:;?!-()áéíóúñ¿¡ ";
int tam_alfa=54;

void entropia(vector<double> lista){
	double sum=0;
	int tam=lista.size();

	for (int i = 0; i < tam; ++i)
	{
		sum=sum + lista[i]*log2(lista[i]);
	}
	sum=(-1)*sum;

	cout<<"entropia de Shannon: "<<sum<<endl;

}

vector<double> normalizar(vector<int> numpi){
	int total=0;

	for (int i = 0; i < numpi.size(); ++i)
	{
		total=total+numpi[i];
	}

	//cout<<total<<endl;
	int con=0;
	for (int i = 0; i < numpi.size(); ++i)
	{
		if (numpi[i] == 0)
		{
			con++;
		}
	}

	vector<double> norm(numpi.size() - con);
	con=0;
	for (int i = 0; i < numpi.size(); ++i)
	{
		if (numpi[i]!=0)
		{
			norm[con]=double(numpi[i])/double(total);
			con++;
		}
	}

	//cout<<"tam de norm: "<<norm.size()<<endl;

	return norm;

}

string permutar(string txt){
	int a,b;
	char la;
	char lb;
	for (int i = 0; i < txt.size(); ++i)
	{
		a=rand()%txt.size();
		b=rand()%txt.size();

		la=txt[a];
		lb=txt[b];

		txt[a]=lb;
		txt[b]=la;
	}
	ofstream salida("salida.txt");
	salida<<txt;
	return txt;
}

void hartley(int tam){
	cout<<"entropia de hartley: "<<log2(tam)<<endl;
}

string leer_txt(){
  char cadena[128];
  string texto="";
  ifstream fe("texto.txt");
  while (!fe.eof()) {
    fe >> cadena;
    texto=texto+" "+cadena;
  }
  return permutar(texto); // modificar esto si no quieres que se permute el texto leido.
}

int find_alfa(char letra){
	for (int i = 0; i < alfa.size(); ++i)
	{
		if (letra==alfa[i])
		{
			return i;
		}
	}
	return alfa.size();
}

vector<int> contar_letras( string in){
	vector<int> conta(alfa.size()+1);
	for (int i = 0; i < alfa.size(); ++i)
	{
		conta[i]=0;
	}
	for (int i = 0; i < in.size(); ++i)
	{
		conta[find_alfa(in[i])]++;
	}

	/*for (int i = 0; i < alfa.size()+1; ++i)
	{
		cout<<i<<"  "<<alfa[i]<<"  "<<conta[i]<<endl;
	}*/

	vector<int> contador(tam_alfa);

	for (int i = 0; i < tam_alfa; ++i)
	{
		contador[i]=0;
	}
	for (int i = 0; i < find_alfa(')'); ++i)
	{
		contador[i]=conta[i];
	}
	int pos=find_alfa(')');
	for (int i = find_alfa(')'); i < alfa.size(); i+=2)
	{
		contador[pos]=conta[i];
		pos++;
	}
	contador[pos]=conta[conta.size()-2];

	//cout<<contador[pos]<<endl;

/*	for (int i = 0; i < tam_alfa; ++i)
	{
		cout<<i<<"--> "<<contador[i]<<endl;
	}*/
	return contador;
}

string gen_texto(){
	string texto="";
	int cont=0;
	string letra;
	int val;
	while (cont<4000){
		
		val=rand()%10;
		val++;
		for (int i = 0; i < val; ++i)
		{
			letra=alfa[rand()%(tam_alfa-10)];
			texto=texto+letra;
		}
		texto=texto + " ";
		cont++;
	}
	return texto;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int tama=20;
	double lista[tama];
	for (int i = 0; i < tama; ++i)
	{
		lista[i]=0.05;
	}
	//cout<<gen_texto()<<endl;


	//cout<<leer_txt()<<endl;

	vector<double> lf;
	lf=normalizar(contar_letras(leer_txt()));// modificar si quieres leer o quieres generar texto

	entropia(lf);
	hartley(lf.size());

	return 0;
}