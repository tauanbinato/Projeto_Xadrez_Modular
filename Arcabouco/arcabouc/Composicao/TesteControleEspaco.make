##################################################
###
### Diretivas de MAKE para o construto: TesteControleEspaco
### Gerado a partir de: TesteControleEspaco.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteControleEspaco


### Nomes de paths

Pinc                 = ..\Tabelas
Ptab                 = ..\Tabelas
Pdef                 = ..\Tabelas
Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

Finc                 = ..\Tabelas
Ftab                 = ..\Tabelas
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
O       = /Ox  /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\princip.obj   $(Fobj)\generico.obj   $(Fobj)\tabsimb.obj \
   $(Fobj)\lerparm.obj   $(Fobj)\cespdin.obj   $(Fobj)\conta.obj \
   $(Fobj)\geraalt.obj   $(Fobj)\intrpced.obj   $(Fobj)\intrpcnt.obj \
   $(Fobj)\testced.obj \
   Construto

### Limpar arquivos

limpa :
   ..\..\Ferramnt\CompileBanner /c$(NOME)
   ..\..\Ferramnt\CompileBanner /c$(NOME) >$(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\princip.obj :  {$(Pc)}\princip.c \
    {$(Ph)}generico.h           {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\generico.obj :  {$(Pc)}\generico.c \
    {$(Ph)}cespdin.h            {$(Ph)}generico.h           {$(Ph)}intrpced.h           \
    {$(Ph)}intrpcnt.h           {$(Ph)}lerparm.h            {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\tabsimb.obj :  {$(Pc)}\tabsimb.c \
    {$(Ph)}cespdin.h            {$(Ph)}generico.h           {$(Ph)}tabsimb.h            \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lerparm.obj :  {$(Pc)}\lerparm.c \
    {$(Ph)}generico.h           {$(Ph)}lerparm.h            {$(Ph)}tabsimb.h            \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\cespdin.obj :  {$(Pc)}\cespdin.c \
    ..\tabelas\idtiposespaco.def {$(Ph)}cespdin.h            {$(Ph)}generico.h           \
    {$(Ph)}geraalt.h            {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\conta.obj :  {$(Pc)}\conta.c \
    {$(Ph)}cespdin.h            {$(Ph)}conta.h              {$(Ph)}generico.h           \
    {$(Ph)}tabsimb.h            {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\geraalt.obj :  {$(Pc)}\geraalt.c \
    {$(Ph)}geraalt.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\intrpced.obj :  {$(Pc)}\intrpced.c \
    {$(Ph)}cespdin.h            {$(Ph)}generico.h           {$(Ph)}intrpced.h           \
    {$(Ph)}lerparm.h            {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\intrpcnt.obj :  {$(Pc)}\intrpcnt.c \
    {$(Ph)}conta.h              {$(Ph)}generico.h           {$(Ph)}intrpcnt.h           \
    {$(Ph)}lerparm.h            {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\testced.obj :  {$(Pc)}\testced.c \
    {$(Ph)}cespdin.h            {$(Ph)}generico.h           {$(Ph)}lerparm.h            \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\princip.obj   $(Fobj)\generico.obj   $(Fobj)\tabsimb.obj \
   $(Fobj)\lerparm.obj   $(Fobj)\cespdin.obj   $(Fobj)\conta.obj \
   $(Fobj)\geraalt.obj   $(Fobj)\intrpced.obj   $(Fobj)\intrpcnt.obj \
   $(Fobj)\testced.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteControleEspaco
###
##################################################

