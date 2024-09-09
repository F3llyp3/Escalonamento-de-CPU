#ifndef RR_H
#define RR_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void rr();

// int indice = fila.front(); //OBTER INDICE DO 1º PROCESSO DA FILA
// fila.pop(); // TIRANDO-O DA FILA
// if(processos[indice].cont==0){
//   processos[indice].t_resposta = tempo_atual;
//   processos[indice].cont = 1;
// }
// while(processos[indice].t_chegada < tempo_atual){
//   indice = (indice +1) % processos.size();
//   //cout << "teste" << endl;
// }
// if(processos[indice].t_restante > 0){
//   if(processos[indice].t_restante > quantum){
//     tempo_atual += quantum; 
//     processos[indice].t_restante -= quantum;
//     fila.push(indice); // COLOCA-O NO FIM DA FILA
//     }else{ // SE RESTA MENOS QUE O QUANTUM
//       tempo_atual += processos[indice].t_restante;
//       processos[indice].t_restante = 0;
//       processos[indice].t_retorno = tempo_atual - processos[indice].t_chegada;
//       processos[indice].t_espera = processos[indice].t_retorno - processos[indice].t_pico;
//     }
// }


#endif