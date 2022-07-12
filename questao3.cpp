/*
Crie um programa que controla o consumo de energia dos eletrodomésticos de uma casa. Leia até
10 eletrodomésticos com nome, potência (real em kW) e tempo ativo por dia (real, em horas). Ao
final leia um tempo t (em dias) e apresente: nome, potência, horas de uso diário, consumo diário e
consumo relativo (percentual) de cada eletrodoméstico nesse período e o total de Kw consumido no
período.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct eletrodomestico{
    char nome[10];
    float potencia;
    float tempodiario;
    
};

float consumo_total(eletrodomestico* eletron, int t, int qtd_eletrons){
    
    float consumo = 0;
    for(int i = 0; i < qtd_eletrons; i++){
    consumo += t * eletron[i].potencia * eletron[i].tempodiario;
    }
    
    return consumo;
}


int main(){
     // entrada: tempo t, eletrodomesticos e campos
    int t;
    cout << "digite qtd dias: ", cin >> t;
    
    int qtd_eletrons;
    cout << "quantos eletrodomesticos?\n", cin >> qtd_eletrons;
    
    eletrodomestico eletrons[qtd_eletrons];
    for(int i = 0; i < qtd_eletrons; i++){
        
        getchar();
        cout << "nome: ";
        gets(eletrons[i].nome);
        
        cout << "potencia: ", cin >> eletrons[i].potencia;
        
        cout << "tempo ativo por dia (horas): ", cin >> eletrons[i].tempodiario;
        
    }
    
    
    
    // apresentacao
    
    for(int i = 0; i < qtd_eletrons; i++){
        
        cout << "eletrodomestico: " << eletrons[i].nome << "\n";
        
        cout << "potencia: " << eletrons[i].potencia << "KW\n";
        
        cout << "horas de uso diário: " << eletrons[i].tempodiario << " horas\n";
        
        cout << "consumo diário: " << eletrons[i].tempodiario * eletrons[i].potencia << "KWH\n";
        
        cout << "consumo relativo: " << (t * eletrons[i].tempodiario * eletrons[i].potencia)/
                                        consumo_total(eletrons, t, qtd_eletrons) * 100 << "%\n\n";
    }
    
    cout << "total de Kw consumido no período: " << consumo_total(eletrons, t, qtd_eletrons);
}
