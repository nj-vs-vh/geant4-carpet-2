# run dump_to_text for every file in DATA_DIR and save output to OUT_DIR

DATA_DIR=~/corsika-showers/proton-primary-selection
OUT_DIR=~/corsika-showers/proton-primary-selection-tsv-dump/


mkdir -p ${OUT_DIR}
ls ${DATA_DIR} | xargs --max-lines=1 -I{} ./dump_to_text ${DATA_DIR}/{} ${OUT_DIR}