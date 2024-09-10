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
  int tempo_atual = processos[0].t_chegada; //O tempo inicial é o tempo de chegada do primeiro processo
  for(int i =0; i<processos.size(); i++){
    
    if(i == 0){
      processos[i].t_resposta = processos[i].t_chegada;
      processos[i].t_espera = 0;
      processos[i].t_retorno = processos[i].t_pico;
      tempo_atual += processos[i].t_pico;
    
    }else{
      processos[i].t_resposta = tempo_atual - processos[i].t_chegada;
      if(processos[i].t_resposta < 0) 
          processos[i].t_resposta = 0;
      
      processos[i].t_espera = tempo_atual - processos[i].t_chegada;
      if(processos[i].t_espera < 0)
        processos[i].t_espera = 0;
      
      //processo[i].t_espera = processo[i].t_resposta; // Ou simplificando, t_espera = t_resposta
      
      processos[i].t_retorno = (processos[i].t_resposta + processos[i].t_pico);
      
      tempo_atual += processos[i].t_pico;
    }
  }

  
  // Imprimindo resultados
  float espera_med, retorno_med, resposta_med;
  espera_med = retorno_med = resposta_med = 0;
  
  for(int i=0; i<processos.size(); i++){
      espera_med+= processos[i].t_espera;
      retorno_med+= processos[i].t_retorno;
      resposta_med+= processos[i].t_resposta;
  }
  cout << fixed << setprecision(1);
  cout << "FCFS " << retorno_med/processos.size() <<" " << resposta_med/processos.size() << " " << espera_med/processos.size() << endl;
  
}
