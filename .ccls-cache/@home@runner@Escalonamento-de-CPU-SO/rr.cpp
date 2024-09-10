#include "rr.h"

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
  
  int tempo_atual = 0;
  int aux=0; // Quantidade de processos finalizados
  queue<processo> fila_p;
  vector<processo> finalizados;
  

  for(int i=0; i<processos.size(); i++){   // Iguala o tempo restante ao tempo de pico
    processos[i].t_restante = processos[i].t_pico;
  }  
  
  int indice = 0; // Indice dos processos que ja entraram na fila de prontos
  int quantum = 0; 
  processo *p = NULL; // Processo auxiliar
  
  while(aux!=processos.size()){ 
    // Verifica o tempo de chegada dos processos e coloca na fila caso ja tenha chegado
    while(processos[indice].t_chegada == tempo_atual && indice<processos.size()){
      fila_p.push(processos[indice]);
      indice++;
    }
    //Tratando processos na fila de prontos
    tempo_atual++;
    if(!fila_p.empty()){  // Enquanto a fila de prontos não estiver vazia      
      p = &fila_p.front();
      
      if(p->t_pico == p->t_restante){
        p->t_resposta = tempo_atual - p->t_chegada -1;
      }
      
      while(processos[indice].t_chegada == tempo_atual && indice<processos.size()){ // Verifica se nenhum outro processo chegou
        fila_p.push(processos[indice]);
        indice++;
      }
      
      p->t_restante--;
      quantum++;
      if(quantum == 2 || p->t_restante == 0){     // Após passar o quantum de 2 ou o processo acabar
        fila_p.pop();                             // Retira da fila de prontos
        quantum = 0;                              // Reseta o quantum
        if(p->t_restante > 0){                    // Se o processo ainda possui tempo restante
          fila_p.push(*p);                        // Coloca o processo de volta na fila de prontos
        }else{                                    // Se não, calcula o t_retorno e coloca no vetor finalizados
          p->t_retorno = tempo_atual - p->t_chegada;
          aux++;                                  // Aumenta o aux, quantidade de processos finalizados
          finalizados.push_back(*p);
        }
      }
    }
  }  

  for(int i=0; i<processos.size(); i++){  // Calculando tempo de espera
    finalizados[i].t_espera = finalizados[i].t_retorno - finalizados[i].t_pico;
  }

  // Imprimindo resultados
  float espera_med, retorno_med, resposta_med;
  espera_med = retorno_med = resposta_med = 0;

  for(int i=0; i<finalizados.size(); i++){
    espera_med+= finalizados[i].t_espera;
    retorno_med+= finalizados[i].t_retorno;
    resposta_med+= finalizados[i].t_resposta;
  }
  
  cout << fixed << setprecision(1);
  cout << "RR " << retorno_med/finalizados.size() <<" " << resposta_med/finalizados.size() << " " << espera_med/finalizados.size() << endl;
  
}