##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SGELuaCore
ConfigurationName      :=Release
WorkspacePath          := "/home/stuckie/Projects/stuckiegamez/SGEngine/SGEngine"
ProjectPath            := "/home/stuckie/Projects/stuckiegamez/SGEngine/SGECORE/SGELuaCore"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Steven Campbell
Date                   :=10/19/15
CodeLitePath           :="/home/stuckie/.codelite"
LinkerName             :=/usr/bin/g++ 
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="SGELuaCore.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -s
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)lua5.1 
ArLibs                 :=  "lua5.1" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++ 
CC       := /usr/bin/gcc 
CXXFLAGS :=  -O3 -pedantic -W -Wall -fPIC $(Preprocessors)
CFLAGS   :=  -O3 -pedantic -W -Wall -fPIC $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/SGELuaCore.cpp$(ObjectSuffix) $(IntermediateDirectory)/Engine_Logger.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "/home/stuckie/Projects/stuckiegamez/SGEngine/SGEngine/.build-release"
	@echo rebuilt > "/home/stuckie/Projects/stuckiegamez/SGEngine/SGEngine/.build-release/SGELuaCore"

$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/SGELuaCore.cpp$(ObjectSuffix): SGELuaCore.cpp $(IntermediateDirectory)/SGELuaCore.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/stuckie/Projects/stuckiegamez/SGEngine/SGECORE/SGELuaCore/SGELuaCore.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SGELuaCore.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SGELuaCore.cpp$(DependSuffix): SGELuaCore.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SGELuaCore.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SGELuaCore.cpp$(DependSuffix) -MM "SGELuaCore.cpp"

$(IntermediateDirectory)/SGELuaCore.cpp$(PreprocessSuffix): SGELuaCore.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SGELuaCore.cpp$(PreprocessSuffix) "SGELuaCore.cpp"

$(IntermediateDirectory)/Engine_Logger.cpp$(ObjectSuffix): ../../SGEngine/Engine/Logger.cpp $(IntermediateDirectory)/Engine_Logger.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/stuckie/Projects/stuckiegamez/SGEngine/SGEngine/Engine/Logger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_Logger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_Logger.cpp$(DependSuffix): ../../SGEngine/Engine/Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_Logger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_Logger.cpp$(DependSuffix) -MM "../../SGEngine/Engine/Logger.cpp"

$(IntermediateDirectory)/Engine_Logger.cpp$(PreprocessSuffix): ../../SGEngine/Engine/Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_Logger.cpp$(PreprocessSuffix) "../../SGEngine/Engine/Logger.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../SGEngine/.build-release/SGELuaCore"


