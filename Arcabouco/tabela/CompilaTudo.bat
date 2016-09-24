@ECHO  OFF
REM  Compila todos os programas que compõem o exemplo tabela

pushd  .

del *.err
del ExemploTabela*.exe
del *.obj

cl /D_CRT_SECURE_NO_DEPRECATE /Ox /F 32000 /J /W4 GeraTab.c  >  GeraTab.err

cl /D_CRT_SECURE_NO_DEPRECATE /Ox /F 32000 /J /W4 GeraTbdf.c >> GeraTbdf.err

nmake /Fexemplotabela.make

copy  *.err  tudo.err
notepad tudo.err

popd
