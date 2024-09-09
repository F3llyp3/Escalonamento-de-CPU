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
  //cout << "teste";
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
  int quantum = 2;
  int tempo_atual = 0;
  int aux=0;
  

  for(int i=0; i<processos.size(); i++){ // INSERINDO TEMPO QUE RESTA
    processos[i].t_restante = processos[i].t_pico;
  }

  
  int indice = 0;
  processo p;
  while(aux!=processos.size()){ 
    // verifica o tempo de chegada dos processos
    while(processos[indice].t_chegada == tempo_atual){
      fila_p.push(processos[indice]);
      indice++;
    }
    //TRATANDO DOS PROCESSOS NA FILA DE PRONTOS
    
      //if(fila_p.front().t_restante > 0){
        if(!fila_p.empty()){      
          if(tempo_atual%quantum == 0){
            p = fila_p.front();
            fila_p.pop();
            if(p.t_restante > 0){
              fila_p.push(p);
            }else{
              
            }
           }
          
          tempo_atual++;
          //else{
          //   aux++;
          // }
          
        // }else{
        //   tempo_atual += fila_p.front().t_restante;
        //   fila_p.front().t_restante = 0;
        //     fila_p.front().t_restante = tempo_atual - fila_p.front().t_restante;
        //     fila_p.front().t_restante = fila_p.front().t_restante - fila_p.front().t_restante;
        //   aux++;
        //   fila_p.pop();
        // }
      
        }
    
  
  // // debug 

  // for(int i=0; i<processos.size(); i++){
  //   cout << "P[" << i+1 << "]:" << "retorno: " << processos[i].t_retorno << " espera: " << processos[i].t_espera << " resposta: " << processos[i].t_resposta << endl; 
  // }
  
  // IMPRIMINDO RESULTADOS
  float espera_med, retorno_med, resposta_med;
  espera_med = retorno_med = resposta_med = 0;

  for(int i=0; i<processos.size(); i++){
      espera_med+= processos[i].t_espera;
      retorno_med+= processos[i].t_retorno;
      resposta_med+= processos[i].t_resposta;
  }

  cout << "RR " << retorno_med/processos.size() <<" " << resposta_med/processos.size() << " " << espera_med/processos.size() << endl;
  
}