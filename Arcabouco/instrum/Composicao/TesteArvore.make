##################################################
###
### Diretivas de MAKE para o construto: TesteArvore
### Gerado a partir de: TesteArvore.comp
###
### ----- Arquivo gerado, N�O EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteArvore


### Nomes de paths

Pdef                 = ..\Tabelas
Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diret�rios para gera��o

Fdef                 = ..\Tabelas
Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de gera��o

all : limpa \
   $(Fobj)\arvore.obj   $(Fobj)\testarv.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Depend�ncias de m�dulos objeto a compilar

$(Fobj)\arvore.obj :  {$(Pc)}\arvore.c \
    ..\\tabelas\\idtiposespaco.def {$(Ph)}arvore.h             {$(Ph)}cespdin.h            \
    {$(Ph)}conta.h              {$(Ph)}generico.h           {$(Pdef)}tiposespacosarvore.def \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\testarv.obj :  {$(Pc)}\testarv.c \
    {$(Ph)}arvore.h             {$(Ph)}cespdin.h            {$(Ph)}generico.h           \
    {$(Ph)}lerparm.h            {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Termina��o

Construto : \
   $(Fobj)\arvore.obj   $(Fobj)\testarv.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteArvore
###
##################################################

