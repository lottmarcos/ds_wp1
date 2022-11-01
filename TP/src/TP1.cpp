#include "TP1.h"
#include "memlog.h"

using namespace std;

// FUNÇÕES SOBRE CARTA
carta::carta() {
   numero = 0;
   naipe = " ";
}
bool carta::set_carta(string nome_carta) {
   int numero_carta = 0;
   if (nome_carta.length() == 2)
      numero_carta = ctoi(nome_carta[0]);

   else if (nome_carta.length() == 3){
      numero_carta = 10 * ctoi(nome_carta[0]);
      numero_carta += ctoi(nome_carta[1]);
   }
   string naipe_carta(1, nome_carta[nome_carta.length() -1]);

   if ((naipe_carta == "P" || naipe_carta == "E" ||naipe_carta == "C" ||naipe_carta == "O")
          && (numero_carta <= 13 && numero_carta >= 1)) {
         numero = numero_carta;
         naipe = naipe_carta;
         return true;
      }
   else 
      return false;
}
void carta::imprime_carta() {
   cout << numero << naipe << " ";
}

// FUNÇÕES SOBRE JOGADOR
jogador::jogador() {
   valido = false;
   dinheiro = 0;
   sequencia = 0;
}
void jogador::set_jogador(string nome_jogador, int din) {
   nome = nome_jogador;
   valido = true;
   dinheiro = din;
}
void jogador::add_carta(string nome_carta, int posicao) {
   carta c;
   if(c.set_carta(nome_carta))
      mao[posicao] = c;
   else {
      cout << "ERRO AO ADICIONAR CARTA" << endl;
      exit(1);
   }
}
void jogador::create_player(string linha, int word_count, int dinheiro) {
//cria o jogador
   int word_name_count = word_count - 6;
   stringstream s(linha);
   string aux_name, name;
   if (word_name_count > 1) {
      for (int i = 0; i < word_name_count; i++) {
         s >> aux_name;
         name += aux_name;
         if(i == word_name_count -1)
            break;
         name += " ";
      }
   }
   else s >> name;

   set_jogador(name, dinheiro);

   //seta aposta
   int aposta_tmp = 0;
   s >> aposta_tmp;
   aposta = aposta_tmp;

   // cria as cartas
   limpa_mao();
   string aux_carta;
   for (int i = 0; i < 5; i++) {
      s >> aux_carta;
      add_carta(aux_carta, i);
   }
   ordena_mao();
   sequencia = get_sequencia();
   seq_sigla = get_sigla (sequencia);
}
void jogador::limpa_mao() {
   for (int i = 0; i < 5; i++) {
      mao[i].numero = 0;
      mao[i].naipe = " ";
   }
   sequencia = get_sequencia();
   seq_sigla = get_sigla(sequencia);
}
void jogador::ordena_mao() {
   int i, j, trocou;
   int n = 5;
   for(i = 0; i < n-1; i++) {
      trocou = 0;
      for(j = 1; j < n-i; j++){
         if (mao[j].numero < mao[j-1].numero)
            swap(mao[j-1], mao[j]);
            trocou = 1;
             leMemLog((long int)(&(mao[j].numero)),sizeof(carta), 0);
      }
      if (!trocou) {
         break;
      }
   }
   
}
void jogador::imprime_mao() {
   if (valido)
   cout << nome << ' ' << seq_sigla  << endl;
   cout << "CARTAS: ";
   for (int i = 0; i < 5 ; i++) {
      mao[i].imprime_carta();
   }
   cout << endl;
}
bool jogador::carta_igual(carta a, carta b) {
   return (a.numero == b.numero);
}
bool jogador::has_pair() {
   for (int i = 0; i < 5; i++) {
      if (mao[i].numero == mao[i+1].numero)
         return true;
   }
   return false;
}
carta jogador::has_pair2() {
   for (int i = 0; i < 5; i++) {
      if (mao[i].numero == mao[i+1].numero)
         return mao[i+1];
   }
   return mao[4];
}
int jogador::get_sequencia() {
   //RSF
   if (mao[0].numero == 1 && (mao[1].numero == 10 && mao[1].naipe == mao[0].naipe) &&
      (mao[2].numero == 11 && mao[2].naipe == mao[0].naipe) &&
      (mao[3].numero == 12 && mao[3].naipe == mao[0].naipe) &&
      (mao[4].numero == 13 && mao[4].naipe == mao[0].naipe))
      return 10;
   //SF
   else if (mao[1].naipe == mao[0].naipe && mao[1].numero == (mao[0].numero +1) &&
            mao[2].naipe == mao[0].naipe && mao[2].numero == (mao[1].numero +1) &&
            mao[3].naipe == mao[0].naipe && mao[3].numero == (mao[2].numero +1) &&
            mao[4].naipe == mao[0].naipe && mao[4].numero == (mao[3].numero +1))
         return 9;
   //FK
   else if ((carta_igual(mao[0], mao[1]) && carta_igual(mao[0], mao[2]) && carta_igual(mao[0], mao[3]) && (carta_igual(mao[0], mao[4]) == false))
            ||(carta_igual(mao[1], mao[2]) && carta_igual(mao[1], mao[3]) && carta_igual(mao[1], mao[4]) && (carta_igual(mao[0], mao[1]) == false))){
         if ((carta_igual(mao[0], mao[1]) && carta_igual(mao[0], mao[2]) && carta_igual(mao[0], mao[3]) && (carta_igual(mao[0], mao[4]) == false))) {
               maior_seq = mao[0];
               maior_notseq = mao[4];
            }
         else {
            maior_seq = mao[1];
            maior_notseq = mao[0];
         }
         return 8;
      }
   //FH
   else if ((carta_igual(mao[0], mao[1]) && carta_igual(mao[0], mao[2]) && carta_igual(mao[3], mao[4]) && (carta_igual(mao[0], mao[3]) == false))
            ||(carta_igual(mao[0], mao[1]) && carta_igual(mao[2], mao[3]) && carta_igual(mao[2], mao[4]) && (carta_igual(mao[0], mao[2]) == false))){
         if ((carta_igual(mao[0], mao[1]) && carta_igual(mao[0], mao[2]) && carta_igual(mao[3], mao[4]) && (carta_igual(mao[0], mao[3]) == false))){
            maior_seq = mao[0];
            maior_notseq = mao[4];
         }
         else {
            maior_seq = mao[4];
            maior_notseq = mao[0];
         }
         return 7;
      }
   //F
   else if (mao[0].naipe == mao[1].naipe && mao[0].naipe == mao[2].naipe 
            && mao[0].naipe == mao[3].naipe && mao[0].naipe == mao[4].naipe) {

         maior_seq = mao[4];
         return 6;
         }
   //S
   else if (mao[1].numero == (mao[0].numero +1) && mao[2].numero == (mao[1].numero +1) &&
            mao[3].numero == (mao[2].numero +1) && mao[4].numero == (mao[3].numero +1)){

         maior_seq = mao[4];
         return 5;
         }
   //TK
   else if ((carta_igual(mao[0], mao[1]) && carta_igual(mao[0], mao[2]) && (carta_igual(mao[3], mao[4]) == false) && (carta_igual(mao[0], mao[3]) == false))
            ||((carta_igual(mao[0], mao[1]) == false) && carta_igual(mao[2], mao[3]) && carta_igual(mao[2], mao[4]) && (carta_igual(mao[0], mao[2]) == false))
            ||(carta_igual(mao[1], mao[2]) && carta_igual(mao[1], mao[3]) && (carta_igual(mao[0], mao[4]) == false) && (carta_igual(mao[0], mao[1]) == false) && (carta_igual(mao[1], mao[4]) == false))){

         if ((carta_igual(mao[0], mao[1]) && carta_igual(mao[0], mao[2]) && (carta_igual(mao[3], mao[4]) == false) && (carta_igual(mao[0], mao[3]) == false))) {
            maior_seq = mao[2];
            maior_notseq = mao[4];
         }
         else if (((carta_igual(mao[0], mao[1]) == false) && carta_igual(mao[2], mao[3]) && carta_igual(mao[2], mao[4]) && (carta_igual(mao[0], mao[2]) == false))){
            maior_seq = mao[4];
            maior_notseq = mao[1];
         }
         else if ((carta_igual(mao[1], mao[2]) && carta_igual(mao[1], mao[3]) && (carta_igual(mao[0], mao[4]) == false) && (carta_igual(mao[0], mao[1]) == false) && (carta_igual(mao[1], mao[4]) == false))){
            maior_seq = mao[3];
            maior_notseq = mao[4];
         }

         return 4;
         }
   //TP
   else if ((carta_igual(mao[0], mao[1]) && carta_igual(mao[2], mao[3]) && (carta_igual(mao[4], mao[3]) == false))
            || (carta_igual(mao[1], mao[2]) && carta_igual(mao[3], mao[4]) && (carta_igual(mao[0], mao[1]) == false))
            || (carta_igual(mao[0], mao[1]) && carta_igual(mao[3], mao[4]) && (carta_igual(mao[1], mao[2]) == false) && (carta_igual(mao[2], mao[3]) == false))){

         if ((carta_igual(mao[0], mao[1]) && carta_igual(mao[2], mao[3]) && (carta_igual(mao[4], mao[3]) == false))){
            maior_seq = mao[3];
            maior_notseq = mao[4];
         }
         if ((carta_igual(mao[1], mao[2]) && carta_igual(mao[3], mao[4]) && (carta_igual(mao[0], mao[1]) == false))){
            maior_seq = mao[4];
            maior_notseq = mao[2];
         }
         if ((carta_igual(mao[1], mao[2]) && carta_igual(mao[3], mao[4]) && (carta_igual(mao[0], mao[1]) == false))){
            maior_seq = mao[4];
            maior_notseq = mao[2];
         }

         return 3;
         }
   //OP
   else if (has_pair()){
         carta aux = has_pair2();
         if (aux.numero == mao[4].numero) {
            maior_seq = aux;
            maior_notseq = mao[2];
         }
         else {
            maior_seq = aux;
            maior_notseq = mao[4];
         }
         return 2;
         }
   //HC
   else {
      maior_seq = mao[4];
   }
      return 1;
}

