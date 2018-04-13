INC_DIR += $(call select_from_repositories,src/lib/libjavacore)

OPT_CC += -DU_USING_ICU_NAMESPACE=0
