REM Gera o zip de distribuicao

c:
cd \lixo
md distribuicao


cd \aartigos\autotest\simples

copy  *.c        \lixo\distribuicao
copy  *.h        \lixo\distribuicao
copy  *.build    \lixo\distribuicao
copy  *.comp     \lixo\distribuicao
copy  *.exe      \lixo\distribuicao
copy  *.list     \lixo\distribuicao
copy  *.make     \lixo\distribuicao
copy  *.log      \lixo\distribuicao
copy  *.script   \lixo\distribuicao

copy  Compila.bat          \lixo\distribuicao
copy  CompilaTudo.bat      \lixo\distribuicao
copy  estatisticas.estat   \lixo\distribuicao
copy  exbestat.exe         \lixo\distribuicao
copy  GeraMake.bat         \lixo\distribuicao
copy  GeraTudo.bat         \lixo\distribuicao
copy  Gmake.dat            \lixo\distribuicao
copy  Leiame-ArcaboucoSimples-2005-03.pdf  \lixo\distribuicao
copy  LimpaTudo.bat        \lixo\distribuicao
copy  TestaTudo.bat        \lixo\distribuicao
copy  ArcaboucoTeste.lib   \lixo\distribuicao
copy  Tudo.bat             \lixo\distribuicao

copy  ..\ferramnt\compilebanner.exe  \lixo\distribuicao
copy  ..\ferramnt\exbestat.exe    \lixo\distribuicao
copy  ..\ferramnt\Gmake.exe       \lixo\distribuicao
copy  ..\ferramnt\Gmake-5-4.pdf   \lixo\distribuicao

copy  ..\documentos\GMake-5-4.pdf    \lixo\distribuicao
copy  ..\documentos\MCC-09-03-TesteAutomatizado.pdf   \lixo\distribuicao

cd \lixo\distribuicao
del *.zip
pkzipc teste-automatizado-simples-2005-03 -add=up 
