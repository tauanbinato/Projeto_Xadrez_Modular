@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del ExemploSimples*.exe

del *.obj
nmake /Fexemplosimples.make "PRD="

del *.obj
nmake /FexemplosimplesDBG.make 

copy  *.err  tudo.err

notepad tudo.err

popd
