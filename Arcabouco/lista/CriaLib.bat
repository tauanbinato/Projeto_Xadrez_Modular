ECHO Cria a biblioteca a ser utilizada no exemplo \simples
ECHO assume o arcabouco todo construído e correto

pushd  .

cd  ..\arcabouc\objetos
del    *.obj
del    *.lib
nmake /F..\composicao\crialib.make  "PRD="
copy   arcaboucoteste.lib ..\..\simples

popd
