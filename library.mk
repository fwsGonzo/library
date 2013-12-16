##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=library
ConfigurationName      :=Debug
WorkspacePath          := "E:\Git\library"
ProjectPath            := "E:\Git\library"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=GONZO
Date                   :=12/16/13
CodeLitePath           :="E:\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="library.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=E:\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/library_config$(ObjectSuffix) $(IntermediateDirectory)/library_log$(ObjectSuffix) $(IntermediateDirectory)/library_main$(ObjectSuffix) $(IntermediateDirectory)/res_library.rc$(ObjectSuffix) $(IntermediateDirectory)/src_main$(ObjectSuffix) $(IntermediateDirectory)/bitmap_bitmap$(ObjectSuffix) $(IntermediateDirectory)/bitmap_colortools$(ObjectSuffix) $(IntermediateDirectory)/bitmap_lodepng$(ObjectSuffix) $(IntermediateDirectory)/compression_lzo$(ObjectSuffix) $(IntermediateDirectory)/math_baseconv$(ObjectSuffix) \
	$(IntermediateDirectory)/math_frustum$(ObjectSuffix) $(IntermediateDirectory)/math_matrix$(ObjectSuffix) $(IntermediateDirectory)/math_quaternion$(ObjectSuffix) $(IntermediateDirectory)/math_vec3$(ObjectSuffix) $(IntermediateDirectory)/math_vec4$(ObjectSuffix) $(IntermediateDirectory)/math_vector$(ObjectSuffix) $(IntermediateDirectory)/math_voronoi$(ObjectSuffix) $(IntermediateDirectory)/network_hostaddr$(ObjectSuffix) $(IntermediateDirectory)/network_socket$(ObjectSuffix) $(IntermediateDirectory)/network_tcpsocket$(ObjectSuffix) \
	$(IntermediateDirectory)/noise_cosnoise$(ObjectSuffix) $(IntermediateDirectory)/noise_gabor$(ObjectSuffix) $(IntermediateDirectory)/noise_multifractal$(ObjectSuffix) $(IntermediateDirectory)/noise_noise1234$(ObjectSuffix) $(IntermediateDirectory)/noise_sdnoise1234$(ObjectSuffix) $(IntermediateDirectory)/noise_simplex1234$(ObjectSuffix) $(IntermediateDirectory)/noise_srdnoise23$(ObjectSuffix) $(IntermediateDirectory)/noise_torusnoise$(ObjectSuffix) $(IntermediateDirectory)/noise_turbulence$(ObjectSuffix) $(IntermediateDirectory)/noise_worley$(ObjectSuffix) \
	$(IntermediateDirectory)/opengl_camera$(ObjectSuffix) $(IntermediateDirectory)/opengl_fbo$(ObjectSuffix) $(IntermediateDirectory)/opengl_input$(ObjectSuffix) $(IntermediateDirectory)/opengl_oglfont$(ObjectSuffix) $(IntermediateDirectory)/opengl_oglfont_shader$(ObjectSuffix) $(IntermediateDirectory)/opengl_opengl$(ObjectSuffix) $(IntermediateDirectory)/opengl_openglext$(ObjectSuffix) $(IntermediateDirectory)/opengl_shader$(ObjectSuffix) $(IntermediateDirectory)/opengl_texture$(ObjectSuffix) $(IntermediateDirectory)/opengl_vao$(ObjectSuffix) \
	$(IntermediateDirectory)/opengl_window$(ObjectSuffix) $(IntermediateDirectory)/script_script$(ObjectSuffix) $(IntermediateDirectory)/sound_sound$(ObjectSuffix) $(IntermediateDirectory)/sound_soundsystem$(ObjectSuffix) $(IntermediateDirectory)/sound_stream$(ObjectSuffix) $(IntermediateDirectory)/sound_stream_channel$(ObjectSuffix) $(IntermediateDirectory)/storage_bitarray$(ObjectSuffix) $(IntermediateDirectory)/threading_TThread$(ObjectSuffix) $(IntermediateDirectory)/threading_TThreadPool$(ObjectSuffix) $(IntermediateDirectory)/timing_highperf$(ObjectSuffix) \
	$(IntermediateDirectory)/timing_timer$(ObjectSuffix) $(IntermediateDirectory)/voxels_voxelizer$(ObjectSuffix) $(IntermediateDirectory)/voxels_voxelmodel$(ObjectSuffix) 



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
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/library_config$(ObjectSuffix): library/config.cpp $(IntermediateDirectory)/library_config$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/library_config$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/library_config$(DependSuffix): library/config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/library_config$(ObjectSuffix) -MF$(IntermediateDirectory)/library_config$(DependSuffix) -MM "library/config.cpp"

$(IntermediateDirectory)/library_config$(PreprocessSuffix): library/config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/library_config$(PreprocessSuffix) "library/config.cpp"

