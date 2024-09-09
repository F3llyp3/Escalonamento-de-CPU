#include "rr.h"
#include <queue>

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

  queue<int> fila;
  int quantum = 2;
  int tempo_atual = 0;

  for(int i=0; i<processos.size(); i++){ // INSERINDO TEMPO QUE RESTA
    processos[i].t_restante = processos[i].t_pico;
  }

  for(int i=0; i<processos.size(); i++){
    fila.push(i); //PREENCHNEDO FILA COM INDICES DOS PROCESSOS
  }

  while(!fila.empty()){ //ENQUANTO A FILA NÃO ESTIVER VAZIA

    int indice = fila.front(); //OBTER INDICE DO 1º PROCESSO DA FILA
    fila.pop(); // TIRANDO-O DA FILA

    if(processos[indice].t_restante > 0){
        // if(processos[indice].cont == 0){
        //   processos[indice].t_resposta = tempo_atual -processos[indice].t_chegada;
        //   processos[indice].cont = 1;
        // }



      if(processos[indice].t_restante > quantum){
        tempo_atual += quantum; 
        processos[indice].t_restante -= quantum;
        fila.push(indice); // COLOCA-O NO FIM DA FILA
        }else{ // SE RESTA MENOS QUE O QUANTUM
          tempo_atual += processos[indice].t_restante;
          processos[indice].t_restante = 0;
          processos[indice].t_retorno = tempo_atual - processos[indice].t_chegada;
          processos[indice].t_espera = processos[indice].t_retorno - processos[indice].t_pico;
        }
    }

  }
  // debug 

  for(int i=0; i<processos.size(); i++){
    cout << "P[" << i+1 << "]:" << "retorno: " << processos[i].t_retorno << " espera: " << processos[i].t_espera << " resposta: " << processos[i].t_resposta << endl; 
  }

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