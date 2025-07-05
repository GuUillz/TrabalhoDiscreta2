cmake_minimum_required(VERSION 3.10)
project(SimulacaoEpidemica)

# --- Configurações Globais ---
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Define diretórios de include ---
include_directories(
    ${PROJECT_SOURCE_DIR}/include 
)

# --- Lista de arquivos fonte ---
file(GLOB SOURCES "src/*.cpp")  # Pega todos os .cpp em src/
# --- Cria o executável ---
add_executable(SimulacaoEpidemica ${SOURCES})
