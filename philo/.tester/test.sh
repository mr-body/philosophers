#!/bin/bash

# Exibe o cabeçalho artístico
echo "                                                         "
echo "          __   _ __                   __                 "    
echo "    ___  / /  (_) /__  ___ ___  ___  / /  ___ _______    "
echo "   / _ \/ _ \/ / / _ \(_-</ _ \/ _ \/ _ \/ -_) __(_-<    "
echo "  / .__/_//_/_/_/\___/___/\___/ .__/_//_/\__/_/ /___/    "
echo " /_/                         /_/                         "
echo "                                                         "
echo -e "                  ${VERDE}mr.body${RESET}(waalexan)                      "

# Códigos de cores
VERDE="\033[0;32m"
AMARELO="\033[0;33m"
VERMELHO="\033[0;31m"
AZUL="\033[0;34m"
RESET="\033[0m"

# Verificar se o número correto de argumentos foi passado
if [ "$#" -ne 1 ]; then
    echo -e "\t  ${VERMELHO}Uso: $0 APP${RESET}"
    exit 1
fi

# Caminho para o programa a ser executado
APP="$1"

# Função para perguntar ao usuário se deseja continuar
# Função para perguntar ao usuário se deseja continuar
perguntar_continuar() {
    while true; do
        echo -e "${AMARELO}Deseja continuar com o próximo teste? (y/n): ${RESET}"
        read -p ">> " resposta
        case "$resposta" in
            [Yy]* ) return 0;;  # Continua com o próximo teste
            [Nn]* ) exit 0;;   # Encerra o script
            * ) echo -e "${VERMELHO}Por favor, responda com y ou n.${RESET}";;
        esac
    done
}

# Verifique se o programa existe e é executável
if [ -x "$APP" ]; then
    printf "${AZUL}[1]${VERDE} Teste $1 1 800 200 200${RESET}  \n\n"
    # Execute o programa com argumentos
    "$APP" 1 800 200 200
    # Capture o código de saída do programa
    EXIT_CODE=$?
    if [ $EXIT_CODE -eq 0 ]; then
        printf "\n${VERDE}NOTA: ${RESET}O filósofo não deve comer, ele deve morrer\n"
    else
        printf "${VERMELHO}Erro: O programa retornou o código de saída $EXIT_CODE.${RESET}\n"
    fi

    perguntar_continuar

    printf "${AZUL}[2]${VERDE} Teste $1 5 800 200 200 7${RESET}  \n\n"
    # Execute o programa com argumentos
    "$APP" 5 800 200 200 7
    # Capture o código de saída do programa
    EXIT_CODE=$?
    if [ $EXIT_CODE -eq 0 ]; then
        printf "\n${VERDE}NOTA: ${RESET}Nenhum filósofo deve morrer e a simulação deve parar quando todos os filósofos tiverem comido pelo menos 7 vezes.\n"
    else
        printf "${VERMELHO}Erro: O programa retornou o código de saída $EXIT_CODE.${RESET}\n"
    fi

    perguntar_continuar

    printf "${AZUL}[3]${VERDE} Teste $1 4 310 200 100${RESET}  \n\n"
    # Execute o programa com argumentos
    "$APP" 4 310 200 100
    # Capture o código de saída do programa
    EXIT_CODE=$?
    if [ $EXIT_CODE -eq 0 ]; then
        printf "\n${VERDE}NOTA: ${RESET}Um filósofo deve morrer.\n"
    else
        printf "${VERMELHO}Erro: O programa retornou o código de saída $EXIT_CODE.${RESET}\n"
    fi

    perguntar_continuar

    printf "${AZUL}[4]${VERDE} Teste $1 5 800 200 200${RESET}  \n\n"
    # Execute o programa com argumentos
    "$APP" 5 800 200 200
    # Capture o código de saída do programa
    EXIT_CODE=$?
    if [ $EXIT_CODE -eq 0 ]; then
        printf "\n${VERDE}NOTA: ${RESET}Nenhum filósofo deve morrer\n"
    else
        printf "${VERMELHO}Erro: O programa retornou o código de saída $EXIT_CODE.${RESET}\n"
    fi

else
    echo "{VERMELHO}Erro: O programa '$APP' não foi encontrado ou não é executável.${RESET}\n"
    exit 1
fi
