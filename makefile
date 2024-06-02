# Nome do projeto
PROJECT_NAME_CLI := alienfx-cli
PROJECT_NAME_GUI := alienfx-gui

# Diretórios
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
LIB_DIR := lib
DATA_DIR := data

# Fontes e cabeçalhos
SOURCES_CLI := $(SRC_DIR)/main.cpp
SOURCES_GUI := $(SRC_DIR)/gui.cpp
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
GLADE_FILE := layout.glade

# Compiler e flags
CXX := g++
CXXFLAGS := -std=c++17 -I$(INCLUDE_DIR) `pkg-config --cflags libusb-1.0 gtkmm-3.0`
LDFLAGS := `pkg-config --libs libusb-1.0 gtkmm-3.0`

# Diretórios de instalação
PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
DATADIR := $(PREFIX)/share/$(PROJECT_NAME_GUI)

# Regras de construção
all: $(BUILD_DIR)/$(PROJECT_NAME_CLI) $(BUILD_DIR)/$(PROJECT_NAME_GUI)

$(BUILD_DIR)/$(PROJECT_NAME_CLI): $(SOURCES_CLI) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_CLI) $(LDFLAGS)

$(BUILD_DIR)/$(PROJECT_NAME_GUI): $(SOURCES_GUI) $(HEADERS) $(GLADE_FILE)
	mkdir -p $(BUILD_DIR)
	cp $(GLADE_FILE) $(BUILD_DIR)  # Copia o arquivo GLADE para o diretório de construção
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_GUI) $(LDFLAGS)

# Regras de instalação
install: $(BUILD_DIR)/$(PROJECT_NAME_CLI) $(BUILD_DIR)/$(PROJECT_NAME_GUI)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(BUILD_DIR)/$(PROJECT_NAME_CLI) $(DESTDIR)$(BINDIR)
	cp $(BUILD_DIR)/$(PROJECT_NAME_GUI) $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(DATADIR)
	cp $(BUILD_DIR)/$(GLADE_FILE) $(DESTDIR)$(DATADIR)  # Copia o arquivo GLADE para o diretório de instalação

# Regras de limpeza
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean install
