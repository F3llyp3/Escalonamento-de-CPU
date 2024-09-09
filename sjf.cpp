#include "sjf.h"

typedef struct{ // struct para de processos
  int t_retorno;
  int t_resposta;
  int t_espera;

  int t_chegada;
  int t_pico;
  int t_termino;
  int t_restante;
} processo;

processo& menorProcesso(vector<processo>& VecProcessos, int tempo_atual){
  int indice_menor = -1;  // Índice do processo com menor tempo de pico
  int menor_tempo_pico = INT_MAX; // Inicializa com um valor grande

  for (int i = 0; i < VecProcessos.size(); i++) {
      if (VecProcessos[i].t_restante > 0 && VecProcessos[i].t_pico < menor_tempo_pico && VecProcessos[i].t_chegada <= tempo_atual) {
          menor_tempo_pico = VecProcessos[i].t_pico;
          indice_menor = i;
      }
  }

  if (indice_menor != -1) {
      return VecProcessos[indice_menor];  // Retorna o processo com menor tempo de pico
  } else {
    static processo vazio;
    vazio.t_restante = 0;
    return vazio; // Lida com o caso onde não há processos com t_restante > 0
  }
  
}

void sjf(void){

  vector<processo> processos; // vetor de processos
  processo auxiliar; // auxiliar para processos

  ifstream file( "processos.txt" ); // lendo arquivo
  if(!file){
    cerr <<"Erro ao abrir o arquivo" << endl;
    return;
  }

  while(file >> auxiliar.t_chegada >> auxiliar.t_pico){ 
    processos.push_back(auxiliar); // armazenando processos
  }

  file.close();
  
  int tempo_total_exec = 0;

  // calcula tempo_total_exec
  for(int i = 0; i < processos.size(); i++){
    tempo_total_exec += processos[i].t_pico;
    processos[i].t_restante = processos[i].t_pico;
  }
  
  
  int tempo_atual = 0;
  size_t index = 0;

  while(tempo_atual < tempo_total_exec){

    while (index < processos.size() && processos[index].t_chegada <= tempo_atual) {
        index++;
    }
    
    processo& processo_atual = menorProcesso(processos,tempo_atual);

    if (processo_atual.t_restante == 0) {
        // Se o processo retornado é fictício, avance o tempo para o próximo processo
        if (index < processos.size()) {
            tempo_atual = processos[index].t_chegada;
            continue;
        }
        break;
    }
    processo_atual.t_resposta = tempo_atual - processo_atual.t_chegada;
    tempo_atual += processo_atual.t_restante;
    processo_atual.t_restante = 0;
    processo_atual.t_termino = tempo_atual;
    //cout << "Processo terminou em: " << processo_atual.t_termino << endl;

    processo_atual.t_retorno = processo_atual.t_termino - processo_atual.t_chegada;
    //processo_atual.t_espera = processo_atual.t_retorno - processo_atual.t_pico;
    processo_atual.t_espera = processo_atual.t_termino - processo_atual.t_chegada - processo_atual.t_pico;
 
  }

  float espera_med, retorno_med, resposta_med;
  espera_med = retorno_med = resposta_med = 0;

  for(int i=0; i<processos.size(); i++){
      espera_med+= processos[i].t_espera;
      retorno_med+= processos[i].t_retorno;
      resposta_med+= processos[i].t_resposta;
  }

  cout << "SJF " << retorno_med/processos.size() <<" " << resposta_med/processos.size() << " " << espera_med/processos.size() << endl;
}
