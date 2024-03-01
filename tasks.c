#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int id = 0;
// cada tarefa vai ter um id, um titulo, uma descrição e por fim um ponteiro para o proximo item da lista de tarefas
typedef struct Task {
    int id;
    char title[50];
    char description[200];
    struct Task* next;
} Task;
// função para adcionar novas tarefas
Task* addTask(Task* head) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    char titulo[50];
    char descricao[200];

    printf("digite o titulo da sua nova tarefa\n\n > ");
    scanf("%s", &titulo);
    printf("\n\ndigite sua nova tarefa\n\n > ");
    scanf("%s", &descricao);

    id++;
    newTask->id = id;
    // a função strcpy da biblioteca string.h vai escrever na lista
    strcpy(newTask->title, titulo);
    strcpy(newTask->description, descricao);
    newTask->next = NULL;
    
    if (head == NULL) {
        return newTask;
    }
    
    Task* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newTask;
    
    return head;
}
// função que remove a ULTIMA TAREFA
Task* removeTask(Task* head) {
    if (head == NULL) {
        return NULL;
    }
    // caso a ultima função ser a de id 1, ou seja, a unica função
    if (head->id == id) {
        Task* newHead = head->next;
        free(head);
        id--;
        return newHead;
    }
    // isso tudo vai procurar e apagar a ultima função
    Task* current = head;
    while (current->next != NULL) {
        if (current->next->id == id) {
            Task* nextTask = current->next->next;
            free(current->next);
            current->next = nextTask;
            id--;
            return head;
        }
        current = current->next;
    }
    // e isso caso não tenha funções
    return head;
}
// função que imprime todas as tarefas ativas 
void displayTasks(Task* head) {
    Task* current = head;
    while (current != NULL) {
        printf("ID: #0%d\n", current->id);
        printf("Titulo: %s\n", current->title);
        printf("Descricao: %s\n", current->description);
        printf("------------------------\n");
        current = current->next;
    }
    // essa é uma função de biblioteca "unistd.h", ela faz com que o programa demore sleep(segundos) para a próxima ação do programa
    sleep(2 + (id * 5));
}

int main() {
    Task* head = NULL;

    int menuOption;

    do {
        system("cls || clear");
        printf("\t\tGerenciador de tarefas\n\n");
        printf("1. visualizar tarefas\n");
        printf("2. adicionar tarefa\n");
        printf("3. remover tarefa\n\n > ");
        scanf("%i", &menuOption);

        system("cls || clear");
        // cada resposta no menu leva a uma função diferente
        switch (menuOption) {
        case 1:
            displayTasks(head); 
            break;
        case 2:
            head = addTask(head);
            break;
        case 3:
            head = removeTask(head);
            break;
        default:
            // se responder algo diferente de 1, 2 ou 3 o programa fecha com a seguinte mensagem de error...
            printf("opcao invalida\n\n");
            break;
        }
    } while(menuOption == 1 || menuOption == 2 || menuOption == 3);
    return 0;
}