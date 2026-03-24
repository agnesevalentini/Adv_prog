
# cmake_minimum_required(VERSION 3.20)

# # Nome del progetto
# project(Interpolation
# PROJECT_DESCRIPTION "Interpolation library"
# LANGUAGES CXX)

# # Abilitare supporto per C++17
# set(CMAKE_CXX_STANDARD 17)





# # Aggiungi la directory di pybind11 (se non è trovata automaticamente)
# # Trova pybind11, se non è trovata in modo automatico, indica il percorso dove è installata
# # Puoi sostituire /path/to/pybind11 con il percorso in cui hai pybind11 installato (ad esempio, una directory di installazione specifica)
# #find_package(pybind11 REQUIRED PATHS )

# # Trova la libreria GSL, se non trovata automaticamente, puoi anche specificare il percorso
# # Sostituisci /path/to/gsl con il percorso in cui GSL è installato
# find_package(GSL REQUIRED PATHS /path/to/gsl)


# # Linkare la libreria GSL
# target_link_libraries(Interpolation PRIVATE GSL::GSL)

# # Linkare la libreria pybind11
# target_link_libraries(Interpolation PRIVATE pybind11::module)

# # Se vuoi specificare un percorso di installazione per il modulo, puoi farlo
# # install(TARGETS Interpolation DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/python3.x/site-packages)




###############################################################
cmake_minimum_required(VERSION 3.20) #HOW TO CHOOSE VERSION

# Nome del progetto
project(Interpolation
DESCRIPTION "Interpolation library"
LANGUAGES CXX)



### per compilare un modulo con Python extension 
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

# Source files variable
set(SRCS "AbstractClass.cpp;LinearInterpolation.cpp;LagrangeInterpolation.cpp;NewtonInterpolation.cpp;pybind11.cpp")
# per settare una variabile che contiene i nomi di file/librerie.. set (VAR ";;;")

pybind11_add_module(Interpolation ${SRCS})


#setting variables


# Specify "REQUIRED" if the library is mandatory.
find_package(GSL 2.8 REQUIRED)


set(GSL_DIR "/usr/local/")

target_include_directories(Interpolation PUBLIC ${GSL_DIR}/include)
target_link_directories(Interpolation PUBLIC ${GSL_DIR}/lib)
# Linkare la libreria GSL
target_link_libraries(Interpolation PRIVATE GSL::gsl GSL::gslcblas)




# Aggiungi flag di compilazione (esempio per -DHAVE_INLINE)
target_compile_definitions(Interpolation PRIVATE -DHAVE_INLINE)

# Imposta le flag di compilazione C++
target_compile_options(Interpolation PRIVATE -Wall -Wextra -Wpedantic)


#eventually install the module
install(TARGETS Interpolation DESTINATION .)



















# #setting variables
# set(LIB_NAME "my_lib")
# ...

# #third party library (gsl gnu scientific library)
# #set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} /path/to/modules/") ...pachetti di librerie e files
# set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} /usr/local/")



# #If the library is not located in a system folder, often a hint can be provided:   ?????
# cmake /path/to/src/ -DBOOST_ROOT=/path/to/boost/installation/
















# # Esempio Completo di Comandi
# # Ecco un esempio completo di come eseguire il comando di compilazione e impostare il LD_LIBRARY_PATH:

# # Configura e compila il progetto
# mkdir build
# cd build
# cmake ..
# make

# # Imposta il LD_LIBRARY_PATH per includere la directory delle librerie GSL
# export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# # Esegui lo script Python
# python3 ../Python.py
