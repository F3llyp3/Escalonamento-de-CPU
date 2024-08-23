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
      processos[i].t_resposta = tempo_atual;
      
      processos[i].t_espera = processos[i].t_resposta - processos[i].t_chegada;
      
      processos[i].t_retorno = (processos[i].t_resposta + processos[i].t_pico) - processos[i].t_chegada;
      
      tempo_atual += processos[i].t_pico;
    }
    //cout << "tempo atual: " << tempo_atual << endl;
  }
  
  for(int i=0; i<processos.size(); i++){
      cout << "Processo " << i+1 << endl;
      cout << processos[i].t_retorno << " ";
      cout << processos[i].t_resposta << " ";
      cout << processos[i].t_espera << " ";
      cout << endl;
  }
  
  
  // IMPRIMINDO RESULTADOS
  float espera_med, retorno_med, resposta_med;
  espera_med = retorno_med = resposta_med = 0;
  
  for(int i=0; i<processos.size(); i++){
      espera_med+= processos[i].t_espera;
      retorno_med+= processos[i].t_retorno;
      resposta_med+= processos[i].t_resposta;
  }
  
  cout << "soma de retorno:" << retorno_med << endl;
  cout << "soma de resposta:" << resposta_med << endl;
  cout << "soma de espera:" << espera_med << endl;
  
  cout << retorno_med/processos.size() <<" " << resposta_med/processos.size() << " " << espera_med/processos.size() << endl;
  // retorno -> resposta -> espera
  // resultado esperado: FCFS 30,5 19,5 19,5 
  //                          122   78  78
  //p1 - 0 20
  //p2 - 0 10
  //p3 - 4 6
  //p4 - 4 8
}