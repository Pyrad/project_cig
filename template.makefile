SRC_DIR	:=	src
OBJ_DIR	:=	objs
BIN_DIR	:=	bin

TAREGT_BIN	:=	run-g
TAREGT_BIN_LINK_NAME	:=	$(TAREGT_BIN)

FTYPE	:=	.cpp

BOOST_INC	:=	<__BOOST_INC_TO_FILL__>
BOOST_LIB	:=	<__BOOST_LIB_TO_FILL__>
BOOST_LNK	:=	boost_regex

CXX	:=	<__CXX_TO_FILL>

mkf_name	:=	$(lastword $(MAKEFILE_LIST))
abs_path	:=	$(abspath $(mkf_name))
cdir		:=	$(dir $(abs_path))
cur_dir		:=	$(realpath $(cdir))
sdir		:=	$(cur_dir)/$(SRC_DIR)
odir		:=	$(cur_dir)/$(OBJ_DIR)
target		:=	$(cur_dir)/$(BIN_DIR)/$(TAREGT_BIN)

all_srcs	:=	$(wildcard $(sdir)/*$(FTYPE))
build_objs	:=	$(foreach n,$(all_srcs),$(subst $(sdir),$(odir),$n))
build_objs	:=	$(patsubst %$(FTYPE),%.o,$(build_objs))

OPT_OPTN	:=	-O2
DEBUG_OPTN	:=	-g
WARN_OPTN	:=	-Wall
MSG_OPTN	:=	-fmessage-length=0
NO_LINK		:=	-c

BUILD_OPTIONS	:=	$(OPT_OPTN) $(DEBUG_OPTN) $(WARN_OPTN) $(MSG_OPTN) $(NO_LINK)

all	: $(build_objs)
	@echo "linked"
	$(CXX) -L$(BOOST_LIB) -l$(BOOST_LNK) $^ -o $(target)
	@echo "Create link to $(target)"
	@ln -s $(target) $(TAREGT_BIN)

$(cur_dir)/$(OBJ_DIR)/%.o : $(cur_dir)/$(SRC_DIR)/%.cpp
	@echo "Building (no linking)"
	$(CXX) $(BUILD_OPTIONS) -I$(BOOST_INC) $< -o $@

.PHONY	:	clean
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(TAREGT_BIN)
