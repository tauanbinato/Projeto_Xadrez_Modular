@ECHO  OFF
REM  Compila programa C usando nmake %1.mak  do conjunto MS Visual c/c++
REM  Sintaxe:  faz  nome-do-arquivo.mak  [o]
REM                    opção  o : compila otimizado. Todos os obj devem 
REM                               ter sido destruidos antes
REM  Necessita o "environment" corretamente inicializado para usar o compilador
REM       c/c++ da Microsoft  (batch "vsvars32.bat", pasta Visualstudio \Common7\Tools)
REM  Pode necessitar o ajuste da secao :contin para que o NotePad abra 
REM                      corretamente o arquivo de mensagens de erro geradas
REM                      ao compilar

pushd  .

if ""=="%1" goto erro

del *.err

if "o"=="%2" goto otimz
if "O"=="%2" goto otimz

nmake /F%1.make
goto contin

:otimz
nmake /F%1.make "PRD="

:contin
notepad %1.err

goto sai

:erro
echo Falta nome do arquivo a compilar

:sai
popd