// FUNÇÕES LISTA ARRANJO
lista_arranjo::lista_arranjo() {
   tamanho = 0;
}
int lista_arranjo::get_tamanho() {
   return tamanho;
}
bool lista_arranjo::vazia() {
   return (tamanho == 0);
}
jogador lista_arranjo::get_jogador(int pos) {
  if ((pos > tamanho) || (pos <= 0)) {
    cout << "ERRO: Posicao invalida!" << endl;
    exit(1);
  }

  return itens[pos-1];
}
void lista_arranjo::set_jogador(jogador item, int pos) {
  if ((pos > tamanho) || (pos <= 0)){
     cout << "ERRO: Posicao invalida!"<< endl;
     exit(1);
  }

  itens[pos-1] = item;
}
void lista_arranjo::insere_inicio(jogador item) {
  if (tamanho == MAXTAM){
    cout << "ERRO: Lista cheia!"<< endl;
    exit(1);
  }

  tamanho++;
  jogadores_validos++;
  for (int i = tamanho; i > 0; i--)
    itens[i] = itens[i-1];

  itens[0] = item;
}
void lista_arranjo::insere_final(jogador item) {
  if (tamanho == MAXTAM){
    cout << "ERRO: Lista cheia!"<< endl;
    exit(1);
  }

  itens[tamanho] = item;
  tamanho++;
  jogadores_validos++;
}
void lista_arranjo::insere_posicao(jogador item, int pos) {
  if (tamanho == MAXTAM){
    cout << "ERRO: Lista cheia!"<< endl;
    exit(1);
  }
  if ((pos > tamanho) || (pos <= 0)){
    cout << "ERRO: Posicao invalida!"<< endl;
    exit(1);
  }

  pos--;
  tamanho++;
  jogadores_validos++;
  for (int i = tamanho; i > pos; i--)
    itens[i] = itens[i-1];

  itens[pos] = item;
}
jogador lista_arranjo::remove_inicio() {
  if (tamanho == 0)
    cout << "ERRO: Lista vazia!"<< endl;

  jogador aux = itens[0];
  for (int i = 0; i < tamanho; i++)
    itens[i] = itens[i+1];

  tamanho--;
  jogadores_validos--;
  return aux;
}
jogador lista_arranjo::remove_final() {
  if (tamanho == 0)
    cout << "ERRO: Lista vazia!"<< endl;

  tamanho--;
  jogadores_validos--;
  return itens[tamanho];
}
jogador lista_arranjo::remove_posicao(int pos) {
  if ((pos > tamanho) || (pos <= 0))
    cout << "ERRO: Posicao invalida!"<< endl;

  pos--;
  jogador aux = itens[pos];
  for (int i = pos; i < tamanho; i++)
    itens[i] = itens[i+1];
  tamanho--;
  jogadores_validos--;
  return aux;
}
int lista_arranjo::pesquisa(int seq) {
  if (tamanho == 0){
    cout << "ERRO: Lista vazia!"<< endl;
    exit(1);
  }

  int count = 0;
  for (int i = 0; i < tamanho; i++) {
    if ((itens[i].sequencia == seq) && (itens[i].valido == true))
      count++;
  }

  return count;
}
void lista_arranjo::invalida_jogadores() {
   if (tamanho == 0){
       cout << "ERRO: Lista vazia!"<< endl;
       exit(1);
   }
   for (int i = 0; i < tamanho; i++){
     jogadores_validos--;
     itens[i].valido = false;
     leMemLog((long int)(&(itens[i].valido)),sizeof(lista_arranjo), 0);
   }
}
int lista_arranjo::aux_find(string name) {
   if (tamanho == 0){
      cout << "ERRO: Lista vazia!" << endl;
      exit(1);
   }

  int i = 0;
  for (i = 0; i < tamanho; i++) {
    if (itens[i].nome == name)
      return i;
  }
  {
      cout << "ERRO: Jogador não existe!" << endl;
      exit(1);
  }
   return 0;
}
void lista_arranjo::find_player(string linha, int count) {
   int word_name_count = count - 6;
   stringstream s(linha);
   string aux_name, name;
   if (word_name_count > 1) {
      for (int i = 0; i < word_name_count; i++) {
         s >> aux_name;
         name += aux_name;
         if(i == word_name_count -1)
            break;
         name += " ";
      }
   }
   else s >> name;

   // acha o jogador com o nome em questão
   int player_index = aux_find(name);

   //valida jogador para a rodada
   itens[player_index].valido = true;
   
   //seta aposta
   int aposta_tmp = 0;
   s >> aposta_tmp;
   itens[player_index].aposta = aposta_tmp;

   // cria as cartas
   itens[player_index].limpa_mao();
   string aux_carta;
   for (int i = 0; i < 5; i++) {
      s >> aux_carta;
      itens[player_index].add_carta(aux_carta, i);
   }
   itens[player_index].ordena_mao();
   itens[player_index].sequencia = itens[player_index].get_sequencia();
   itens[player_index].seq_sigla = get_sigla (itens[player_index].sequencia);

}
void lista_arranjo::imprime() {
  for (int i = 0; i < tamanho; i++)
  if (itens[i].valido == 1) {
    itens[i].imprime_mao();
      cout << endl;
  }
}
void lista_arranjo::limpa() {
  tamanho = 0;
  jogadores_validos = 0;
}
void lista_arranjo::ordena_jogadores() {
   int i, j, trocou;
   int n = tamanho;
   for(i = 0; i < n-1; i++) {
      trocou = 0;
      for(j = 1; j < n-i; j++){
         if (itens[j].dinheiro < itens[j-1].dinheiro)
            troca(itens[j-1], itens[j]);
            trocou = 1;
      }
      if (!trocou) {
         break;
      }
   }
}
void lista_arranjo::imprime_resultado() {
   ordena_jogadores();

   ofstream output_file;
   output_file.open("./output/saida.txt", ios::app);
   output_file << "####" << endl;
   for (int i = tamanho-1; i >= 0; i--) {
      output_file << itens[i].nome << " " << itens[i].dinheiro << endl;
      escreveMemLog((long int)(&(itens[i].dinheiro)),sizeof(double), 0);
      
   }
   output_file.close();
}
void lista_arranjo::ganha_pote(string name, int *nv, int pote) {
   int i = 0;
  for (i = 0; i < tamanho; i++) {
    if (itens[i].nome == name)
      itens[i].dinheiro += (pote / *nv);
  }
}

