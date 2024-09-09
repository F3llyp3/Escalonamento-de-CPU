#include "fcfs.h"

typedef struct{ // struct para de processos
  int t_retorno;
  int t_resposta;
  int t_espera;

  int t_chegada;
  int t_pico;
} processo;


void fcfs(void){
  
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
  

  // IMPLEMENTAÇÃO DO ALGORITMO FCFS
  int tempo_atual = 0;
  for(int i =0; i<processos.size(); i++){
    
    if(i == 0){
      processos[i].t_resposta = processos[i].t_chegada;
      processos[i].t_espera = 0;
      processos[i].t_retorno = processos[i].t_pico;
      tempo_atual += processos[i].t_pico;
    
    }else{
      processos[i].t_resposta = tempo_atual - processos[i].t_chegada;
      if(processos[i].t_resposta < 0) // modifiquei isso aqui, mas acho q tem como fazer
          processos[i].t_resposta = 0;// de uma maneira melhor
      
      processos[i].t_espera = tempo_atual - processos[i].t_chegada;
      if(processos[i].t_espera < 0)
        processos[i].t_espera = 0;
      
      //processo[i].t_espera = processo[i].t_resposta;
      
      processos[i].t_retorno = (processos[i].t_resposta + processos[i].t_pico);
      
      tempo_atual += processos[i].t_pico;
    }
    
  }

  
  // IMPRIMINDO RESULTADOS
  float espera_med, retorno_med, resposta_med;
  espera_med = retorno_med = resposta_med = 0;
  
  for(int i=0; i<processos.size(); i++){
      espera_med+= processos[i].t_espera;
      retorno_med+= processos[i].t_retorno;
      resposta_med+= processos[i].t_resposta;
  }

  cout << "FCFS " << retorno_med/processos.size() <<" " << resposta_med/processos.size() << " " << espera_med/processos.size() << endl;
  
}

/*
cout << "-------------------------" << endl;
cout << "P[" << i+1 << "]:" << "pico: " << processos[i].t_pico << endl;
cout << "P[" << i+1 << "]:" << "chegada: " << processos[i].t_chegada << endl;
cout << "P[" << i+1 << "]:" << "espera: " << processos[i].t_espera << endl;
cout << "P[" << i+1 << "]:" << "retorno: " << processos[i].t_retorno << endl;
cout << "P[" << i+1 << "]:" << "resposta: " << processos[i].t_resposta << endl;

Saida: FCFS 9.75 2.75 2.75
Esperada : FCFS: 10,0 3,0 3,0
0 10
4 4
8 6
21 8
*/