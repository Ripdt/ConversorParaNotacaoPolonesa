#define TAMANHO_FILA 9999

template <typename Type> struct Fila {
  Type vetor[TAMANHO_FILA];
  int comeco;
  int fim;
};

template <typename Type> void inicializar(Fila<Type> &fila) {
  fila.comeco = 0;
  fila.fim = -1;
}

template <typename Type> void inserir(Fila<Type> &fila, Type valor) {
  fila.fim++;
  fila.vetor[fila.fim] = valor;
}

template <typename Type> bool remover(Fila<Type> &fila, Type &valor) {
  if (fila.fim < fila.comeco)
    return false;

  valor = fila.vetor[fila.comeco];
  fila.comeco++;
  return true;
}