#include <iostream>
#include <cstring>
#include "TP1.h"
#include "memlog.h"
#include "msgassert.h"

using namespace std;

int main(int argc, char const *argv[])
{
   // define as variáveis iniciais do jogo 
   string filename("./input/entrada.txt");
   string output("./output/saida.txt");
   
   // inicia registro de acesso
   string lognome = "memlog.out";
   int n = lognome.length();
   char char_array[n + 1];
 
   strcpy(char_array, lognome.c_str());
   iniciaMemLog(&char_array[0]);
   ativaMemLog();

   ifstream input_file(filename);
   ofstream output_file(output, ios::trunc);
   output_file.close();

   int numero_rodadas, dinheiro_inicial;
   if (!input_file.is_open()) {
      cerr << "ERRO DE ABERTURA" << endl 
      << "O arquivo 'entrada.txt' não foi encontrado no diretório 'input/'" << endl;
      return 1;
   }

   input_file >> numero_rodadas >> dinheiro_inicial;
   // realiza a primeira rodada
   // inicializa variáveis básicas
   int numero_jogadores, pingo;
   input_file >> numero_jogadores >> pingo;
   rodada poker;
   poker.pingo = pingo;
   jogador aux;
   lista_arranjo jogadores;

   string trash, linha;
   getline(input_file, trash);
   int contador;
   defineFaseMemLog(0);

   for (int i = 0; i < numero_jogadores; i++) {
      getline(input_file, linha);
      contador = count_words(linha);
      aux.create_player(linha, contador, dinheiro_inicial);
      jogadores.insere_final(aux);
      contador = 0;
   }
   poker.add_pote(&jogadores);
   poker.make(&jogadores);
   jogadores.invalida_jogadores();
   poker.pingo = 0;
   poker.pote = 0;

   numero_rodadas --;
   defineFaseMemLog(1);
   //faz as outras n- 1 jogadas
   for (int i = 0; i < numero_rodadas; i++) {
      //inicializa as variaveis básicas
      defineFaseMemLog(i+2);
      getline(input_file, linha);
      get_parametros(linha, &numero_jogadores, &pingo);
      poker.pingo = pingo;
      for (int j = 0; j < numero_jogadores; j++) {
         getline(input_file, linha);
         contador = count_words(linha);
         jogadores.find_player(linha, contador);
         contador = 0;
      }
      poker.add_pote(&jogadores);
      poker.make(&jogadores);
      jogadores.invalida_jogadores();
      poker.pingo = 0;
      poker.pote = 0;
   }
   
   //imprime resultado final   
   jogadores.imprime_resultado();

   input_file.close();

   return finalizaMemLog();
}
