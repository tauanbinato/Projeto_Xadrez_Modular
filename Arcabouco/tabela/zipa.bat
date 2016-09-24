REM Gera o zip de distribuicao

c:
cd \lixo
md distribuicao


cd \aartigos\autotest\tabela

copy  *.c        \lixo\distribuicao
copy  *.h        \lixo\distribuicao
copy  *.build    \lixo\distribuicao
copy  *.comp     \lixo\distribuicao
copy  *.exe      \lixo\distribuicao
copy  *.list     \lixo\distribuicao
copy  *.make     \lixo\distribuicao
copy  *.log      \lixo\distribuicao
copy  *.script   \lixo\distribuicao
copy  *.def      \lixo\distribuicao
copy  *.espstr   \lixo\distribuicao
copy  *.inc      \lixo\distribuicao
copy  *.tab      \lixo\distribuicao
copy  *.lista    \lixo\distribuicao
copy  *.estat    \lixo\distribuicao

copy  Compila.bat          \lixo\distribuicao
copy  CompilaTudo.bat      \lixo\distribuicao
copy  exbestat.exe         \lixo\distribuicao
copy  GeraMake.bat         \lixo\distribuicao
copy  GeraTudo.bat         \lixo\distribuicao
copy  Gmake.parm           \lixo\distribuicao
copy  LimpaTudo.bat        \lixo\distribuicao
copy  TestaTudo.bat        \lixo\distribuicao
copy  ArcaboucoTeste.lib   \lixo\distribuicao
copy  Tudo.bat             \lixo\distribuicao

copy  ..\ferramnt\compilebanner.exe  \lixo\distribuicao
copy  ..\ferramnt\exbestat.exe       \lixo\distribuicao
copy  ..\ferramnt\Gmake.exe          \lixo\distribuicao

copy  ..\documentos\GMake-5-4.pdf    \lixo\distribuicao

cd \lixo\distribuicao
del *.zip
pkzipc teste-automatizado-tabela-2005-04 -add=up 
