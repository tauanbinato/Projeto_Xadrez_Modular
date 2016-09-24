@ECHO  OFF
REM  Gera os scripts de MAKE para o teste de tabelas

pushd  .

copy  tabelastringinicial.tab  tabelastring.tab
gmake /cExemploTabela

popd
