#include "rr.h"
#include <queue>
#include <algorithm>

typedef struct{ // struct de processos
  int t_retorno;
  int t_resposta;
  int t_espera;

  int t_chegada;
  int t_pico;
  int t_restante;
  int cont;
} processo;


void rr(void){
  vector<processo> processos; // vetor de processos
  processo auxiliar; // auxiliar para processos

  ifstream file( "processos.txt" ); // lendo arquivo
  if(!file){
    cerr <<"Erro ao abrir o arquivo" << endl;
  }

  while(file >> auxiliar.t_chegada >> auxiliar.t_pico){ 
    processos.push_back(auxiliar); // armazenando processos
  }

  file.close();

  // IMPLEMENTAÇÃO DO ALGORITMO RR
  
  queue<processo> fila_p;
  //int quantum = 2;
  int tempo_atual = 0;
  int aux=0;
  vector<processo> finalizados;
  

  for(int i=0; i<processos.size(); i++){ // INSERINDO TEMPO QUE RESTA
    processos[i].t_restante = processos[i].t_pico;
  }  
  
  int indice = 0;
  int quantumAux = 0;
  processo *p = NULL;
  while(aux!=processos.size()){ 
    // verifica o tempo de chegada dos processos
    while(processos[indice].t_chegada == tempo_atual && indice<processos.size()){
      fila_p.push(processos[indice]);
      indice++;
    }
    //TRATANDO DOS PROCESSOS NA FILA DE PRONTOS
        tempo_atual++;
        if(!fila_p.empty()){      
          p = &fila_p.front();
          if(p->t_pico == p->t_restante){
            p->t_resposta = tempo_atual - p->t_chegada -1;
            }
          while(processos[indice].t_chegada == tempo_atual && indice<processos.size()){
            fila_p.push(processos[indice]);
            indice++;
          }
          p->t_restante--;
          //cout << "processo de t_pico: " << p->t_pico << " t_restante: " << p->t_restante << endl;
          quantumAux++;
          if(quantumAux == 2 || p->t_restante == 0){
            fila_p.pop();
            quantumAux = 0;
            if(p->t_restante > 0){ // se resta tempo
              fila_p.push(*p);
           }else{
              p->t_retorno = tempo_atual - p->t_chegada;
              aux++;
              finalizados.push_back(*p);
           }
          }
        }
  }  

  for(int i=0; i<processos.size(); i++){ 
    finalizados[i].t_espera = finalizados[i].t_retorno - finalizados[i].t_pico;
  }
  
  // // debug 
  /*
  for(int i=0; i<processos.size(); i++){
    cout << "Processo com tempo de pico: " << finalizados[i].t_pico << endl;
    cout << "P[" << i+1 << "]:" << "retorno: " << finalizados[i].t_retorno << " espera: " << finalizados[i].t_espera << " resposta: " << finalizados[i].t_resposta << endl; 
   }
  */
  // IMPRIMINDO RESULTADOS
  float espera_med, retorno_med, resposta_med;
  espera_med = retorno_med = resposta_med = 0;

  for(int i=0; i<finalizados.size(); i++){
      espera_med+= finalizados[i].t_espera;
      retorno_med+= finalizados[i].t_retorno;
      resposta_med+= finalizados[i].t_resposta;
  }
  // SAIDA ESPERADA: 31,5 2,0 20,5
  cout << "RR " << retorno_med/finalizados.size() <<" " << resposta_med/finalizados.size() << " " << espera_med/finalizados.size() << endl;
  
}