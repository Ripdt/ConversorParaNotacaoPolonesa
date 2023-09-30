#define TAMANHO_PILHA 9999

template <typename Type> struct Pilha {
  Type vetor[TAMANHO_PILHA];
  int topo;
};

template <typename Type> void inicializar(Pilha<Type> &pilha) {
  pilha.topo = -1;
}

template <typename Type> void inserir(Pilha<Type> &pilha, Type valor) {
  pilha.topo++;
  pilha.vetor[pilha.topo] = valor;
}

template <typename Type> bool remover(Pilha<Type> &pilha, Type &valor) {
  if (pilha.topo == -1)
    return false;

  valor = pilha.vetor[pilha.topo];
  pilha.topo--;
  return true;
}