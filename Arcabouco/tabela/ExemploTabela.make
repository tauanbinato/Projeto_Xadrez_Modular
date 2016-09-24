##################################################
###
### Diretivas de MAKE para o construto: ExemploTabela
### Gerado a partir de: ExemploTabela.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = ExemploTabela


### Nomes de paths

Pobj                 = .
Ptab                 = .
Pinc                 = .
Ph                   = .
Perr                 = .
PDEFAULT             = .
Pespstr              = .
Plista               = .
Pc                   = .

### Nomes de diretórios para geração

Fobj                 = .
Ftab                 = .
Finc                 = .
Fh                   = .
Ferr                 = .
FDEFAULT             = .
Fespstr              = .
Flista               = .
Fc                   = .

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


### Regras de geração

all : limpa \
   $(Ftab)\TabelaString.tab   $(Finc)\TesteTabelaString.inc   $(Fobj)\Tabstr.obj \
   $(Fobj)\TestTbs.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Ftab)\TabelaString.tab :  {$(Plista)}\TabelaString.lista \
    {$(PDEFAULT)}STR_APIC.DEF         {$(PDEFAULT)}STR_SEGL.DEF         {$(Pespstr)}TesteTabelaString.espstr
   geratab   /L$(Ftab)\$(@B).lista   /T$(Ftab)\$(@B).tab  >> $(Ferr)\$(NOME).err

$(Finc)\TesteTabelaString.inc :  {$(Pespstr)}\TesteTabelaString.espstr
   geratbdf  /E$(Ftab)\$(@B).espstr /T$(Ftab)\$(@B).inc   >> $(Ferr)\$(NOME).err

$(Fobj)\Tabstr.obj :  {$(Pc)}\Tabstr.c \
    {$(PDEFAULT)}TabStr.H             {$(Ptab)}TabelaString.tab    
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\TestTbs.obj :  {$(Pc)}\TestTbs.c \
    {$(Ph)}TST_Espc.h           {$(Ph)}TabStr.h             {$(Ph)}generico.h           \
    {$(Ph)}lerparm.h            {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\Tabstr.obj   $(Fobj)\TestTbs.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: ExemploTabela
###
##################################################

