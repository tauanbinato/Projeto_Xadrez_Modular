ECHO Cria a biblioteca a ser utilizada no exemplo \simples
ECHO assume o arcabouco todo constru�do e correto

pushd  .

cd    ..\..\arcabouc\objetos
del    *.obj
del    *.lib
nmake /F..\..\arcabouc\composicao\crialib.make  "PRD="
copy  ArcaboucoTeste.lib  ..\..\instrum\objetos

popd
