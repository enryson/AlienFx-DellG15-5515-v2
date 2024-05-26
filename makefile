# Nome do projeto
PROJECT_NAME := alienfx-cli

# Diretórios
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
LIB_DIR := lib

# Fontes e cabeçalhos
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)

# Compiler e flags
CXX := g++
CXXFLAGS := -std=c++17 -I$(INCLUDE_DIR) `pkg-config --cflags libusb-1.0`
LDFLAGS := `pkg-config --libs libusb-1.0`

# Diretórios de instalação
PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib

# Regras de construção
all: $(BUILD_DIR)/$(PROJECT_NAME)

$(BUILD_DIR)/$(PROJECT_NAME): $(SOURCES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

# Regras de instalação
install: $(BUILD_DIR)/$(PROJECT_NAME)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(BUILD_DIR)/$(PROJECT_NAME) $(DESTDIR)$(BINDIR)

# Regras de limpeza
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean install
