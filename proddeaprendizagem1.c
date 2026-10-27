#include <stdio.h>
#include <string.h>

#define n 10

struct medicamento {
    char nome[30];
    char laboratorio[30];
    char principioA[30];
    char unidade[11];
    char data[11];
    float custo;
    int estoque;
};

// mostra todos os remedios
void todos_medicamentos(struct medicamento a[]){
    printf("\nTodos os Medicamentos\n");
    for(int i = 0; i < n; i++){
        printf("Nome: %s\n", a[i].nome);
        printf("Laboratorio: %s\n", a[i].laboratorio);
        printf("Principio Ativo: %s\n", a[i].principioA);
        printf("Unidade: %s\n", a[i].unidade);
        printf("Vencimento: %s\n", a[i].data);
        printf("Preco de custo: %.2f\n", a[i].custo);
        printf("Estoque: %i\n\n", a[i].estoque);
    }
}

// busca por lab
void medicamentoPlaboratorio(struct medicamento a[]){
    char buscaLa[30];
    int encontrados = 0;

    printf("Digite o nome do laboratorio: ");
    scanf("%s", buscaLa);

    printf("\nMedicamentos do laboratorio %s encontrados:\n", buscaLa);
    for(int i = 0; i < n; i++){
        if(strcmp(a[i].laboratorio, buscaLa) == 0){
            printf("Nome: %s\n", a[i].nome);
            printf("Principio Ativo: %s\n", a[i].principioA);
            printf("Unidade: %s\n", a[i].unidade);
            printf("Vencimento: %s\n", a[i].data);
            printf("Preco de Custo: %.2f\n", a[i].custo);
            printf("Estoque: %i\n\n", a[i].estoque);
            encontrados++;
        }
    }
    if(encontrados == 0){
        printf("Nenhum medicamento encontrado para esse laboratorio.\n");
    }
}

// ve quem tem estoque abaixo do limite
void menorQuantiadade(struct medicamento a[]){
    int quantidade;
    int encontrados = 0;

    printf("Digite o limite minimo para consultar o estoque: ");
    scanf("%i", &quantidade);

    printf("\nMedicamentos com estoque abaixo de %i:\n", quantidade);
    for(int i = 0; i < n; i++){
        if(a[i].estoque < quantidade){
            printf("Nome: %s\n", a[i].nome);
            printf("Laboratorio: %s\n", a[i].laboratorio);
            printf("Principio Ativo: %s\n", a[i].principioA);
            printf("Unidade: %s\n", a[i].unidade);
            printf("Vencimento: %s\n", a[i].data);
            printf("Preco de Custo: %.2f\n", a[i].custo);
            printf("Estoque: %i\n\n", a[i].estoque);
            encontrados++;
        }
    }
    if(encontrados == 0){
        printf("Nenhum medicamento encontrado com estoque menor que %i.\n", quantidade);
    } else {
        printf("Foram encontrados %i medicamentos com menos de %i em estoque.\n", encontrados, quantidade);
    }
}

// calcula validade ate 30 dias
void Vencimento(struct medicamento a[]) {
    char dataUsuario[11];
    int diaU, mesU, anoU;
    int diaM, mesM, anoM;
    int encontrados = 0;

    printf("Informe a data (DD/MM/AAAA): ");
    scanf("%s", dataUsuario);

    // converte a data pra numero inteiro pra comparar facil
    sscanf(dataUsuario, "%i/%i/%i", &diaU, &mesU, &anoU);
    int dataInicio = (anoU * 10000) + (mesU * 100) + diaU;

    // soma 30 dias na data
    diaU += 30;
    if (diaU > 30) {
        diaU -= 30;
        mesU += 1;
        if (mesU > 12) {
            mesU = 1;
            anoU += 1;
        }
    }
    int dataLimite = (anoU * 10000) + (mesU * 100) + diaU;

    printf("\nMedicamentos a vencer nos proximos 30 dias:\n");
    for (int i = 0; i < n; i++) {
        sscanf(a[i].data, "%i/%i/%i", &diaM, &mesM, &anoM);
        int dataMed = (anoM * 10000) + (mesM * 100) + diaM;

        if (dataMed >= dataInicio && dataMed <= dataLimite) {
            printf("Nome: %s\n", a[i].nome);
            printf("Vencimento: %s\n", a[i].data);
            printf("Estoque: %i\n\n", a[i].estoque);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum medicamento vence nos proximos 30 dias.\n");
    }
}

// calcula total pago pelo estoque
void valorTotalPago(struct medicamento a[]) {
    float total = 0;

    for (int i = 0; i < n; i++) {
        total += (a[i].custo * a[i].estoque);
    }

    printf("\nValor total pago pelos medicamentos: R$ %.2f\n", total);
}

int main(){
    int opcao;
    struct medicamento a[n];

    printf("Cadastrar medicamentos\n");
    for(int i = 0; i < n; i++){
        printf("\nMedicamento %i:\n", i + 1);

        printf("Nome: ");
        fgets(a[i].nome, sizeof(a[i].nome), stdin);
        a[i].nome[strcspn(a[i].nome, "\n")] = '\0';

        printf("Laboratorio: ");
        fgets(a[i].laboratorio, sizeof(a[i].laboratorio), stdin);
        a[i].laboratorio[strcspn(a[i].laboratorio, "\n")] = '\0';

        printf("Principio Ativo: ");
        fgets(a[i].principioA, sizeof(a[i].principioA), stdin);
        a[i].principioA[strcspn(a[i].principioA, "\n")] = '\0';

        printf("Unidade: ");
        fgets(a[i].unidade, sizeof(a[i].unidade), stdin);
        a[i].unidade[strcspn(a[i].unidade, "\n")] = '\0';

        printf("Data de Vencimento: ");
        fgets(a[i].data, sizeof(a[i].data), stdin);
        a[i].data[strcspn(a[i].data, "\n")] = '\0';

        printf("Preco de Custo: ");
        scanf("%f", &a[i].custo);

        printf("Quantidade em Estoque: ");
        scanf("%i", &a[i].estoque);

        getchar(); // limpa o enter pro proximo fgets
    }

    do{
        printf("\n Menu\n");
        printf("Opcao 1. Listar todos os medicamentos e seus dados.\n");
        printf("Opcao 2. Listar os medicamentos de um laboratorio informado pelo usuario.\n");
        printf("Opcao 3. Calcular e mostrar a quantidade de medicamentos com quantidade menor no estoque.\n");
        printf("Opcao 4. Mostrar os medicamentos cuja validade e de ate 30 dias.\n");
        printf("Opcao 5. Calcular o valor total pago pelos medicamentos.\n");
        printf("Opcao 0. Sair\n");
        printf("Opcao: ");

        scanf("%i", &opcao);

        switch(opcao){
            case 1:
                todos_medicamentos(a);
                break;
            case 2:
                medicamentoPlaboratorio(a);
                break;
            case 3:
                menorQuantiadade(a);
                break;
            case 4:
                Vencimento(a);
                break;
            case 5:
                valorTotalPago(a);
                break;
            case 0:
                printf("\nSaindo\n");
                break;
            default:
                printf("\nOpcao Invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}