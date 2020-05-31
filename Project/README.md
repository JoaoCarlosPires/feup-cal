# TourMateApp - Rotas Turísticas Urbanas Adaptáveis

Turma 7, Grupo 5

## Lista de Dependências

### API's

GraphViewer

### Ficheiros input

porto_full_nodes_latlng.txt
porto_full_edges.txt
porto_full_nodes_xy.txt 

### Bibliotecas

Usamos o ficheiro MutablePriorityQueue.h, da autoria do Professor João Pascoal Faria, de modo a auxiliar no Algoritmo Prim.

## Instruções Compilação

Abrir a pasta com o código fonte (/code/) no CLion, pasta esta que contém as sub-pastas /lib/ e /maps/ (que contêm, respectivamente, a livraria do GraphViewer e os mapas da cidade do Porto).

### Opção 1

Correr o programa directamente no CLion, após fazer Reload CMake Project.

Nota: Ao correr directamente o programa no CLion após realizar as etapas acima mencionadas, o carregamento do mapa demorará entre 3-5 minutos.

### Opção 2

De forma a diminuir o tempo de carregamento para a ordem dos segundos, sugere-se o seguinte procedimento:

Na pasta .idea/, abrir o ficheiro workspace.xml e acrescentar a seguinte linha:

```
<configuration CONFIG_NAME="Release" />
```
De modo a ficar algo do género:

(...)
```
<component name="CMakeSettings">
    <configurations>
        <configuration CONFIG_NAME="Debug" />
        <configuration CONFIG_NAME="Release" />
    </configurations>
</component>
```
(...)

Fazer Reload CMake Project.

De seguida, o procedimento varia conforme o Sistema Operativo.

#### WINDOWS

Navegar até à pasta cmake-build-release/ (ao mesmo nível das pastas lib/, src/ e maps/) e executar o ficheiro
TourMateApp.exe

OU

No canto superior direito do CLion, alterar no menu drop-down da opção TourMateApp | Debug para
TourMateApp | Release. Correr o programa no CLion.

#### LINUX

No canto superior direito do CLion, alterar no menu drop-down da opção TourMateApp | Debug para
TourMateApp | Release. Correr o programa no CLion.
