#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

float temperatura = 0, energia = 0, historicoTemperaturas[10];
int comunicacao = 1, totalLeituras = 0;
char statusOperacional[32] = "AGUARDANDO";

void loadingInicial()
{
    system("color 0A");

    printf("========================================\n");
    printf("         MISSAO DE CONTROLE\n");
    printf("========================================\n\n");

    printf("Inicializando sistemas");
    for (int i = 0; i < 5; i++) {
        Sleep(500);
        printf(".");
    }
    printf("\n\nSistemas operacionais!\n");
    Sleep(1000);
}

void barraProgresso()
{
    printf("\nAnalisando sistema:\n");
    for (int i = 0; i <= 20; i++)
    {
        // uso \r pra reescrever a mesma linha e simular progresso visual
        printf("\r[");

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        for (int j = i; j < 20; j++)
        {
            printf(" ");
        }
        printf("] %d%%", i * 5);
        Sleep(100);
    }

    printf("\n\n");
}

void cadastrarDados()
{
    system("cls");

    printf("========================================\n");
    printf("        CADASTRO DOS SENSORES\n");
    printf("========================================\n\n");

    printf("Digite a temperatura da nave: ");
    scanf("%f", &temperatura);

    // valida intervalo antes de aceitar, evita valores nulos ou absurdos
    do
    {
        printf("Digite a porcentagem de energia (0 a 100): ");
        scanf("%f", &energia);

        if (energia < 0 || energia > 100)
        {
            printf("Valor invalido! Digite entre 0 e 100.\n\n");
        }

    } while (energia < 0 || energia > 100);
    do
    {
        printf("Status da comunicacao (1 = ONLINE / 0 = OFFLINE): ");
        scanf("%d", &comunicacao);

        if (comunicacao != 0 && comunicacao != 1)
        {
            printf("Valor invalido! Digite apenas 0 ou 1.\n\n");
        }

    } while (comunicacao != 0 && comunicacao != 1);

    if (totalLeituras < 10)
    {
        historicoTemperaturas[totalLeituras] = temperatura;
        totalLeituras++;
    }
    else
    {
        for (int i = 0; i < 9; i++)
        {
            historicoTemperaturas[i] = historicoTemperaturas[i + 1];
        }

        historicoTemperaturas[9] = temperatura;
    }

    printf("\nDados registrados com sucesso!\n");
    Sleep(1500);
}

void visualizarStatus()
{
    system("cls");

    printf("========================================\n");
    printf("         STATUS DA MISSAO\n");
    printf("========================================\n\n");

    if (totalLeituras == 0)
    {
        printf("Nenhum dado foi cadastrado ainda.\n\n");
        system("pause");
        return;
    }
    printf("Temperatura: %.1f C\n", temperatura);
    printf("Energia: %.1f%%\n", energia);

    if (comunicacao == 1)
    {
        printf("Comunicacao: ONLINE\n");
    }
    else
    {
        printf("Comunicacao: OFFLINE\n");
    }

    printf("Status Operacional: %s\n", statusOperacional);
    printf("\n");
    system("pause");
}

void analisarSistema()
{
    system("cls");

    printf("========================================\n");
    printf("       ANALISE DOS SISTEMAS\n");
    printf("========================================\n");

    if (totalLeituras == 0)
    {
        printf("Nenhum dado cadastrado para analise.\n\n");
        system("pause");
        return;
    }

    barraProgresso();

    int alerta = 0;

    printf("Verificando temperatura...\n");
    Sleep(1000);

    if (temperatura > 80)
    {
        printf("ALERTA: SUPERAQUECIMENTO DETECTADO!\n");
        alerta = 1;
    }
    else
    {
        printf("Temperatura estavel.\n");
    }

    printf("\n");
    printf("Verificando energia...\n");
    Sleep(1000);

    if (energia < 20)
    {
        printf("ALERTA: NIVEL CRITICO DE ENERGIA!\n");
        printf("Modo economia ativado.\n");
        alerta = 1;
    }
    else
    {
        printf("Energia em nivel adequado.\n");
    }

    printf("\n");
    printf("Verificando comunicacao...\n");
    Sleep(1000);

    if (comunicacao == 0)
    {
        printf("FALHA NA COMUNICACAO!\n");
        strcpy(statusOperacional, "CRITICO");
    }
    else
    {
        printf("Comunicacao operacional.\n");

        // alerta acumulativo: caso qualque um falhe, o sistema entra em atenção
        if (alerta == 1)
        {
            strcpy(statusOperacional, "ATENCAO");
        }
        else
        {
            strcpy(statusOperacional, "OPERACIONAL");
        }
    }

    printf("\n========================================\n");
    printf("ANALISE FINALIZADA\n");
    printf("========================================\n\n");
    system("pause");
}

void mostrarHistorico()
{
    system("cls");

    printf("========================================\n");
    printf("     HISTORICO DE TEMPERATURAS\n");
    printf("========================================\n\n");

    if (totalLeituras == 0)
    {
        printf("Nenhuma leitura registrada.\n");
    }
    else
    {
        for (int i = 0; i < totalLeituras; i++)
        {
            printf("Leitura %d -> %.1f C\n",
                   i + 1,
                   historicoTemperaturas[i]);
        }
    }

    printf("\n");
    system("pause");
}

int main()
{
    int opcao;
    loadingInicial();

    do
    {
        system("cls");

        printf("========================================\n");
        printf("         MISSAO DE CONTROLE\n");
        printf("========================================\n\n");

        printf("1 - Inserir dados\n");
        printf("2 - Visualizar status\n");
        printf("3 - Executar analise\n");
        printf("4 - Historico das temperaturas\n");
        printf("5 - Encerrar sistema\n\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarDados();
            break;

        case 2:
            visualizarStatus();
            break;

        case 3:
            analisarSistema();
            break;

        case 4:
            mostrarHistorico();
            break;

        case 5:
            system("cls");
            printf("Encerrando sistemas");

            for (int i = 0; i < 3; i++)
            {
                Sleep(500);
                printf(".");
            }

            printf("\n\nMissao finalizada.\n");
            Sleep(1500);
            break;

        default:
            printf("\nOpcao invalida!\n");
            Sleep(1000);
        }

    } while (opcao != 5);
    return 0;
}