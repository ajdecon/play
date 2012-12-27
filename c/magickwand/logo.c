#include <wand/MagickWand.h>

int main(int argc, char* argv[]) {
	MagickWand *mw = NULL;
	MagickWandGenesis();

	mw = NewMagickWand();
	MagickReadImage(mw,"logo:");
	MagickWriteImage(mw,"logo.jpg");
	if (mw) {
		mw = DestroyMagickWand(mw);
	}
	MagickWandTerminus();
}