$(IntermediateDirectory)/library_log$(ObjectSuffix): library/log.cpp $(IntermediateDirectory)/library_log$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/library_log$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/library_log$(DependSuffix): library/log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/library_log$(ObjectSuffix) -MF$(IntermediateDirectory)/library_log$(DependSuffix) -MM "library/log.cpp"

$(IntermediateDirectory)/library_log$(PreprocessSuffix): library/log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/library_log$(PreprocessSuffix) "library/log.cpp"

$(IntermediateDirectory)/library_main$(ObjectSuffix): library/main.cpp $(IntermediateDirectory)/library_main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/library_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/library_main$(DependSuffix): library/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/library_main$(ObjectSuffix) -MF$(IntermediateDirectory)/library_main$(DependSuffix) -MM "library/main.cpp"

$(IntermediateDirectory)/library_main$(PreprocessSuffix): library/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/library_main$(PreprocessSuffix) "library/main.cpp"

$(IntermediateDirectory)/res_library.rc$(ObjectSuffix): res/library.rc
	$(RcCompilerName) -i "E:/Git/library/res/library.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/res_library.rc$(ObjectSuffix) $(RcIncludePath)
$(IntermediateDirectory)/src_main$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main$(DependSuffix) -MM "src/main.cpp"

$(IntermediateDirectory)/src_main$(PreprocessSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main$(PreprocessSuffix) "src/main.cpp"

$(IntermediateDirectory)/bitmap_bitmap$(ObjectSuffix): library/bitmap/bitmap.cpp $(IntermediateDirectory)/bitmap_bitmap$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/bitmap/bitmap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bitmap_bitmap$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bitmap_bitmap$(DependSuffix): library/bitmap/bitmap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bitmap_bitmap$(ObjectSuffix) -MF$(IntermediateDirectory)/bitmap_bitmap$(DependSuffix) -MM "library/bitmap/bitmap.cpp"

$(IntermediateDirectory)/bitmap_bitmap$(PreprocessSuffix): library/bitmap/bitmap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bitmap_bitmap$(PreprocessSuffix) "library/bitmap/bitmap.cpp"

$(IntermediateDirectory)/bitmap_colortools$(ObjectSuffix): library/bitmap/colortools.cpp $(IntermediateDirectory)/bitmap_colortools$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/bitmap/colortools.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bitmap_colortools$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bitmap_colortools$(DependSuffix): library/bitmap/colortools.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bitmap_colortools$(ObjectSuffix) -MF$(IntermediateDirectory)/bitmap_colortools$(DependSuffix) -MM "library/bitmap/colortools.cpp"

$(IntermediateDirectory)/bitmap_colortools$(PreprocessSuffix): library/bitmap/colortools.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bitmap_colortools$(PreprocessSuffix) "library/bitmap/colortools.cpp"

$(IntermediateDirectory)/bitmap_lodepng$(ObjectSuffix): library/bitmap/lodepng.cpp $(IntermediateDirectory)/bitmap_lodepng$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/bitmap/lodepng.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bitmap_lodepng$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bitmap_lodepng$(DependSuffix): library/bitmap/lodepng.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bitmap_lodepng$(ObjectSuffix) -MF$(IntermediateDirectory)/bitmap_lodepng$(DependSuffix) -MM "library/bitmap/lodepng.cpp"

$(IntermediateDirectory)/bitmap_lodepng$(PreprocessSuffix): library/bitmap/lodepng.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bitmap_lodepng$(PreprocessSuffix) "library/bitmap/lodepng.cpp"

$(IntermediateDirectory)/compression_lzo$(ObjectSuffix): library/compression/lzo.cpp $(IntermediateDirectory)/compression_lzo$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/compression/lzo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/compression_lzo$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/compression_lzo$(DependSuffix): library/compression/lzo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/compression_lzo$(ObjectSuffix) -MF$(IntermediateDirectory)/compression_lzo$(DependSuffix) -MM "library/compression/lzo.cpp"

$(IntermediateDirectory)/compression_lzo$(PreprocessSuffix): library/compression/lzo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/compression_lzo$(PreprocessSuffix) "library/compression/lzo.cpp"

$(IntermediateDirectory)/math_baseconv$(ObjectSuffix): library/math/baseconv.cpp $(IntermediateDirectory)/math_baseconv$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/math/baseconv.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_baseconv$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_baseconv$(DependSuffix): library/math/baseconv.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/math_baseconv$(ObjectSuffix) -MF$(IntermediateDirectory)/math_baseconv$(DependSuffix) -MM "library/math/baseconv.cpp"

$(IntermediateDirectory)/math_baseconv$(PreprocessSuffix): library/math/baseconv.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_baseconv$(PreprocessSuffix) "library/math/baseconv.cpp"

$(IntermediateDirectory)/math_frustum$(ObjectSuffix): library/math/frustum.cpp $(IntermediateDirectory)/math_frustum$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/math/frustum.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_frustum$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_frustum$(DependSuffix): library/math/frustum.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/math_frustum$(ObjectSuffix) -MF$(IntermediateDirectory)/math_frustum$(DependSuffix) -MM "library/math/frustum.cpp"

$(IntermediateDirectory)/math_frustum$(PreprocessSuffix): library/math/frustum.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_frustum$(PreprocessSuffix) "library/math/frustum.cpp"

$(IntermediateDirectory)/math_matrix$(ObjectSuffix): library/math/matrix.cpp $(IntermediateDirectory)/math_matrix$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/math/matrix.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_matrix$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_matrix$(DependSuffix): library/math/matrix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/math_matrix$(ObjectSuffix) -MF$(IntermediateDirectory)/math_matrix$(DependSuffix) -MM "library/math/matrix.cpp"

$(IntermediateDirectory)/math_matrix$(PreprocessSuffix): library/math/matrix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_matrix$(PreprocessSuffix) "library/math/matrix.cpp"

$(IntermediateDirectory)/math_quaternion$(ObjectSuffix): library/math/quaternion.cpp $(IntermediateDirectory)/math_quaternion$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/math/quaternion.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_quaternion$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_quaternion$(DependSuffix): library/math/quaternion.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/math_quaternion$(ObjectSuffix) -MF$(IntermediateDirectory)/math_quaternion$(DependSuffix) -MM "library/math/quaternion.cpp"

$(IntermediateDirectory)/math_quaternion$(PreprocessSuffix): library/math/quaternion.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_quaternion$(PreprocessSuffix) "library/math/quaternion.cpp"

$(IntermediateDirectory)/math_vec3$(ObjectSuffix): library/math/vec3.cpp $(IntermediateDirectory)/math_vec3$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/math/vec3.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_vec3$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_vec3$(DependSuffix): library/math/vec3.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/math_vec3$(ObjectSuffix) -MF$(IntermediateDirectory)/math_vec3$(DependSuffix) -MM "library/math/vec3.cpp"

$(IntermediateDirectory)/math_vec3$(PreprocessSuffix): library/math/vec3.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_vec3$(PreprocessSuffix) "library/math/vec3.cpp"

$(IntermediateDirectory)/math_vec4$(ObjectSuffix): library/math/vec4.cpp $(IntermediateDirectory)/math_vec4$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/math/vec4.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_vec4$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_vec4$(DependSuffix): library/math/vec4.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/math_vec4$(ObjectSuffix) -MF$(IntermediateDirectory)/math_vec4$(DependSuffix) -MM "library/math/vec4.cpp"

$(IntermediateDirectory)/math_vec4$(PreprocessSuffix): library/math/vec4.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_vec4$(PreprocessSuffix) "library/math/vec4.cpp"

$(IntermediateDirectory)/math_vector$(ObjectSuffix): library/math/vector.cpp $(IntermediateDirectory)/math_vector$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/math/vector.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_vector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_vector$(DependSuffix): library/math/vector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/math_vector$(ObjectSuffix) -MF$(IntermediateDirectory)/math_vector$(DependSuffix) -MM "library/math/vector.cpp"

$(IntermediateDirectory)/math_vector$(PreprocessSuffix): library/math/vector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_vector$(PreprocessSuffix) "library/math/vector.cpp"

$(IntermediateDirectory)/math_voronoi$(ObjectSuffix): library/math/voronoi.cpp $(IntermediateDirectory)/math_voronoi$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/math/voronoi.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_voronoi$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_voronoi$(DependSuffix): library/math/voronoi.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/math_voronoi$(ObjectSuffix) -MF$(IntermediateDirectory)/math_voronoi$(DependSuffix) -MM "library/math/voronoi.cpp"

$(IntermediateDirectory)/math_voronoi$(PreprocessSuffix): library/math/voronoi.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_voronoi$(PreprocessSuffix) "library/math/voronoi.cpp"

$(IntermediateDirectory)/network_hostaddr$(ObjectSuffix): library/network/hostaddr.cpp $(IntermediateDirectory)/network_hostaddr$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/network/hostaddr.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/network_hostaddr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/network_hostaddr$(DependSuffix): library/network/hostaddr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/network_hostaddr$(ObjectSuffix) -MF$(IntermediateDirectory)/network_hostaddr$(DependSuffix) -MM "library/network/hostaddr.cpp"

$(IntermediateDirectory)/network_hostaddr$(PreprocessSuffix): library/network/hostaddr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/network_hostaddr$(PreprocessSuffix) "library/network/hostaddr.cpp"

$(IntermediateDirectory)/network_socket$(ObjectSuffix): library/network/socket.cpp $(IntermediateDirectory)/network_socket$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/network/socket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/network_socket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/network_socket$(DependSuffix): library/network/socket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/network_socket$(ObjectSuffix) -MF$(IntermediateDirectory)/network_socket$(DependSuffix) -MM "library/network/socket.cpp"

$(IntermediateDirectory)/network_socket$(PreprocessSuffix): library/network/socket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/network_socket$(PreprocessSuffix) "library/network/socket.cpp"

$(IntermediateDirectory)/network_tcpsocket$(ObjectSuffix): library/network/tcpsocket.cpp $(IntermediateDirectory)/network_tcpsocket$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/network/tcpsocket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/network_tcpsocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/network_tcpsocket$(DependSuffix): library/network/tcpsocket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/network_tcpsocket$(ObjectSuffix) -MF$(IntermediateDirectory)/network_tcpsocket$(DependSuffix) -MM "library/network/tcpsocket.cpp"

$(IntermediateDirectory)/network_tcpsocket$(PreprocessSuffix): library/network/tcpsocket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/network_tcpsocket$(PreprocessSuffix) "library/network/tcpsocket.cpp"

$(IntermediateDirectory)/noise_cosnoise$(ObjectSuffix): library/noise/cosnoise.cpp $(IntermediateDirectory)/noise_cosnoise$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/noise/cosnoise.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_cosnoise$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_cosnoise$(DependSuffix): library/noise/cosnoise.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_cosnoise$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_cosnoise$(DependSuffix) -MM "library/noise/cosnoise.cpp"

$(IntermediateDirectory)/noise_cosnoise$(PreprocessSuffix): library/noise/cosnoise.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_cosnoise$(PreprocessSuffix) "library/noise/cosnoise.cpp"

$(IntermediateDirectory)/noise_gabor$(ObjectSuffix): library/noise/gabor.c $(IntermediateDirectory)/noise_gabor$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/gabor.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_gabor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_gabor$(DependSuffix): library/noise/gabor.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_gabor$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_gabor$(DependSuffix) -MM "library/noise/gabor.c"

$(IntermediateDirectory)/noise_gabor$(PreprocessSuffix): library/noise/gabor.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_gabor$(PreprocessSuffix) "library/noise/gabor.c"

$(IntermediateDirectory)/noise_multifractal$(ObjectSuffix): library/noise/multifractal.c $(IntermediateDirectory)/noise_multifractal$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/multifractal.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_multifractal$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_multifractal$(DependSuffix): library/noise/multifractal.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_multifractal$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_multifractal$(DependSuffix) -MM "library/noise/multifractal.c"

$(IntermediateDirectory)/noise_multifractal$(PreprocessSuffix): library/noise/multifractal.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_multifractal$(PreprocessSuffix) "library/noise/multifractal.c"

$(IntermediateDirectory)/noise_noise1234$(ObjectSuffix): library/noise/noise1234.c $(IntermediateDirectory)/noise_noise1234$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/noise1234.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_noise1234$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_noise1234$(DependSuffix): library/noise/noise1234.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_noise1234$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_noise1234$(DependSuffix) -MM "library/noise/noise1234.c"

$(IntermediateDirectory)/noise_noise1234$(PreprocessSuffix): library/noise/noise1234.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_noise1234$(PreprocessSuffix) "library/noise/noise1234.c"

$(IntermediateDirectory)/noise_sdnoise1234$(ObjectSuffix): library/noise/sdnoise1234.c $(IntermediateDirectory)/noise_sdnoise1234$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/sdnoise1234.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_sdnoise1234$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_sdnoise1234$(DependSuffix): library/noise/sdnoise1234.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_sdnoise1234$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_sdnoise1234$(DependSuffix) -MM "library/noise/sdnoise1234.c"

$(IntermediateDirectory)/noise_sdnoise1234$(PreprocessSuffix): library/noise/sdnoise1234.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_sdnoise1234$(PreprocessSuffix) "library/noise/sdnoise1234.c"

$(IntermediateDirectory)/noise_simplex1234$(ObjectSuffix): library/noise/simplex1234.c $(IntermediateDirectory)/noise_simplex1234$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/simplex1234.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_simplex1234$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_simplex1234$(DependSuffix): library/noise/simplex1234.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_simplex1234$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_simplex1234$(DependSuffix) -MM "library/noise/simplex1234.c"

$(IntermediateDirectory)/noise_simplex1234$(PreprocessSuffix): library/noise/simplex1234.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_simplex1234$(PreprocessSuffix) "library/noise/simplex1234.c"

$(IntermediateDirectory)/noise_srdnoise23$(ObjectSuffix): library/noise/srdnoise23.c $(IntermediateDirectory)/noise_srdnoise23$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/srdnoise23.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_srdnoise23$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_srdnoise23$(DependSuffix): library/noise/srdnoise23.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_srdnoise23$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_srdnoise23$(DependSuffix) -MM "library/noise/srdnoise23.c"

$(IntermediateDirectory)/noise_srdnoise23$(PreprocessSuffix): library/noise/srdnoise23.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_srdnoise23$(PreprocessSuffix) "library/noise/srdnoise23.c"

$(IntermediateDirectory)/noise_torusnoise$(ObjectSuffix): library/noise/torusnoise.c $(IntermediateDirectory)/noise_torusnoise$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/torusnoise.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_torusnoise$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_torusnoise$(DependSuffix): library/noise/torusnoise.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_torusnoise$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_torusnoise$(DependSuffix) -MM "library/noise/torusnoise.c"

$(IntermediateDirectory)/noise_torusnoise$(PreprocessSuffix): library/noise/torusnoise.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_torusnoise$(PreprocessSuffix) "library/noise/torusnoise.c"

$(IntermediateDirectory)/noise_turbulence$(ObjectSuffix): library/noise/turbulence.c $(IntermediateDirectory)/noise_turbulence$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/turbulence.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_turbulence$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_turbulence$(DependSuffix): library/noise/turbulence.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_turbulence$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_turbulence$(DependSuffix) -MM "library/noise/turbulence.c"

$(IntermediateDirectory)/noise_turbulence$(PreprocessSuffix): library/noise/turbulence.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_turbulence$(PreprocessSuffix) "library/noise/turbulence.c"

$(IntermediateDirectory)/noise_worley$(ObjectSuffix): library/noise/worley.c $(IntermediateDirectory)/noise_worley$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Git/library/library/noise/worley.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/noise_worley$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/noise_worley$(DependSuffix): library/noise/worley.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/noise_worley$(ObjectSuffix) -MF$(IntermediateDirectory)/noise_worley$(DependSuffix) -MM "library/noise/worley.c"

$(IntermediateDirectory)/noise_worley$(PreprocessSuffix): library/noise/worley.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/noise_worley$(PreprocessSuffix) "library/noise/worley.c"

$(IntermediateDirectory)/opengl_camera$(ObjectSuffix): library/opengl/camera.cpp $(IntermediateDirectory)/opengl_camera$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/camera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_camera$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_camera$(DependSuffix): library/opengl/camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_camera$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_camera$(DependSuffix) -MM "library/opengl/camera.cpp"

$(IntermediateDirectory)/opengl_camera$(PreprocessSuffix): library/opengl/camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_camera$(PreprocessSuffix) "library/opengl/camera.cpp"

$(IntermediateDirectory)/opengl_fbo$(ObjectSuffix): library/opengl/fbo.cpp $(IntermediateDirectory)/opengl_fbo$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/fbo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_fbo$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_fbo$(DependSuffix): library/opengl/fbo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_fbo$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_fbo$(DependSuffix) -MM "library/opengl/fbo.cpp"

$(IntermediateDirectory)/opengl_fbo$(PreprocessSuffix): library/opengl/fbo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_fbo$(PreprocessSuffix) "library/opengl/fbo.cpp"

$(IntermediateDirectory)/opengl_input$(ObjectSuffix): library/opengl/input.cpp $(IntermediateDirectory)/opengl_input$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/input.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_input$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_input$(DependSuffix): library/opengl/input.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_input$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_input$(DependSuffix) -MM "library/opengl/input.cpp"

$(IntermediateDirectory)/opengl_input$(PreprocessSuffix): library/opengl/input.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_input$(PreprocessSuffix) "library/opengl/input.cpp"

$(IntermediateDirectory)/opengl_oglfont$(ObjectSuffix): library/opengl/oglfont.cpp $(IntermediateDirectory)/opengl_oglfont$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/oglfont.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_oglfont$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_oglfont$(DependSuffix): library/opengl/oglfont.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_oglfont$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_oglfont$(DependSuffix) -MM "library/opengl/oglfont.cpp"

$(IntermediateDirectory)/opengl_oglfont$(PreprocessSuffix): library/opengl/oglfont.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_oglfont$(PreprocessSuffix) "library/opengl/oglfont.cpp"

$(IntermediateDirectory)/opengl_oglfont_shader$(ObjectSuffix): library/opengl/oglfont_shader.cpp $(IntermediateDirectory)/opengl_oglfont_shader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/oglfont_shader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_oglfont_shader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_oglfont_shader$(DependSuffix): library/opengl/oglfont_shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_oglfont_shader$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_oglfont_shader$(DependSuffix) -MM "library/opengl/oglfont_shader.cpp"

$(IntermediateDirectory)/opengl_oglfont_shader$(PreprocessSuffix): library/opengl/oglfont_shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_oglfont_shader$(PreprocessSuffix) "library/opengl/oglfont_shader.cpp"

$(IntermediateDirectory)/opengl_opengl$(ObjectSuffix): library/opengl/opengl.cpp $(IntermediateDirectory)/opengl_opengl$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/opengl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_opengl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_opengl$(DependSuffix): library/opengl/opengl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_opengl$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_opengl$(DependSuffix) -MM "library/opengl/opengl.cpp"

$(IntermediateDirectory)/opengl_opengl$(PreprocessSuffix): library/opengl/opengl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_opengl$(PreprocessSuffix) "library/opengl/opengl.cpp"

$(IntermediateDirectory)/opengl_openglext$(ObjectSuffix): library/opengl/openglext.cpp $(IntermediateDirectory)/opengl_openglext$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/openglext.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_openglext$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_openglext$(DependSuffix): library/opengl/openglext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_openglext$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_openglext$(DependSuffix) -MM "library/opengl/openglext.cpp"

$(IntermediateDirectory)/opengl_openglext$(PreprocessSuffix): library/opengl/openglext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_openglext$(PreprocessSuffix) "library/opengl/openglext.cpp"

$(IntermediateDirectory)/opengl_shader$(ObjectSuffix): library/opengl/shader.cpp $(IntermediateDirectory)/opengl_shader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/shader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_shader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_shader$(DependSuffix): library/opengl/shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_shader$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_shader$(DependSuffix) -MM "library/opengl/shader.cpp"

$(IntermediateDirectory)/opengl_shader$(PreprocessSuffix): library/opengl/shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_shader$(PreprocessSuffix) "library/opengl/shader.cpp"

$(IntermediateDirectory)/opengl_texture$(ObjectSuffix): library/opengl/texture.cpp $(IntermediateDirectory)/opengl_texture$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/texture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_texture$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_texture$(DependSuffix): library/opengl/texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_texture$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_texture$(DependSuffix) -MM "library/opengl/texture.cpp"

$(IntermediateDirectory)/opengl_texture$(PreprocessSuffix): library/opengl/texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_texture$(PreprocessSuffix) "library/opengl/texture.cpp"

$(IntermediateDirectory)/opengl_vao$(ObjectSuffix): library/opengl/vao.cpp $(IntermediateDirectory)/opengl_vao$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/vao.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_vao$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_vao$(DependSuffix): library/opengl/vao.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_vao$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_vao$(DependSuffix) -MM "library/opengl/vao.cpp"

$(IntermediateDirectory)/opengl_vao$(PreprocessSuffix): library/opengl/vao.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_vao$(PreprocessSuffix) "library/opengl/vao.cpp"

$(IntermediateDirectory)/opengl_window$(ObjectSuffix): library/opengl/window.cpp $(IntermediateDirectory)/opengl_window$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/opengl/window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opengl_window$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opengl_window$(DependSuffix): library/opengl/window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opengl_window$(ObjectSuffix) -MF$(IntermediateDirectory)/opengl_window$(DependSuffix) -MM "library/opengl/window.cpp"

$(IntermediateDirectory)/opengl_window$(PreprocessSuffix): library/opengl/window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opengl_window$(PreprocessSuffix) "library/opengl/window.cpp"

$(IntermediateDirectory)/script_script$(ObjectSuffix): library/script/script.cpp $(IntermediateDirectory)/script_script$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/script/script.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/script_script$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/script_script$(DependSuffix): library/script/script.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/script_script$(ObjectSuffix) -MF$(IntermediateDirectory)/script_script$(DependSuffix) -MM "library/script/script.cpp"

$(IntermediateDirectory)/script_script$(PreprocessSuffix): library/script/script.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/script_script$(PreprocessSuffix) "library/script/script.cpp"

$(IntermediateDirectory)/sound_sound$(ObjectSuffix): library/sound/sound.cpp $(IntermediateDirectory)/sound_sound$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/sound/sound.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sound_sound$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sound_sound$(DependSuffix): library/sound/sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sound_sound$(ObjectSuffix) -MF$(IntermediateDirectory)/sound_sound$(DependSuffix) -MM "library/sound/sound.cpp"

$(IntermediateDirectory)/sound_sound$(PreprocessSuffix): library/sound/sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sound_sound$(PreprocessSuffix) "library/sound/sound.cpp"

$(IntermediateDirectory)/sound_soundsystem$(ObjectSuffix): library/sound/soundsystem.cpp $(IntermediateDirectory)/sound_soundsystem$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/sound/soundsystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sound_soundsystem$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sound_soundsystem$(DependSuffix): library/sound/soundsystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sound_soundsystem$(ObjectSuffix) -MF$(IntermediateDirectory)/sound_soundsystem$(DependSuffix) -MM "library/sound/soundsystem.cpp"

$(IntermediateDirectory)/sound_soundsystem$(PreprocessSuffix): library/sound/soundsystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sound_soundsystem$(PreprocessSuffix) "library/sound/soundsystem.cpp"

$(IntermediateDirectory)/sound_stream$(ObjectSuffix): library/sound/stream.cpp $(IntermediateDirectory)/sound_stream$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/sound/stream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sound_stream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sound_stream$(DependSuffix): library/sound/stream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sound_stream$(ObjectSuffix) -MF$(IntermediateDirectory)/sound_stream$(DependSuffix) -MM "library/sound/stream.cpp"

$(IntermediateDirectory)/sound_stream$(PreprocessSuffix): library/sound/stream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sound_stream$(PreprocessSuffix) "library/sound/stream.cpp"

$(IntermediateDirectory)/sound_stream_channel$(ObjectSuffix): library/sound/stream_channel.cpp $(IntermediateDirectory)/sound_stream_channel$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/sound/stream_channel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sound_stream_channel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sound_stream_channel$(DependSuffix): library/sound/stream_channel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sound_stream_channel$(ObjectSuffix) -MF$(IntermediateDirectory)/sound_stream_channel$(DependSuffix) -MM "library/sound/stream_channel.cpp"

$(IntermediateDirectory)/sound_stream_channel$(PreprocessSuffix): library/sound/stream_channel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sound_stream_channel$(PreprocessSuffix) "library/sound/stream_channel.cpp"

$(IntermediateDirectory)/storage_bitarray$(ObjectSuffix): library/storage/bitarray.cpp $(IntermediateDirectory)/storage_bitarray$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/storage/bitarray.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/storage_bitarray$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/storage_bitarray$(DependSuffix): library/storage/bitarray.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/storage_bitarray$(ObjectSuffix) -MF$(IntermediateDirectory)/storage_bitarray$(DependSuffix) -MM "library/storage/bitarray.cpp"

$(IntermediateDirectory)/storage_bitarray$(PreprocessSuffix): library/storage/bitarray.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/storage_bitarray$(PreprocessSuffix) "library/storage/bitarray.cpp"

$(IntermediateDirectory)/threading_TThread$(ObjectSuffix): library/threading/TThread.cpp $(IntermediateDirectory)/threading_TThread$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/threading/TThread.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/threading_TThread$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/threading_TThread$(DependSuffix): library/threading/TThread.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/threading_TThread$(ObjectSuffix) -MF$(IntermediateDirectory)/threading_TThread$(DependSuffix) -MM "library/threading/TThread.cpp"

$(IntermediateDirectory)/threading_TThread$(PreprocessSuffix): library/threading/TThread.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/threading_TThread$(PreprocessSuffix) "library/threading/TThread.cpp"

$(IntermediateDirectory)/threading_TThreadPool$(ObjectSuffix): library/threading/TThreadPool.cpp $(IntermediateDirectory)/threading_TThreadPool$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/threading/TThreadPool.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/threading_TThreadPool$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/threading_TThreadPool$(DependSuffix): library/threading/TThreadPool.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/threading_TThreadPool$(ObjectSuffix) -MF$(IntermediateDirectory)/threading_TThreadPool$(DependSuffix) -MM "library/threading/TThreadPool.cpp"

$(IntermediateDirectory)/threading_TThreadPool$(PreprocessSuffix): library/threading/TThreadPool.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/threading_TThreadPool$(PreprocessSuffix) "library/threading/TThreadPool.cpp"

$(IntermediateDirectory)/timing_highperf$(ObjectSuffix): library/timing/highperf.cpp $(IntermediateDirectory)/timing_highperf$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/timing/highperf.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/timing_highperf$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/timing_highperf$(DependSuffix): library/timing/highperf.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/timing_highperf$(ObjectSuffix) -MF$(IntermediateDirectory)/timing_highperf$(DependSuffix) -MM "library/timing/highperf.cpp"

$(IntermediateDirectory)/timing_highperf$(PreprocessSuffix): library/timing/highperf.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/timing_highperf$(PreprocessSuffix) "library/timing/highperf.cpp"

$(IntermediateDirectory)/timing_timer$(ObjectSuffix): library/timing/timer.cpp $(IntermediateDirectory)/timing_timer$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/timing/timer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/timing_timer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/timing_timer$(DependSuffix): library/timing/timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/timing_timer$(ObjectSuffix) -MF$(IntermediateDirectory)/timing_timer$(DependSuffix) -MM "library/timing/timer.cpp"

$(IntermediateDirectory)/timing_timer$(PreprocessSuffix): library/timing/timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/timing_timer$(PreprocessSuffix) "library/timing/timer.cpp"

$(IntermediateDirectory)/voxels_voxelizer$(ObjectSuffix): library/voxels/voxelizer.cpp $(IntermediateDirectory)/voxels_voxelizer$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/voxels/voxelizer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/voxels_voxelizer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/voxels_voxelizer$(DependSuffix): library/voxels/voxelizer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/voxels_voxelizer$(ObjectSuffix) -MF$(IntermediateDirectory)/voxels_voxelizer$(DependSuffix) -MM "library/voxels/voxelizer.cpp"

$(IntermediateDirectory)/voxels_voxelizer$(PreprocessSuffix): library/voxels/voxelizer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/voxels_voxelizer$(PreprocessSuffix) "library/voxels/voxelizer.cpp"

$(IntermediateDirectory)/voxels_voxelmodel$(ObjectSuffix): library/voxels/voxelmodel.cpp $(IntermediateDirectory)/voxels_voxelmodel$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Git/library/library/voxels/voxelmodel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/voxels_voxelmodel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/voxels_voxelmodel$(DependSuffix): library/voxels/voxelmodel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/voxels_voxelmodel$(ObjectSuffix) -MF$(IntermediateDirectory)/voxels_voxelmodel$(DependSuffix) -MM "library/voxels/voxelmodel.cpp"

$(IntermediateDirectory)/voxels_voxelmodel$(PreprocessSuffix): library/voxels/voxelmodel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/voxels_voxelmodel$(PreprocessSuffix) "library/voxels/voxelmodel.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/library_config$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/library_config$(DependSuffix)
	$(RM) $(IntermediateDirectory)/library_config$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/library_log$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/library_log$(DependSuffix)
	$(RM) $(IntermediateDirectory)/library_log$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/library_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/library_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/library_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/library.rc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_bitmap$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_bitmap$(DependSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_bitmap$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_colortools$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_colortools$(DependSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_colortools$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_lodepng$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_lodepng$(DependSuffix)
	$(RM) $(IntermediateDirectory)/bitmap_lodepng$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/compression_lzo$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/compression_lzo$(DependSuffix)
	$(RM) $(IntermediateDirectory)/compression_lzo$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_baseconv$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_baseconv$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_baseconv$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_frustum$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_frustum$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_frustum$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_matrix$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_matrix$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_matrix$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_quaternion$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_quaternion$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_quaternion$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_vec3$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_vec3$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_vec3$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_vec4$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_vec4$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_vec4$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_vector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_vector$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_vector$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_voronoi$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_voronoi$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_voronoi$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/network_hostaddr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/network_hostaddr$(DependSuffix)
	$(RM) $(IntermediateDirectory)/network_hostaddr$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/network_socket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/network_socket$(DependSuffix)
	$(RM) $(IntermediateDirectory)/network_socket$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/network_tcpsocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/network_tcpsocket$(DependSuffix)
	$(RM) $(IntermediateDirectory)/network_tcpsocket$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_cosnoise$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_cosnoise$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_cosnoise$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_gabor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_gabor$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_gabor$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_multifractal$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_multifractal$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_multifractal$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_noise1234$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_noise1234$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_noise1234$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_sdnoise1234$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_sdnoise1234$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_sdnoise1234$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_simplex1234$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_simplex1234$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_simplex1234$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_srdnoise23$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_srdnoise23$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_srdnoise23$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_torusnoise$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_torusnoise$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_torusnoise$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_turbulence$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_turbulence$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_turbulence$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/noise_worley$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/noise_worley$(DependSuffix)
	$(RM) $(IntermediateDirectory)/noise_worley$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_camera$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_camera$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_camera$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_fbo$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_fbo$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_fbo$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_input$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_input$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_input$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_oglfont$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_oglfont$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_oglfont$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_oglfont_shader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_oglfont_shader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_oglfont_shader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_opengl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_opengl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_opengl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_openglext$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_openglext$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_openglext$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_shader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_shader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_shader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_texture$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_texture$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_texture$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_vao$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_vao$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_vao$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/opengl_window$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/opengl_window$(DependSuffix)
	$(RM) $(IntermediateDirectory)/opengl_window$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/script_script$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/script_script$(DependSuffix)
	$(RM) $(IntermediateDirectory)/script_script$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sound_sound$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sound_sound$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sound_sound$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sound_soundsystem$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sound_soundsystem$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sound_soundsystem$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sound_stream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sound_stream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sound_stream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sound_stream_channel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sound_stream_channel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sound_stream_channel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/storage_bitarray$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/storage_bitarray$(DependSuffix)
	$(RM) $(IntermediateDirectory)/storage_bitarray$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/threading_TThread$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/threading_TThread$(DependSuffix)
	$(RM) $(IntermediateDirectory)/threading_TThread$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/threading_TThreadPool$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/threading_TThreadPool$(DependSuffix)
	$(RM) $(IntermediateDirectory)/threading_TThreadPool$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/timing_highperf$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/timing_highperf$(DependSuffix)
	$(RM) $(IntermediateDirectory)/timing_highperf$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/timing_timer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/timing_timer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/timing_timer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/voxels_voxelizer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/voxels_voxelizer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/voxels_voxelizer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/voxels_voxelmodel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/voxels_voxelmodel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/voxels_voxelmodel$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) ".build-debug/library"


