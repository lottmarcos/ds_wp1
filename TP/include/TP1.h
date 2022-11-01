#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#define swap(A, B) {carta c = A; A = B; B = c; }
#define troca(A, B) {jogador c = A; A = B; B = c; }

using namespace std;

// CARTAS
class carta {
   public:
   carta();

   int numero; //numero entre 1 e 13 - ÁS ao REI
   string naipe;

   bool set_carta(string nome_carta);
   void imprime_carta();
};

// JOGADOR
class jogador {
   public:
   jogador(); 

   string nome; //nome do jogador, pode ser nome composto
   int dinheiro;
   carta mao[5];
   int aposta; //multiplo de 50 e > 0
   bool valido;
   int sequencia;
   string seq_sigla;
   carta maior_seq, maior_notseq;

   void set_jogador(string nome_jogador, int din);
   void create_player(string linha, int word_count, int dinheiro);
   void add_carta(string nome_carta, int posicao); //posicao [0 - 5]
   void ordena_mao(); //ordena a mão de acordo com o numero de cada carta (insertnsort)
   void imprime_mao();
   void limpa_mao(); //limpa a mao do jogador
   bool carta_igual(carta a, carta b); //verifica se duas cartas são iguais
   bool has_pair(); //verifica se existe um par na mão
   carta has_pair2(); //verifica se existe um par na mão
   int get_sequencia(); //retorna o valor da sequencia (1 HC -> 10 RSF)
};

// LISTA ARRANJO
class lista_arranjo {
  public:
    int tamanho;
    int jogadores_validos;
    static const int MAXTAM = 100;
    jogador itens[MAXTAM];

    lista_arranjo();
    int get_tamanho();
    bool vazia();
    jogador get_jogador(int pos);
    void set_jogador(jogador jogador, int pos);
    void insere_inicio(jogador jogador);
    void insere_final(jogador jogador);
    void insere_posicao(jogador jogador, int pos);
    jogador remove_inicio();
    jogador remove_final();
    jogador remove_posicao(int pos);
    int pesquisa(int sequencia);
    void invalida_jogadores();
    void find_player(string linha, int count);
    int aux_find(string name);
    void ganha_pote(string name, int *nv, int pote);
    void ordena_jogadores();
    void imprime_resultado();
    void imprime();
    void limpa();
};

// RODADA
class rodada {
   public:
   rodada();

   int pingo; //min 50
   int pote; // montante de pingos + apostas

   void add_pote(lista_arranjo *jogadores); //retorna false se o jogador for pobre
   void limpa_rodada();
   void make(lista_arranjo *jogadores); //faz a rodada
   string find_winner(lista_arranjo *jogadores, int sequencia, int *nv); //resolve criterios de desempate
};

// GLOBAIS
int ctoi(char c); // transforma um número em char para inteiro
int count_words(string str); // conta a quantidade de palavras numa string
string get_sigla(int i); // retorna a sigla da sequência (HC -> RSF)
string find_winner(lista_arranjo *jogadores, int sequencia, int *nv); // resolve critérios de desempate e descobre quem é / quem são os jogadores
void get_parametros(string linha, int *numero_jogadores, int *pingo); // gerencia os parametros de cada todada

