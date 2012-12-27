#include <wand/MagickWand.h>

int main(int argc, char* argv[]) {
	MagickWand *mw = NULL;
	DrawingWand *dw = NULL;
	PixelWand *fill = NULL;
	int x,y;

	MagickWandGenesis();
	mw = NewMagickWand();
	MagickReadImage(mw,"logo:");

	fill = NewPixelWand();
	dw = NewDrawingWand();
	PixelSetColor(fill,"green");
	DrawSetFillColor(dw,fill);
	for (x=200;x<210;x++)
		for (y=100;y<110;y++)
			DrawPoint(dw,x,y);
	

	MagickDrawImage(mw,dw);


	MagickWriteImage(mw,"logo.jpg");

	if (dw) dw = DestroyDrawingWand(dw);
	if (fill) fill = DestroyPixelWand(fill);
	if (mw) mw = DestroyMagickWand(mw);
	MagickWandTerminus();
}