// FUNÇÕES SOBRE RODADA
rodada::rodada() {
   pingo = 0;
   pote = 0;
}
void rodada::add_pote(lista_arranjo *jogadores) {
   
   for (int i = 0; i < jogadores->tamanho; i++){
      if (jogadores->itens[i].dinheiro - pingo <= 0){
         cout << "ERRO: Jogador sem dinheiro!"<< endl;
         exit(1);
      }

      if (jogadores->itens[i].valido == true) {
         jogadores->itens[i].dinheiro -= jogadores->itens[i].aposta;
         pote += jogadores->itens[i].aposta;
      }
         jogadores->itens[i].dinheiro -= pingo;
         pote += pingo;
  }
}
void rodada::limpa_rodada() {
   pingo = 0;
   pote = 0;
}
void rodada::make(lista_arranjo *jogadores) {
   // acha a maior sequencia e quantos jogadores são
   int i, nv = 0;

   for (i = 10; i > 0; i--) {
      nv = jogadores->pesquisa(i);
      if (nv != 0)
         break;
   }

   string jogada = get_sigla(i);
   string winner = find_winner(jogadores, i, &nv);

   ofstream output_file;
   output_file.open("./output/saida.txt", ios::app);
   int din_ganhado = pote/nv;
   output_file << nv << " " << din_ganhado << " " << jogada << endl 
        << winner << endl;
   output_file.close();

}
string rodada::find_winner(lista_arranjo *jogadores, int sequencia, int *nv) {
   jogador aux[*nv];
   int j = 0;
   for (int i = 0; i < jogadores->tamanho; i++)
      if ((jogadores->itens[i].sequencia == sequencia) && (jogadores->itens[i].valido == true)) {
         aux[j] = jogadores->itens[i];
         j++;
      }
   if (*nv == 1){
      jogadores->ganha_pote(aux[0].nome, nv, pote);
      return aux[0].nome;
   }

   // desempata
   int count = 0;
   
   jogador maior;
   maior = aux[0];

   for (int i = 0; i < *nv; i++) {
      if (aux[i].maior_seq.numero > maior.maior_seq.numero)
         maior = aux[i];
      else if (aux[i].maior_seq.numero == maior.maior_seq.numero)
         count++;
   }

   if (count == 1) {
      *nv = 1;
      jogadores->ganha_pote(maior.nome, nv, pote);
      return maior.nome;
   }

   else {
      jogador desempata[count];
      int j = 0;
      for (int i = 0; i < *nv; i++) {
         if (aux[i].maior_seq.numero == maior.maior_seq.numero){
            desempata[j] = aux[i];
            j++;
         }
      }
      
      jogador menor;
      menor = desempata[0];
      count = 0;
      for (int i = 0; i < j; i++) {
         if (desempata[i].maior_notseq.numero > menor.maior_notseq.numero)
            menor = desempata[i];
         else if (desempata[i].maior_notseq.numero == menor.maior_notseq.numero)
            count++;
      }
      if (count == 1) {
         *nv = 1;
         jogadores->ganha_pote(menor.nome, nv, pote);
         return menor.nome;
      }
      else
         *nv = count;

      //gera a string com os nomes dos vencedores
      jogador gambiarra[count];
      string vencedores;
      int h = 0;
         for (int i = 0; i < *nv; i++) {
            if (desempata[i].maior_notseq.numero == menor.maior_notseq.numero){
               gambiarra[h] = desempata[i];
               h++;
            }
         }
      *nv = h;
      for (int i = 0; i < h; i++) {
         jogadores->ganha_pote(gambiarra[i].nome, nv, pote);
         vencedores += gambiarra[i].nome;
         if(!(i+1 == h))
         vencedores += ", ";
      }
   
      return vencedores;
   }
}

// FUNÇÕES GLOBAIS
int ctoi(char c) {
   int n = c - '0';
   return n;
}
int count_words(string str) {
    stringstream s(str);
    string word;
 
    int count = 0;
    while (s >> word)
        count++;
    return count;
}
string get_sigla(int i) {
   switch (i)
   {
   case 10:
      return "RSF";
   case 9:
      return "SF";
   case 8:
      return "FK";
   case 7:
      return "FH";
   case 6:
      return "F";
   case 5:
      return "S";
   case 4:
      return "TK";
   case 3:
      return "TP";
   case 2:
      return "OP";
   default:
      return "HC";
   }
}
void get_parametros(string linha, int *numero_jogadores, int *pingo) {
   stringstream stream(linha);
   stream >> *numero_jogadores >> *pingo;
}

