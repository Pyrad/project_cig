SRC_DIR	:=	src
OBJ_DIR	:=	objs
BIN_DIR	:=	bin

TAREGT_BIN	:=	run-g
TAREGT_BIN_LINK_NAME	:=	$(TAREGT_BIN)

FTYPE	:=	.cpp

BOOST_INC	:=	<__BOOST_INC_TO_FILL__>
BOOST_LIB	:=	<__BOOST_LIB_TO_FILL__>
BOOST_LNK	:=	boost_regex boost_filesystem

CXX	:=	<__CXX_TO_FILL>

mkf_name	:=	$(lastword $(MAKEFILE_LIST))
abs_path	:=	$(abspath $(mkf_name))
cdir		:=	$(dir $(abs_path))
cur_dir		:=	$(realpath $(cdir))
sdir		:=	$(cur_dir)/$(SRC_DIR)
odir		:=	$(cur_dir)/$(OBJ_DIR)
target		:=	$(cur_dir)/$(BIN_DIR)/$(TAREGT_BIN)
target_r	:=	$(BIN_DIR)/$(TAREGT_BIN)

all_srcs	:=	$(wildcard $(sdir)/*$(FTYPE))
all_srcs_relative	:=	$(foreach n,$(all_srcs),$(subst $(cur_dir),.,$n))
build_objs	:=	$(foreach n,$(all_srcs),$(subst $(sdir),$(odir),$n))
build_objs	:=	$(patsubst %$(FTYPE),%.o,$(build_objs))
build_objs	:=	$(foreach obj,$(build_objs),$(subst $(cur_dir),.,$(obj)))

LINK_LIBS	:=	$(foreach n,$(BOOST_LNK),$(subst $n,-l$n,$n))

OPT_OPTN	:=	-O2
DEBUG_OPTN	:=	-g
WARN_OPTN	:=	-Wall
MSG_OPTN	:=	-fmessage-length=0
NO_LINK		:=	-c

BUILD_OPTIONS	:=	$(OPT_OPTN) $(DEBUG_OPTN) $(WARN_OPTN) $(MSG_OPTN) $(NO_LINK)

all	: $(build_objs)
	@echo "linked"
	@if [[ -f $(target) ]]; then echo "$(target) exists"; rm -rf $(target); fi
	@if [[ -L $(TAREGT_BIN) ]]; then echo "./$(TAREGT_BIN) exists"; rm -rf $(TAREGT_BIN); fi
	$(CXX) -std=c++11 -L$(BOOST_LIB) -o $(target) $^ $(LINK_LIBS)
	@echo "Create link to $(target)"
	@ln -s $(target_r) $(TAREGT_BIN)

./$(OBJ_DIR)/%.o : ./$(SRC_DIR)/%.cpp
	@echo "Building (no linking)"
	@#$(CXX) -std=c++11 $(BUILD_OPTIONS) -I$(BOOST_INC) $< -o $@
	g++ -I$(BOOST_INC) $(BUILD_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

one	:
	@# This will build all sources and link them all in one step
	@if [[ -f $(target) ]]; then echo "$(target) exists"; rm -rf $(target); fi
	@if [[ -L $(TAREGT_BIN) ]]; then echo "./$(TAREGT_BIN) exists"; rm -rf $(TAREGT_BIN); fi
	g++ -std=c++11 $(all_srcs_relative) -o $(target) -L$(BOOST_LIB) -I$(BOOST_INC) $(LINK_LIBS)
	@echo "Create link to $(target)"
	@ln -s $(target_r) $(TAREGT_BIN)

linktest	: $(build_objs)
	/usr/bin/g++ -std=c++11 $(build_objs) \
            -L/home/pyrad/procs/boost_1_73_0/lib \
            -o /home/pyrad/worksrc/github/project_cig/bin/run-g \
            -lboost_filesystem

info:
	@echo "build_objs: $(build_objs)"
	@echo "Linked libs:" $(LINK_LIBS)
	@echo "all_srcs_relative:" $(all_srcs_relative)


.PHONY	:	clean
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(TAREGT_BIN)
