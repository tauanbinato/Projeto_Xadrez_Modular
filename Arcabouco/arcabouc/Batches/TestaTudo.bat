rem testa todos os scripts

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testefuncoes          /s..\scripts\testefuncoes            /l..\produto\testegenerico            /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testealeatorio        /s..\scripts\testealeatorio          /l..\produto\testealeatorio           /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testelerparametros    /s..\scripts\testelerparametros      /l..\produto\testelerparametros       /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteControleEspaco   /s..\scripts\testecontroleespaco     /l..\produto\testecontroleespaco      /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteControleEspaco   /s..\scripts\testecontroleespaco-lim /l..\produto\testecontroleespaco-lim  /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteControleEspaco   /s..\scripts\testecontroleespaco-voa /l..\produto\testecontroleespaco-voa  /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testetabelasimbolos   /s..\scripts\testetabelasimbolos     /l..\produto\testetabelasimbolos      /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testecontadores       /s..\scripts\testecontadores         /l..\produto\testecontadores          /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\..\ferramnt\CompileBanner     /c"Estatisticas acumuladas"
..\..\ferramnt\exbestat /e..\scripts\estatisticas

:sai

