.PHONY : all hax screen_init stage2 loader clean

TARGET		=	arm9loaderhax
PYTHON 		=	python
INDIR		=	data_input
OUTDIR		=	data_output

all : $(OUTDIR) hax

hax : $(OUTDIR) screen_init stage2 loader

$(OUTDIR):
	@[ -d $(OUTDIR) ] || mkdir -p $(OUTDIR)

screen_init:
	@[ -d payload_stage2/data ] || mkdir -p payload_stage2/data
	$(MAKE) -C screen_init
	@cp screen_init/screen_init.bin payload_stage2/data/

stage2:
	@[ -d loader/data ] || mkdir -p loader/data
	@$(MAKE) -C payload_stage2
	@cp payload_stage2/payload_stage2.bin loader/data/

loader:
	@$(MAKE) -C loader
	@cp loader/loader.bin $(OUTDIR)/arm9loaderhax.bin

clean:
	@echo clean...
	@$(MAKE) -C screen_init clean
	@$(MAKE) -C payload_stage2 clean
	@$(MAKE) -C loader clean
	rm -rf data_output
